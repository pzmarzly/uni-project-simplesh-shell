#include "paths.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

char *find_home() {
  char *env = getenv("HOME");
  if (env)
    return env;
  printf("Warning: no HOME environment variable set.\n");
  return strdup("/");
}

char *get_cwd() {
  char *cwd = malloc(1024);
  getcwd(cwd, 1024);
  return cwd;
}
