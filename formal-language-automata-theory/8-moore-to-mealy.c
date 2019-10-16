// Author : Anindya Kundu - 510817020

// This program stores and prints the State Table of a
// Moore Machine. It takes the "number of states", the
// "inputs", the "transitional functions" and the res-
// pective "output" for each state as input.

// The Table is a 2D array of rows = number of states
// and columns = number of inputs + 1(for output).
// It is assumed that the states are serially denoted
// from 'A', hence present state isn't stored. It is
// also assumed that input syntax is correct semanti-
// cally and syntactically as follows:
// * Enter Number of States: *integer*
// * Enter Inputs: #,#,..,# (# : lower alpha / digit)
// * Enter Transitional Functions:
// *   δ(%, $) → *uppercase alphabet*
// *     Output: *character*

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define clear() printf("\033[H\033[J")

char *getInputs(int *);
void inputTransFuncs(char *, char *, int, int);
void printStateTableMealy(char *, char *, int, int);
void printStateTableMoore(char *, char *, int, int);
void toMealy(char *, char *, int, int, char *);

int main(int argc, int *argv[]){
	clear(); int r, c;
    printf("Enter Number of States: ");
    scanf("%d", &r);
    printf("Enter Inputs: ");
    char *ip = getInputs(&c);
    printf("Enter Transitional Functions:\n");
    char ar[r][c + 1]; inputTransFuncs(&ar[0][0], ip, r, c + 1);
    printStateTableMoore(&ar[0][0], ip, r, c + 1);
    char tb[r][2 * c]; toMealy(&ar[0][0], ip, r, c, &tb[0][0]);
    printStateTableMealy(&tb[0][0], ip, r, c);

	return 0;
}

char *getInputs(int *n){
    char s[64], t[64]; *n = 0;
    scanf("%s", s);
    for(int i = 0; s[i] != '\0'; i++)
    	if(islower(s[i]) || isdigit(s[i]))	t[(*n)++] = s[i];
    char *ip = (char *) malloc(sizeof(char) * (*n));
    for(int i = 0; i < (*n); i++)	ip[i] = t[i];
    return ip;
}

void inputTransFuncs(char *ar, char *ip, int r, int c){
    for(int i = 0; i < r; i++){
        for(int j = 0; j < c - 1; j++){
            printf("  δ(%c, %c) → ", ('A' + i), *(ip + j));
            scanf(" %c", (ar + (c * i) + j));
        }   printf("    Output: ");
        scanf(" %c", (ar + (c * i) + (c - 1))); printf("\n");
    }
}

void printStateTableMoore(char *ar, char *ip, int r, int c){
	printf("\nState Table:\n------------\n   PS\t");
    if(c % 2 == 0)
    {   for(int i = 1; i < c / 2; i++)  printf("\t");   printf("   ");  }
    else
    {   for(int i = 1; i < (c - 1) / 2; i++)  printf("\t");   printf("       ");  }
    printf("N S\n--------");
    for(int i = 0; i < c; i++)	printf("--------"); printf("\n");
    printf("\t"); for(int i = 0; i < c - 1; i++)	printf("|   %c\t", ip[i]);
	printf("\n--------");
    for(int i = 0; i < c; i++)	printf("--------"); printf("\n");

    for(int i = 0; i < r; i++){
    	printf("    %c\t", ('A' + i));
    	for(int j = 0; j < c - 1; j++)
    		printf("|   %c\t", *(ar + (c * i) + j));
    	printf("|   %c\n", *(ar + (c * i) + (c - 1)));
    }	printf("\n");
}

void printStateTableMealy(char *ar, char *ip, int r, int c){
    printf("\nState Table for Mealy:\n----------------------\n   PS\t");
    for(int i = 1; i < c; i++)  printf("\t");
    printf("     NS / OP\n--------");
    for(int i = 0; i < 2 * c; i++)  printf("--------"); printf("\n");
    for(int i = 0; i < c; i++)  printf("\t|\t%c", ip[i]);
    printf("\n--------");
    for(int i = 0; i < 2 * c; i++)  printf("--------"); printf("\n");

    for(int i = 0; i < r; i++){
        printf("    %c\t", ('A' + i));
        for(int j = 0; j < c; j++){
            printf("|   %c\t", *(ar + (2 * c * i) + ((2 * j) + 0)));
            printf("|   %c\t", *(ar + (2 * c * i) + ((2 * j) + 1)));
        }
        printf("\n");
    }   printf("\n");
}

void toMealy(char *ar, char *ip, int r, int c, char *fin){
    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            *(fin + (2 * c * i) + 2 * j) = *(ar + ((c + 1) * i) + j);
            int temp = *(fin + (2 * c * i) + 2 * j) - 'A';
            *(fin + (2 * c * i) + 2 * j + 1) = *(ar + ((c + 1) * temp) + c);
        }
    }
}