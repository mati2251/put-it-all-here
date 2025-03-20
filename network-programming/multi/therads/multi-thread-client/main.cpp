#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <error.h>
#include <netdb.h>
#include <sys/epoll.h>
#include <poll.h>
#include <thread>

void read_therad(int fd)
{
    while (1)
    {
        char buffer[255];
        ssize_t buffsize = 255;
        int size = read(fd, buffer, buffsize);
        if (size == -1)
            error(1, errno, "falied read server %d", fd);
        size = write(1, buffer, size);
        if (size == -1)
            error(1, errno, "falied write to stdout %d", fd);
    }
}

void write_therad(int fd)
{
    while (1)
    {
        char buffer[255];
        ssize_t buffsize = 255;
        int size = read(1, buffer, buffsize);
        if (size == -1)
            error(1, errno, "read failed on stdin %d", fd);
        if (buffer == "exit")
            break;
        size = write(fd, buffer, size);
        if (size == -1)
            error(1, errno, "failed send to server %d", fd);
    }
}

int main(int argc, char **argv)
{
    if (argc != 3)
        error(1, 0, "Need 2 args");

    addrinfo *resolved, hints = {.ai_flags = 0, .ai_family = AF_INET, .ai_socktype = SOCK_STREAM};
    int res = getaddrinfo(argv[1], argv[2], &hints, &resolved);
    if (res || !resolved)
        error(1, 0, "getaddrinfo: %s", gai_strerror(res));
    printf("Connecting to %s\n", resolved->ai_addr->sa_data);
    int sock = socket(resolved->ai_family, resolved->ai_socktype, 0);
    if (sock == -1)
        error(1, errno, "socket failed");

    res = connect(sock, resolved->ai_addr, resolved->ai_addrlen);
    if (res)
        error(1, errno, "connect failed");

    freeaddrinfo(resolved);

    std::thread reader(read_therad, sock);
    std::thread writer(write_therad, sock);
    writer.join();
    reader.detach();
    return 0;
}
