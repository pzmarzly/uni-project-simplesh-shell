#include "process_line.h"
#include "ensure_no_pipes.h"
#include "expand_globs.h"
#include "split_into_words.h"
#include <data_types/string.h>
#include <data_types/vector.h>
#include <data_types/words.h>
#include <data_types/redirects.h>
#include <executing/task.h>
#include <string.h>

static char *eat_command_name(string line, words words) {
  char *word = first_word(words, line);
  delete_first_word(words);
  return word;
}

static vector eat_arguments(string line, words words) {
  vector ret = vector_new();
  while (vector_size(words) > 0) {
    char *word = first_word(words, line);
    if (word[0] == '>' || word[0] == '<'
      || word[0] == '|')
      break;
    vector_push(ret, (any_t) word);
    delete_first_word(words);
  }
  return ret;
}

static redirects eat_redirects(string line, vector words) {
  vector ret = vector_new();
  char last_seen = '\0';
  while (vector_size(words) > 0) {
    char *word = first_word(words, line);
    if (word[0] == '|')
      break;

    if (strlen(word) == 1 && (word[0] == '>' || word[0] == '<')) {
      last_seen = word[0];
      delete_first_word(words);
      continue;
    }

    if (last_seen) {
      vector_push(ret, (any_t) last_seen);
      vector_push(ret, (any_t) word);
    } else if (word[0] == '>' || word[0] == '<') {
      vector_push(ret, (any_t) word[0]);
      vector_push(ret, (any_t) (word + 1));
    }

    delete_first_word(words);
  }
  return ret;
}

void process_line(char *line) {
  string l = string_from_cstr(line);
  expand_globs(l);

  words words = split_into_words(l);
  if (vector_size(words) == 0)
    goto end;

  if (!ensure_no_pipes(l, words)) // FIXME: support pipes
    goto end;

  // eat_variables(words); // FIXME: support setting variables
  char *command = eat_command_name(l, words);
  vector arguments = eat_arguments(l, words);
  redirects redirects = eat_redirects(l, words);

  task task = task_new(command, arguments, redirects);
  #ifdef DEBUG
  task_debug(task);
  #endif
  task_run(task);

  end:
  vector_free(words);
  string_free(l);
}
