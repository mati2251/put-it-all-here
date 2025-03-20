#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define MAX 512

int main(int argc, char* argv[]){
    char buf[MAX];
    int desc_zrod, desc_cel;
    int lbajt;

    if (argc<3){
        fprintf(stderr, "Za malo argumentow. Uzyj:\n");
        fprintf(stderr, "%s <plik zrodlowy> <plik docelowy>\n", argv[0]);
        exit(1);
    }

    desc_zrod = open(argv[1], O_RDONLY);
    if (desc_zrod == -1){
        perror("Blad otwarcia pliku zrodlowego");
        exit(1);
    }

    desc_cel = creat(argv[2], 0640);
    if (desc_cel == -1){
        perror("Blad utworzenia pliku docelowego");
        exit(1);
    }

    while((lbajt = read(desc_zrod, buf, MAX)) > 0){
        if (write(desc_cel, buf, lbajt) == -1){
            perror("Blad zapisu pliku docelowego");
            exit(1);
        }
    }
    if (lbajt == -1){
        perror("Blad odczytu pliku zrodlowego");
        exit(1);
    }

    if (close(desc_zrod) == -1 || close(desc_cel) == -1){
        perror("Blad zamkniecia pliku");
        exit(1);
    }

    exit(0);
}