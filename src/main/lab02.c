#include <mySimpleComputer.h>

int
main ()
{
  mt_clrscreen ();
  mt_gotoXY (5, 10);
  mt_setbgcolor (BLACK);
  mt_setfgcolor (RED);
  printf ("rus lang: загадка линукса 🐧");
  mt_gotoXY (6, 8);
  mt_setbgcolor (BLACK);
  mt_setfgcolor (GREEN);
  mt_gotoXY (10, 1);
  printf ("Test for Lab2");
  getchar ();

  sc_memorySet (0, 5);
  sc_memorySet (1, 4);
  sc_memorySet (2, 3);
  sc_memorySet (3, 2);
  sc_memorySet (4, 1);
  sc_memorySet (5, 9999);
  sc_regSet (OVERFLOW, 1);
  sc_regSet (DIVISION_BY_ZERO, 1);
  sc_regSet (OUT_OF_MEMORY, 1);
  sc_regSet (INCORRECT_COMMAND, 1);
}