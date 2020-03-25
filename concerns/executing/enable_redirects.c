#include "enable_redirects.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

struct redirects_state {
  int stdin_fd;
  int stdout_fd;
  int stderr_fd;
};

redirects_state enable_redirects(int new_stdin, int new_stdout, int new_stderr) {
  redirects_state ret = malloc(sizeof(struct redirects_state));

  fflush(stdout);
  fflush(stderr);

  // 1. dup will create a copy of current fd.
  // 2. dup2 will a copy of new fd, close the current fd
  // and put a copy of new fd in its place.
  // 3. We don't need new_fd anymore.

  if (new_stdin == UNCHANGED) {
    ret->stdin_fd = UNCHANGED;
  } else {
    ret->stdin_fd = dup(STDIN_FILENO);
    dup2(new_stdin, STDIN_FILENO);
    close(new_stdin);
  }

  if (new_stdout == UNCHANGED) {
    ret->stdout_fd = UNCHANGED;
  } else {
    ret->stdout_fd = dup(STDOUT_FILENO);
    dup2(new_stdout, STDOUT_FILENO);
    close(new_stdout);
  }

  if (new_stderr == UNCHANGED) {
    ret->stderr_fd = UNCHANGED;
  } else {
    ret->stderr_fd = dup(STDERR_FILENO);
    dup2(new_stderr, STDERR_FILENO);
    close(new_stderr);
  }

  return ret;
}

void revert_redirects(redirects_state state) {
  fflush(stdout);
  fflush(stderr);

  if (state->stdin_fd != UNCHANGED)
    dup2(state->stdin_fd, STDIN_FILENO);
  if (state->stdout_fd != UNCHANGED)
    dup2(state->stdout_fd, STDOUT_FILENO);
  if (state->stderr_fd != UNCHANGED)
    dup2(state->stderr_fd, STDERR_FILENO);

  free(state);
}
