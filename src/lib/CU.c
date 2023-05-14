#include "CU.h"

int
CU ()
{
  int value;
  int command;
  int operand;
  sc_memoryGet (IP, &value);
  if (sc_commandDecode (value & 0x3FFF, &command, &operand))
    {
      sc_regSet (INCORRECT_COMMAND, 1);
      return -1;
    }
  switch (command)
    {
    case READ:
      if (readCU (operand))
        return -1;
      break;
    case WRITE:
      if (writeCU (operand))
        return -1;
      break;
    case LOAD:
      if (loadCU (operand))
        return -1;
      break;
    case STORE:
      if (storeCU (operand))
        return -1;
      break;
    case JUMP:
      if (jumpCU (operand))
        return -1;
      break;
    case JNEG:
      if (jnegCU (operand))
        return -1;
      break;
    case JZ:
      if (jzCU (operand))
        return -1;
      break;
    case HALT:
      return -1;
    default:
      if (ALU (command, operand))
        return -1;
      break;
    }
  return 0;
}
int
readCU (int operand)
{
  char buffer[10] = { 0 };
  int number;
  rk_myTermRestore ();
  // RESET_CURSOR;
  read (0, buffer, sizeof (buffer));
  // CLEAR_INPUT;
  fflush (0);
  rk_myTermSave ();
  rk_myTermRegime (0, 30, 0, 0, 0);
  if (buffer[0] != '+' && buffer[0] != '-')
    return -1;
  number = (int)strtol (&buffer[1], NULL, 16);
  if (number > 0x3FFF)
    return -1;
  if (buffer[0] == '-')
    number = number | 0x4000;
  sc_memorySet (operand, number);
  return 0;
}
int
writeCU (int operand)
{
  int value;
  int command;
  char buf[6];
  if (sc_memoryGet (operand, &value)
      || sc_commandDecode (value & 0x3FFF, &command, &operand))
    {
      sc_regSet (INCORRECT_COMMAND, 1);
      return -1;
    }
  snprintf (buf, 6, "%c%02X%02X", (value & 0x4000) ? '-' : '+', command,
            operand);
  // RESET_CURSOR;
  write (1, buf, 5);
  getchar ();
  // CLEAR_INPUT;
  return 0;
}
int
loadCU (int operand)
{
  int value;
  if (sc_memoryGet (operand, &value))
    {
      sc_regSet (INCORRECT_COMMAND, 1);
      return -1;
    }
  ACCUM = value;
  return 0;
}
int
storeCU (int operand)
{
  if (operand < 0 || operand > 99)
    {
      sc_regSet (OUT_OF_MEMORY, 1);
      return -1;
    }
  if (sc_memorySet (operand, ACCUM))
    return -1;
  return 0;
}
int
jumpCU (int operand)
{
  if (operand < 0 || operand > 99)
    {
      sc_regSet (OUT_OF_MEMORY, 1);
      return -1;
    }
  IP = operand - 1;
  return 0;
}
int
jnegCU (int operand)
{
  if ((ACCUM >> 14) & 1)
    {
      if (operand < 0 || operand > 99)
        {
          sc_regSet (OUT_OF_MEMORY, 1);
          return -1;
        }
      IP = operand - 1;
    }
  return 0;
}
int
jzCU (int operand)
{
  if ((ACCUM & 0x3FFF) == 0)
    {
      if (operand < 0 || operand > 99)
        {
          sc_regSet (OUT_OF_MEMORY, 1);
          return -1;
        }
      IP = operand - 1;
    }
  return 0;
}