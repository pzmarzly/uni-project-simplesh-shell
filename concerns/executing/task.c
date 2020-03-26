#include "task.h"
#include "builtins.h"
#include "find_exe.h"
#include "run_exe.h"
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

static void enable_redirects(task task) {
  while (vector_size(task->redirects) > 0) {
    char direction = first_redirect_direction(task->redirects);

    // FIXME: support multiplexing (tee).
    // dup2 clones the handle, so we can close the original.
    if (direction == '>') {
      int fd = open(first_redirect_path(task->redirects), O_CREAT | O_WRONLY | O_TRUNC);
      if (fd == -1) {
        perror("open");
      } else {
        dup2(fd, STDOUT_FILENO);
        close(fd);
      }
    } else if (direction == '2') {
      int fd = open(first_redirect_path(task->redirects), O_CREAT | O_WRONLY | O_TRUNC);
      if (fd == -1) {
        perror("open");
      } else {
        dup2(fd, STDERR_FILENO);
        close(fd);
      }
    } else if (direction == '<') {
      int fd = open(first_redirect_path(task->redirects), O_RDONLY);
      if (fd == -1) {
        perror("open");
      } else {
        dup2(fd, STDIN_FILENO);
        close(fd);
      }
    }

    delete_first_redirect(task->redirects);
  }
}

int task_run(task task) {
  if (!task->exe) {
    printf("%sCommand not found%s\n", terminal_red(), terminal_default());
    return 1;
  }

  char **arguments = arguments_to_unix(task);

  // Create copies of IO handles.
  int stdin_fd = dup(STDIN_FILENO);
  int stdout_fd = dup(STDIN_FILENO);
  int stderr_fd = dup(STDIN_FILENO);
  enable_redirects(task);

  int ret = 1;
  if (task->is_builtin)
    ret = run_builtin(task->command, arguments);
  else
    ret = run_exe(task->exe, arguments);

  // Restore IO. dup2 will close whatever has fd=STDIN_FILENO,
  // duplicate stdin_fd and put the copy in place
  // of STDOUT_FILENO.
  dup2(stdin_fd, STDIN_FILENO);
  dup2(stdout_fd, STDOUT_FILENO);
  dup2(stderr_fd, STDERR_FILENO);

  free(arguments);
  return ret;
}

void task_free(task task) {
  free(task->command);

  size_t args = vector_size(task->arguments);
  for (size_t i = 0; i < args; i++)
    free((char *)vector_get(task->arguments, i));
  vector_free(task->arguments);

  size_t redirs = vector_size(task->redirects);
  for (size_t i = 0; i < redirs; i += 2)
    free((char *)vector_get(task->redirects, i));
  vector_free(task->redirects);

  free(task);
}
