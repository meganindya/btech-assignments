#include <stdio.h>
#include <pthread.h>

int sum_even = 0, sum_odd = 0, n = 10;

void *evenThread(void *t) {
    for(int i = 2; i <= n; i += 2) {
        printf("V : %d\tTID : %p\n", i, t);
        sum_even += i;
    }
}

void *oddThread(void *t)  {
    for(int i = 1; i <= n; i += 2) {
        printf("V : %d\tTID : %p\n", i, t);
        sum_odd  += i;
    }
}

int main(int argc, char *argv[]) {
    printf("\n");

    pthread_t todd, teven;
    pthread_create(&todd,  NULL, oddThread,  &todd );
    pthread_create(&teven, NULL, evenThread, &teven);

    pthread_join(todd,  NULL);
    pthread_join(teven, NULL);

    printf("\nSum : %d\n\n", (sum_even + sum_odd));

    pthread_exit(NULL);
}