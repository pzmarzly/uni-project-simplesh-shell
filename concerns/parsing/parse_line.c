#include "parse_line.h"
#include "expand_globs.h"
#include "split_into_words.h"
#include <data_types/redirects.h>
#include <data_types/vector.h>
#include <data_types/words.h>
#include <executing/task.h>
#include <string.h>

static char *eat_command_name(char *line, words words) {
  char *word = first_word(words, line);
  delete_first_word(words);
  return word;
}

static vector eat_arguments(char *line, words words) {
  vector ret = vector_new();
  while (vector_size(words) > 0) {
    char *word = first_word(words, line);
    if (word[0] == '>' || word[0] == '<' || word[0] == '|') {
      free(word);
      break;
    }
    vector_push(ret, (any_t)word);
    delete_first_word(words);
  }
  return ret;
}

static redirects eat_redirects(char *line, vector words) {
  vector ret = vector_new();
  char last_seen = '\0';
  while (vector_size(words) > 0) {
    char *word = first_word(words, line);
    if (word[0] == '|') {
      free(word);
      break;
    }

    if (strlen(word) == 1 && (word[0] == '>' || word[0] == '<')) {
      last_seen = word[0];
      delete_first_word(words);
      free(word);
      continue;
    }
    if (strlen(word) == 2 && word[0] == '2' && word[1] == '>') {
      last_seen = word[0];
      delete_first_word(words);
      free(word);
      continue;
    }

    if (last_seen) {
      vector_push(ret, (any_t)last_seen);
      vector_push(ret, (any_t)word);
      last_seen = '\0';
      delete_first_word(words);
    } else if (word[0] == '>' || word[0] == '<') {
      vector_push(ret, (any_t)word[0]);
      vector_push(ret, (any_t)(word + 1));
      delete_first_word(words);
    } else if (word[0] == '2' && word[1] == '>') {
      vector_push(ret, (any_t)word[0]);
      vector_push(ret, (any_t)(word + 2));
      delete_first_word(words);
    } else {
      delete_first_word(words);
      free(word);
    }
  }
  return ret;
}

int parse_line(char *line, task *output) {
  int ret = PARSE_ERROR;
  char *l = strdup(line);
  expand_globs(&l);

  words words = split_into_words(l);
  if (vector_size(words) == 0) {
    ret = PARSE_EMPTY;
    goto end;
  }

  // eat_variables(words); // FIXME: support setting variables
  char *command = eat_command_name(l, words);
  vector arguments = eat_arguments(l, words);
  redirects redirects = eat_redirects(l, words);

  *output = task_new(command, arguments, redirects);
  ret = PARSE_OK;

end:
  vector_free(words);
  free(l);
  return ret;
}
