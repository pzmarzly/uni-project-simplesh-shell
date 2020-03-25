#include "task.h"
#include <stdio.h>

struct task {
  string command;
  vector arguments;
  redirects redirects;
};

task task_new(string command, vector arguments, redirects redirects) {
  task ret = malloc(sizeof(struct task));
  ret->command = command;
  ret->arguments = arguments;
  ret->redirects = redirects;
  return ret;
}

void task_debug(task task) {
  printf("Command: %s\n", string_to_cstr(task->command));

  vector arguments = vector_clone(task->arguments);
  while (vector_size(arguments) > 0) {
    printf("Argument: %s\n", (char *) vector_get(arguments, 0));
    vector_delete(arguments, 0);
  }

  vector redirects = vector_clone(task->redirects);
  while (vector_size(redirects) > 0) {
    printf("Redirect %c: %s\n", first_redirect_direction(redirects), first_redirect_path(redirects));
    delete_first_redirect(redirects);
  }
}

void task_run(task task) {
  // TODO: implement.
  (void)task;
}
