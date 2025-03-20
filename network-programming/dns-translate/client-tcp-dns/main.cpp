#include <netdb.h>
#include <cstdio>
#include <error.h>
#include <unistd.h>
#include <iostream>
#include <arpa/inet.h>
#define BUFFER_SIZE 100

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        std::cout << "Usage: " << argv[0] << " <host> <port>" << std::endl;
        return 1;
    }
    const char *host = argv[1];
    const char *port = argv[2];
    addrinfo hints{
        .ai_family = AF_INET,
        .ai_socktype = SOCK_STREAM};
    addrinfo *resolved;
    int res = getaddrinfo(host, port, &hints, &resolved);
    if (res != 0)
    {
        std::cout << "getaddrinfo: " << gai_strerror(res) << std::endl;
        return 1;
    }
    for (addrinfo *it = resolved; it; it = it->ai_next)
    {
        sockaddr_in *addr = (sockaddr_in *)it->ai_addr;
        printf(" %s\n", inet_ntoa(addr->sin_addr));
        int soc = socket(it->ai_family, it->ai_socktype, it->ai_protocol);

        auto err = connect(soc, it->ai_addr, it->ai_addrlen);
        if (err == -1)
        {
            perror("Error connecting to server-tcp");
            return 1;
        }
        char buffer[BUFFER_SIZE] = "GET / HTTP/1.0\r\n\r\n";
        size_t bytes_read;
        write(soc, buffer, sizeof(buffer));
        bytes_read = read(soc, buffer, BUFFER_SIZE);
        while ((bytes_read = read(soc, buffer, BUFFER_SIZE)) > 0)
        {
            std::cout << "TEST" << std::endl;
            err = (int)write(1, buffer, bytes_read);
            if (err == -1)
            {
                perror("Error writing to stdout");
                return 1;
            }
        }
        if (bytes_read == -1)
        {
            perror("Error reading file");
            return 1;
        }
    }
    return 0;
}
