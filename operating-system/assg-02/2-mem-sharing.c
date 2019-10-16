#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int *a = (int *) malloc(sizeof(int));
    printf("%p\n", a);
}