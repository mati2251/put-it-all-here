#include <iostream>
#include <csignal>
#include <netinet/in.h>

int main() {
    sockaddr_in addr = {
            .sin_family = AF_INET,
            .sin_port = htons(3000),
            .sin_addr = {INADDR_ANY}
    };
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    const int one = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
    int err = bind(sock, (sockaddr *) &addr, sizeof(addr));
    if (err < 0) {
        std::cerr << "Error binding socket" << std::endl;
        return 1;
    }
    listen(sock, 2);
    std::cout << "Listening on port 3000" << std::endl;
    int client = accept(sock, nullptr, nullptr);
    write(client, "Hello, world!\n", 14);
//    while (true) {
        write(client, "Enter a string: \n", 16);
        sleep(1);
//    }
    close(client);
    return 0;
}
