#ifndef CORE_H
#define CORE_H

#include "lib/libddcutil/include/ddcutil_c_api.h"
#include "lib/libddcutil/include/ddcutil_status_codes.h"
#include "lib/libddcutil/include/ddcutil_types.h"



void mon_init();
void mon_cleanup();
// void load_ddcutil();
// void unload_ddcutil_s();

typedef struct {
    DDCA_Display_Ref *display_ref;  // Pointer to DDCA_Display_Ref
    bool active;                   // Status if display is active
    bool available;                // Status if display is available
    void *id;                      // Pointer to some identifier or data related to display
} DisplayData;

//interface-like
typedef DisplayData** (*i_get_displays_data_fp) ();

#endif // CORE_H
