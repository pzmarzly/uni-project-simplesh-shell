#include "vector.h"

struct vector {
  GArray *inner;
};

vector vector_new() {
  vector v = malloc(sizeof(vector));
  v->inner = g_array_new(false, false, sizeof(any_t));
  return v;
}

size_t vector_size(vector v) { return g_array_size(v->inner); }
void vector_push(vector v, any_t el) { g_array_append_val(v->inner, el); }
void vector_el(vector v, unsigned index) { return g_array_index(v, any_t, index); }

void vector_free(vector v) {
  g_array_free(v->inner, true);
  free(v);
}
