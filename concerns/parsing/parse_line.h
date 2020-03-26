#pragma once
#include <executing/task.h>

#define PARSE_OK 0
#define PARSE_EMPTY 1
#define PARSE_ERROR 2
int parse_line(char *line, task* output);
