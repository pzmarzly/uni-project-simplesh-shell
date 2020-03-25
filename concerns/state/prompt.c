#include "prompt.h"
#include "paths.h"
#include "terminal.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static bool is_root() { return getuid() == 0; }

char *get_prompt(int last_exit_code) {
  char *cwd = get_cwd();
  int cwd_len = strlen(cwd);

  char *buf = malloc(cwd_len + 20);
  strcpy(buf, last_exit_code ? terminal_red() : terminal_green());
  strcat(buf, cwd);
  strcat(buf, terminal_default());
  strcat(buf, is_root() ? "# " : "$ ");

  free(cwd);
  return buf;
}
