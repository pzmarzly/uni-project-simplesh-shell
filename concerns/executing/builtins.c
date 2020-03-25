#include "builtins.h"
#include <stdlib.h>
#include <state/paths.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
// Based on https://brennan.io/2015/01/16/write-a-shell-in-c/

static int b_cd(char **args)
{
  char *path = args[1];
  if (path == NULL)
    path = find_home();
  if (chdir(path) != 0) {
    perror("Cannot cd: ");
    return 1;
  }
  return 0;
}

static _Noreturn int b_exit(char **args) {
  // FIXME: exit with code.
  (void)args;
  exit(0);
}

char *builtins_str[] = {
  "cd",
  "exit"
};

int (*builtins_func[]) (char **) = {
  &b_cd,
  &b_exit
};

static unsigned builtins_count() {
  return sizeof(builtins_str) / sizeof(char *);
}

bool is_builtin(char *name) {
  for (unsigned i = 0; i < builtins_count(); i++) {
    if (strcmp(name, builtins_str[i]) == 0) {
      return true;
    }
  }
  return false;
}

int run_builtin(char *name, char **args) {
  for (unsigned i = 0; i < builtins_count(); i++) {
    if (strcmp(name, builtins_str[i]) == 0) {
      return (*builtins_func[i])(args);
    }
  }
  printf("Internal error: built-in command not found\n");
  return 1;
}
