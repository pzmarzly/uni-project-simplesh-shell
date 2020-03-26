#include <parsing/parse_line.h>
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

    task task;
    int status = parse_line(line, &task);
    if (status == PARSE_OK) {
      add_history(line);
#ifdef DEBUG
      task_debug(task);
#endif
      last_exit_code = task_run(task);
      task_free(task);
    } else if (status == PARSE_EMPTY) {
      last_exit_code = 0;
    } else if (status == PARSE_ERROR) {
      last_exit_code = 1;
    }

    free(line);
  }

  return 0;
}
