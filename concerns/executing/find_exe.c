#include "find_exe.h"
#include <unistd.h>
#include <string.h>
#include <stdio.h>

char *find_exe(string command) {
  char *s = string_to_cstr(command);
  size_t ss = strlen(s);

  // Check if a path was given.
  if (strchr(s, '/') != NULL)
    return s;

  char *dirs = getenv("PATH");
  if (!dirs) {
    printf("Warning: PATH not set\n");
    free(s);
    return NULL;
  }
  // strtok is destructive.
  dirs = strdup(dirs);

  char *dir = strtok(dirs, ":");
  while (dir != NULL) {
    // We need executable permissions
    // to access files in the directory.
    if (access(dir, X_OK) != 0) continue;

    size_t sdir = strlen(dir);
    char *path = malloc(sdir + ss + 2);
    memcpy(path, dir, sdir);
    path[sdir] = '/';
    memcpy(path + sdir + 1, s, ss);
    path[sdir + 1 + ss] = '\0';

    if (access(path, X_OK) == 0) {
      free(s);
      return path;
    }
    free(path);

    dir = strtok(NULL, ":");
  }

  free(s);
  return NULL;
}
