#include "kv.h"
#include "vector.h"

#define BUCKETS 32
struct kv {
  vector buckets[BUCKETS];
};

kv kv_new() {
  kv v = malloc(sizeof(kv));
  for (size_t i = 0; i < BUCKETS; i++)
    v->buckets[i] = vector_new();
  return v;
}

void kv_free(kv v) {
  for (size_t i = 0; i < BUCKETS; i++)
    vector_free(v->buckets[i]);
  free(v);
}
