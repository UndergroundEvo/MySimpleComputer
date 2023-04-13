#ifndef MYBIGCHARS_H
#define MYBIGCHARS_H

#include "include.h"
#include "myTerm.h"

#define ACS_CKBOARD '@' // Штриховка
#define ACS_UL '#'      // Левый верхний угол
#define ACS_UR '#'      // Правый верхний угол
#define ACS_DR '#'      // Правый нижний угол
#define ACS_DL '#'      // Левый нижний угол
#define ACS_H '*'       // Горизонтальная линия
#define ACS_V '*'       // Вертикальная линия

/* как это поправить?????? */

// #define ACS_CKBOARD '▓' // Штриховка
// #define ACS_UL '┏'      // Левый верхний угол
// #define ACS_UR '┓'      // Правый верхний угол
// #define ACS_DR '┛'      // Правый нижний угол
// #define ACS_DL '┗'      // Левый нижний угол
// #define ACS_H '━'       // Горизонтальная линия
// #define ACS_V '┃'       // Вертикальная линия

extern unsigned int bc[][2];

int bc_printA (char ch);
int bc_box (int x, int y, int width, int height);
int bc_printbigchar (unsigned int *big, int x, int y, enum colors colorFG,
                     enum colors colorBG);
int bc_setbigcharpos (unsigned int *big, int x, int y, int value);
int bc_getbigcharpos (unsigned int *big, int x, int y, int *value);
int bc_bigcharwrite (int fd, unsigned int *big, int count);
int bc_bigcharread (int fd, unsigned int *big, int need_count, int *count);
#endif