#define HOLDS_STATE

#include <state/state.h>
#include <stdlib.h>

#include <data_types/string.tests.h>

int main() {
  init_state();

  string_tests();

  return 0;
}
