#include "stdio.h"
#include <dlfcn.h>
//#include "stdlib.h"

#include "utils.h"

static void *ddcutil;

void load_ddcutil() {
  // TODO make a direct dlopen and handle it LD_LIBRARY_PATH
  ddcutil = dlopen("libs/libddcutil/libddcutil.so", RTLD_NOW); //RTLD_LAZY ?

  if (!ddcutil) {
    fprintf(stderr, "Error loading library: %s\n", dlerror());
  }
}
void unload_ddcutil_s() {
  if (ddcutil != NULL)
    dlclose(ddcutil);
}

void mon_init(){
    {
    load_ddcutil();
    if (ddcutil == NULL)
      die("failed to dynamically load ddcutil", 1);
  }
}