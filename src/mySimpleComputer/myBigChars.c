#include <mySimpleComputer.h>
// #include "myBigChars.h"

int
bc_printA (char *str)
{
  printf ("\033(0%s\033(B", str);
  return 0;
}

int
bc_box (int x, int y, int width, int height)
{
  int rows, cols;
  mt_getscreensize (&rows, &cols);
  if ((x <= 0) || (y <= 0) || (x + width - 1 > cols) || (y + height - 1 > rows)
      || (width <= 1) || (height <= 1))
    return -1;
  mt_gotoXY (x, y);
  bc_printA ((char *)UI_LU);
  mt_gotoXY (x + width - 1, y);
  bc_printA ((char *)UI_RU);
  mt_gotoXY (x + width - 1, y + height - 1);
  bc_printA ((char *)UI_LD);
  mt_gotoXY (x, y + height - 1);
  bc_printA ((char *)UI_RD);

  for (int i = 1; i < width - 1; i++)
    {
      mt_gotoXY (x + i, y);
      bc_printA ((char *)UI_HOR);
      mt_gotoXY (x + i, y + height - 1);
      bc_printA ((char *)UI_HOR);
    }

  for (int i = 1; i < height - 1; i++)
    {
      mt_gotoXY (x, y + i);
      bc_printA ((char *)UI_VER);
      mt_gotoXY (x + width - 1, y + i);
      bc_printA ((char *)UI_VER);
    }
  return 0;
}

int
bc_printbigchar (int *big, int x, int y, enum colors colorFG,
                 enum colors colorBG)
{
  return 0;
}

int
bc_setbigcharPos (int *big, int x, int y, int value)
{
  return 0;
}

int
bc_getbigcharpos (int *big, int x, int y, int *value)
{
  return 0;
}

int
bc_bigcharwrite (int fd, int *big, int count)
{
  return 0;
}

int
bc_bigcharread (int fd, int *big, int need_count, int *count)
{
  return 0;
}