// #include "myTerm.hpp"
#include <mySimpleComputer.h>

#define UI_SHADE "▒" // Штриховка
#define UI_LU "┏"    // Левый верхний угол
#define UI_RU "┓"    // Правый верхний угол
#define UI_RD "┗"    // Правый нижний угол
#define UI_LD "┛"    // Левый нижний угол
#define UI_HOR "━"   // Горизонтальная линия
#define UI_VER "┃"   // Вертикальная линия

int bc_printA (char *str);
int bc_box (int x1, int y1, int width, int height);
int bc_printbigchar (int *big, int x, int y, enum colors main,
                     enum colors secondary);
int bc_setbigcharpos (int *big, int x, int y, int value);
int bc_getbigcharpos (int *big, int x, int y, int *value);
int bc_bigcharwrite (int fd, int *big, int count);
int bc_bigcharread (int fd, int *big, int need_count, int *count);