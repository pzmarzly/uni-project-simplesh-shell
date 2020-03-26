#pragma once
#include "string.h"
#include "vector.h"

// redirects is a vector where each odd element
// is a character representing a direction (<, >, or 2),
// and every even element is a char* to a path.
typedef struct vector *redirects;
char first_redirect_direction(redirects redirects);
char *first_redirect_path(redirects redirects);
void delete_first_redirect(redirects redirects);
