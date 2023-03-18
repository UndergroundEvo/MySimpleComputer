﻿#include <mySimpleComputer.h>

const unsigned char MEM_SIZE = 100;

unsigned char *memory;
unsigned char checkSystem;

int
sc_memoryInit ()
{
  memory = (unsigned char *)calloc (MEM_SIZE, sizeof (unsigned char));
  for (int i = 0; i < MEM_SIZE; i++)
    memory[i] = 0;
  return 0;
}

int
sc_memorySet (int address, int value)
{
  if (address < 0 || address >= MEM_SIZE)
    {
      printf ("! Невозможно задать заначение / Указан не верный адрес! \n");
      sc_regSet (OUT_OF_MEMORY, 1);
    }
  else
    memory[address] = value;
  return 0;
}

int
sc_memoryGet (int address, int *value)
{
  if (address < 0 || address >= MEM_SIZE)
    {
      printf ("! Невозможно получить заначение / Указан не верный адрес! \n");
      sc_regSet (OUT_OF_MEMORY, 1);
    }
  else
    *value = memory[address];
  return 0;
}

int
sc_memorySave (char *filename)
{
  FILE *f;
  if (!filename)
    {
      sc_regSet (OUT_OF_MEMORY, 1);
    }
  else
    {
      f = fopen (filename, "wb");
      fwrite (memory, sizeof (unsigned char), 100, f);
      fclose (f);
    }
  return 0;
}

int
sc_memoryLoad (char *filename)
{
  FILE *f;
  if (!filename)
    {
      sc_regSet (OUT_OF_MEMORY, 1);
    }
  else
    {
      f = fopen (filename, "rb");
      fread (memory, sizeof (unsigned char), 100, f);
      fclose (f);
    }
  return 0;
}

int
sc_regInit (void)
{
  checkSystem = 0;
  return 0;
}

int
sc_regSet (int reg, int value)
{
  if (reg < 0 || reg >= REG_SIZE)
    printf ("Указан неверный флаг! \n");
  if (value != 0 && value != 1)
    printf ("Только значения 1 и 0 \n");
  value == 1 ? (checkSystem |= (1 << reg)) : (checkSystem &= ~(1 << reg));
  return 0;
}

int
sc_regGet (int reg, int *value)
{
  if (reg < 0 || reg >= REG_SIZE)
    printf ("Нет данного регистра \n");
  else
    *value = checkSystem & reg;
  return 0;
}

int
sc_commandEncode (int command, int operand, int *value)
{
  *value = 0;
  *value |= (command & 127);
  *value = *value << 7;
  *value |= (operand & 127);
  return 0;
}

int
sc_commandDecode (int value, int *command, int *operand)
{
  if ((value >> 14) != 0) {
      sc_regSet (INCORRECT_COMMAND, 4);
      return (-1);
  }
  *operand = (value & 127);
  *command = ((value >> 7) & 127);
  return 0;
}
