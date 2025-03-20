#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
    int desc;
    long rozm;

    if (argc < 2){
        fprintf(stderr, "Za malo argumentow. Uzyj:\n");
        fprintf(stderr, "%s <nazwa pliku>\n", argv[0]);
        exit(1);
    }

    desc = open(argv[1], O_RDONLY);
    if (desc == -1){
        perror("Blad otwarcia pliku");
        exit(1);
    }

    rozm = lseek(desc, 0, SEEK_END);
    if (rozm == -1){
        perror("Blad w pozycjonowaniu");
        exit(1);
    }

    printf("Rozmiar pliku %s: %ld\n", argv[1], rozm);

    if (close(desc) == -1){
        perror("Blad zamkniecia pliku");
        exit(1);
    }

    exit(0);
}
