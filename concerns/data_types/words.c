#include "words.h"
#include "string.h"
#include "vector.h"

char *first_word(words words, char *line) {
  unsigned a = (unsigned)vector_get(words, 0);
  unsigned b = (unsigned)vector_get(words, 1);
  char *s = strdup(line + a);
  s[b - a + 1] = '\0';
  return s;
}

void delete_first_word(words words) { vector_delete_range(words, 0, 1); }
