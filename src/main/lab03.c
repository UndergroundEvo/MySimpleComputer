#include <include.h>

int
main ()
{
  mt_clrscreen ();
  bc_printbigchar (bc[1], 1, 1, GREEN, BLACK);
  bc_printbigchar (bc[11], 1, 9, RED, BLACK);
  bc_printbigchar (bc[3], 1, 17, MAGENT, BLACK);
  // bc_printbigchar(bc[2], 1, 28, SUN, BLACK);
  mt_gotoXY (1, 20);
}