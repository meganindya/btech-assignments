/**
 * @file Simple TCP server program
 * @brief This server can chat with one client at a time. The client
 * initiates a conversation, to which this server replies. The server
 * and client get alternate changes to send a message. The conversation
 * ends when one of them sends a "bye".
 *
 * @ref https://pubs.opengroup.org/onlinepubs/7908799/
 * @ref https://www.man7.org/linux/man-pages/man7/
 *
 * ****************************************************************************
 * compile using [cc -o server tcp-server.c]
 * run using [./server]
 * ****************************************************************************
 *
 * @author Anindya Kundu <anindya.k22@outlook.com>
 * @date 2020-06-02
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
#define BUFF 1024            /** @def maximum buffer size in bytes */

/** chat function declaration */
void _chat(int);

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
    /** client socket file descriptor */
    int connfd;
    /** server address descriptor */
    struct sockaddr_in ser_addr;
    /** client address descriptor */
    struct sockaddr_in cli_addr;

    // create socket and verify
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
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

    // listen on socket and verify
    if ((listen(sockfd, 5)) != 0)
    {
        perror("-- listen failed, error");
        exit(1);
    }
    else
    {
        printf("\n==========\n");
        printf("-- server listening on port %u\n", PORT);
    }

    /** client address descriptor length */
    socklen_t addr_len;
    // accept the data packet from client and verification
    if ((connfd = accept(sockfd, (SADR *)&cli_addr, &addr_len)) == -1)
    {
        perror("-- client accept failed, error");
        exit(1);
    }
    else
    {
        printf("-- client accepted by server\n");
    }

    // call function for chat
    _chat(connfd);

    // close socket after chatting
    close(sockfd);
    printf("\n-- socket closed\n");
}

/**
 * Conducts the chat between client and server.
 *
 * @private
 * @param connfd - client socket file descriptor
 */
void _chat(int connfd)
{
    char buff[BUFF];

    printf("\n");
    // infinite loop for chat
    while (1)
    {
        // clear buffer and receive client message
        bzero(buff, BUFF);
        read(connfd, buff, sizeof(buff));
        printf("CLIENT: %s\n", buff);

        // if message is "bye", exit chat
        if (strncmp("bye", buff, 3) == 0)
        {
            printf("\n-- server exit\n");
            break;
        }

        // clear buffer and store server message
        bzero(buff, BUFF);
        printf("SERVER: ");
        scanf("%s", buff);

        // send buffer to client
        write(connfd, buff, sizeof(buff));

        // if message is "bye", exit chat
        if (strncmp("bye", buff, 3) == 0)
        {
            printf("\n-- server exit\n");
            break;
        }
    }
}
