/**
 * @file Simple UDP client ping-pong program
 * @brief This client sends "ping" packets to a UDP server which sends
 * back a "pong" packet. This client calculates the Round-Trip-Time
 * for the ping-pong transaction.
 *
 * @ref https://pubs.opengroup.org/onlinepubs/7908799/
 * @ref https://www.man7.org/linux/man-pages/man7/
 *
 * ****************************************************************************
 * compile using [cc -o client udp-client.c]
 * run using [./client]
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
#include <sys/time.h>   /** @include time types */

#define PORT 4200            /** @def PORT number of Server */
#define SADR struct sockaddr /** @def short reference symbol */

/** ping-pong function declaration */
void _pingpong(int);

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

    // create socket and verify
    if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("-- socket creation failed, error");
        exit(1);
    }
    else
    {
        printf("-- socket created successfully\n");
    }

    printf("\n");

    // call function for chat
    _pingpong(sockfd);

    // close socket after chatting
    close(sockfd);
    printf("\n-- socket closed\n");
}

/**
 * Sends 10 "ping" packets to server, and receives "pong" packets
 * in return.
 * Calculates the Round-Trip-Time for each ping-pong and reports
 * the average.
 *
 * @private
 * @param sockfd - client socket file descriptor
 */
void _pingpong(int sockfd)
{
    /** server address descriptor */
    struct sockaddr_in ser_addr;

    // initialize all bytes in ser_addr to 0
    bzero(&ser_addr, sizeof(ser_addr));

    // assign IP, PORT
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_port = htons(PORT);
    ser_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // set default sending address to server address
    connect(sockfd, (SADR*)&ser_addr, sizeof(ser_addr));

    char buff[8];
    /** server address descriptor length */
    socklen_t addr_len = sizeof(ser_addr);

    double rtt = 0;
    for (int i = 0; i < 10; i++) {
        // record initial time
        struct timeval start;
        gettimeofday(&start, NULL);

        // send pong
        sendto(sockfd, "ping", 4, 0, (SADR *)&ser_addr, addr_len);

        // clear buffer and receive pong
        bzero(buff, sizeof(buff));
        recvfrom(sockfd, buff, sizeof(buff), 0, NULL, NULL);

        // record final time
        struct timeval end;
        gettimeofday(&end, NULL);

        // calculate round-trip-time of one journey in ms
        double _t_start = start.tv_sec * 1e3 + (start.tv_usec / 1000.0);
        double _t_end = end.tv_sec * 1e3 + (end.tv_usec / 1000.0);
        double _rtt = _t_end - _t_start;

        printf("ping %d : %lfms\n", (i + 1), _rtt);

        rtt += _rtt;
    }

    // calculate average
    rtt /= 10;
    printf("\nAverage RTT: %lfms\n", rtt);
}
