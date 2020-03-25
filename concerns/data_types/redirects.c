#include "redirects.h"
#include "string.h"
#include "vector.h"

char first_redirect_direction(redirects redirects) {
  return (char)vector_get(redirects, 0);
}

char *first_redirect_path(redirects redirects) {
  return (char *)vector_get(redirects, 1);
}

void delete_first_redirect(redirects redirects) {
  vector_delete_range(redirects, 0, 1);
}
