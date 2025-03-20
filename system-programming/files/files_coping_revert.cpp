#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>


#define MAX 512

using namespace std;

string revert(string str){
    int len = str.length();
    int n=len-1;
    for(int i=0;i<(len/2);i++){
        swap(str[i],str[n]);
        n = n-1;
    }
    return str;
}

int main(int argc, char *argv[]) {
    char buf[MAX];
    int desc_zrod, desc_cel;
    int lbajt;

    if (argc < 3) {
        fprintf(stderr, "Za malo argumentow. Uzyj:\n");
        fprintf(stderr, "%s <plik zrodlowy> <plik docelowy>\n", argv[0]);
        exit(1);
    }

    desc_zrod = open(argv[1], O_RDONLY);
    if (desc_zrod == -1) {
        perror("Blad otwarcia pliku zrodlowego");
        exit(1);
    }

    desc_cel = creat(argv[2], 0640);
    if (desc_cel == -1) {
        perror("Blad utworzenia pliku docelowego");
        exit(1);
    }
    int actual_position = lseek(desc_zrod, 0, SEEK_END) - MAX;
    int how_many_read = MAX;

    if (actual_position <= 0) {
        how_many_read += actual_position;
        actual_position = lseek(desc_zrod, 0, SEEK_SET);
    } else {
        actual_position = lseek(desc_zrod, actual_position, SEEK_SET) - MAX;
    }
    while ((lbajt = read(desc_zrod, buf, how_many_read)) > 0) {
        if (actual_position <= 0) {
            how_many_read += actual_position;
            actual_position = lseek(desc_zrod, 0, SEEK_SET);
        } else {
            actual_position = lseek(desc_zrod, actual_position, SEEK_SET) - MAX;
        }
        if (write(desc_cel, revert(buf).c_str(), lbajt) == -1) {
            perror("Blad zapisu pliku docelowego");
            exit(1);
        }
        if (how_many_read != MAX)
            break;
    }
    if (lbajt == -1) {
        perror("Blad odczytu pliku zrodlowego");
        exit(1);
    }

    if (close(desc_zrod) == -1 || close(desc_cel) == -1) {
        perror("Blad zamkniecia pliku");
        exit(1);
    }

    exit(0);
}