#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX 80
#define PORT 4200
#define SA struct sockaddr


void func(int);     // chat function declaration



int main(int argc, char *argv[]) {
    int sockfd, connfd, len;
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
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    // bind newly created socket to given IP and verify
    if ((bind(sockfd, (SA*) &servaddr, sizeof(servaddr))) == -1) {
        perror("-- socket bind failed, error");
        exit(0);
    }
    else
        printf("-- socket binded successfully\n");
    
    // server is ready to listen and verification
    if ((listen(sockfd, 5)) != 0) {
        perror("-- listen failed, error");
        exit(0);
    }
    else
        printf("-- server listening on port %u\n", PORT);
    
    len = sizeof(cliaddr);
    // accept the data packet from client and verification
    connfd = accept(sockfd, (SA*) &cliaddr, &len);
    if (connfd == -1) {
        perror("-- client accept failed, error");
        exit(0);
    }
    else
        printf("-- client accepted by server\n");

    // function for chat between client and server
    func(connfd);

    // close socket after chatting
    close(sockfd);
}

// function for chat between client and server
void func(int sockfd) {
    char buff[MAX];
    int n;

    // infinite loop for chat
    while (1) {
        bzero(buff, MAX);

        // read the message from client and copy it in buffer
        read(sockfd, buff, sizeof(buff));

        // print buffer which contains the client contents
        printf("From client: %sTo   client: ", buff);

        bzero(buff, MAX);
        n = 0;

        // copy server message in buffer
        while ((buff[n++] = getchar()) != '\n');

        // send buffer to client
        write(sockfd, buff, sizeof(buff));

        // if msg contains "exit" then server exit and chat ended
        if (strncmp("exit", buff, 4) == 0) {
            printf("server exit\n");
            break;
        }
    }
}
