#include "ALU.h"

int
ALU (int command, int operand)
{
  int value;
  switch (command)
    {
    case ADD:
      if (sc_memoryGet (operand, &value))
        {
          sc_regSet (OUT_OF_MEMORY, 1);
          return -1;
        }
      if (addALU (value))
        return -1;
      break;
    case SUB:
      if (sc_memoryGet (operand, &value))
        {
          sc_regSet (OUT_OF_MEMORY, 1);
          return -1;
        }
      if (subALU (value))
        return -1;
      break;
    case DIVIDE:
      if (sc_memoryGet (operand, &value))
        {
          sc_regSet (OUT_OF_MEMORY, 1);
          return -1;
        }
      if (divALU (value))
        return -1;
      break;
    case MUL:
      if (sc_memoryGet (operand, &value))
        {
          sc_regSet (OUT_OF_MEMORY, 1);
          return -1;
        }
      if (mulALU (value))
        return -1;
      break;
    case OR:
      if (sc_memoryGet (operand, &value))
        {
          sc_regSet (OUT_OF_MEMORY, 1);
          return -1;
        }
      if (orALU (value))
        return -1;
      break;
      // default:
      //   sc_regSet (FIVE, 1);
      //   return -1;
    }
  return 0;
}
int
addALU (int value)
{
  int accum_copy;
  int value_copy;
  int res;
  accum_copy = ACCUM & 0x3FFF;
  if (ACCUM & 0x4000)
    accum_copy = -accum_copy;
  value_copy = value & 0x3FFF;
  if (value & 0x4000)
    value_copy = -value_copy;
  res = accum_copy + value_copy;
  if (res < 0)
    {
      res = -res;
      res |= 0x4000;
    }
  ACCUM = res & 0x7FFF;
  return 0;
}
int
subALU (int value)
{
  int accum_copy;
  int value_copy;
  int res;
  accum_copy = ACCUM & 0x3FFF;
  if (ACCUM & 0x4000)
    accum_copy = -accum_copy;
  value_copy = value & 0x3FFF;
  if (value & 0x4000)
    value_copy = -value_copy;
  res = accum_copy - value_copy;
  if (res < 0)
    {
      res = -res;
      res |= 0x4000;
    }
  ACCUM = res & 0x7FFF;
  return 0;
}
int
divALU (int value)
{
  int accum_copy;
  int value_copy;
  int res;
  if (value == 0)
    {
      sc_regSet (DIVISION_BY_ZERO, 1);
      return -1;
    }
  accum_copy = ACCUM & 0x3FFF;
  if (ACCUM & 0x4000)
    accum_copy = -accum_copy;
  value_copy = value & 0x3FFF;
  if (value & 0x4000)
    value_copy = -value_copy;
  res = accum_copy / value_copy;
  if (res < 0)
    {
      res = -res;
      res |= 0x4000;
    }
  ACCUM = res & 0x7FFF;
  return 0;
}
int
mulALU (int value)
{
  int accum_copy;
  int value_copy;
  int res;
  accum_copy = ACCUM & 0x3FFF;
  if (ACCUM & 0x4000)
    accum_copy = -accum_copy;
  value_copy = value & 0x3FFF;
  if (value & 0x4000)
    value_copy = -value_copy;
  res = accum_copy * value_copy;
  if (res < 0)
    {
      res = -res;
      res |= 0x4000;
    }
  ACCUM = res & 0x7FFF;
  return 0;
}
int
orALU (int value)
{
  int accum_copy;
  int value_copy;
  int res;
  accum_copy = ACCUM & 0x3FFF;
  if (ACCUM & 0x4000)
    accum_copy = -accum_copy;
  value_copy = value & 0x3FFF;
  if (value & 0x4000)
    value_copy = -value_copy;
  res = accum_copy || value_copy;
  if (res < 0)
    {
      res = -res;
      res |= 0x4000;
    }
  ACCUM = res & 0x7FFF;
  return 0;
}