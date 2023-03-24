#include <stdint.h>
#include <stdio.h>
// #include <stdin.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

// #define OTHER_ERROR -1
#define OVERFLOW 0
#define DIVISION_BY_ZERO 1
#define OUT_OF_MEMORY 2
#define IGNORING_CLOCK_PULSES 3
#define INCORRECT_COMMAND 4
#define REG_SIZE 5

#define UI_SHADE "▒" // Штриховка
#define UI_LU "┏"    // Левый верхний угол
#define UI_RU "┓"    // Правый верхний угол
#define UI_RD "┗"    // Правый нижний угол
#define UI_LD "┛"    // Левый нижний угол
#define UI_HOR "━"   // Горизонтальная линия
#define UI_VER "┃"   // Вертикальная линия

extern unsigned char *memory;
extern unsigned char checkSystem;
extern unsigned short ACCUM;
extern unsigned char IP;

enum colors
{
  RED,
  GREEN,
  BLUE,
  YELLOW,
  MANGETA,
  CYAN,
  WHITE,
  BLACK
};

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
/*                        myTerm.h                         */
int mt_clrscreen ();
int mt_gotoXY (int numRow, int numCol);
int mt_getscreensize (int *rows, int *cols);
int mt_setfgcolor (enum colors);
int mt_setbgcolor (enum colors);
/*                        myBigChars.h                     */
int bc_printA (char *str);
int bc_box (int x1, int y1, int width, int height);
int bc_printbigchar (int *big, int x, int y, enum colors main,
                     enum colors secondary);
int bc_setbigcharpos (int *big, int x, int y, int value);
int bc_getbigcharpos (int *big, int x, int y, int *value);
int bc_bigcharwrite (int fd, int *big, int count);
int bc_bigcharread (int fd, int *big, int need_count, int *count);