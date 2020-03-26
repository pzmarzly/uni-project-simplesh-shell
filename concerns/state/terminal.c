#include "terminal.h"
#include <stdio.h>
#include <unistd.h>

bool can_colorize() {
  static int can_colorize = 2;
  if (can_colorize == 2)
    can_colorize = isatty(fileno(stdin));
  return can_colorize;
}

char *terminal_green() { return can_colorize() ? "\033[0;32m" : ""; }

char *terminal_red() { return can_colorize() ? "\033[0;31m" : ""; }

char *terminal_orange() { return can_colorize() ? "\033[0;33m" : ""; }

char *terminal_default() { return can_colorize() ? "\033[0m" : ""; }
