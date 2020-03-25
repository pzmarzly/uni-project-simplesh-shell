#include "vector.h"
#include <string.h>

struct vector {
  any_t *raw;
  size_t used;
  size_t capacity;
};

#define U sizeof(any_t)

vector vector_new() {
  vector v = malloc(sizeof(struct vector));
  v->raw = malloc(8 * U);
  v->used = 0;
  v->capacity = 8;
  return v;
}

size_t vector_size(vector v) { return v->used; }

vector vector_clone(vector v) {
  vector v2 = malloc(sizeof(struct vector));
  v2->raw = malloc(v->capacity * U);
  v2->used = v->used;
  v2->capacity = v->capacity;
  memcpy(v2->raw, v->raw, v->capacity * U);
  return v2;
}

static void resize(vector v) {
  v->raw = realloc(v->raw, v->capacity * 2 * U);
  v->capacity *= 2;
}

void vector_push(vector v, any_t el) { vector_set(v, vector_size(v), el); }

void vector_set(vector v, unsigned index, any_t el) {
  if (index >= v->capacity)
    resize(v);
  v->raw[index] = el;
  if (index >= v->used)
    v->used = index + 1;
}

any_t vector_get(vector v, unsigned index) { return v->raw[index]; }

void vector_delete(vector v, unsigned index) {
  vector_delete_range(v, index, index);
}

void vector_delete_range(vector v, unsigned start, unsigned end) {
  unsigned diff = end - start + 1;
  unsigned size = v->capacity;
  // shift left
  for (unsigned idx = start; idx < size; idx++) {
    if (idx + diff < v->used) {
      v->raw[idx] = v->raw[idx + diff];
    }
  }
  v->used -= diff;
}

void vector_insert_empty_range(vector v, unsigned start, unsigned len) {
  unsigned end = v->used - 1;
  if (end + len >= v->capacity)
    resize(v);
  // shift right
  for (unsigned idx = end; idx > start + len; idx--) {
    v->raw[idx] = v->raw[idx - len];
  }
}

any_t *vector_memory(vector v) { return v->raw; }

void vector_free(vector v) {
  free(v->raw);
  free(v);
}
