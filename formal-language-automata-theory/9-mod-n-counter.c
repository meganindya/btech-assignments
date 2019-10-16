#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define clear() printf("\033[H\033[J");

void makeMooreMachine(int *, int);
void printStateTable(int *, int *, int, int);
void counter(int *, int, int);
void toBinary(int *, int, int);

int main(int argc, int *argv[]){
	clear(); printf("Enter value of 'n' : ");
	int n; scanf("%d", &n);
	int ar[n][3]; makeMooreMachine(&ar[0][0], n);
	int ip[2] = {0, 1}; 
	printStateTable(&ar[0][0], ip, n, 3);

	printf("Count value upto   : ");
	int z; scanf("%d", &z);
	counter(&ar[0][0], n, z);

	return 0;
}

void makeMooreMachine(int *ar, int n){
	for(int i = 0; i < n; i++)
		*(ar + (3 * i) + 2) = i;
	*ar = 0; int z = 1 << n;
	for(int i = 0; i < z; i++){
		int bin[n], curr = 0;
		toBinary(bin, i, n - 1);
		for(int j = 0; j < n - 1; j++)
			curr = *(ar + (3 * curr) + bin[j]);
		*(ar + (3 * curr) + bin[n - 1]) = i % n;
	}
}

void printStateTable(int *ar, int *ip, int r, int c){
	printf("\nState Table:\n------------\n   PS\t       ");
    printf("N S\n--------");
    for(int i = 0; i < c; i++)	printf("--------"); printf("\n");
    printf("\t"); for(int i = 0; i < c - 1; i++)	printf("|   %d\t", ip[i]);
	printf("\n--------");
    for(int i = 0; i < c; i++)	printf("--------"); printf("\n");

    for(int i = 0; i < r; i++){
    	printf("    %c\t", ('A' + i));
    	for(int j = 0; j < c - 1; j++)
    		printf("|   %c\t", *(ar + (c * i) + j) + 'A');
    	printf("|   %d\n", *(ar + (c * i) + (c - 1)));
    }	printf("\n");
}

void counter(int *ar, int n, int z){
	int l = ceil((float)log(z + 1) / (float)log(2));
	for(int i = 0; i <= z; i++){
		int bin[l]; toBinary(bin, i, l - 1);
		printf("    %d\t:  ", i);
		for(int i = 0; i < l; i++)	printf("%d", bin[i]);	printf("\t :   ");
		int curr = 0, out;
		for(int j = 0; j < l; j++)
			curr = *(ar + (3 * curr) + bin[j]);
		//out = *(ar + (3 * curr) + bin[n - 1]);
		printf("%d\n", curr);
	}	printf("\n");
}

void toBinary(int *b, int n, int p){
	if(p == -1)	return;
	b[p] = n % 2;
	toBinary(b, n / 2, p - 1);
}