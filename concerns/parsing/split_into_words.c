#include "split_into_words.h"
#include <stdbool.h>
#include <string.h>

static char *eat_until(char *s, char delim) {
  while (*s && *s != delim) {
    if (*s == '\\') {
      if (*(s + 1))
        s++;
      s++;
    } else if (*s == '\'') {
      s = eat_until(s, '\'');
    } else if (*s == '\"') {
      s = eat_until(s, '\"');
    } else {
      s++;
    }
  }
  // Now s either s[0] == '\0' or s[0] == delim.
  return s;
}

static void trim(char **s) {
  // Trim left.
  while (*s && **s == ' ')
    (*s)++;
  // Trim right.
  // TODO: implement.
}

vector split_into_words(string l) {
  char *start = string_to_cstr(l);
  trim(&start);
  vector ret = vector_new();
  while (true) {
    char *end = eat_until(start, ' ');
    if (end) {
      vector_push(ret, (any_t) start);
      vector_push(ret, (any_t) end - 1);
      start = end + 1;
    } else {
      vector_push(ret, (any_t) start);
      vector_push(ret, (any_t) start + strlen(start));
      return ret;
    }
  }
}
