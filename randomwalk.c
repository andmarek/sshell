#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

static void init_curses()
{
  initscr();
  raw();
  noecho();
}

static void end_curses()
{
  refresh();
  endwin();
}

static void coin_flip
{

}


int main()
{
  int l, init_x, init_y, i, j;

  printw("How many steps would you like?\n");
  l = getch();

  init_curses();

  while(i < l) {

    l++;
  }

  end_curses();
  return 0;
}
