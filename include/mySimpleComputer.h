#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

#define OVERFLOW 0
#define DIVISION_BY_ZERO 1
#define OUT_OF_MEMORY 2
#define IGNORING_CLOCK_PULSES 3
#define INCORRECT_COMMAND 4
#define REG_SIZE 5

extern unsigned char *memory;
extern unsigned char checkSystem;
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
