#include <iostream>
#include <csignal>
#include <netinet/in.h>
#include <ctype.h>

int main() {
    sockaddr_in serv_addr = {
            .sin_family = AF_INET,
            .sin_port = htons(3000),
            .sin_addr = {INADDR_ANY}
    };
    int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    socklen_t serv_addr_len = sizeof(serv_addr);
    char buffer[100] = "Hello, world!";
    sleep(1);
    sendto(
            sock,
            buffer,
            sizeof buffer,
            0,
            (sockaddr *) &serv_addr,
            serv_addr_len
    );
    ssize_t bytes_read = recvfrom(
            sock,
            buffer,
            sizeof(buffer),
            0,
            (sockaddr *) &serv_addr,
            &serv_addr_len
    );
    std::cout << "Received: " << buffer << std::endl;
    if (bytes_read == -1) {
        perror("Error reading from socket");
        return 1;
    }
    close(sock);
    return 0;
}

