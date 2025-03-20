#include <iostream>
#include <csignal>
#include <netinet/in.h>
#include <ctype.h>

int main() {
    sockaddr_in addr = {
            .sin_family = AF_INET,
            .sin_port = htons(3000),
            .sin_addr = {INADDR_ANY}
    };
    int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    int err = bind(sock, (sockaddr *) &addr, sizeof(addr));
    if (err < 0) {
        std::cerr << "Error binding socket" << std::endl;
        return 1;
    }
    std::cout << "Listening on port 3000" << std::endl;
    sockaddr_in client_addr{
            .sin_family = AF_INET,
            .sin_port = htons(3000),
            .sin_addr = {INADDR_ANY}
    };
    socklen_t client_addr_len = sizeof(client_addr);
    char buffer[100];
    sleep(1);
    ssize_t bytes_read = recvfrom(
            sock,
            buffer,
            sizeof(buffer),
            0,
            (sockaddr *) &client_addr,
            &client_addr_len
    );
    if (bytes_read == -1) {
        perror("Error reading from socket");
        return 1;
    }
    std::cout << "Received " << bytes_read << " bytes" << std::endl;
    std::cout << "Received: " << buffer << std::endl;
    for (int i = 0; i < bytes_read; i++) {
        buffer[i] = toupper(buffer[i]);
    }
    ssize_t bytes_written = sendto(
            sock,
            buffer,
            (size_t) bytes_read,
            0,
            (sockaddr *) &client_addr,
            client_addr_len
    );
    if (bytes_written == -1) {
        perror("Error writing to socket");
        return 1;
    }
    std::cout << "Sent " << bytes_written << " bytes" << std::endl;
    close(sock);
    return 0;
}

