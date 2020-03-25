#include "task.h"
#include <stdio.h>

struct task {};

task task_new(string command, vector arguments, vector redirects) {
  task ret = malloc(sizeof(struct task));
  printf("Command: %s\n", string_to_cstr(command));
  while (vector_size(arguments) > 0) {
    printf("Argument: %s\n", (char *) vector_get(arguments, 0));
    vector_delete(arguments, 0);
  }
  (void)redirects;
  return ret;
}

void task_run(task task) {
  // TODO: implement.
  (void)task;
}
