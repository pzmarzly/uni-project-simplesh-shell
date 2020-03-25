#include "task.h"

struct task {};

task task_new(string command, vector arguments, vector redirects) {
  task ret = malloc(sizeof(struct task));
  // TODO: implement.
  (void)command;
  (void)arguments;
  (void)redirects;
  return ret;
}

void task_run(task task) {
  // TODO: implement.
  (void)task;
}
