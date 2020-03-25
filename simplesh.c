#include <parsing/process_line.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <state/prompt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  while (true) {
    char *prompt = get_prompt();
    char *line = readline(prompt);
    free(prompt);

    if (!line)
      break;
    process_line(line);
    free(line);
  }

  return 0;
}
