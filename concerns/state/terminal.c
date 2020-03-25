#include "terminal.h"
#include <stdio.h>
#include <unistd.h>

bool can_colorize() { return isatty(fileno(stdin)); }

char *terminal_green() { return can_colorize() ? "\033[0;32m" : ""; }

char *terminal_red() { return can_colorize() ? "\033[0;31m" : ""; }

char *terminal_orange() { return can_colorize() ? "\033[0;33m" : ""; }

char *terminal_default() { return can_colorize() ? "\033[0m" : ""; }
