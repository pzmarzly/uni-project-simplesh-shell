#include "process_line.h"
#include "ensure_no_pipes.h"
#include "expand_globs.h"
#include "split_into_words.h"
#include <data_types/string.h>
#include <data_types/vector.h>
#include <data_types/words.h>
#include <executing/task.h>

static string eat_command_name(string line, words words) {
  char *word = first_word(words, line);
  string ret = string_from_cstr(word);
  free(word);

  delete_first_word(words);
  return ret;
}

static vector eat_arguments(string line, words words) {
  vector ret = vector_new();
  while (vector_size(words) > 0) {
    char *word = first_word(words, line);
    free(word);
  }
  return ret;
}

static vector eat_redirects(string line, vector words) {
  // TODO: implement.
  (void)line;
  return words;
}

void process_line(char *line) {
  string l = string_from_cstr(line);
  expand_globs(l);

  vector words = split_into_words(l);
  if (!ensure_no_pipes(l, words)) // FIXME: support pipes
    goto end;

  // eat_variables(words); // FIXME: support setting variables
  string command = eat_command_name(l, words);
  vector arguments = eat_arguments(l, words);
  vector redirects = eat_redirects(l, words);

  task task = task_new(command, arguments, redirects);
  task_run(task);

  end:
  vector_free(words);
  string_free(l);
}
