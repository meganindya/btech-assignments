#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX 80
#define PORT 4200
#define SA struct sockaddr


void func(int);     // chat function declaration



int main(int argc, char *argv[]) {
    int sockfd, connfd;
    struct sockaddr_in servaddr, cliaddr;

    // create socket and verify
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("-- socket creation failed, error");
        exit(0);
    }
    else
        printf("-- socket created successfully\n");

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
    }
    else
        printf("-- connected to server\n");

    // function for chat between client and server
    func(sockfd);

    // close socket after chatting
    close(sockfd);
}

// function for chat between client and server
void func(int sockfd) {
    char buff[MAX];
    int n;

    while (1) {
        bzero(buff, sizeof(buff));

        printf("Enter message: ");
        n = 0;
        while ((buff[n++] = getchar()) != '\n');

        write(sockfd, buff, sizeof(buff));

        bzero(buff, sizeof(buff));

        read(sockfd, buff, sizeof(buff));
        printf("Server: %s", buff);

        if ((strncmp(buff, "exit", 4)) == 0) {
            printf("client exit\n");
            break;
        }
    }
}
