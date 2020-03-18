#include "string.h"

struct string {
  vector storage;
};

string string_new() {
  string v = malloc(sizeof(string));
  v->storage = vector_new();
  return v;
}

size_t string_size(string v) { return vector_size(v->storage); }

void string_free(string v) {
  vector_free(v->storage);
  free(v);
}
