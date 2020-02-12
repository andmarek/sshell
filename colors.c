//#include "colors.h"
#include <stdio.h>
#include <stdlib.h>

#define ANSI_COLOR_BLACK      "\x1b[30m"
#define ANSI_COLOR_RED      "\x1b[30m"
#define ANSI_COLOR_GREEn      "\x1b[30m"

void red() {
      printf("\033[1;31m");
      printf("\033[0m");
}

void yellow() {
      printf("\033[1;33m");
}

void reset() {
      printf("\033[0m");
}



