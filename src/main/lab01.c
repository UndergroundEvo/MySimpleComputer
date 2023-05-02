#include <mySimpleComputer.h>

int
main ()
{
  int value = 0;
  sc_memoryInit ();
  sc_memorySet (1, 5);
  sc_memorySet (2, 4);
  sc_memorySet (3, 3);
  sc_memorySet (4, 2);
  sc_memorySet (5, 1);
  for (int i = 0; i < 5; i++)
    {
      sc_memoryGet (i + 1, &value);
    }
  sc_memorySave ("test.bin");
  printf ("Сохранение файла \n");

  sc_memorySet (1, 99);
  sc_memoryGet (1, &value);
  printf ("RAM[ 1 ] = ");
  printf ("%d", value);
  printf ("\n");

  sc_memoryLoad ("test.bin");
  printf ("Чтение файла: \n");
  for (int i = 0; i < 5; i++)
    {
      sc_memoryGet (i + 1, &value);
      printf ("%d", value);
      printf ("\n");
    }
  printf ("\n\n");
  sc_regInit ();
  sc_regSet (IGNORING_CLOCK_PULSES, 1);

  sc_regGet (OVERFLOW, &value);
  printf ("Переполнение при выполнении операции: ");
  printf ("%d", value);
  printf ("\n");

  sc_regGet (DIVISION_BY_ZERO, &value);
  printf ("Ошибка деления на 0: ");
  printf ("%d", value);
  printf ("\n");

  sc_regGet (OUT_OF_MEMORY, &value);
  printf ("Ошибка выхода за границы памяти: ");
  printf ("%d", value);
  printf ("\n");

  sc_regGet (IGNORING_CLOCK_PULSES, &value);
  printf ("Игнорирование тактовых импульсов: ");
  printf ("%d", value);
  printf ("\n");

  sc_regGet (INCORRECT_COMMAND, &value);
  printf ("Указана неверная команда: ");
  printf ("%d", value);
  printf ("\n");

  printf ("\n\n");
  int f = 0, f_c = 0, f_o = 0;

  sc_commandEncode (0x33, 0x59, &f);
  printf ("Закодированная команда: \n");
  printf ("%d", f);
  printf ("\n");

  sc_commandDecode (f, &f_c, &f_o);
  printf ("Команда: ");
  printf ("%d", f_c);
  printf ("\n");
  printf ("Операнд: ");
  printf ("%d", f_o);
  printf ("\n");
}
