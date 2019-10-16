#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

int t = 5, n = 1000;
int *a, tno = 0;

void *soe(void *val) {
    int v = tno++;

    int min = (n / t) * v + 1;
    min = min < 2 ? 2 : min;
    int max = (n / t) * (v + 1);
    max = max > n ? n : max;

    for(int i = min; i <= max && (i * i) <= n; i++)
        for(int j = i * i; j <= n; j = j += i)
            a[j] = 1;
}

int main(int argc, char *argv[]) {
    printf("\n");
    a = (int *) malloc(sizeof(int) * (n + 1));
    for(int i = 0; i < n; i++)  a[i] = 0;

    pthread_t threads[t + 1];
    for(int i = 0; i <= t; i++)
        pthread_create(&threads[i], NULL, soe, NULL);
    
    for(int i = 0; i <= t; i++)
        pthread_join(threads[i], NULL);

    printf("Primes till %d : ", n);
    for(int i = 2; i <= n; i++)
        if(a[i] != 1)
            printf("%d ", i);
    printf("\n\n");

    pthread_exit(NULL);
}