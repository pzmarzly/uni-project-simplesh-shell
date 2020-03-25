#pragma once
#include "vector.h"
#include "string.h"

typedef struct vector *words;
char *first_word(words words, string line);
void delete_first_word(words words);
