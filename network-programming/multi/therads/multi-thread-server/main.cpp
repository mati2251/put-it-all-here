#include <iostream>
#include <csignal>
#include <netinet/in.h>
#include <error.h>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <fcntl.h>

std::mutex mut;
std::condition_variable cv;
int number = 0;
int size = 0;
bool ready = false;

int main(int argc, char **argv)
{
    if (argc != 2)
        error(1, 0, "Usage: %s <port>", argv[0]);

    sockaddr_in addr = {
        .sin_family = AF_INET,
        .sin_port = htons(atoi(argv[1])),
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
    std::cout << "Listening on port " << 3000 << std::endl;
    while (1)
    {
        int new_client = accept(sock, NULL, NULL);
        std::cout << "New client connected" << std::endl;
        std::thread([=]
                    {
                        while (true)
                        {                        
                        char buf[10];
                        size = read(new_client, &buf, 10);
                        if (size == -1)
                        {
                            std::cerr << "Error reading from socket" << std::endl;
                            return 1;
                        }
                        if (atoi(buf) == 0){
                            std::cout << "Client disconnected" << std::endl;
                            close(new_client);
                            return 0;
                        }
                        std::lock_guard<std::mutex> lock(mut);
                        std::cout<<new_client<<" override new number to value "<<atoi(buf)<<" about size "<<size<<std::endl;
                        ready = true;
                        number = atoi(buf); 
                        cv.notify_all();
                        } })
            .detach();
        std::thread([=]
                    {
                        while (1)
                        {
                        std::unique_lock<std::mutex> lck(mut);
                        cv.wait(lck);
                        if (fcntl(new_client, F_GETFL) == -1 && errno == EBADF){\
                            return 0;
                        }
                        char buf[11];
                        sprintf(buf,"%d\n", number);
                        int send_size = write(new_client, buf, size + 1);
                        std::cout<<"New number value "<<number<<" about size "<<send_size-1<<" bytes, sended to "<<new_client<<std::endl;
                        if (size == -1)
                            {
                            std::cerr << "Error writing to socket" << std::endl;
                            return 1;
                        }
                        } })
            .detach();
    }
    return 0;
}