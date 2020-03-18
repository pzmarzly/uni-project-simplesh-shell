#include "line_processing.h"

void process_line(char *line) {
  string l = string_from_cstr(line);
  if (!is_complete(l)) {
    printf("Error: simplesh does not support commands spanning over multiple lines.\n");
    return;
  }

  unsigned commands = count_commands(l);

  for (unsigned i = 0; i < commands; i++) {
    kv variables = variables_from_state();
    kv new_variables = eat_variables(l);
    kv_override(variables, new_variables);
    expand_variables(l, variables);

    vector words = split_into_words(l);
    expand_globs(words);
    string command = eat_command_name(words);
    vector arguments = eat_arguments(words);
    vector redirects = eat_redirects(words);
  }
}
