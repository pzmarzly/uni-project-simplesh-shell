#include "split_into_words.tests.h"
#include "split_into_words.h"
#include <assert.h>
#include <data_types/vector.h>

void split_into_words_tests() {
  vector x1 = split_into_words("");
  assert(vector_size(x1) == 0);

  vector x2 = split_into_words(" ");
  assert(vector_size(x2) == 0);

  vector x3 = split_into_words("make test");
  assert(vector_size(x3) == 4);
  assert(vector_get(x3, 0) == 0);
  assert(vector_get(x3, 1) == 3);
  assert(vector_get(x3, 2) == 5);
  assert(vector_get(x3, 3) == 8);

  vector x4 = split_into_words(" make test");
  assert(vector_size(x4) == 4);
  assert(vector_get(x4, 0) == 1);
  assert(vector_get(x4, 1) == 4);
  assert(vector_get(x4, 2) == 6);
  assert(vector_get(x4, 3) == 9);

  vector x5 = split_into_words("make test ");
  assert(vector_size(x5) == 4);
  assert(vector_get(x5, 0) == 0);
  assert(vector_get(x5, 1) == 3);
  assert(vector_get(x5, 2) == 5);
  assert(vector_get(x5, 3) == 8);

  vector x6 = split_into_words(" make  test ");
  assert(vector_size(x6) == 4);
  assert(vector_get(x6, 0) == 1);
  assert(vector_get(x6, 1) == 4);
  assert(vector_get(x6, 2) == 7);
  assert(vector_get(x6, 3) == 10);

  vector x7 = split_into_words(" \"make test\" ");
  assert(vector_size(x7) == 2);
  assert(vector_get(x7, 0) == 2);
  assert(vector_get(x7, 1) == 10);

  vector x8 = split_into_words(" \"make test ");
  assert(vector_get(x8, 0) == 1);
}
