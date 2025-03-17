#include "stdio.h"
#include "stdlib.h"
#include <stdint.h>


void die(const char *message, int exit_code) {
  // Print the message
  fprintf(stderr, "Error: %s\n", message);

  // Exit the program with the given exit code
  exit(exit_code);
}


void bytes_to_hex_string(uint8_t *bytes, size_t length, char *hex_string) {
    // Format the bytes as a hex string
    for (size_t i = 0; i < length; ++i) {
        // Each byte is represented by two hex characters
        sprintf(hex_string + (i * 2), "%02X", bytes[i]);
    }
    hex_string[length * 2] = '\0'; // Null-terminate the string
}