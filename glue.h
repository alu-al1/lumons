#ifndef GLUE_H
#define GLUE_H

#include "lib/libddcutil/include/ddcutil_c_api.h"
#include "lib/libddcutil/include/ddcutil_status_codes.h"
#include "lib/libddcutil/include/ddcutil_types.h"

#include "common.h"

#define GLUE_MAX_BRLEV_DISPLAY_INFOS_DEFAULT 4

#ifndef GLUE_MAX_BRLEV_DISPLAY_INFOS
#define GLUE_MAX_BRLEV_DISPLAY_INFOS (GLUE_MAX_BRLEV_DISPLAY_INFOS_DEFAULT)
#endif

#define GLUE_MAX_BRLEV_DISPLAY_INFOS_S                                         \
  ((GLUE_MAX_BRLEV_DISPLAY_INFOS) != 0                                         \
       ? (GLUE_MAX_BRLEV_DISPLAY_INFOS)                                        \
       : (GLUE_MAX_BRLEV_DISPLAY_INFOS_DEFAULT))

typedef struct {
  int i;
  int active; // Status if display is
              // active
  DDCA_IO_Path dev;
  DDCA_Display_Ref *display_ref; // Pointer to
                                 // DDCA_Display_Ref
} BRLEV_DisplayInfo;

BRLEV_Result get_basic_displays_info();

#endif // GLUE_H
