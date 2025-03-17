#include "stdio.h"
#include <stdlib.h>

#include "core.h"
#include "utils.h"

char edid_hex_repr[256];
DDCA_Display_Info_List *infos;
DDCA_Capabilities *caps;

void mon_cleanup(){
  if (infos != NULL) ddca_free_display_info_list(infos);
  if (caps != NULL) free(caps);
}

int get_displays_data_impl() {
  infos = NULL;
  caps = malloc(sizeof(DDCA_Capabilities));

  if (caps == NULL) {
    printf("buy more RAM for %s %s\n", "DDCA_Capabilities", "caps");
    return 1;
  }
  //   s = ((DDCA_Status(*)(bool, DDCA_Display_Ref **))f)(0, &infos);
  // TODO get additional info on the error
  // TODO wrap int into iCoreError
  if (ddca_get_display_info_list2(1, &infos) != DDCRC_OK) {
    return 1;
  }
  // TODO mb? we may increase DDCA_EDID_MFG_ID_FIELD_SIZE to get mfg_id that
  // will be more reliable
  for (size_t i = 0; i < (size_t)infos->ct; ++i) {
    bytes_to_hex_string(infos->info[i].edid_bytes, 128, edid_hex_repr);
    printf("Found mon with edid (in hex): %s\n",edid_hex_repr);
    if (infos->info[i].dref == NULL) {
      printf("skipping display as it has no dref: %s\n", edid_hex_repr);
      continue;
    }
    // int code = thirdparty_report_parsed_caps_impl(caps, infos->info[i].dref, 1);
    // if (code != DDCRC_OK) {
    //   printf("skipping display as it errored on reporting parsed capabilities "
    //          "with code %d: "
    //          "%s\n",
    //          code, edid_hex_repr);
    //   continue;
    // }
    // for (int j = 0; j < caps->vcp_code_ct; ++j) {
    //   printf("mon code: %02X code: %02X first value: %02X\n",
    //          infos->info[i].product_code, caps->cmd_codes[j],
    //          caps->vcp_codes[j].value_ct != 0 ? caps->vcp_codes[j].values[0]
    //                                           : -1);
    // }
    // TODO ddca_report_parsed_capabilities_by_dref
  }

  free(caps);

  return 0;
}

void mon_init() {
  get_displays_data_impl();
}