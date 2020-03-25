#include "split_into_words.h"
#include <stdbool.h>
#include <string.h>

static char *eat_until(char *s, char delim1, char delim2) {
  while (*s && *s != delim1 && *s != delim2) {
    if (*s == '\\') {
      if (*(s + 1))
        s++;
      s++;
    } else if (*s == '\'') {
      s = eat_until(s + 1, '\'', '\0');
      if (*s) s++;
    } else if (*s == '\"') {
      s = eat_until(s + 1, '\"', '\0');
      if (*s) s++;
    } else {
      s++;
    }
  }
  // Now s either s[0] == '\0' or s[0] == delim.
  return s;
}

static void add(vector v, char *a, char *b, char *base) {
  if (b - a > 0) {
    vector_push(v, (any_t) (a - base));
    vector_push(v, (any_t) (b - 1 - base));
  }
}

vector split_into_words(string l) {
  char *base = string_to_cstr(l);
  vector ret = vector_new();
  char *start = base;
  while (true) {
    char *end = eat_until(start, ' ', '\t');
    if (*end) {
      add(ret, start, end, base);
      start = end + 1;
    } else {
      add(ret, start, start + strlen(start), base);
      break;
    }
  }
  free(base);
  return ret;
}
