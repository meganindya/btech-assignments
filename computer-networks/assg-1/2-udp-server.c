#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
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

    // initialize all bytes of server address to 0
    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    // bind server address to socket descriptor and verify
    if ((bind(sockfd, (SA*) &servaddr, sizeof(servaddr))) == -1) {
        perror("-- socket bind failed, error");
        exit(0);
    } else
        printf("-- socket binded successfully\n");

    // call function for chat
    chat(sockfd);

    // close socket descriptor
    close(sockfd);
}

// function for chat between client and server
void chat(int sockfd) {
    char buff[MAX]; int i;

    printf("\n");
    // infinite loop for chat
    while (1) {
        struct sockaddr_in cliaddr;
        int len = sizeof(cliaddr);

        // clear buffer and receive client message
        bzero(buff, sizeof(buff)); i = 0;
        recvfrom(sockfd, buff, sizeof(buff), 0, (SA*) &cliaddr, &len);
        printf("Client: %s", buff);

        // if message contains "exit" then end chat
        if (strncmp("exit", buff, 4) == 0) {
            printf("\n-- server exit\n");
            break;
        }

        // clear buffer and store server message
        bzero(buff, sizeof(buff)); i = 0;
        printf("Server: ");
        while ((buff[i++] = getchar()) != '\n');

        // send response
        sendto(sockfd, buff, MAX, 0, (SA*) &cliaddr, sizeof(cliaddr));

        // if message contains "exit" then end chat
        if (strncmp("exit", buff, 4) == 0) {
            printf("\n-- server exit\n");
            break;
        }
    }
}
