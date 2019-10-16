#include <stdio.h>
#include <signal.h>

void sigHandler(int x) {
    printf(" You cannot kill me!\nBut he can\n");
}

int main() {
    signal(SIGINT, sigHandler);
    while(1);

    return 0;
}