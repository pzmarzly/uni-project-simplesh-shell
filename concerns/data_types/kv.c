#include "kv.h"

#define BUCKETS 32
struct kv {
  vector buckets[BUCKETS];
};

kv kv_new() {
  kv v = malloc(sizeof(kv));
  v->storage = vector_new();
  return v;
}

size_t kv_size(kv v) { return vector_size(v->storage); }

void kv_free(kv v) {
  vector_free(v->storage);
  free(v);
}
