#include <parsing/process_line.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <state/prompt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  int last_exit_code = 0;
  while (true) {
    char *prompt = get_prompt(last_exit_code);
    char *line = readline(prompt);
    free(prompt);

    if (!line)
      break;
    last_exit_code = process_line(line);
    free(line);
  }

  return 0;
}
