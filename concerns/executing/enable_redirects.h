#pragma once

#define UNCHANGED -1

typedef struct redirects_state *redirects_state;
redirects_state enable_redirects(int new_stdin, int new_stdout, int new_stderr);
void revert_redirects(redirects_state state);
