#include <myTerm.h>

unsigned short ACCUM;
unsigned char IP;

int
mt_clrscreen ()
{
  system ("clear");
  return 0;
}

int
mt_gotoXY (int col, int row)
{
  int rows, cols;
  if (mt_getscreensize (&rows, &cols) == -1)
    return -1;
  if ((row > rows) || (row <= 0) || (col > cols) || (col <= 0))
    return -1;
  printf ("\033[%d;%dH", row, col);
  return 0;
}

int
mt_getscreensize (int *rows, int *cols)
{
  struct winsize ws;
  if (ioctl (1, TIOCGWINSZ, &ws))
    return -1;
  *rows = ws.ws_row;
  *cols = ws.ws_col;
  return 0;
}

int
mt_setfgcolor (enum colors color)
{
  printf ("\033[38;5;%dm", color);
  return 0;
}

int
mt_setbgcolor (enum colors color)
{
  printf ("\033[48;5;%dm", color);
  return 0;
}

int
mt_setdefaultcolorsettings ()
{
  printf ("\033[0m");
  return 0;
}
