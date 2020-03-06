#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define PORT 4200
#define SA struct sockaddr
#define MAX 100000


void talk(int);             // chat function declaration
void invertImage(char *);   // invert function declaration



int main(int argc, char *argv[]) {
    // clear terminal
    system("clear");

    int sockfd; struct sockaddr_in servaddr;

    // create socket and verify
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("-- socket creation failed, error");
        exit(0);
    }

    // initialize all bytes in servaddr to 0
    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // connect client socket to server socket
    if (connect(sockfd, (SA*) &servaddr, sizeof(servaddr)) == -1) {
        perror("-- connection with server failed, error");
        exit(0);
    } else
        printf("-- connected to server\n");

    // call function for chat
    talk(sockfd);

    // close socket after chatting
    close(sockfd);
}

// function for chat between client and server
void talk(int sockfd) {
    char buff[MAX]; int i;

    // clear buffer and request image from server
    bzero(buff, sizeof(buff)); i = 0;
    printf("-- requesting image");
    strcpy(buff, "send monalisa.pgm");
    write(sockfd, buff, sizeof(buff));

    // clear buffer and receive server image
    bzero(buff, sizeof(buff)); i = 0;
    read(sockfd, buff, sizeof(buff));
    printf("-- image received");
    puts(buff);

    // inverting and sending image
    invertImage(buff);
    write(sockfd, buff, sizeof(buff));
}

// inverts the pixel values in the buffer
void invertImage(char *buff) {

}
