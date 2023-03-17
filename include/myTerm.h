#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

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

void mt_clrscr ();
void mt_gotoXY (int numRow, int numCol);
void mt_setfgcolor (enum colors);
void mt_setbgcolor (enum colors);