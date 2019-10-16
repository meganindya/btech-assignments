#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>

int main() {
    //int pid = fork();
    if(fork() == 0) {
        printf("%d\tThis is the child\n", getpid());
        if(fork() == 0) {
            printf("%d\tThis is the grandchild\n", getpid());
            sleep(2);
        }
    }
    else {
        wait(NULL);
        printf("%d\tThis is the parent\n", getpid());
        system("ps -el | grep a.out");
    }
}