#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/syscall.h>

#define PORT 4200
#define SA struct sockaddr
#define MAX 1000


void chat(int);     // chat function declaration



int main(int argc, char *argv[]) {
    // clear terminal screen
    system("clear");

    int sockfd; struct sockaddr_in servaddr;

    // create UDP socket and verify
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        perror("-- socket creation failed, error");
        exit(0);
    } else
        printf("-- socket created successfully\n");

    // initialize all bytes in servaddr to 0
    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // set default sending address to server address
    connect(sockfd, (SA*) &servaddr, sizeof(servaddr));

    // call function for chatting
    chat(sockfd);

    // close socket descriptor
    close(sockfd);
}

// function for chat between client and server
void chat(int sockfd) {
    char buff[MAX]; int n;

    printf("\n");
    // infinite loop for chat
    while (1) {
        // clear buffer and store client message
        bzero(buff, sizeof(buff)); n = 0;
        printf("Client: ");
        while ((buff[n++] = getchar()) != '\n');

        // request to send datagram
        sendto(sockfd, buff, MAX, 0, (SA*) NULL, sizeof(struct sockaddr_in));

        // if message contains "exit" then end chat
        if ((strncmp(buff, "exit", 4)) == 0) {
            printf("\n-- client exit\n");
            break;
        }

        // clear buffer and store server message
        bzero(buff, sizeof(buff)); n = 0;

        recvfrom(sockfd, buff, sizeof(buff), 0, (SA*) NULL, NULL);
        printf("Server: %s", buff);

        // if message contains "exit" then end chat
        if ((strncmp(buff, "exit", 4)) == 0) {
            printf("\n-- client exit\n");
            break;
        }
    }
}
