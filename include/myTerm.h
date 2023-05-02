#ifndef MYTERM_H
#define MYTERM_H

#include "include.h"

enum colors
{
  BLACK,
  YELLOW,
  RED,
  GREEN,
  BROWN,
  BLUE,
  MAGENT,
  CYAN,
  DARK_GRAY,
  LIGHT_GRAY,
  PINK,
  LIME,
  SUN,
  AQUA,
  LIGHT_MAGENT,
  LIGHT_CYAN,
  WHITE,
  DEFAULT
};

int mt_clrscreen ();
int mt_getscreensize (int *rows, int *cols);
int mt_gotoXY (int numRow, int numCol);
int mt_setfgcolor (enum colors);
int mt_setbgcolor (enum colors);
int mt_setdefaultcolorsettings ();
#endif