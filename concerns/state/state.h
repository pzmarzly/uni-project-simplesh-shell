#pragma once
#include <stdbool.h>

#ifdef HOLDS_STATE
#define EXTERN /* nothing */
#else
#define EXTERN extern
#endif

struct state {
  char *cwd;
};

EXTERN struct state *state;

void init_state();
bool state_is_root();
char *state_get_prompt();
