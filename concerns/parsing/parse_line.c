#include "parse_line.h"
#include "ensure_no_pipes.h"
#include "expand_globs.h"
#include "split_into_words.h"
#include <data_types/redirects.h>
#include <data_types/string.h>
#include <data_types/vector.h>
#include <data_types/words.h>
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
    if (word[0] == '>' || word[0] == '<' || word[0] == '|')
      break;
    vector_push(ret, (any_t)word);
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
    if (strlen(word) == 2 && word[0] == '2' && word[1] == '>') {
      last_seen = word[0];
      delete_first_word(words);
      continue;
    }

    if (last_seen) {
      vector_push(ret, (any_t)last_seen);
      vector_push(ret, (any_t)word);
      last_seen = '\0';
    } else if (word[0] == '>' || word[0] == '<') {
      vector_push(ret, (any_t)word[0]);
      vector_push(ret, (any_t)(word + 1));
    } else if (word[0] == '2' && word[1] == '>') {
      vector_push(ret, (any_t)word[0]);
      vector_push(ret, (any_t)(word + 2));
    }

    delete_first_word(words);
  }
  return ret;
}

int parse_line(char *line, task *output) {
  int ret = PARSE_ERROR;
  string l = string_from_cstr(line);
  expand_globs(l);

  words words = split_into_words(l);
  if (vector_size(words) == 0) {
    ret = PARSE_EMPTY;
    goto end;
  }

  if (!ensure_no_pipes(l, words)) // FIXME: support pipes
    goto end;

  // eat_variables(words); // FIXME: support setting variables
  char *command = eat_command_name(l, words);
  vector arguments = eat_arguments(l, words);
  redirects redirects = eat_redirects(l, words);

  *output = task_new(command, arguments, redirects);
  ret = PARSE_OK;

end:
  vector_free(words);
  string_free(l);
  return ret;
}
