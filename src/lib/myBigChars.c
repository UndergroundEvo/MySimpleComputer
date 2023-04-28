#include <myBigChars.h>

char buf[512];
enum colors color;
unsigned int bc[][2] = {
  { 0xE7E7FFFF, 0xFFFFE7E7 }, { 0x1CDC7C3C, 0xFFFF1C1C },
  { 0xFF07FFFF, 0xFFFFE0FF }, { 0xFF07FFFF, 0xFFFF07FF },
  { 0xFFE7E7E7, 0x070707FF }, { 0xFFE0FFFF, 0xFFFF07FF },
  { 0xFFE0FFFF, 0xFFFFE7FF }, { 0x1C0EFFFE, 0x3838FE38 },
  { 0x7EE7FF7E, 0x7EFFE77E }, { 0xFFE7FFFF, 0xFFFF07FF },
  { 0xFFE7FF7E, 0xE7E7E7FF }, { 0xFEE7FFFE, 0xFEFFE7FE },
  { 0xE0E7FF7E, 0x7EFFE7E0 }, { 0xE7E7FFF8, 0xF8FFE7E7 },
  { 0xFFE0FFFF, 0xFFFFE0FF }, { 0xFFE0FFFF, 0xE0E0E0FF },
  { 0x7E180000, 0x00000018 }, { 0x7E000000, 0x00000000 },
};
/* 0,1,2,3,4,5,6,7,8,9,A,B,C,D,E,F,+,- */

int
bc_printA (char ch)
{
  WRITE_STR (ch);
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
  WRITE_WCHAR (ACS_UL);
  mt_gotoXY (x + width - 1, y);
  WRITE_WCHAR (ACS_UR);
  mt_gotoXY (x + width - 1, y + height - 1);
  WRITE_WCHAR (ACS_DR);
  mt_gotoXY (x, y + height - 1);
  WRITE_WCHAR (ACS_DL);
  for (int i = 1; i < width - 1; ++i)
    {
      mt_gotoXY (x + i, y);
      WRITE_WCHAR (ACS_H);
      mt_gotoXY (x + i, y + height - 1);
      WRITE_WCHAR (ACS_H);
    }
  for (int i = 1; i < height - 1; ++i)
    {
      mt_gotoXY (x, y + i);
      WRITE_WCHAR (ACS_V);
      mt_gotoXY (x + width - 1, y + i);
      WRITE_WCHAR (ACS_V);
    }
  return 0;
}
int
bc_printbigchar (unsigned int *big, int x, int y, enum colors colorFG,
                 enum colors colorBG)
{
  if (colorFG != 0)
    mt_setfgcolor (colorFG);
  if (colorBG != 0)
    mt_setfgcolor (colorBG);
  for (int i = 0; i < 8; ++i)
    for (int j = 0; j < 8; ++j)
      {
        mt_gotoXY (x + i, y + j);
        int value;
        if (bc_getbigcharpos (big, i, j, &value))
          value = -1;
        if (value)
          WRITE_WCHAR (ACS_CKBOARD);
        else
          WRITE_STR (' ');
      }
  mt_setdefaultcolorsettings ();
  return 0;
}
int
bc_setbigcharpos (unsigned int *big, int x, int y, int value)
{
  int shift;
  if (value < 0 || value > 1 || x < 1 || x > 8 || y < 1 || y > 8)
    return -1;
  if (y <= 4)
    {
      shift = (y * 8) - (8 - x) - 1;
      big[0] = big[0] | (1 << shift);
    }
  else
    {
      shift = ((y - 4) * 8) - (8 - x) - 1;
      big[1] = big[1] | (1 << shift);
    }
  return 0;
}
int
bc_getbigcharpos (unsigned int *big, int x, int y, int *value)
{
  if ((x < 0) || (x > 7) || (y < 0) || (y > 7))
    return -1;
  *value = (big[y / 4] & (1 << (8 * (y % 4) + (7 - x)))) != 0;
  return 0;
}
int
bc_bigcharwrite (int fd, unsigned int *big, int count)
{
  if (write (fd, big, count * 2 * sizeof (unsigned int)))
    return -1;
  return 0;
}
int
bc_bigcharread (int fd, unsigned int *big, int need_count, int *count)
{
  *count = 0;
  for (int i = 0; i < need_count * 2; ++i)
    {
      if (read (fd, &big[i], sizeof (unsigned int)) == -1)
        return -1;
      if (!((i + 1) % 2))
        (*count)++;
    }
  return 0;
}