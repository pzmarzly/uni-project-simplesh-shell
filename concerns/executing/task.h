#pragma once
#include <data_types/string.h>
#include <data_types/vector.h>
#include <data_types/kv.h>

typedef struct task* task;
task task_new(string command, vector arguments, vector redirects);
void task_run(task task);
