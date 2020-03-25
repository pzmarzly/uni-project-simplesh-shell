#pragma once
#include "vector.h"
#include "string.h"

// words is a vector where each odd element
// is a starting index and each even element
// in a corresponding ending one.
typedef struct vector *words;
char *first_word(words words, string line);
void delete_first_word(words words);
