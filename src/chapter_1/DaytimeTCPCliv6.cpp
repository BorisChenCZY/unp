/*
====================
Daytime client protocol-dependent that  works with IPV6.
====================
*/
#include "unp.h"

using namespace unp;
int main( int argc, char **argv ) {
    int socketfd, n;
    char recvline[MAXLINE + 1];
    sockaddr_in6 servaddr{};

    if (argc != 2)
        ErrorQuit("usage: a.out <IPaddress>");

    if ((socketfd = socket(AF_INET6, SOCK_STREAM, 0)) < 0)
        ErrorSys("socket error");

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin6_family = AF_INET6;
    servaddr.sin6_port = htons(13); // convert 16-bits number to network order
    if (inet_pton(AF_INET6, argv[1], &servaddr.sin6_addr) <= 0) // present to numeric -> convert ip address to number format
        ErrorQuit("inet_pton error for %s", argv[1]);

    if (connect(socketfd, reinterpret_cast<SA *>(&servaddr), sizeof(servaddr)) < 0)
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
