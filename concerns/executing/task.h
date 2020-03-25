#pragma once
#include <data_types/redirects.h>
#include <data_types/string.h>
#include <data_types/vector.h>

typedef struct task *task;
task task_new(char *command, vector arguments, redirects redirects);
void task_debug(task task);
void task_run(task task);
