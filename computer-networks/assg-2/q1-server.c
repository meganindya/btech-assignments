#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>

#define PORT 4200
#define SA struct sockaddr
#define MAX 100000


void talk(int);     // chat function declaration



int main(int argc, char *argv[]) {
    // clear terminal
    system("clear");

    int sockfd, connfd;
    struct sockaddr_in servaddr, cliaddr;

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
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    // bind newly created socket to given IP and verify
    if ((bind(sockfd, (SA*) &servaddr, sizeof(servaddr))) == -1) {
        perror("-- socket bind failed, error");
        exit(0);
    }

    while (1) {
        // server is ready to listen and verification
        if ((listen(sockfd, 5)) != 0) {
            perror("-- listen failed, error");
            exit(0);
        } else
            printf("-- server listening on port %u\n", PORT);

        int len = sizeof(cliaddr);
        // accept the data packet from client and verification
        connfd = accept(sockfd, (SA*) &cliaddr, &len);
        if (connfd == -1) {
            perror("-- client accept failed, error");
            exit(0);
        } else
            printf("-- client accepted by server\n");

        // call function for chat
        talk(connfd);

        printf("Exit? (Y/n) : ");
        char temp; scanf("%d", &temp);
        if (temp == 'Y')    break;
    }

    // close socket after chatting
    close(sockfd);
}

// function for chat between client and server
void talk(int sockfd) {
    char buff[MAX]; int i;

    // clear buffer and receive client message
    bzero(buff, MAX); i = 0;
    read(sockfd, buff, sizeof(buff));

    // if message contains "exit", exit
    if (strncmp("send", buff, 4) == 0) {
        char temp[MAX];
        strcpy(temp, &buff[5]);
        printf("\n-- \'%s\' requested\n", temp);
    }

    // clear buffer and store server message
    bzero(buff, MAX); i = 0;
    printf("Server: ");
    while ((buff[i++] = getchar()) != '\n');

    // send buffer to client
    write(sockfd, buff, sizeof(buff));

    // if message contains "exit", exit
    if (strncmp("exit", buff, 4) == 0)
        printf("\n-- server exit\n");
}
