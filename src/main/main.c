#include <include.h>
/* волшебный пингвин 🐧 */

int
main (int argc, char const *argv[])
{
  ui_initial ();
  signal (SIGALRM, signalHandler);
  signal (SIGUSR1, signalHandler);
  enum keys key;
  if (argc == 2)
    {
      sc_memoryLoad ((char *)argv[1]);
    }
  else if (argc > 2)
    {
      ui_messageOutput ((char *)"Exceeded the number of arguments", RED);
      return -1;
    }
  do
    {
      key = KEY_OTHER;
      ui_update ();
      rk_readKey (&key);
      switch (key)
        {
        case KEY_UP:
          ui_moveCurrMemPointer (KEY_UP);
          break;
        case KEY_RIGHT:
          ui_moveCurrMemPointer (KEY_RIGHT);
          break;
        case KEY_DOWN:
          ui_moveCurrMemPointer (KEY_DOWN);
          break;
        case KEY_LEFT:
          ui_moveCurrMemPointer (KEY_LEFT);
          break;

        case KEY_L:
          ui_loadMemory ();
          break;
        case KEY_S:
          ui_saveMemory ();
          break;

        case KEY_R:
          raise (SIGALRM);
          break;
        case KEY_T:
          setCurrMemPointer_to_ICounter ();
          ui_update ();
          CU ();
          break;
        case KEY_I:
          raise (SIGUSR1);
          break;

        case KEY_F5:
          ui_setAccumulator ();
          break;
        case KEY_F6:
          ui_setICounter ();
          break;

        case KEY_ENTER:
          ui_setMCellValue ();
          break;

        case KEY_ESC:
          break;
        case KEY_OTHER:
          break;
        }
    }
  while (key != KEY_ESC);

  return 0;
}