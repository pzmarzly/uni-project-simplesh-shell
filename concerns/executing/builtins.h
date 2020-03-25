#pragma once
#include <stdbool.h>

bool is_builtin(char *name);
int run_builtin(char *name, char **args);
