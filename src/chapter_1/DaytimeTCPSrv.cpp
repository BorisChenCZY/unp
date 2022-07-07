/*
====================
Daytime TCP server
====================
*/
#include "unp.h"
#include <ctime>
#include <sstream>
#include <format>

using namespace unp;
int main(int argc, char **argv) {
    int listenfd, connfd;
    sockaddr_in servaddr{};
    char buff[MAXLINE];
    time_t ticks;

    listenfd = Socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(13);

    Bind(listenfd, reinterpret_cast<SA*>(&servaddr), sizeof(servaddr));
    Listen(listenfd, LISTENQ); // backlog ?

    while (true) {
        connfd = Accept(listenfd, reinterpret_cast<SA*>(NULL), NULL);
        ticks = time(NULL);
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
        Write(connfd, buff, strlen(buff));
        Close(connfd);
    }

    return 0;
}
