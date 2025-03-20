#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void f(int sig_num){
    printf("Przechwycenie syg. nr %d\n", sig_num);
}

int main(){
    printf("Domyslna obsluga sygnalu\n");
    signal(SIGINT, SIG_DFL);
    sleep(5);
    printf("Ignorowanie sygnalu\n");
    signal(SIGINT, SIG_IGN);
    sleep(5);
    printf("Przechwytywanie sygnalu\n");
    signal(SIGINT, f);
    sleep(5);
}

