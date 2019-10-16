#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int *a = (int *) malloc(sizeof(int));

    if(fork()) {
        printf("Child\t>> ");
        printf("PID : %d\tADD : %p\n",
            getpid(), a);
    }
    else {
        printf("Parent\t>> ");
        printf("PID : %d\tADD : %p\n",
            getpid(), a);
    }
}