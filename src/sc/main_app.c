#include <mySimpleComputer.h>

/* волшебный пингвин 🐧 */
void
PrintTerminal ()
{
  int rows = 0, lines = 0;
  int size;
  int sign;
  int num;
  int line = 2;
  char str[4];
  ACCUM = 23;
  mt_clrscreen ();
  mt_gotoXY (3, 3);
  mt_getscreensize (&rows, &lines);
  mt_setfgcolor (1);
  mt_setbgcolor (2);
  printf ("%d %d\n", rows, lines);
  for (int i = 0; i < 100; ++i)
    {
      if (i % 10 == 0)
        {
          mt_gotoXY (line, 2);
          line++;
        }
      num = 0;
      num = memory[i] & 0x3FFF;
      sign = memory[i] >> 15;
      memset (str, 0, 4);
      if (sign == 1)
        write (1, "-", 1);
      else
        write (1, "+", 1);
      if (num < 1000)
        write (1, "0", 1);
      if (num < 100)
        write (1, "0", 1);
      if (num < 10)
        write (1, "0", 1);
      size = sprintf (str, "%d", num);
      write (1, str, size);
      if ((i + 1) % 10 != 0)
        write (1, " ", 1);
    }

  mt_gotoXY (1, 64);
  // write (1, "Accumulator", 11);
  write (1, "Аккамулятор", 11);
  mt_gotoXY (2, 66);
  sign = ACCUM >> 15;
  num = ACCUM & 0x3FFF;
  size = sprintf (str, "%d", num);
  write (1, str, size);

  mt_gotoXY (4, 64);
  // write (1, "InstructionCounter", 18);
  write (1, "Счетчик инструкций", 18);
  mt_gotoXY (5, 66);
  sign = IP >> 8;
  num = IP & 0x7F;

  size = sprintf (str, "%d", num);
  write (1, str, size);

  mt_gotoXY (7, 64);
  // write (1, "Operation", 9);
  write (1, "Операция", 9);

  mt_gotoXY (10, 64);
  // write (1, "Flags", 5);
  write (1, "Флаги", 5);
  mt_gotoXY (11, 66);

  for (int i = 1; i < 6; ++i)
    {
      if (i == 1)
        {
          write (1, "O", 1);
        }
      else if (i == 2)
        {
          write (1, "E", 1);
        }
      else if (i == 3)
        {
          write (1, "V", 1);
        }
      else if (i == 4)
        {
          write (1, "M", 1);
        }
      else if (i == 5)
        {
          write (1, "T", 1);
        }

      write (1, " ", 1);
    }

  mt_gotoXY (13, 64);
  // write (1, "Keys", 4);
  write (1, "Клавиши", 4);

  mt_gotoXY (14, 64);
  // write (1, "l - load", 8);
  write (1, "l - загрузка", 8);
  mt_gotoXY (15, 64);
  // write (1, "s - save", 8);
  write (1, "s - сохранение", 8);
  mt_gotoXY (16, 64);
  // write (1, "r - run", 7);
  write (1, "r - запуск", 7);
  mt_gotoXY (17, 64);
  // write (1, "t - step", 8);
  write (1, "t - шаг", 8);
  mt_gotoXY (18, 64);
  // write (1, "i - reset", 5);
  write (1, "i - сброс", 5);
  mt_gotoXY (19, 64);
  // write (1, "f5 - accumulator", 16);
  write (1, "f5 - аккамулятор", 16);
  mt_gotoXY (20, 64);
  write (1, "f6 - IP", 7);

  mt_gotoXY (24, 1);
  // write (1, "Input/Output:", 13);
  write (1, "Ввод/Вывод:", 13);
  mt_gotoXY (25, 1);
  write (1, "35> +1F1F", 9);
  mt_gotoXY (26, 1);
  write (1, "35< +1F1F", 9);
}

int
main ()
{
  system ("chcp 1251");
  sc_memoryInit ();
  sc_regInit ();
  PrintTerminal ();
  return 0;
}