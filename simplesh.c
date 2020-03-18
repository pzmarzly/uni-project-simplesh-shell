#define HOLDS_STATE

#include "concerns/parsing/line_processing.h"
#include "concerns/state/state.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  init_state();

  while (true) {
    char *prompt = state_get_prompt();
    char *line = readline(prompt);
    free(prompt);

    if (!line)
      break;
    process_line(line);
    free(line);
  }

  return 0;
}
