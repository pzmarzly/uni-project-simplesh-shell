#include "task.h"
#include "builtins.h"
#include "find_exe.h"
#include <state/terminal.h>
#include <stdio.h>
#include <string.h>

struct task {
  bool is_builtin;
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

void task_run(task task) {
  if (!task->exe) {
    printf("%sCommand not found%s\n", terminal_red(), terminal_default());
    return;
  }
  // TODO: implement.
  (void)task;
}
