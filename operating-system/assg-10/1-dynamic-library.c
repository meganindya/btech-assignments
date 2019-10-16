#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <dlfcn.h>

#define SIZE 5

void libLoadHandler();
void libUnloadHandler();
void errorHandler();


void *handle;
char *error;
int (*addVec) (int, int *, int *);


int main(int argc, char *argv[]) {
    libLoadHandler();

    
    int arr1[SIZE], arr2[SIZE], res;

    srand(time(0));
    for (int i = 0; i < SIZE; i++) {
        arr1[i] = 11 + (rand() % 10);
        arr2[i] = 11 + (rand() % 10);
    }
    
    res = addVec(SIZE, arr1, arr2);

    printf("ARR1\tARR2\n====\t====\n");
    for (int i = 0; i < SIZE; i++)
        printf(" %d\t %d\n", arr1[i], arr2[i]);
    
    printf("\nSum: %d\n", res);


    libUnloadHandler();
    return 0;
}


void libLoadHandler() {
    handle = dlopen("./bin/mylib.so", RTLD_LAZY);
    
    addVec = dlsym(handle, "addVec");
    errorHandler();
}

void libUnloadHandler() {
    dlclose(handle);
    errorHandler();
}

void errorHandler() {
    if (dlerror() != NULL) {
        fprintf(stderr, "%s\n", error);
        exit(1);
    }
}