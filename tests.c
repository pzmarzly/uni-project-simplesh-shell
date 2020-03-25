#include <state/terminal.h>
#include <stdio.h>
#include <stdlib.h>

#include <data_types/string.tests.h>
#include <data_types/words.tests.h>
#include <parsing/split_into_words.tests.h>

int main() {
  string_tests();
  split_into_words_tests();
  words_tests();

  printf("%sOK%s\n", terminal_green(), terminal_default());
  return 0;
}
