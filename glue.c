#include "stdio.h"
#include <stdlib.h>

#include "common.h"
#include "glue.h"
#include "utils.h"

DDCA_Display_Info_List *infos;
DDCA_Capabilities *caps;

void glue_basic_display_info_cleanup() {
  if (infos != NULL)
    ddca_free_display_info_list(infos);
  if (caps != NULL)
    free(caps);
}

BRLEV_Result get_basic_displays_info() {
  BRLEV_Result res = {0};
  infos = NULL; // TODO who should free it?
  caps = malloc(sizeof(DDCA_Capabilities));

  if (caps == NULL) {
    printf("buy more RAM for %s %s\n", "DDCA_Capabilities", "caps");
    goto resolve;
  }

  {
    DDCA_Status code = ddca_get_display_info_list2(1, &infos);
    if (code != DDCRC_OK) {
      printf(
          "[EE] [glue] ddca_get_display_info_list2(...) failed with code %d\n",
          (int)code);
      goto resolve;
    }
    if (infos == NULL) {
      printf("[EE] [glue] ddca_get_display_info_list2(...) res is still "
             "nullptr even the lib returned code %d\n",
             (int)code);
      goto resolve;
    }
  }

  for (typeof(infos->ct) i = 0; i < infos->ct; ++i) {
    if (infos->info[i].dref == NULL) {
      printf("skipping display as it has no dref: %d\n", infos->info[i].dispno);
      continue;
    }

    {
      if (res.resp == NULL) {
        res.resp = (void *)malloc(sizeof(BRLEV_DisplayInfo *) * (int)infos->ct);

        if (res.resp == NULL) {
          printf("[EE] [glue] failed to allocate resp with %d slots",
                 (int)infos->ct);
          goto resolve;
        }
      }
    }

    ((BRLEV_DisplayInfo **)res.resp)[res.cnt] =
        malloc(sizeof(BRLEV_DisplayInfo));
    if (((BRLEV_DisplayInfo **)res.resp)[res.cnt] == NULL) {
      printf("Memory allocation failed for display info %d!\n", i);
      goto resolve;
    }
    ((BRLEV_DisplayInfo **)res.resp)[res.cnt]->i = i;
    ((BRLEV_DisplayInfo **)res.resp)[res.cnt]->dev = infos->info[i].path;
    ((BRLEV_DisplayInfo **)res.resp)[res.cnt]->display_ref =
        infos->info[i].dref;
    ((BRLEV_DisplayInfo **)res.resp)[res.cnt]->active = 1; // TODO

    printf("+");
    ++res.cnt;
  }
    printf("\n");
    
  res.ok = 1;

resolve:
  glue_basic_display_info_cleanup();
  res.is_owner = 1;
  return res;
}
