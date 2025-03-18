#ifndef CORE_H
#define CORE_H

#include "lib/libddcutil/include/ddcutil_c_api.h"
#include "lib/libddcutil/include/ddcutil_status_codes.h"
#include "lib/libddcutil/include/ddcutil_types.h"



void mon_init();
void mon_cleanup();
// void load_ddcutil();
// void unload_ddcutil_s();



//interface-like
// typedef DisplayData** (*i_get_displays_data_fp) ();

#endif // CORE_H
