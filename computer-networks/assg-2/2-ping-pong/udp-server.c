/**
 * @file Simple UDP server ping-pong program
 * @brief This server receives "ping" packets from a UDP client, and
 * sends back a "pong" packet.
 *
 * @ref https://pubs.opengroup.org/onlinepubs/7908799/
 * @ref https://www.man7.org/linux/man-pages/man7/
 *
 * ****************************************************************************
 * compile using [cc -o server udp-server.c]
 * run using [./server]
 * ****************************************************************************
 *
 * @author Anindya Kundu <anindya.k22@outlook.com>
 * @date 2020-06-04
 */

#include <stdio.h>      /** @include standard buffered input/output */
#include <sys/types.h>  /** @include data types */
#include <sys/socket.h> /** @include main sockets header */
#include <netinet/in.h> /** @include Internet address family */
#include <arpa/inet.h>  /** @include definitions for internet operations */
#include <string.h>     /** @include string operations */
#include <stdlib.h>     /** @include standard library definitions */
#include <unistd.h>     /** @include standard symbolic constants and types */

#define PORT 4200            /** @def PORT number */
#define SADR struct sockaddr /** @def short reference symbol */

/** pong function declaration */
void _pong(int);

/**
 * Main function.
 *
 * @param argc - command line arguments' count
 * @param argv - command line arguments
 * @returns exit status
 */
int main(int argc, char *argv[])
{
    /** clear terminal (stdlib.h) */
    system("clear");    // unix-like
    // system("cls");      // cmd/powershell

    /** server socket file descriptor */
    int sockfd;
    /** server address descriptor */
    struct sockaddr_in ser_addr;

    // create datagram socket and verify
    if ((sockfd = socket(PF_INET, SOCK_DGRAM, 0)) == -1)
    {
        perror("-- socket creation failed, error");
        exit(1);
    }
    else
    {
        printf("-- socket created successfully\n");
    }

    // initialize all bytes in ser_addr to 0
    bzero(&ser_addr, sizeof(ser_addr));

    // assign IP, PORT
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_port = htons(PORT);
    ser_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    // bind newly created socket to given IP and verify
    if ((bind(sockfd, (SADR *)&ser_addr, sizeof(ser_addr))) == -1)
    {
        perror("-- socket bind failed, error");
        exit(1);
    }
    else
    {
        printf("-- socket binded successfully\n");
    }

    printf("==========\n\n");

    // call function that handles the pong returns
    _pong(sockfd);

    // close socket after chatting
    close(sockfd);
    printf("\n-- socket closed\n");
}

/**
 * Returns a "pong" packet everytime it receives a "ping" packet.
 *
 * @private
 * @param sockfd - server socket file descriptor
 */
void _pong(int sockfd)
{
    char buff[8];
    /** client address descriptor */
    struct sockaddr_in cli_addr;
    /** client address descriptor length */
    socklen_t addr_len;

    for (int i = 0; i < 10; i++)
    {
        // clear buffer and receive ping
        bzero(buff, sizeof(buff));
        recvfrom(sockfd, buff, sizeof(buff), 0, (SADR*)&cli_addr, &addr_len);

        // send pong
        sendto(sockfd, "pong", 4, 0, (SADR*)&cli_addr, sizeof(cli_addr));

        printf("pong %d\n", (i + 1));
    }
}
