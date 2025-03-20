#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <error.h>
#include <netdb.h>
#include <sys/epoll.h>
#include <poll.h>

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

    pollfd fds[2];
    fds[0].fd = 0;
    fds[0].events = POLLIN;
    fds[1].fd = sock;
    fds[1].events = POLLIN;

    while (1)
    {
        int i = poll(fds, 2, -1);
        if (fds[1].revents & POLLHUP)
            break;
        if (fds[0].revents & POLLIN)
        {
            char buf[1024];
            int r = read(0, buf, sizeof(buf));
            if (r == -1)
                error(1, errno, "read failed");
            r = write(sock, buf, r);
            if (r == -1)
                error(1, errno, "write failed");
        }
        if (fds[1].revents & POLLIN){
            char buf[1024];
            int r = read(sock, buf, sizeof(buf));
            if (r == -1)
                error(1, errno, "read failed");
            r = write(1, buf, r);
            if (r == -1)
                error(1, errno, "write failed");
        }
    }
    close(sock);
    return 0;
}