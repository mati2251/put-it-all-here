#include <unistd.h>
#include <thread>
#include <arpa/inet.h>
#include <netdb.h>
#include <cstdio>

int main() {
    hostent *ret = gethostbyname("wp.pl");
    printf("%s: %s\n", ret->h_name, inet_ntoa(**(in_addr **) ret->h_addr_list));
    return 0;
}
