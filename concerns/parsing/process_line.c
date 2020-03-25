#include "process_line.h"
#include "ensure_no_pipes.h"
#include "expand_globs.h"
#include "split_into_words.h"
#include <data_types/string.h>
#include <data_types/vector.h>
#include <executing/task.h>

static string eat_command_name(string line, vector words) {
  size_t a = (size_t) vector_get(words, 0);
  size_t b = (size_t) vector_get(words, 1);
  vector_delete_range(words, 0, 1);

  char *s = string_to_cstr(line);
  s[b] = '\0';
  string ret = string_from_cstr(s + a);
  free(s);

  return ret;
}

static vector eat_arguments(string line, vector words) {
  // TODO: implement.
  (void)line;
  return words;
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
