#ifndef MYSIMPLECOMPUTER_H
#define MYSIMPLECOMPUTER_H

#include "include.h"

#define OVERFLOW 0
#define DIVISION_BY_ZERO 1
#define OUT_OF_MEMORY 2
#define IGNORING_CLOCK_PULSES 3
#define INCORRECT_COMMAND 4
#define REG_SIZE 5

extern const unsigned char MEM_SIZE;
extern unsigned char *memory;
extern unsigned char checkSystem;
extern const short int SC_REG_SIZE;
extern unsigned short ACCUM;
extern unsigned char IP;

int sc_memoryInit ();
int sc_memorySet (int address, int value);
int sc_memoryGet (int address, int *value);
int sc_memorySave (char *filename);
int sc_memoryLoad (char *filename);
int sc_regInit (void);
int sc_regSet (int register, int value);
int sc_regGet (int register, int *value);
int sc_commandEncode (int command, int operand, int *value);
int sc_commandDecode (int value, int *command, int *operand);
#endif