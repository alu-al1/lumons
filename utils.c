#include "stdio.h"
#include "stdlib.h"

void die(const char *message, int exit_code) {
  // Print the message
  fprintf(stderr, "Error: %s\n", message);

  // Exit the program with the given exit code
  exit(exit_code);
}
