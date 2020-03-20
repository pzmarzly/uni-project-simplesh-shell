#pragma once

typedef void* any_t;

typedef struct kv* kv;
typedef struct {
    char *name;
    char *value;
} kv_entry;

kv kv_new();
kv_entry kv_get(kv k, char *key);
kv_entry* kv_get_all(kv k);
void kv_set(kv k, char *key, char *value);
void kv_override(kv k, kv with);
