struct cachezoom_generic_param {
  unsigned long long param_0;
  unsigned long long param_1;
  unsigned long long param_2;
  unsigned long long param_3;
};


#define CACHEZOOM_IOCTL_UNINSTALL_TIMER _IOWR('p', 0x01, struct cachezoom_generic_param)
#define CACHEZOOM_IOCTL_INSTALL_TIMER   _IOWR('p', 0x02, struct cachezoom_generic_param)
#define CACHEZOOM_IOCTL_TEST            _IOWR('p', 0x03, struct cachezoom_generic_param)
#define CACHEZOOM_IOCTL_INIT   					_IOWR('p', 0x05, struct cachezoom_generic_param)
