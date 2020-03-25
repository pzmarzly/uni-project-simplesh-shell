#include "run_exe.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
// Based on https://brennan.io/2015/01/16/write-a-shell-in-c/

int run_exe(char *name, char **args) {
  int status;

  pid_t pid = fork();

  if (pid == 0) {

    // Child process.
    extern char** environ;
    if (execve(name, args, environ) == -1) {
      perror("execve error");
    }
    exit(1);

  } else if (pid < 0) {

    // Parent process error.
    perror("Error forking");
    return 1;

  } else {

    // Parent process.
    do {
      waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    return status;

  }
}
