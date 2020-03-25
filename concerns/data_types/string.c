#include "string.h"
#include "vector.h"
#include <string.h>

struct string {
  vector chars;
};

string string_new() {
  string v = malloc(sizeof(string));
  v->chars = vector_new();
  return v;
}

size_t string_size(string v) { return vector_size(v->chars); }

void string_free(string v) {
  vector_free(v->chars);
  free(v);
}

char *string_to_cstr(string v) {
  size_t size = vector_size(v->chars);
  char *ret = malloc(size + 1);
  memcpy(ret, vector_memory(v->chars), size);
  ret[size] = '\0';
  return ret;
}

string string_from_cstr(char *cstr) {
  size_t len = strlen(cstr);
  string ret = string_new();
  memcpy(vector_memory(ret->chars), cstr, len);
  return ret;
}
