#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <error.h>
#include <netdb.h>
#include <sys/epoll.h>

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

    int efd = epoll_create1(0);
    epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = 0;
    epoll_ctl(efd, EPOLL_CTL_ADD, 0, &ev);
    ev.events = EPOLLIN;
    ev.data.fd = sock;
    epoll_ctl(efd, EPOLL_CTL_ADD, sock, &ev);

    while (1)
    {
        epoll_event events[2];
        int ready = epoll_wait(efd, events, 2, -1);
        for (int i = 0; i < ready; i++)
        {
            if (events[i].events & EPOLLIN)
            {
                char buf[1024];
                int r = read(events[i].data.fd, buf, sizeof(buf));
                int sfd = 1;
                if (events[i].data.fd == 0)
                {
                    sfd = sock;
                }
                write(sfd, buf, r);
            }
        }
    }
}