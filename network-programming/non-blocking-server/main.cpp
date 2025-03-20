#include <iostream>
#include <csignal>
#include <netinet/in.h>
#include <fcntl.h>

int main()
{
    sockaddr_in addr = {
        .sin_family = AF_INET,
        .sin_port = htons(3000),
        .sin_addr = {INADDR_ANY}};
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    const int one = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
    int err = bind(sock, (sockaddr *)&addr, sizeof(addr));
    if (err < 0)
    {
        std::cerr << "Error binding socket" << std::endl;
        return 1;
    }
    listen(sock, 2);
    std::cout << "Listening on port 3000" << std::endl;
    int client = accept(sock, nullptr, nullptr);
    char buf[1024];
    err = fcntl(client, F_SETFL, fcntl(sock, F_GETFL) | O_NONBLOCK);
    if (err < 0)
    {
        std::cerr << "Error setting socket to non-blocking" << std::endl;
        return 1;
    }
    sleep(1);
    err = read(client, buf, 1024);
    if (err < 0)
    {
        if (errno == EAGAIN || errno == EWOULDBLOCK)
        {
            std::cout << "No data available" << std::endl;
        }
        else
        {
            std::cerr << "Error reading from socket" << std::endl;
            return 1;
        }
    }
    write(1, buf, err);
    write(client, "Hello, world!\n", 14);
    close(client);
    return 0;
}
