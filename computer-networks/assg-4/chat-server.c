/**
 * @file Simple multi-client chat server program
 * @brief This server can connect to multiple clients (upto 1024). It provides
 * one of two requests: LIST and SEND. LIST returns list of connected clients.
 * SEND forwards message from client to other respective client.
 *
 * @ref https://pubs.opengroup.org/onlinepubs/7908799/
 * @ref https://www.man7.org/linux/man-pages/man7/
 * @ref https://linux.die.net/man/3/pthread_cond_init
 *
 * ****************************************************************************
 * compile using [cc -o server chat-server.c -lpthread]
 * run using [./server]
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

// client descriptor structure
struct client
{
    int index;                      // attach index
    int sockfd;                     // socket file descriptor
    struct sockaddr_in sock_addr;   // socket address descriptor
    socklen_t len;                  // length of address
};

/** number of clients connected */
int clientCount = 0;

// initialize mutex lock
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
// initialize condition variables
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

/** client descriptor list array */
struct client Client[1024];
/** list of threads for clients */
pthread_t thread[1024];

/**
 * Main function.
 *
 * @returns exit status
 */
int main(void)
{
    /** clear terminal (stdlib.h) */
    system("clear");

    /** server socket file descriptor */
    int serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    /** server socket address descriptor */
    struct sockaddr_in serv_addr;

    // set parameters
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(4201);
    serv_addr.sin_addr.s_addr = htons(INADDR_ANY);

    // bind socket
    if (
        bind(
            serv_sock, (struct sockaddr *)&serv_addr , sizeof(serv_addr)
        ) == -1
    )
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // listen on socket
    if (listen(serv_sock, 1024) == -1)
    {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    printf("-- server listenting on port 4200\n\n");

    while (1)
    {
        // accept client and add its descriptor to client array
        Client[clientCount].sockfd = accept(
            serv_sock,
            (struct sockaddr*)&Client[clientCount].sock_addr,
            &Client[clientCount].len
        );

        Client[clientCount].index = clientCount;

        // create new thread to talk to client
        pthread_create(
            &thread[clientCount], NULL, _chat, (void *) &Client[clientCount]
        );

        // increment client count
        clientCount ++;
    }

    // wait for threads on main thread
    for (int i = 0; i < clientCount; i++)
    {
        pthread_join(thread[i], NULL);
    }

    close(serv_sock);
}

/**
 * Receives one of two requests: LIST or SEND. If LIST, server sends the
 * list of connected clients. If SEND, it reads ID no, then reads the message
 * and forwards the message to the client (for that ID).
 *
 * @param ClientDetail struct for client descriptor
 */
void *_chat(void *ClientDetail)
{
    struct client *clientDetail = (struct client *)ClientDetail;

    int index = clientDetail->index;
    int cli_sock = clientDetail->sockfd;

    printf("client %d connected\n", index + 1);

    while (1)
    {
        char buff[1024];
        int read = recv(cli_sock, buff, 1024, 0);
        buff[read] = '\0';  // (\0 at position = length: end of string)

        char output[1024];

        if (strcmp(buff, "LIST") == 0)
        {
            int l = 0;
            for (int i = 0; i < clientCount; i++)
            {
                if (i != index)
                {
                    l += snprintf(
                        output + l,
                        1024,
                        " client %d is at socket %d\n",
                        i + 1,
                        Client[i].sockfd
                    );
                }
            }

            strcpy(buff, "~LST~");
            // send type to receiver client
            send(cli_sock, buff, 1024, 0);

            // send list
            send(cli_sock, output, 1024, 0);
        }
        else if (strcmp(buff, "SEND") == 0)
        {
            read = recv(cli_sock, buff, 1024, 0);
            buff[read] = '\0'; // (\0 at position = length: end of string)

            int id = atoi(buff) - 1;

            // read type
            read = recv(cli_sock, buff, 1024, 0);
            buff[read] = '\0'; // (\0 at position = length: end of string)

            int type = 1;
            if (strcmp(buff, "IMG") == 0)
            {
                type = 0;
                strcpy(buff, "~IMG~");
                // send type to receiver client
                send(Client[id].sockfd, buff, 1024, 0);
            }
            else
            {
                strcpy(buff, "~TXT~");
                // send type to receiver client
                send(Client[id].sockfd, buff, 1024, 0);
            }

            if (type == 1)
            {
                read = recv(cli_sock, buff, 1024, 0);
                buff[read] = '\0'; // (\0 at position = length: end of string)

                // send text
                send(Client[id].sockfd, buff, 1024, 0);
            }
            else
            {
                FILE *fp = fopen("temp", "w+");

                _recvImage(fp, cli_sock);

                // head to start of file handler
                fseek(fp, 0L, SEEK_SET);

                _sendImage(fp, cli_sock);

                fclose(fp);

                remove("temp");
            }
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
