/*
====================
Daytime client specifically works with IPV4.
====================
*/
#include "unp.h"

using namespace unp;
int main( int argc, char **argv ) {
    int socketfd, n;
    char recvline[MAXLINE + 1];
    sockaddr_in servaddr{};

    if (argc != 2)
        ErrorQuit("usage: a.out <IPaddress>");

    if ((socketfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        ErrorSys("socket error");

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(13); // todo question?
    if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0) // present to numeric -> convert ip address to number format
        ErrorQuit("inet_pton error for %s", argv[1]);

    if (connect(socketfd, reinterpret_cast<SA*>(&servaddr), sizeof(servaddr)) < 0)
        ErrorSys("connect error");

    while ( (n = read(socketfd, recvline, MAXLINE)) > 0)
    {
        recvline[n] = 0;
        if (fputs(recvline, stdout) == EOF)
            ErrorSys("fputs error");
    }

    if (n < 0)
        ErrorSys("read error");

    return 0;
}
