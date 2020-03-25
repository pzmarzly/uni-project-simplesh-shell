#include "state.h"
#include "paths.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void init_state() {
  state = malloc(sizeof(struct state));
  state->cwd = get_cwd();
}

bool state_is_root() { return getuid() == 0; }

char *state_get_prompt() {
  int cwd_len = strlen(state->cwd);
  char *buf = malloc(cwd_len + 3);
  memcpy(buf, state->cwd, cwd_len);
  buf[cwd_len] = state_is_root() ? '#' : '$';
  buf[cwd_len + 1] = ' ';
  buf[cwd_len + 2] = '\0';
  return buf;
}
