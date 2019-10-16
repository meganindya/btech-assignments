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


void *reader1(void *);
void *reader2(void *);
void *reader3(void *);
void lockRead();
void unlockRead();
void readAction();

void *writer(void *);

int countLines(FILE *);
int pin_thread_to_core(int);



sem_t mutex, wrt;
int readCount = 0;
int n = 1;


int main(int argc, char *argv[]) {
    srand(time(0));
    FILE* fp = fopen("file.txt", "w");
    fprintf(fp, "This is the Initial text.\n");
    fclose(fp);

    sem_init(&mutex, 0, 1);
    sem_init(&wrt,   0, 1);

    pthread_t rd1, rd2, rd3, wr;
    pthread_create(&rd1, NULL, reader1, NULL);
    pthread_create(&rd2, NULL, reader2, NULL);
    pthread_create(&rd3, NULL, reader3, NULL);
    pthread_create(&wr,  NULL, writer,  NULL);

    pthread_join(rd1, NULL);
    pthread_join(rd2, NULL);
    pthread_join(rd3, NULL);
    pthread_join(wr, NULL);

    sem_destroy(&mutex);
    sem_destroy(&wrt  );

    return 0;
}


void *reader1(void *t) {
    pin_thread_to_core(1);

    while(n <= 500) {
        lockRead();

        readAction();

        unlockRead();

        //sleep(rand());
    }
}

void *reader2(void *t) {
    pin_thread_to_core(2);

    while(n <= 500) {
        lockRead();

        readAction();

        unlockRead();

        //sleep(rand());
    }
}

void *reader3(void *t) {
    pin_thread_to_core(3);

    while(n <= 500) {
        lockRead();

        readAction();

        unlockRead();

        //sleep(rand());
    }
}

void lockRead() {
    sem_wait(&mutex);
    readCount++;
    if(readCount == 1)
        sem_wait(&wrt);
    sem_post(&mutex);
}

void unlockRead() {
    sem_wait(&mutex);
    readCount--;
    if(readCount == 0)
        sem_post(&wrt);
    sem_post(&mutex);
}

void readAction() {
    FILE* fp = fopen("file.txt", "r");
    printf("%d\tReader\treaders: %d\tlines: %d\n",
        n++, readCount, countLines(fp));
    usleep(10000);
    fclose(fp);
}


void *writer(void *t) {
    pin_thread_to_core(0);
    
    while(n <= 500) {
        sem_wait(&wrt);


        FILE* fp = fopen("file.txt", "a+");
        fprintf(fp, "Added a New Line.\n");
        fclose(fp);
        fp = fopen("file.txt", "r");
        printf("%d\tWriter\treaders: %d\tlines: %d\n",
            n++, readCount, countLines(fp));
        //usleep(100000);
        fclose(fp);


        sem_post(&wrt);

        //sleep(rand() * 3);
    }
}


int countLines(FILE *fp) {
    int lines = 0;
    char ch;
 
    while(ch != EOF) {
        ch = getc(fp);
        if (ch == '\n') lines++;
    }

    return lines;
}


int pin_thread_to_core(int core_id) {
   cpu_set_t cpuset;
   CPU_ZERO(&cpuset);
   CPU_SET(core_id, &cpuset);

   pthread_t current_thread = pthread_self();
   return pthread_setaffinity_np(
       current_thread, sizeof(cpu_set_t), &cpuset);
}