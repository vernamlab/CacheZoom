#define _GNU_SOURCE

#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sched.h>
#include <sys/types.h>
#include <unistd.h>
#include "../cachezoom.h"


int main(int argc, char * argv[])
{

  if (argc < 2){
    printf("[X] No arguments provided!\n");
    return -1;
  }

  
  int _FD_;
  struct cachezoom_generic_param param;
  OPEN_CACHEZOOM_DRV();
   
  
  int sw = atoi(argv[1]);

  switch(sw)
  {
    case 0:
      if (argc < 6){
        printf("[X] Not enough arguments provided!\n");
        return 1;
      }
      INIT_CACHEZOOM(strtoull(argv[2], NULL, 16), strtoull(argv[3], NULL, 16), atoi(argv[4]), atoi(argv[5]));
      break;
    case 1:      
      INSTALL_TIMER();
      break;
    case 2:
      UNINSTALL_TIMER();
      break;
   case 3:
      TEST_CACHEZOOM();
      break;
    default:
      printf("Invalid switch.\n");
      return -1;
      break;
  }    
}
