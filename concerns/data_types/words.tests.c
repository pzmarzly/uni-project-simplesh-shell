#include "words.tests.h"
#include "words.h"
#include <assert.h>
#include <parsing/split_into_words.h>
#include <string.h>

void words_tests() {
  string line = string_from_cstr("  make  test");
  vector words = split_into_words(line);

  assert(strcmp(first_word(words, line), "make") == 0);
  delete_first_word(words);
  assert(vector_size(words) == 2);

  assert(strcmp(first_word(words, line), "test") == 0);
  delete_first_word(words);
  assert(vector_size(words) == 0);
}
