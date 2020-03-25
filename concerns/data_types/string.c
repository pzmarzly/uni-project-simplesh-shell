#include "string.h"
#include "vector.h"
#include <string.h>

struct string {
  vector chars;
};

string string_new() {
  string v = malloc(sizeof(struct string));
  v->chars = vector_new();
  return v;
}

size_t string_length(string v) { return vector_size(v->chars); }

void string_free(string v) {
  vector_free(v->chars);
  free(v);
}

char *string_to_cstr(string v) {
  size_t size = vector_size(v->chars);
  char *ret = malloc(size + 1);
  for (size_t idx = 0; idx < size; idx++)
    ret[idx] = (char)vector_get(v->chars, idx);
  ret[size] = '\0';
  return ret;
}

string string_from_cstr(char *cstr) {
  string ret = string_new();
  while (*cstr)
    vector_push(ret->chars, (any_t) * (cstr++));
  return ret;
}
