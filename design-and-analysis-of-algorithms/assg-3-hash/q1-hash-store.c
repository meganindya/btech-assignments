#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define KEYS 100000

typedef struct listnode {
    int val;
    struct listnode *next;
} node;


int hash_by_mod(int a, int len) {
    return a % len;
}

int hash_by_mult(int a, int len) {
    double temp = (double) a * 0.5514;
    temp -= floor(temp);
    return floor((double) len * temp);
}


void store_linear_probing(FILE *fp, float lf, int *keys) {
    int len = KEYS / lf, *arr = (int *) malloc(sizeof(int) * len);

    for (int i = 0; i < KEYS; i++) {
        int loc = hash_by_mod(keys[i], len);
        while ((arr[loc++] % len) != 0);
        arr[loc - 1] = keys[i];
    }

    for (int i = 0; i < len; i++)
        fprintf(fp, "%d\n", arr[i]);
}


void store_quadratic_probing(FILE *fp, float lf, int *keys) {
    int len = KEYS / lf, *arr = (int *) malloc(sizeof(int) * len);

    for (int i = 0; i < KEYS; i++) {
        int loc = hash_by_mod(keys[i], len);

        int j = 1;
        while ((arr[loc] % len) != 0)
            loc += j * j++;
        arr[loc] = keys[i];
    }

    for (int i = 0; i < len; i++)
        fprintf(fp, "%d\n", arr[i]);
}


void store_chaining(FILE *fp, float lf, int *keys) {
    int len = KEYS / lf;
    node **arr = (node **) malloc(sizeof(node *) * len);
    for (int i = 0; i < len; i++)   arr[i] = null;

    for (int i = 0; i < KEYS; i++) {
        int loc = hash_by_mod(keys[i], len);
        
        node *temp = (node *) malloc(sizeof(node));
        temp -> val = keys[i];
        temp -> next = arr[loc];
        arr[loc] = temp;
    }

    for (int i = 0; i < len; i++) {
        fprintf(fp, "%d\n", i);
        node *curr = arr[i];
        while (curr != null) {
            fprintf(fp, "%d\n", curr -> val);
            curr = curr -> next;
        }
        fprintf(fp, "%d\n", -1);
    }
}


void store_double_hashing(FILE *fp, float lf, int *keys) {
    int len = KEYS / lf, *arr = (int *) malloc(sizeof(int) * len);

    for (int i = 0; i < KEYS; i++) {
        int loc = hash_by_mod(keys[i], len);
        while ((arr[loc++] % len) != 0);
        arr[loc - 1] = keys[i];
    }

    for (int i = 0; i < len; i++)
        fprintf(fp, "%d\n", arr[i]);
}


int main(int argc, char *argv[]) {
    float lf[5] = { 0.1, 0.5, 0.8, 0.9, 0.99 };

    FILE *finp = fopen("./q1-data-input/keys.dat", "r");
    int keys[KEYS];
    for (int i = 0; i < KEYS; i++)
        fscanf(finp, "%d", &keys[i]);
    fclose(finp);


    for (int i = 0; i < 5; i++) {
        char fname[30] = "./q1-data-input/lin-prob-X.dat";
        fname[25] = i + '0';
        FILE *fp = fopen(fname, "w+");
        store_linear_probing(fp, lf[i], keys);
        fclose(fp);
    }


    for (int i = 0; i < 5; i++) {
        char fname[31] = "./q1-data-input/quad-prob-X.dat";
        fname[25] = i + '0';
        FILE *fp = fopen(fname, "w+");
        store_quadratic_probing(fp, lf[i], keys);
        fclose(fp);
    }


    for (int i = 0; i < 5; i++) {
        char fname[30] = "./q1-data-input/chaining-X.dat";
        fname[25] = i + '0';
        FILE *fp = fopen(fname, "w+");
        store_chaining(fp, lf[i], keys);
        fclose(fp);
    }


    for (int i = 0; i < 5; i++) {
        char fname[33] = "./q1-data-input/double-hash-X.dat";
        fname[25] = i + '0';
        FILE *fp = fopen(fname, "w+");
        store_double_hashing(fp, lf[i], keys);
        fclose(fp);
    }


    return 0;
}
