#include "stdio.h"
#include <stdlib.h>

#include "core.h"
#include "utils.h"

#include "glue.h"

void mon_init() {
  BRLEV_Result res = get_basic_displays_info();
  printf("get_basic_displays_info() ok?: %d\n", res.ok);

  if (res.ok) {
    printf("found mons: %d\n", res.cnt);
  }

  if (res.is_owner && res.resp != NULL) {
    for (size_t i = 0; i < res.cnt; ++i) {
      if (res.resp[i] != NULL)
        free(res.resp[i]);
    }
    res.resp = NULL;
  }
  
}