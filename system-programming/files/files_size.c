#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
    int desc, i;
    long rozm;

    if (argc < 2){
        fprintf(stderr, "Za malo argumentow. Uzyj:\n");
        fprintf(stderr, "%s <nazwa pliku> ...\n", argv[0]);
        exit(1);
    }

    for (i=1; i<argc; i++) {
        desc = open(argv[i], O_RDONLY);
        if (desc == -1){
            char s[50];
            sprintf(s, "Blad otwarcia pliku %s", argv[i]);
            perror(s);
            continue;
        }

        rozm = lseek(desc, 0, SEEK_END);
        if (rozm == -1){
            perror ("Blad w pozycjonowaniu");
            exit(1);
        }

        printf("Rozmiar pliku %s: %ld\n", argv[i], rozm);

        if (close(desc) == -1){
            perror("Blad zamkniecia pliku");
            exit(1);
        }
    }

    exit(0);
}