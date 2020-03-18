typedef void* any_t;

typedef struct kv* kv;

kv kv_new();
char* kv_get(kv k, char *key);
char** kv_get_all(kv k);
void kv_set(kv k, char *key, char *value);
void kv_override(kv k, kv with);
