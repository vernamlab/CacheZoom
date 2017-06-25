
#include "Enclave.h"
#include "Enclave_t.h"

#define CPU_L1_CACHE_SET_COUNT   64
#define CPU_L1_CACHE_SET_ASSOC   8
#define CPU_L1_LINE_OFFSET_WORD  0b1000000000000

#define idx(_line, _set) ( ((CPU_L1_LINE_OFFSET_WORD) * (_line)) / 8 + (((CPU_L1_CACHE_SET_ASSOC) * (_set))))
#define idx0(_set) ((((CPU_L1_CACHE_SET_ASSOC) * (_set))))

#define DATA_SIZE 0x10000


long do_something_secret(void)
{
  unsigned long secret_data[DATA_SIZE];
  unsigned int x = 0;
  unsigned long * ptr = secret_data;

  for(int i=0; i < 5000; i++)
  {
    x &= *(ptr + idx0(i%64));
    asm volatile("lfence;");
  }
}