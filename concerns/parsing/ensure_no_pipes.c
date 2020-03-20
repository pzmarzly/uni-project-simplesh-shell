#include "ensure_no_pipes.h"
#include <stdio.h>

static bool has_pipes(string l) {
  // TODO: implement.
  (void)l;
  return false;
}

bool ensure_no_pipes(string l) {
  if (has_pipes(l)) {
    printf("Error: simplesh does not support output piping.\n");
    return false;
  }
  return true;
}
