#include "kernel/cachezoom_kernel.h"

#define OPEN_CACHEZOOM_DRV()({\
  do {\
    _FD_ = open("/dev/cachezoom", O_RDWR);\
    if (_FD_ == -1) {\
      printf("Couldn't open /dev/cachezoom\n");\
      return -1;\
    }\
    } while(0);\
})


#define INIT_CACHEZOOM(next_dead, timer_inter, interval, target)({\
  do {\
    param.param_0 = next_dead;\
    param.param_1 = timer_inter;\
    param.param_2 = interval;\
    param.param_3 = target;\
    if(ioctl(_FD_, CACHEZOOM_IOCTL_INIT, &param)) {\
      printf("IOCTL failed %d\n", errno);\
      return -1;\
    }\
  } while(0);\
})

#define INSTALL_TIMER()({\
  do {\  
    if(ioctl(_FD_, CACHEZOOM_IOCTL_INSTALL_TIMER, &param)) {\
      printf("IOCTL failed %d\n", errno);\
      return -1;\
    }\
  } while(0);\
})

#define UNINSTALL_TIMER()({\
  do {\
    if(ioctl(_FD_, CACHEZOOM_IOCTL_UNINSTALL_TIMER, &param)) {\
      printf("IOCTL failed %d\n", errno);\
      return -1;\
    }\
  } while(0);\
})


#define TEST_CACHEZOOM()({\
  do {\
    if(ioctl(_FD_, CACHEZOOM_IOCTL_TEST, &param)) {\
      printf("IOCTL failed %d\n", errno);\
      return -1;\
    }\
  } while(0);\
})
