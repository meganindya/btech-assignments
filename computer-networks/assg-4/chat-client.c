/**
 * @file Simple multi-client chat client program
 * @brief This client can send messages to other clients through a server.
 * It uses one of two responses: LIST and SEND to retrieve client list
 * and send message to another client, respectively.
 *
 * @ref https://pubs.opengroup.org/onlinepubs/7908799/
 * @ref https://www.man7.org/linux/man-pages/man7/
 * @ref https://linux.die.net/man/3/pthread_cond_init
 *
 * ****************************************************************************
 * compile using [cc -o client chat-client.c -lpthread]
 * run using [./server]
 * 
 * use LIST to get list of clients
 * use SEND #cliID #msg to send #msg to client having ID #cliID
 * ****************************************************************************
 *
 * @author Anindya Kundu <anindya.k22@outlook.com>
 * @date 2020-06-14
 */

#include <stdio.h>      /** @include standard buffered input/output */
#include <stdlib.h>     /** @include standard library definitons */
#include <pthread.h>    /** @include POSIX thread operations */
#include <netinet/in.h> /** @include internet address family */
#include <sys/socket.h> /** @include main sockets header */
#include <arpa/inet.h>  /** @include definitions for internet operations */
#include <errno.h>      /** @include system error numbers */
#include <string.h>     /** @include string operations */
#include <unistd.h>     /** @include standard symbolic constants and types */

/** chat handler function declaration */
void *_chat(void *);
/** image sending function declaration */
void _sendImage(FILE *, int);
/** image receiving function declaration */
void _recvImage(FILE *, int);

int main(void)
{
    /** clear terminal (stdlib.h) */
    system("clear");

    /** client socket file descriptor */
    int cli_sock = socket(PF_INET, SOCK_STREAM, 0);
    /** client socket address descriptor */
    struct sockaddr_in serv_addr;

    // set parameters
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(4201);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (
        connect(
            cli_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)
        ) == -1
    )
    {
        perror("could not connect to server\n");
        exit(EXIT_FAILURE);
    }

    printf("-- connected to server\n\n");

    /** thread to talk to server */
    pthread_t thread;
    pthread_create(&thread, NULL, _chat, (void *)&cli_sock);

    // input requests and send to server
    while (1)
    {
        char buff[1024];
        scanf("%s", buff);

        if (strcmp(buff, "LIST") == 0)
        {
            send(cli_sock, buff, 1024, 0);
        }
        else if (strcmp(buff, "SEND") == 0)
        {
            send(cli_sock, buff, 1024, 0);

            scanf("%s", buff);
            send(cli_sock, buff, 1024, 0);

            scanf("%s", buff);
            send(cli_sock, buff, 1024, 0);

            int type = 1;
            if (strcmp(buff, "~IMG") == 0)
            {
                type = 0;
            }

            if (type == 1)
            {
                scanf("%[^\n]s", buff);
                send(cli_sock, buff, 1024, 0);
            }
            else
            {
                /** file descriptor of sending image */
                FILE *fp = fopen("res/x31_f18.ascii.pgm", "r");

                _sendImage(fp, cli_sock);

                // free file handler
                fclose(fp);
            }
            
        }
    }

    close(cli_sock);
}

/**
 * Handles chat for each thread.
 *
 * @param sockfd socket file descriptor
 */
void *_chat(void *sockfd)
{
    int cli_sock = *((int *)sockfd);
    while (1)
    {
        char buff[1024];
        int len_m = recv(cli_sock, buff, 1024, 0);
        buff[len_m] = '\0'; // (\0 at position = length: end of string)

        if (strcmp(buff, "~LST~") == 0 || strcmp(buff, "~TXT~") == 0)
        {
            len_m = recv(cli_sock, buff, 1024, 0);
            buff[len_m] = '\0'; // (\0 at position = length: end of string)

            printf("%s\n", buff);
        }
        else
        {
            /** file descriptor of receiving image */
            FILE *fp = fopen("res/recv_img.ascii.pgm", "w+");

            _recvImage(fp, cli_sock);

            printf(" image received\n");

            // free file handler
            fclose(fp);
        }
        
    }
}

/**
 * Extracts magic number, width, height, maximum grayscale value,
 * per pixel value, from the file, and sends them to the socket
 * descriptor address.
 *
 * @private
 * @param fp - pointer to file handler
 * @param connfd - client socket file descriptor
 */
void _sendImage(FILE *fp, int connfd)
{
    uint32_t _net_b;

    // read and send magic number (file format)
    char _magic[8];
    fgets(_magic, sizeof(_magic), fp);
    send(connfd, &_magic, sizeof(_magic), 0);

    // read and send width of image
    int _width;
    fscanf(fp, "%d ", &_width);
    _net_b = htonl(_width);
    send(connfd, &_net_b, sizeof(_net_b), 0);

    // read and send height of image
    int _height;
    fscanf(fp, "%d ", &_height);
    _net_b = htonl(_height);
    send(connfd, &_net_b, sizeof(_net_b), 0);

    // read and send max grayscale value
    int _gmax;
    fscanf(fp, "%d ", &_gmax);
    _net_b = htonl(_gmax);
    send(connfd, &_net_b, sizeof(_net_b), 0);

    // read, invert, and send per pixel value
    for (int i = 0; i < _width * _height; i++)
    {
        int _temp;
        fscanf(fp, "%d ", &_temp);
        _net_b = htonl(_temp);
        send(connfd, &_net_b, sizeof(_net_b), 0);
    }

    printf("-- image sent\n");
}

/**
 * Receives magic number, width, height, maximum grayscale value,
 * per pixel value, from the socket, and saves them in the file
 * descriptor address.
 *
 * @private
 * @param fp - pointer to file handler
 * @param connfd - client socket file descriptor
 */
void _recvImage(FILE *fp, int connfd)
{
    // receive and write magic number (file format)
    char _magic[8];
    recv(connfd, _magic, sizeof(_magic), 0);
    fprintf(fp, "%s", _magic);

    // receive and write width of image
    int _width;
    recv(connfd, &_width, sizeof(_width), 0);
    fprintf(fp, "%d ", ntohl(_width));

    // receive and write height of image
    int _height;
    recv(connfd, &_height, sizeof(_height), 0);
    fprintf(fp, "%d ", ntohl(_height));

    // receive and write max grayscale value
    int _gmax;
    recv(connfd, &_gmax, sizeof(_gmax), 0);
    fprintf(fp, "%d ", ntohl(_gmax));

    // read and write per pixel value
    for (int i = 0; i < ntohl(_width) * ntohl(_height); i++)
    {
        uint32_t _temp;
        recv(connfd, &_temp, sizeof(_temp), 0);
        fprintf(fp, "%d ", ntohl(_temp));
    }
}
