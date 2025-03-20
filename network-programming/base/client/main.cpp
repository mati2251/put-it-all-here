#include <iostream>
#include <csignal>
#include <netinet/in.h>

#define BUFFER_SIZE 100

int main(int argc, char *argv[]) {
    unsigned short port_number = htons(3000);
    sockaddr_in address{
            .sin_family = AF_INET,
            .sin_port = port_number,
            .sin_addr = {.s_addr = INADDR_ANY}
    };
    int source = socket(
            AF_INET,
            SOCK_STREAM,
            IPPROTO_TCP
    );
    auto err = connect(
            source,
            (sockaddr *) &address,
            sizeof(address)
    );
    if (err == -1) {
        perror("Error connecting to server-tcp");
        return 1;
    }
    char buffer[BUFFER_SIZE];
    size_t bytes_read;
    while ((bytes_read = read(source, buffer, BUFFER_SIZE)) > 0) {
        if (bytes_read == -1) {
            perror("Error reading file");
            return 1;
        }
        err = (int) write(1, buffer, bytes_read);
        if (err == -1) {
            perror("Error writing to stdout");
            return 1;
        }
    }
    shutdown(source, SHUT_RDWR);
    close(source);
    return 0;
}
