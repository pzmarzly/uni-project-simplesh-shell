#include "string.tests.h"
#include "string.h"
#include <string.h>
#include <assert.h>

void string_tests() {
  string s = string_from_cstr("Test");
  assert(string_length(s) == 4);
  char *x = string_to_cstr(s);
  assert(strlen(x) == 4);

  string_free(s);
  free(x);
}
