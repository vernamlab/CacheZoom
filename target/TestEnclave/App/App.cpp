#define _GNU_SOURCE

#include <stdio.h>
#include <sched.h>
#include <string.h>
#include <assert.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

# define MAX_PATH FILENAME_MAX

#include "sgx_urts.h"
#include "App.h"
#include "Enclave_u.h"
#include "../../../cachezoom.h"

# define TOKEN_FILENAME   "enclave.token"
# define ENCLAVE_FILENAME "enclave.signed.so"

/* Global EID shared by multiple threads */
sgx_enclave_id_t global_eid = 0;

/* Application entry */
int SGX_CDECL main(int argc, char *argv[])
{
  int _FD_;

  int i;

  
  sgx_status_t ret = SGX_ERROR_UNEXPECTED;
  sgx_launch_token_t token = {0};
  int updated = 0;
  ret = sgx_create_enclave(ENCLAVE_FILENAME, SGX_DEBUG_FLAG, &token, &updated, &global_eid, NULL);
  if (ret != SGX_SUCCESS) {
      printf("sgx_create_enclave Error: %d\n", ret);
      return -1;
  }


  OPEN_CACHEZOOM_DRV();

  struct cachezoom_generic_param param;

  INSTALL_TIMER();  

  for(int i = 0; i < 2000000 ; i++);

  long x;
  
  ret = do_something_secret(global_eid, &x);

  for(int i = 0; i < 2000000 ; i++);

  UNINSTALL_TIMER();  


  if (ret != SGX_SUCCESS) {
      printf("Error: %d\n", ret);
      return -1;
  }
 
  /* Destroy the enclave */
  sgx_destroy_enclave(global_eid);
  if (ret != SGX_SUCCESS) {
      printf("Error: %d\n", ret);
      return -1;
  }

  printf("Info: Successfully returned.\n");
  return 0;
}
