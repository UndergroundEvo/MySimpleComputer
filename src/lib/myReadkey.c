#include "myReadkey.h"
struct termios save;

int rk_readKey(enum keys* key) {
    fflush(stdout); // очистка потока вывода
    char buffer[5] = "\0";
    rk_myTermRegime(0, 30, 0, 0, 0);
    read(fileno(stdin), buffer, 5);
    rk_myTermRestore();
    if (key == NULL)
    {
        return -1;
    }
    if (buffer[0] == '\E')
    {
        switch (buffer[1])
        {
        case '\0':
            *key = KEY_ESC;
            break;
        case '[':
            switch (buffer[2])
            {
            case 'A':
                *key = KEY_UP;
                break;
            case 'B':
                *key = KEY_DOWN;
                break;
            case 'C':
                *key = KEY_RIGHT;
                break;
            case 'D':
                *key = KEY_LEFT;
                break;
            case '5':
                *key = KEY_F5;
                break;
            case '1':
                if (buffer[3] == '7' && buffer[4] == '~')
                    *key = KEY_F6;
                else if (buffer[3] == '5' && buffer[4] == '~')
                    *key = KEY_F5;
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
    }
    else if (buffer[0] == '\n' && buffer[1] == '\0')
    {
        *key = KEY_ENTER;
    }
    else
    {
        switch (buffer[0])
        {
        case 'L':
            *key = KEY_L;
            break;
        case 'S':
            *key = KEY_S;
            break;
        case 'R':
            *key = KEY_R;
            break;
        case 'T':
            *key = KEY_T;
            break;
        case 'I':
            *key = KEY_I;
            break;
        default:
            break;
        }
    }
    return 0;
}
int rk_myTermSave() {
    if (tcgetattr(fileno(stdin), &save))
        return -1;
    return 0;
}
int rk_myTermRestore() {
    tcsetattr(fileno(stdin), TCSAFLUSH, &save);
    return 0;
}
int rk_myTermRegime(int regime, unsigned int vtime, unsigned int vmin, int echo, int sigint) {
    struct termios curr;
    tcgetattr(fileno(stdin), &curr);
    if (regime)
        curr.c_lflag |= ICANON;
    else {
        curr.c_lflag &= ~ICANON;
        sigint ? (curr.c_lflag |= ISIG) : (curr.c_lflag &= ~ISIG);
        echo ? (curr.c_lflag |= ECHO) : (curr.c_lflag &= ~ECHO);
        curr.c_cc[VMIN] = vmin;
        curr.c_cc[VTIME] = vtime;
    }
    tcsetattr(0, TCSAFLUSH, &curr);
    return 0;
}
