#include "paths.h"
#include "terminal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *find_home() {
  char *env = getenv("HOME");
  if (env)
    return env;
  printf("%sWarning: HOME not set%s\n", terminal_orange(), terminal_default());
  return strdup("/");
}

char *get_cwd() {
  char *cwd = malloc(1024);
  getcwd(cwd, 1024);
  return cwd;
}
