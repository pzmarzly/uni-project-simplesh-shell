#pragma once
#include <stdlib.h>

typedef void* any_t;
typedef struct vector* vector;

vector vector_new();
size_t vector_size(vector v);
void vector_push(vector v, any_t el);
void vector_set(vector v, unsigned index, any_t el);
any_t vector_get(vector v, unsigned index);
void vector_delete(vector v, unsigned index);
void vector_delete_range(vector v, unsigned start, unsigned end);
void vector_insert_empty_range(vector v, unsigned start, unsigned len);
any_t *vector_memory(vector v);
void vector_free(vector v);
