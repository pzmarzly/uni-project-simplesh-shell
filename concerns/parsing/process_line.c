#include "process_line.h"
#include "ensure_complete.h"
#include "ensure_no_pipes.h"
#include "expand_globs.h"
#include "split_into_words.h"
#include <data_types/string.h>
#include <data_types/vector.h>
#include <executing/task.h>

static string eat_command_name(vector words) {
  string ret = (string) vector_get(words, 0);
  vector_delete(words, 0);
  return ret;
}

static vector eat_arguments(vector words) {
  // TODO: implement.
  return words;
}

static vector eat_redirects(vector words) {
  // TODO: implement.
  return words;
}

void process_line(char *line) {
  string l = string_from_cstr(line);
  if (!ensure_complete(l))
    return;
  if (!ensure_no_pipes(l))
    return;

  vector words = split_into_words(l);

  // eat_variables(words); // FIXME: support setting variables

  expand_globs(l);

  string command = eat_command_name(words);
  vector arguments = eat_arguments(words);
  vector redirects = eat_redirects(words);

  task task = task_new(command, arguments, redirects);
  task_run(task);

  vector_free(words);
  string_free(l);
}
