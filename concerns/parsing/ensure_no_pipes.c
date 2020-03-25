#include "ensure_no_pipes.h"
#include <stdio.h>

static bool has_pipes(string line, vector words) {
  // TODO: implement.
  (void)line;
  (void)words;
  return false;
}

bool ensure_no_pipes(string line, vector words) {
  if (has_pipes(line, words)) {
    printf("Error: simplesh does not support output piping.\n");
    return false;
  }
  return true;
}
