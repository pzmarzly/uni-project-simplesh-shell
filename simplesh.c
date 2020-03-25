#define HOLDS_STATE

#include <parsing/process_line.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <state/state.h>
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
