#include "state.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static char *find_home() {
  char *env = getenv("HOME");
  if (env)
    return env;
  printf("Warning: no HOME environment variable set.\n");
  return strdup("/");
}

void init_state() {
  state = malloc(sizeof(struct state));
  state->pwd = find_home();
}

bool state_is_root() { return getuid() == 0; }

char *state_get_prompt() {
  int pwd_len = strlen(state->pwd);
  char *buf = malloc(pwd_len + 2);
  memcpy(buf, state->pwd, pwd_len);
  buf[pwd_len] = state_is_root() ? '#' : '$';
  buf[pwd_len + 1] = '\0';
  return buf;
}
