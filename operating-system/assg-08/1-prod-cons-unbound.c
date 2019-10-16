/* @Mega328p */

#define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <time.h>
#include <string.h>
#include <semaphore.h>

#define BUFFER_SIZE 100000


typedef struct {
    int x;
}   item;


void *producer(void *);
void *consumer(void *);



sem_t mutex, empty, full;
item buffer[BUFFER_SIZE];
int in = 0, out = 0;
int n = 50, v = 1;


int main(int argc, char *argv[]) {
    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full,  0, 0);

    pthread_t p, c;
    pthread_create(&p, NULL, producer, NULL);
    pthread_create(&c, NULL, consumer, NULL);

    pthread_join(p, NULL);
    pthread_join(c, NULL);

    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full );

    return 0;
}

void *producer(void *t) {
    while(n) {
        item nextProduced;

        nextProduced.x = v++;
        printf("%d  produced\n", nextProduced.x);

        sem_wait(&empty);
        sem_wait(&mutex);

        buffer[in] = nextProduced;
        in = (in + 1) % BUFFER_SIZE;
        printf("%d  inserted\n", nextProduced.x);
        n--;

        sem_post(&mutex);
        sem_post(&full );
    }

    pthread_exit(0);
}

void *consumer(void *t) {
    while(1) {
        item nextConsumed;
        
        sem_wait(&full );
        sem_wait(&mutex);

        nextConsumed = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        printf("%d  extracted\n", nextConsumed.x);

        sem_post(&mutex);
        sem_post(&empty);

        printf("%d  consumed\n", nextConsumed.x);

        int fval;
        sem_getvalue(&full, &fval);
        if(n == 0 && fval == 0)
            break;
    }

    pthread_exit(0);
}