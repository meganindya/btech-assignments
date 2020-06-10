/**
 * @file Simple web server (TCP) program
 * @brief This server receives the request for a PGM image from a client
 * and sends the image to the client. The client receives the image,
 * inverts it and sends back the inverted image.
 *
 * @ref https://pubs.opengroup.org/onlinepubs/7908799/
 * @ref https://people.sc.fsu.edu/~jburkardt/data/pgma/pgma.html
 *
 * ****************************************************************************
 * compile using [cc -o server web-server.c]
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

#define PORT 3701            /** @def PORT number */
#define SADR struct sockaddr /** @def short reference symbol */
#define BUFF 1024            /** @def maximum buffer BUFF in bytes */

/** image requesting-sending-receiving function declaration */
void _transactImages(int);
/** image sending function declaration */
void _sendImage(FILE *, int);
/** image receiving function declaration */
void _recvImage(FILE *, int);

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
    ser_addr.sin_addr.s_addr = INADDR_ANY;

    // bind newly created socket to given IP and verify
    if (bind(sockfd, (SADR *)&ser_addr, sizeof(ser_addr)) == -1)
    {
        perror("-- socket bind failed, error");
        exit(1);
    }
    else
    {
        printf("-- socket binded successfully\n");
    }

    // server is ready to listen and verification
    if (listen(sockfd, 1) < 0)
    {
        perror("-- listen failed, error");
        exit(1);
    }

    /** client address descriptor length */
    socklen_t addr_len;
    // accept the data packet from client and verify
    if ((connfd = accept(sockfd, (SADR *)&cli_addr, &addr_len)) == -1)
    {
        perror("-- client accept failed, error");
        exit(1);
    }
    else
    {
        printf("-- client accepted by server\n");
    }

    // call function to process image
    _transactImages(connfd);

    // close socket
    close(sockfd);
    close(connfd);
    printf("\n-- socket closed\n");
}

/**
 * Receives request for a PGM image from the client, and sends it to the client.
 * The client then inverts it and sends it back which this server receives.
 *
 * @private
 * @param connfd - client socket file descriptor
 */
void _transactImages(int connfd)
{
    char buff[BUFF];

    // clear buffer and receive client request (filename)
    bzero(buff, BUFF);
    read(connfd, buff, sizeof(buff));
    printf("\nrequest for %s received from client\n", buff);

    // copy filename to fname
    /** stores filename of PGM image */
    char fname[128];
    strcpy(fname, "res/");   // add relative path
    strcpy(fname + 4, buff); // add filename after path

    bzero(buff, BUFF);

    // open image file
    FILE *fp = fopen(fname, "r");
    if (fp == NULL) // file not found
    {
        printf("FILE NOT FOUND\n");

        // store and send error message
        strcpy(buff, "NOFILE");
        send(connfd, buff, sizeof(buff), 0);

        return;
    }
    else
    {
        printf("\nFILE FOUND\n");

        // store and send found message
        strcpy(buff, "FFOUND");
        send(connfd, buff, sizeof(buff), 0);
    }

    // clear buffer and read ready to receive signal
    bzero(buff, BUFF);
    recv(connfd, buff, sizeof(buff), 0);
    printf("\nsending file\n");

    // send file to client
    _sendImage(fp, connfd);

    // free file handler
    fclose(fp);

    char nname[128];
    strcpy(nname, "res/inv_");
    strcpy(nname + 8, fname + 4);

    fp = fopen(nname, "w+");
    if (fp == NULL)
    {
        printf("RECEIVE FAILED\n");
        return;
    }

    // read inverted image from client
    _recvImage(fp, connfd);

    // free file handler
    fclose(fp);
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

    printf("\nimage sent\n");
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
    fprintf(fp,"%d ",ntohl(_width));

    // receive and write height of image
    int _height;
    recv(connfd, &_height, sizeof(_height), 0);
    fprintf(fp,"%d ",ntohl(_height));

    // receive and write max grayscale value
    int _gmax;
    recv(connfd, &_gmax, sizeof(_gmax), 0);
    fprintf(fp,"%d ",ntohl(_gmax));

    // read and write per pixel value
    for (int i = 0; i < ntohl(_width) * ntohl(_height); i++)
    {
        uint32_t _temp;
        recv(connfd, &_temp, sizeof(_temp), 0);
        fprintf(fp, "%d ", ntohl(_temp));
    }

    printf("\ninverted image received\n");
}