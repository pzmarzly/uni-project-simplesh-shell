#include "find_exe.h"
#include <state/terminal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

char *find_exe(char *command) {
  size_t s_command = strlen(command);

  char *dirs = getenv("PATH");
  if (!dirs) {
    printf("%sWarning: PATH not set%s\n", terminal_orange(),
           terminal_default());
    return NULL;
  }
  // strtok is destructive.
  dirs = strdup(dirs);

  char *dir = strtok(dirs, ":");
  while (dir != NULL) {
    // We need executable permissions
    // to access files in the directory.
    if (access(dir, X_OK) != 0)
      continue;

    size_t s_dir = strlen(dir);
    char *path = malloc(s_dir + s_command + 2);
    memcpy(path, dir, s_dir);
    path[s_dir] = '/';
    memcpy(path + s_dir + 1, command, s_command);
    path[s_dir + 1 + s_command] = '\0';

    if (access(path, X_OK) == 0) {
      free(dirs);
      return path;
    }
    free(path);

    dir = strtok(NULL, ":");
  }

  free(dirs);
  return NULL;
}
