#include <stdlib.h>

typedef void* any_t;
typedef struct vector* vector;

vector vector_new();
size_t vector_size(vector v);
void vector_push(vector v, any_t el);
any_t *vector_el(vector v, unsigned index);
void vector_free(vector v);
