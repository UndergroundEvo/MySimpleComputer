#ifndef MYBIGCHARS_H
#define MYBIGCHARS_H

#include "include.h"

#define ACS_CKBOARD "\u2593" // Штриховка
#define ACS_UL "\u250F"      // Левый верхний угол
#define ACS_UR "\u2513"      // Правый верхний угол
#define ACS_DR "\u251B"      // Правый нижний угол
#define ACS_DL "\u2517"      // Левый нижний угол
#define ACS_H "\u2501"       // Горизонтальная линия
#define ACS_V "\u2503"       // Вертикальная линия

// #define ACS_CKBOARD '▓' // Штриховка
// #define ACS_UL '┏'      // Левый верхний угол
// #define ACS_UR '┓'      // Правый верхний угол
// #define ACS_DR '┛'      // Правый нижний угол
// #define ACS_DL '┗'      // Левый нижний угол
// #define ACS_H '━'       // Горизонтальная линия
// #define ACS_V '┃'       // Вертикальная линия

extern unsigned int bc[][2];
extern enum colors color;

int bc_printA (char ch);
int bc_box (int x, int y, int width, int height);
int bc_printbigchar (unsigned int *big, int x, int y, enum colors colorFG,
                     enum colors colorBG);
int bc_setbigcharpos (unsigned int *big, int x, int y, int value);
int bc_getbigcharpos (unsigned int *big, int x, int y, int *value);
int bc_bigcharwrite (int fd, unsigned int *big, int count);
int bc_bigcharread (int fd, unsigned int *big, int need_count, int *count);

#define WRITE_STR(str) printf ("\033(0%c\033(B", str)
#define WRITE_WCHAR(str) printf (str)
#endif