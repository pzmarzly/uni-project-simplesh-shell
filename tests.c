#define HOLDS_STATE

#include <state/state.h>
#include <stdlib.h>
#include <stdio.h>

#include <data_types/string.tests.h>
#include <parsing/split_into_words.tests.h>

int main() {
  init_state();

  string_tests();
  split_into_words_tests();

  printf("OK\n");
  return 0;
}
