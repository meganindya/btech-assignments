/**
 * @file Simple web client (TCP) program
 * @brief This client sends a request for a PGM image file to the server.
 * The server sends the image, which this client inverts and sends back.
 *
 * @ref https://pubs.opengroup.org/onlinepubs/7908799/
 * @ref https://people.sc.fsu.edu/~jburkardt/data/pgma/pgma.html
 * @ref https://man7.org/linux/man-pages//man3/strncpy.3.html
 *
 * ****************************************************************************
 * compile using [cc -o client web-client.c]
 * run using [./client]
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

#define PORT 3701            /** @def PORT number of Server */
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
    system("clear"); // unix-like
    // system("cls");      // cmd/powershell

    /** socket file descriptor */
    int sockfd;
    /** server address descriptor */
    struct sockaddr_in ser_addr;

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
    ser_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // localhost

    // connect client socket to server socket
    if (connect(sockfd, (SADR *)&ser_addr, sizeof(ser_addr)) == -1)
    {
        perror("-- connection with server failed, error");
        exit(1);
    }
    else
    {
        printf("-- connected to server\n");
    }

    // call image processing function
    _transactImages(sockfd);

    // close socket after image processed
    close(sockfd);
    printf("\n-- socket closed\n");
}

/**
 * Sends server a request for a PGM image file, and receives the image from
 * the server. It then inverts the image, and sends it back to the server.
 *
 * @private
 * @param connfd - server socket file descriptor
 */
void _transactImages(int connfd)
{
    char buff[BUFF];

    /** stores filename of original PGM image */
    char *fname = "x31_f18.ascii.pgm";
    // clear buffer and store filename
    bzero(buff, sizeof(buff));
    strcpy(buff, fname);

    // send request (filename: fname) to server
    send(connfd, buff, sizeof(buff), 0);
    printf("\nrequesting %s from server\n", fname);

    // clear buffer and receive server message
    bzero(buff, sizeof(buff));
    recv(connfd, buff, sizeof(buff), 0);

    // if error message, exit
    if (strncmp("NOFILE", buff, 6) == 0)
    {
        printf("\nFILE ERROR\n");
        return;
    }
    else
    {
        printf("\nFILE FOUND\n");
    }

    // clear buffer and send ready signal
    bzero(buff, sizeof(buff));
    send(connfd, "ready", sizeof("ready"), 0);
    printf("\nreceiving file\n");

    /** stores temporary filename of PGM image */
    char *tname = "res/temp.ascii.pgm";
    // open temporary file
    FILE *fp = fopen(tname, "w+");
    if (fp == NULL)
    {
        printf("\nRECEIVE FAILED\n");
        return;
    }

    // read image from server into temporary file
    _recvImage(fp, connfd);

    // head to start of file handler
    fseek(fp, 0L, SEEK_SET);

    // send file to server
    _sendImage(fp, connfd);

    // remove temporary file
    remove(tname);

    // free file handler
    fclose(fp);
}

/**
 * Extracts magic number, width, height, maximum grayscale value,
 * per pixel value, from the file, and sends them (inverts pixel
 * values before sending) to the socket descriptor address.
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
        _net_b = htonl(_gmax - _temp);  // invert
        send(connfd, &_net_b, sizeof(_net_b), 0);
    }

    printf("\ninverted image sent\n");
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

    printf("\nimage received\n");
}
