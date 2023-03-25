#include <mySimpleComputer.h>
#include <myTerm.h>

void
printTerminal ()
{
  mt_clrscreen ();
  mt_gotoXY (30, 1);
  printf (" Memory ");
  mt_gotoXY (66, 1);
  printf (" accumulator ");
  mt_gotoXY (63, 4);
  printf (" instructionCounter ");
  mt_gotoXY (68, 7);
  printf (" Operation ");
  mt_gotoXY (68, 10);
  printf (" Flags ");
  mt_gotoXY (48, 13);
  printf (" Keys: ");
  char *hotK[] = { (char *)"l  - load",
                   (char *)"s  - save",
                   (char *)"r  - run",
                   (char *)"t  - step",
                   (char *)"i  - reset",
                   (char *)"F5 - accumulator",
                   (char *)"F6 - instructionCounter" };

  for (int i = 0; i < sizeof (hotK) / sizeof (*hotK); ++i)
    {
      mt_gotoXY (48, i + 14);
      printf ("%s", hotK[i]);
    }
}

void
printMEM ()
{
  for (int i = 0; i < 10; ++i)
    for (int j = 0; j < 10; ++j)
      {
        mt_gotoXY (2 + (5 * j + j), 2 + i);
        int tmp = memory[i * 10 + j];
        if ((tmp >> 14) & 1)
          printf (" %04X", tmp & (~(1 << 14)));
        else
          printf ("+%04X", tmp);
      }
}

int
printflag ()
{
  char tmp[] = { 'O', 'Z', 'M', 'P', 'C' };
  // char tmp[] = {'⚰', '🧨', '🗿', '⛔', '🛑'};
  for (int i = 0; i < REG_SIZE; i++)
    {
      int value;
      if (sc_regGet (i, &value))
        return -1;
      if (value)
        {
          mt_gotoXY (69 + (i * 2), 11);
          printf ("%c", tmp[i]);
        }
    }
  return 0;
}

int
main ()
{
  sc_memoryInit ();
  sc_regInit ();

  sc_memorySet (0, 5);
  sc_memorySet (1, 4);
  sc_memorySet (2, 3);
  sc_memorySet (3, 2);
  sc_memorySet (4, 1);

  printTerminal ();
  printMEM ();
  sc_regSet (REG_SIZE, 5);
  sc_regSet (DIVISION_BY_ZERO, 1);
  sc_regSet (OUT_OF_MEMORY, 1);
  sc_regSet (INCORRECT_COMMAND, 1);
  printflag ();
  mt_gotoXY (1, 24);
  getchar();
  return 0;
}
