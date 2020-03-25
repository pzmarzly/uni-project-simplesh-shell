#include "task.h"
#include <stdio.h>

struct task {};

task task_new(string command, vector arguments, redirects redirects) {
  task ret = malloc(sizeof(struct task));
  printf("Command: %s\n", string_to_cstr(command));
  while (vector_size(arguments) > 0) {
    printf("Argument: %s\n", (char *) vector_get(arguments, 0));
    vector_delete(arguments, 0);
  }
  while (vector_size(redirects) > 0) {
    printf("Redirect %c: %s\n", first_redirect_direction(redirects), first_redirect_path(redirects));
    delete_first_redirect(redirects);
  }
  return ret;
}

void task_run(task task) {
  // TODO: implement.
  (void)task;
}
