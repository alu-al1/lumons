#include "stdio.h" //TODO exclude if not used
#include "stdlib.h" //TODO exclude if not used

#include "ui.h"
#include "core.h"

inline static void init() {
  mon_init();
  ui_init();
}

inline static void  destroy() {
  mon_cleanup();
}

int main() {
  init();
  ui_render_loop();
  destroy();
  return 0;
}
