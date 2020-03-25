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
      s = eat_until(s + 1, '\'', '\0') + 1;
    } else if (*s == '\"') {
      s = eat_until(s + 1, '\"', '\0') + 1;
    } else {
      s++;
    }
  }
  // Now s either s[0] == '\0' or s[0] == delim.
  return s;
}

static void trim(char **s) {
  // Trim left.
  while (**s == ' ')
    (*s)++;
  // Trim right.
  // TODO: implement.
}

static void add(vector v, char *a, char *b, char *s) {
  if (b - a > 0) {
    vector_push(v, (any_t) (a - s));
    vector_push(v, (any_t) (b - 1 - s));
  }
}

vector split_into_words(string l) {
  char *s = string_to_cstr(l);
  char *start = s;
  trim(&start);
  vector ret = vector_new();
  while (true) {
    char *end = eat_until(start, ' ', '\t');
    if (*end) {
      add(ret, start, end, s);
      start = end + 1;
    } else {
      add(ret, start, start + strlen(start), s);
      free(s);
      return ret;
    }
  }
}
