// Author : Anindya Kundu - 510817020

// This program stores and prints the State Table of a
// Mealy Machine. It takes the "number of states", the
// "inputs", the "transitional functions" and the res-
// pective "outputs" for each function as input.

// The Table is a 2D array of rows = number of states
// and columns = 2 * number of inputs.
// It is assumed that the states are serially denoted
// from 'A', hence present state isn't stored. It is
// also assumed that input syntax is correct semanti-
// cally and syntactically as follows:
// * Enter Number of States: *integer*
// * Enter Inputs: #,#,...,# (# : lower alpha / digit)
// * Enter Transitional Functions:
// *   δ(%, $) → *uppercase alphabet*
// *     Output: *character*

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define clear() printf("\033[H\033[J")

typedef struct mealy{
	int staNo, subNo;
}	cell;

char *getInputs(int *);
void inputTransFuncs(char *, char *, int, int);
void printStateTableMealy(char *, char *, int, int);
void printStateTableMoore(char *, char *, int, int);
char **toMoore(char *, char *, int, int, int *);

int main(int argc, int *argv[]){
	clear(); int r, c, len;
    printf("Enter Number of States: ");
    scanf("%d", &r);
    printf("Enter Inputs: ");
    char *ip = getInputs(&c);
    printf("Enter Transitional Functions:\n");
    char ar[r][2 * c]; inputTransFuncs(&ar[0][0], ip, r, c);
    printStateTableMealy(&ar[0][0], ip, r, c);
    char **ot = toMoore(&ar[0][0], ip, r, 2 * c, &len);
    char tb[len][c + 1];
    for(int i = 0; i < len; i++)
		for(int j = 0; j < c + 1; j++)
			tb[i][j] = ot[i][j];
    printStateTableMoore(&tb[0][0], ip, len, c + 1);

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
        for(int j = 0; j < c; j++){
            printf("  δ(%c, %c) → ", ('A' + i), *(ip + j));
            scanf(" %c", (ar + (2 * c * i) + ((2 * j) + 0)));
            printf("    Output: ");
            scanf(" %c", (ar + (2 * c * i) + ((2 * j) + 1)));
            printf("\n");
        }
    }
}

void printStateTableMealy(char *ar, char *ip, int r, int c){
	printf("\nState Table for Mealy:\n----------------------\n   PS\t");
    for(int i = 1; i < c; i++)	printf("\t");
    printf("     NS / OP\n--------");
    for(int i = 0; i < 2 * c; i++)	printf("--------"); printf("\n");
    for(int i = 0; i < c; i++)	printf("\t|\t%c", ip[i]);
	printf("\n--------");
    for(int i = 0; i < 2 * c; i++)	printf("--------"); printf("\n");

    for(int i = 0; i < r; i++){
    	printf("    %c\t", ('A' + i));
    	for(int j = 0; j < c; j++){
    		printf("|   %c\t", *(ar + (2 * c * i) + ((2 * j) + 0)));
    		printf("|   %c\t", *(ar + (2 * c * i) + ((2 * j) + 1)));
    	}
    	printf("\n");
    }	printf("\n");
}

void printStateTableMoore(char *ar, char *ip, int r, int c){
	printf("\nState Table for Moore:\n----------------------\n   PS\t");
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

char **toMoore(char *ar, char *ip, int r, int c, int *len){
	int ipn = strlen(ip), sts[r][ipn], k = 0;
	for(int i = 0; i < r; i++)
		for(int j = 0; j < ipn; j++)
			sts[i][j] = 0;
	for(int i = 0; i < r; i++)
		for(int j = 0; j < c; j += 2){
			int st = *(ar + (c * i) + j + 0) - 'A';
			int op = *(ar + (c * i) + j + 1) - ip[0];
			sts[st][op] = 1;
		}
	for(int i = 0; i < r; i++)
		for(int j = 0; j < ipn; j++)
			if(sts[i][j] == 1)	k++;

	cell *intStates[k][(c / 2) + 1];
	char intOutput[k][c / 2]; k = 0;
	for(int i = 0; i < r; i++)
		for(int j = 0; j < ipn; j++){
			if(sts[i][j] == 1){
				cell *temp = (cell *) malloc(sizeof(cell));
				temp -> staNo = i;
				temp -> subNo = j;
				intStates[k++][0] = temp;
			}
		}
	for(int i = 0; i < k; i++){
		cell *temp = intStates[i][0];
		int curr = temp -> staNo;
		for(int j = 0; j < c; j += 2){
			cell *new = (cell *) malloc(sizeof(cell));
			new -> staNo = *(ar + (c * curr) + j + 0) - 'A';
			new -> subNo = *(ar + (c * curr) + j + 1) - ip[0];
			intStates[i][(j / 2) + 1] = new;
			intOutput[i][j / 2] = new -> subNo;
		}
	}
	printf("\nState Table for Intermediate:\n-----------------------------\n");
	for(int i = 0; i < k; i++){
		cell *temp = intStates[i][0];
		printf("|%c%d|\t", (temp -> staNo) + 'A', temp -> subNo);
		for(int j = 1; j <= c / 2; j++){
			temp = intStates[i][j];
			printf("|%c%d|\t", (temp -> staNo) + 'A', temp -> subNo);
			printf("| %d |\t", intOutput[i][j - 1]);
		}	printf("\n");
	}	printf("\n");

	char **final = (char **) malloc(sizeof(char *) * k);
	for(int i = 0; i < k; i++)
		final[i] = (char *) malloc(sizeof(char) * ((c / 2) + 1));
	for(int i = 0; i < k; i++){
		for(int j = 0; j < c / 2; j++){
			cell *temp = intStates[i][j + 1];
			int st = temp -> staNo;
			int op = temp -> subNo, p, l = 0;
			for(int i = 0; i < op; i++)
				if(sts[st][i] == 1)	l++;
			for(int i = 0; i < k; i++){
				cell *pos = intStates[i][0];
				if(pos -> staNo == st){		p = i; break;	}
			}	final[i][j] = p + l;
		}
		cell *now = intStates[i][0];
		final[i][c / 2] = now -> subNo;
	}	*len = k;
	
	if(final[0][c / 2] == 1){
		char **nwfin = (char **) malloc(sizeof(char *) * (k + 1));
		for(int i = 0; i < k + 1; i++)
			nwfin[i] = (char *) malloc(sizeof(char) * ((c / 2) + 1));
		for(int i = 1; i < k + 1; i++){
			for(int j = 0; j < c / 2; j++)
				nwfin[i][j] = final[i - 1][j] + 'B';
			nwfin[i][c / 2] = final[i - 1][c / 2] + ip[0];
		}	*len = k + 1;
		for(int j = 0; j < c / 2; j++)
			nwfin[0][j] = nwfin[1][j];
		nwfin[0][c / 2] = ip[0];
		return nwfin;
	}
	return final;
}