#include <include.h>

int rk_pause(int time) {
    fflush(stdout); // очистка потока вывода
    char buffer[5] = "\0";
    rk_myTermRegime(0, time, 0, 0, 0);
    read(fileno(stdin), buffer, 5);
    rk_myTermRestore();
    return 0;
}
int print_norm(char* str, enum colors color) {
    printf("\033[38;5;%dm%s\033[0m", color, str);
    rk_pause(25);
    return 0;
}