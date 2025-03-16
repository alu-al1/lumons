#include "stdio.h"
#include "stdlib.h"

// TODO make a direct include and handle it in linking
#include "libs/libddcutil/include/ddcutil_c_api.h"

#include "ui.h"
#include "core.h"

inline static void init() {
  mon_init();
  ui_init();
}

inline static void  destroy() { unload_ddcutil_s(); }

int main() {
  init();
  ui_render_loop();
  destroy();
  return 0;
}
