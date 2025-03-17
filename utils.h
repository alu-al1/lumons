#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include "stdio.h"

#define COUNT_OF(x)                                                            \
  ((sizeof(x) / sizeof(0 [x])) / ((size_t)(!(sizeof(x) % sizeof(0 [x])))))

static void *element;
#define foreach(array, code_block)                                             \
  for (size_t i = 0; (array)[i] != NULL; ++i) {                                \
    element = (array)[i];                                                      \
    code_block                                                                 \
  }


void bytes_to_hex_string(uint8_t *bytes, size_t length, char *hex_string);

void die(const char *message, int exit_code);

#endif // UTILS_H
