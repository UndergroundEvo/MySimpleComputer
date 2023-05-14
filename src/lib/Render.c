#include <Render.h>

short currMemCell = 0;
enum keys;

void
signalHandler(int signal) {
    switch (signal) {
    case SIGALRM:
        setCurrMemPointer_to_ICounter();
        ui_update();
        if (CU()) {
            sc_regSet(IGNORING_CLOCK_PULSES, 1);
            ui_update();
            alarm(0);
        }
        else alarm(1);
        rk_myTermRegime(0, 0, 0, 0, 0);
        break;

    case SIGUSR1:
        alarm(0);
        ui_initial();
        break;
    default:
        break;
    }
    //switch (signal)
    //  {
    //  case SIGALRM:
    //    // currMemCell = checkSystem;
    //    checkSystem++;
    //    ui_update ();
    //    alarm (1);
    //    rk_myTermRegime (0, 0, 0, 0, 0);
    //    break;
    //  case SIGUSR1:
    //    alarm (0);
    //    ui_initial ();
    //    break;
    //  default:
    //    break;
    //  }
}

int
rk_pause (int time)
{
  fflush (stdout); // очистка потока вывода
  char buffer[5] = "\0";
  rk_myTermRegime (0, time, 0, 0, 0);
  read (fileno (stdin), buffer, 5);
  rk_myTermRestore ();
  return 0;
}
int 
setCurrMemPointer_to_ICounter() {
    currMemCell = checkSystem;
    return 0;
}
int
check_HEX (const char *buffer)
{
  if ((strlen (buffer) == 0) || (strlen (buffer) > 4))
    return 0;
  for (int i = 0; i < strlen (buffer); ++i)
    if (!(isxdigit (buffer[i])))
      return 0;
  return 1;
}
int
check_DEC (const char *buffer)
{
  if ((strlen (buffer) == 0) || (strlen (buffer) > 5))
    return 0;
  for (int i = 0; i < strlen (buffer); ++i)
    if (!(isdigit (buffer[i])))
      return 0;
  return 1;
}
int
print_norm (char *str, enum colors color)
{
  printf ("\033[38;5;%dm%s\033[0m", color, str);
  rk_pause (25);
  return 0;
}
int
ui_initial ()
{
  currMemCell = 0;
  if (rk_myTermSave ())
    return -1;
  sc_memoryInit ();
  sc_regInit ();
  sc_regSet (IGNORING_CLOCK_PULSES, 1);
  return 0;
}
int
ui_update ()
{
  mt_clrscreen ();
  drawingBoxes ();
  drawingTexts ();
  drawingMemory ();
  drawingAccumulator ();
  drawingInstructionCounter ();
  drawingOperation ();
  drawingFlags ();
  drawingBigChar ();
  mt_gotoXY (1, 23);
  printf ("Input/Output:\n");
  return 0;
}
int
ui_moveCurrMemPointer (enum keys key)
{
  printf ("%d", key);
  switch (key)
    {
    case KEY_UP:
      (currMemCell <= 9) ? (currMemCell = 90 + currMemCell)
                         : (currMemCell -= 10);
      return 0;
    case KEY_RIGHT:
      (!((currMemCell + 1) % 10)) ? (currMemCell -= 9) : (currMemCell += 1);
      return 0;
    case KEY_DOWN:
      (currMemCell >= 90) ? (currMemCell = currMemCell - 90)
                          : (currMemCell += 10);
      return 0;
    case KEY_LEFT:
      (!(currMemCell % 10)) ? (currMemCell += 9) : (currMemCell -= 1);
      return 0;

    case KEY_L:
      break;
    case KEY_S:
      break;
    case KEY_R:
      break;
    case KEY_T:
      break;
    case KEY_I:
      break;
    case KEY_F5:
      break;
    case KEY_F6:
      break;
    case KEY_ESC:
      break;
    case KEY_ENTER:
      break;
    case KEY_OTHER:
      break;
    }
  return -1;
}
int
ui_setMCellValue ()
{
  char buffer[10];
  printf ("Set value of the memory cell \033[38;5;%dm%d\033[0m\n",
          LIGHT_MAGENT, currMemCell);
  printf ("Enter value \033[38;5;%dmHEX\033[0m format: ", MAGENT);
  fgets (buffer, 10, stdin);
  if (buffer[strlen (buffer) - 1] != '\n')
    clearBuffIn ();
  if (!checkCorrectInput (buffer))
    {
      ui_messageOutput ((char *)"Invalid input", LIME);
      return -1;
    }
  long int number;
  char *tmp;
  if (buffer[0] == '+')
    {
      number = strtol (&buffer[1], &tmp, 16);
      if (number > 0x3FFF)
        {
          ui_messageOutput (
              (char *)"The command value must not exceed 14 bits (0x3FFF)",
              LIME);
          return -1;
        }
      sc_memorySet (currMemCell, (short int)number);
    }
  else
    {
      number = strtol (buffer, &tmp, 16);
      if (number > 0x3FFF)
        {
          ui_messageOutput (
              (char *)"The value must not exceed 14 bits (0x3FFF)", LIME);
          return -1;
        }
      number = (1 << 14) | number;
      sc_memorySet (currMemCell, (short int)number);
    }
  return 0;
}
int
ui_saveMemory ()
{
  char filename[102];
  printf ("Saving file...\n");
  printf ("Enter the file name to save > ");
  mt_setfgcolor (GREEN);
  fgets (filename, 102, stdin);
  mt_setdefaultcolorsettings ();
  if (filename[strlen (filename) - 1] != '\n')
    {
      printf ("\033[38;5;%dmThe file name is too long. The length is trimmed "
              "to the first 100 characters.\033[0m\n",
              BLUE);
      clearBuffIn ();
    }
  else
    filename[strlen (filename) - 1] = '\0';
  if (sc_memorySave (filename))
    {
      ui_messageOutput ((char *)"Failed to save memory", LIME);
      return -1;
    }
  else
    ui_messageOutput ((char *)"Successful save", GREEN);
  return 0;
}
int
ui_loadMemory ()
{
  char filename[102];
  printf ("Loading file...\n");
  printf ("Enter the file name to load > ");
  mt_setfgcolor (GREEN);
  fgets (filename, 102, stdin);
  mt_setdefaultcolorsettings ();
  if (filename[strlen (filename) - 1] != '\n')
    {
      ui_messageOutput ((char *)"The name of the file to open is too long (up "
                                "to 100 characters are allowed)",
                        SUN);
      clearBuffIn (); // очистка потока ввода
      return -1;
    }
  filename[strlen (filename) - 1] = '\0';
  if (sc_memoryLoad (filename))
    {
      ui_messageOutput ((char *)"Failed to load memory", LIME);
      return -1;
    }
  else
    ui_messageOutput ((char *)"Successful load", GREEN);
  return 0;
}
int
ui_setICounter ()
{
  char buffer[10];
  printf ("Set a value \033[38;5;%dm\"InstructionCounter\"\033[0m between "
          "\033[38;5;%dm0x0\033[0m and \033[38;5;%dm0x63\033[0m inclusive\n",
          GREEN, LIME, LIME);
  printf ("Enter value in \033[38;5;%dmHEX\033[0m format > ", MAGENT);
  fgets (buffer, 10, stdin);
  if (buffer[strlen (buffer) - 1] != '\n')
    clearBuffIn (); // очистка потока ввода
  if (!checkCorrectInput (buffer))
    {
      ui_messageOutput ((char *)"Invalid input", LIME);
      return -1;
    }
  long int number;
  char *tmp;
  if (buffer[0] == '+')
    number = strtol (&buffer[1], &tmp, 16);
  else
    number = strtol (buffer, &tmp, 16);
  if (number > MEM_SIZE - 1)
    {
      ui_messageOutput ((char *)"Exceeded the allowed range", LIME);
      return -1;
    }
  checkSystem = number;
  return 0;
}
int
ui_setAccumulator ()
{

  char buffer[10];
  printf ("Set a value \033[38;5;%dm\"Accumulator\"\033[0m", GREEN);
  printf ("\nEnter value in \033[38;5;%dmHEX\033[0m format > ", BROWN);
  fgets (buffer, 10, stdin);
  if (buffer[strlen (buffer) - 1] != '\n')
    clearBuffIn ();
  else
    buffer[strlen (buffer) - 1] = '\0';
  unsigned short int res = 0;
  int i;
  if (buffer[0] == '+')
    {
      ui_messageOutput ((char *)"Invalid input", RED);
      return -1;
    }
  else
    {
      res |= (1 << 14);
      if (buffer[0] == '-')
        {
          i = 1;
          res |= (1 << 13);
        }
      else
        i = 0;
    }
  if (!check_HEX (&buffer[i]))
    {
      ui_messageOutput ((char *)"Invalid input", RED);
      return -1;
    }
  long int number;
  char *tmp;
  number = strtol (&buffer[i], &tmp, 16);
  if (buffer[0] == '+')
    {
      if (number > 0x3FFF)
        {
          ui_messageOutput (
              (char *)"The command value must not exceed 14 bits (0x3FFF)",
              RED);
          return -1;
        }
      else
        {
          number &= 0x3FFF;
          if ((number >> 8) > 0x7F)
            {
              ui_messageOutput (
                  (char *)"The command cannot be more than 7 bits (0x7F)",
                  RED);
              return -1;
            }
          if ((number & 0xFF) > 0x7F)
            {
              ui_messageOutput (
                  (char *)"The operand cannot be more than 7 bits (0x7F)",
                  RED);
              return -1;
            }
          else
            {
              int value = 0;
              if (sc_commandEncode ((int)((number >> 8)), (int)(number & 0xFF),
                                    &value))
                return -1;
              res |= value;
            }
        }
    }
  else
    {
      if ((number > 0x2000) || ((number > 0x1FFF) && (buffer[0] != '-')))
        {
          ui_messageOutput ((char *)"The valid range for the value of the "
                                    "number from -0x2000 to 0x1FFF inclusive",
                            RED);
          return -1;
        }
      if (buffer[0] == '-')
        {
          number = ~number + 1;
          if (!((number >> 13) & 1))
            res &= ~(1 << 13);
        }
      number &= 0x1FFF;
      res |= number;
    }
  ACCUM = res;
  return 0;
}
int
drawingBoxes ()
{
  if (bc_box (1, 1, 61, 12)) // Окно Memory
    return -1;
  if (bc_box (62, 1, 22, 3)) // Окно accumulator
    return -1;
  if (bc_box (62, 4, 22, 3)) // Окно instructionCounter
    return -1;
  if (bc_box (62, 7, 22, 3)) // Окно Operation
    return -1;
  if (bc_box (62, 10, 22, 3)) // Окно Flags
    return -1;
  if (bc_box (1, 13, 52, 10)) // Окно BigChars
    return -1;
  if (bc_box (53, 13, 31, 10)) // Окно Keys
    return -1;

  return 0;
}
int
drawingTexts ()
{
  /* Заголовки */
  mt_gotoXY (30, 1);
  printf (" Memory ");
  mt_gotoXY (66, 1);
  printf (" Accumulator ");
  mt_gotoXY (63, 4);
  printf (" InstructionCounter ");
  mt_gotoXY (67, 7);
  printf (" Operation ");
  mt_gotoXY (69, 10);
  printf (" Flags ");
  mt_gotoXY (54, 13);
  printf (" Keys: ");

  /* HotKeys */
  char *hotK[]
      = { (char *)"CAPS REQUIRED!",   (char *)"L  - Load",
          (char *)"S  - Save",        (char *)"R  - Run (SIGALRM)",
          (char *)"T  - Step",        (char *)"I  - Reset (SIGUSR1)",
          (char *)"F5 - Accumulator", (char *)"F6 - Instruction Counter" };

  for (int i = 0; i < sizeof (hotK) / sizeof (*hotK); ++i)
    {
      mt_gotoXY (54, i + 14);
      printf ("%s", hotK[i]);
    }
  return 0;
}
int
drawingMemory ()
{
  for (int i = 0; i < 10; ++i)
    for (int j = 0; j < 10; ++j)
      {
        mt_gotoXY (2 + (5 * j + j), 2 + i);
        int tmp = memory[i * 10 + j];
        if ((i * 10 + j) == currMemCell)
          mt_setbgcolor (GREEN);
        else
          mt_setbgcolor (WHITE);
        if ((tmp >> 14) & 1)
          printf (" %04X", tmp & (~(1 << 14)));
        else
          printf ("+%04X", tmp);
      }
  return 0;
}
int
drawingAccumulator ()
{
  mt_gotoXY (71, 2);
  printf ("%04X", ACCUM);
  return 0;
}
int
drawingOperation ()
{
  mt_gotoXY (71, 7);
  return 0;
}
int
drawingInstructionCounter ()
{
  mt_gotoXY (71, 5);
  printf ("%04X", checkSystem);
  return 0;
}
int
drawingFlags ()
{
  // char tmp[] = { 'O', 'Z', 'M', 'I', 'C' };
  // char tmp[] = { "⚰", "🧨", "🗿", "⛔", "🛑" };
  char *tmp[] = { (char *)"\u26B0", (char *)"\U0001F9E8", (char *)"\U0001F5FF",
                  (char *)"\U0001F6AB", (char *)"\U0001F6D1" };
  for (int i = 0; i < SC_REG_SIZE; ++i)
    {
      int value;
      if (sc_regGet (i, &value))
        return -1;
      mt_gotoXY (68 + (i * 2), 11);
      if (value)
        {
          mt_setfgcolor (MAGENT);
          printf ("%s", tmp[i]);
        }
      else
        {
          mt_setfgcolor (SUN);
          printf ("%s", tmp[i]);
        }
      mt_setdefaultcolorsettings ();
    }
  return 0;
}
int
drawingBigChar ()
{
  int tmp;
  sc_memoryGet (currMemCell, &tmp);
  if (!((tmp >> 14) & 1))
    bc_printbigchar (bc[16], 2, 14, GREEN, BLACK); // +
  tmp &= 0x3FFF;
  for (int i = 0; i < 4; ++i)
    {
      int ch = (tmp & (0xF << (4 * (3 - i)))) >> (4 * (3 - i));
      bc_printbigchar (bc[ch], 2 + 8 * (i + 1) + 2 * (i + 1), 14, GREEN,
                       BLACK);
    }
  return 0;
}
int
checkCorrectInput (const char buffer[10])
{
  return 1;
}
int
ui_messageOutput (char *str, enum colors color)
{
  printf ("\033[38;5;%dm%s\033[0m", color, str);
  rk_pause (25);
  return 0;
}
int
clearBuffIn ()
{
  int c;
  do
    {
      c = getchar ();
    }
  while (c != '\n' && c != '\0');
  return 0;
}