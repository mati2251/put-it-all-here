#include <stdio.h>
#include <unistd.h>
#include <signal.h>

volatile int y = 0;

void f(int i) {
    printf("Przechwycenie syg.\n");
//    x++;
}

int main() {
    signal(SIGFPE, f);
    int x = 1 / y;
    printf("x=%d\n", x);
    return 0;
};