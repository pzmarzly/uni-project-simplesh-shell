#include "ensure_complete.h"
#include <stdio.h>

static bool is_complete(string l) {
  (void)l;
  // TODO: implement.
  return true;
}

bool ensure_complete(string l) {
  if (!is_complete(l)) {
    printf("Error: simplesh does not support commands spanning over multiple lines.\n");
    return false;
  }
  return true;
}
