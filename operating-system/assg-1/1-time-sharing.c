#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) { 
    for(int i = 0; i < 10000; i++)
        printf("%d\t%c\n", (i + 1), argv[1][0]);

    return 0; 
}