#ifndef MYREADKEY_HPP
#define MYREADKEY_HPP

#include "include.h"

extern struct termios save;

enum keys
{
    KEY_L,
    KEY_S,
    KEY_R,
    KEY_T,
    KEY_I,
    KEY_F5,
    KEY_F6,
    KEY_UP,
    KEY_DOWN,
    KEY_RIGHT,
    KEY_LEFT,
    KEY_ESC,
    KEY_ENTER,
    KEY_OTHER,
};

int rk_readKey(enum keys* key);
int rk_myTermSave();
int rk_myTermRestore();
int rk_myTermRegime(int regime, unsigned int vtime, unsigned int vmin, int echo, int sigint);
#endif