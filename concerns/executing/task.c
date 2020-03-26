#include "task.h"
#include "builtins.h"
#include "find_exe.h"
#include "run_exe.h"
#include "enable_redirects.h"
#include <state/terminal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

struct task {
  bool is_builtin;
  char *command;
  char *exe;
  vector arguments;
  redirects redirects;
};

static bool is_path(char *command) { return strchr(command, '/') != NULL; }

task task_new(char *command, vector arguments, redirects redirects) {
  task ret = malloc(sizeof(struct task));

  if (is_path(command)) {
    ret->is_builtin = false;
    ret->exe = command;
  } else if (is_builtin(command)) {
    ret->is_builtin = true;
    ret->exe = command;
  } else {
    ret->is_builtin = false;
    ret->exe = find_exe(command);
  }

  ret->command = command;
  ret->arguments = arguments;
  ret->redirects = redirects;
  return ret;
}

void task_debug(task task) {
  if (task->exe)
    printf("Executable: %s\n", task->exe);
  else
    printf("Executable not found\n");

  vector arguments = vector_clone(task->arguments);
  while (vector_size(arguments) > 0) {
    printf("Argument: %s\n", (char *)vector_get(arguments, 0));
    vector_delete(arguments, 0);
  }

  vector redirects = vector_clone(task->redirects);
  while (vector_size(redirects) > 0) {
    printf("Redirect %c: %s\n", first_redirect_direction(redirects),
           first_redirect_path(redirects));
    delete_first_redirect(redirects);
  }
}

static char **arguments_to_unix(task task) {
  unsigned ext_arg_len = vector_size(task->arguments);

  char **arguments = malloc(sizeof(char *) * (ext_arg_len + 2));
  arguments[0] = task->command;
  for (unsigned i = 0; i < ext_arg_len; i++)
    arguments[i + 1] = (char *)vector_get(task->arguments, i);
  arguments[ext_arg_len + 1] = NULL;

  return arguments;
}

static void redirects_to_unix(task task, int *stdin_fd, int *stdout_fd, int *stderr_fd) {
  while (vector_size(task->redirects) > 0) {
    char direction = first_redirect_direction(task->redirects);
    if (direction == '>') {
      // FIXME: check for open(2) errors
      int fd = open(first_redirect_path(task->redirects), O_CREAT | O_WRONLY | O_TRUNC);
      *stdout_fd = fd;
      // FIXME: support redirecting stderr separately
      *stderr_fd = dup(*stdout_fd);
    } else if (direction == '<') {
      *stdin_fd = open(first_redirect_path(task->redirects), O_RDONLY);
    }
    // FIXME: support multiple redirects (multicasting) or at least throw error
    delete_first_redirect(task->redirects);
  }
}

int task_run(task task) {
  if (!task->exe) {
    printf("%sCommand not found%s\n", terminal_red(), terminal_default());
    return 1;
  }

  char **arguments = arguments_to_unix(task);

  int stdin_fd = UNCHANGED;
  int stdout_fd = UNCHANGED;
  int stderr_fd = UNCHANGED;
  redirects_to_unix(task, &stdin_fd, &stdout_fd, &stderr_fd);
  redirects_state state = enable_redirects(stdin_fd, stdout_fd, stderr_fd);

  int ret = 1;
  if (task->is_builtin)
    ret = run_builtin(task->command, arguments);
  else
    ret = run_exe(task->exe, arguments);

  revert_redirects(state);
  free(arguments);
  return ret;
}

void task_free(task task) {
  free(task->command);
  vector_free(task->arguments);
  vector_free(task->redirects);
  free(task);
}
