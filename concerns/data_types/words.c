#include "words.h"
#include "string.h"
#include "vector.h"

char *first_word(words words, char *line) {
  size_t a = (size_t)vector_get(words, 0);
  size_t b = (size_t)vector_get(words, 1);
  char *s = strdup(line);
  s[b + 1] = '\0';
  return s + a;
}

void delete_first_word(words words) { vector_delete_range(words, 0, 1); }
