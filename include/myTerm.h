#ifndef MYTERM_H
#define MYTERM_H

#include "include.h"

enum colors
{
  RED,
  GREEN,
  BLUE,
  YELLOW,
  MANGETA,
  CYAN,
  WHITE,
  BLACK
};

int mt_clrscreen ();
int mt_getscreensize (int *rows, int *cols);
int mt_gotoXY (int numRow, int numCol);
int mt_setfgcolor (enum colors);
int mt_setbgcolor (enum colors);
#endif