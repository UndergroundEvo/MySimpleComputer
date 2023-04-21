#include "include.h"
#include "myReadKey.h"
/*как убрать табул€цию??????????????????*/
// codirovka s'ela dryzei
void
menu ()
{
  enum keys key = 0;
  do
    {
      key = 0;
      int value;
      mt_clrscreen ();
      printf ("Press: ENTER/F5/F6/S/R/ESC \n");
      printf ("ENTER - view 1st mem. cell \n");
      printf ("F5 - set 1st mem. cell to 255 \n");
      printf ("F6 - set 1st mem. cell to 0 \n");
      printf ("S - Save terminal condition \n");
      printf ("R - Restore terminal condition \n");
      printf ("T - Clear screen \n");
      printf ("ESC - Exit \n");

      rk_readKey (&key);
      switch (key)
        {
        case KEY_ENTER:
          sc_memoryGet (1, &value);
          printf ("Memory: %d", value);
          getchar ();
          break;
        case KEY_F5:
          sc_memorySet (1, 255);
          printf ("Memory set!");
          getchar ();
          break;
        case KEY_F6:
          sc_memorySet (1, 0);
          printf ("Memory set!");
          getchar ();
          break;
        case KEY_L:
          rk_myTermRestore ();
          printf ("Restored!");
          getchar ();
          break;
        case KEY_S:
          rk_myTermSave ();
          printf ("Saved!");
          getchar ();
          break;
        case KEY_T:
          mt_clrscreen ();
          getchar ();
          break;
        case KEY_ESC:
          break;
        default:
          menu ();
        }
    }
  while (key != KEY_ESC);
}
int
main ()
{
  enum keys key;
  int value;
  sc_memoryInit ();
  sc_memorySet (1, 0);
  sc_memoryGet (1, &value);
  printf ("%d\n", value);
  menu ();
  return 0;
}