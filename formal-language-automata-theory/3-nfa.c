// Author : Anindya Kundu - 510817020

// This program stores and prints the State Table of a
// Non-deterministic Finite Automata. It takes the
// "number of states", the "inputs", the "transitional
// functions" and the final state as input.

// The Table is a 2D array of rows = number of states
// and columns = number of inputs.
//   '→' is placed before initial state.
//   '●' is placed before final state.
// The data type of the table is a defined structure
// containing the string of the next states and length.

// It is assumed that the states are serially denoted
// from 'A', hence present state isn't stored. It is
// also assumed that the first state is the initial
// state. Also, the input syntax is to be correct
// semantically and syntactically as follows:
// * Enter Number of States: *integer*
// * Enter Inputs: #,#,..,# (# : lower alpha / digit)
// * Enter Transitional Functions:
// *   δ(%, $) → #,...,#  *uppercase alphabet / '-'*
//                        (only '-' in it's case)
// * Enter Final State/s: *uppercase alphabet*
// * Enter String to Check: *string of lalpha/ digit*
// * Check Another String? (Y/n): *character*

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>

#define clear() printf("\033[H\033[J")

typedef struct nfa{
	char *s;   //string of next states
	int n;     //length of string
}	cell;

char *getVals(int *, int);
void inputTransFuncs(cell **, char *, int, int);
void printStateTable(cell **, char *, int, int, char *);
int max(int *, int);
int checkAccepted(char *, cell **, int, char *, char *, int, int);

int main(int argc, char *argv[]){
    clear(); int r, c;
    printf("Enter Number of States: ");
    scanf("%d", &r);
    printf("Enter Inputs: ");
    char *ip = getVals(&c, 1);
    printf("Enter Transitional Functions:\n");
    cell *ar[r][c]; inputTransFuncs(&ar[0][0], ip, r, c);
    printf("Enter Final State/s: ");
    int n_fin; char *fin = getVals(&n_fin, 2);

    printf("\nState Table:\n------------\n");
    printStateTable(&ar[0][0], ip, r, c, fin);

    check:
    printf("\nEnter String to Check: ");
    char str[64]; scanf("%s", str);
    int z = checkAccepted(str, &ar[0][0], c, ip, fin, 0, 0);
    if(z == 1)			printf("-- String is Accepted by NFA\n");
    else if(z == 0)		printf("-- String is NOT Accepted by NFA\n");
    else if(z == -1)	printf("-- String is INVALID\n");
    printf("\nCheck Another String? (Y/n): ");
    char x; scanf(" %c", &x);
    if(x == 'Y' || x == 'y')	goto check;

    printf("\n");
    return 0;
}

//returns a string of inputs(z = 1) / next states(z = 2)
//  (stores length in passed pointer)
char *getVals(int *n, int z){
    char s[64], t[64]; *n = 0;
    scanf("%s", s);
    for(int i = 0; s[i] != '\0'; i++){
        if(z == 1 && (islower(s[i]) || isdigit(s[i])))  t[(*n)++] = s[i];
        if(z == 2 && (isupper(s[i]) || s[i] == '-'))    t[(*n)++] = s[i];
    }
    char *ip = (char *) malloc(sizeof(char) * (*n));
    for(int i = 0; i < (*n); i++)   ip[i] = t[i];
    return ip;
}

void inputTransFuncs(cell **ar, char *ip, int r, int c){
    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            printf("  δ(%c, %c) → ", ('A' + i), *(ip + j));
            cell *temp = (cell *) malloc(sizeof(cell));
            temp -> s = getVals(&(temp -> n), 2);
            *(ar + (c * i) + j) = temp;
        }
    }
}

void printStateTable(cell **ar, char *ip, int r, int c, char *fn){
    printf("   P S\t");
    if(c % 2 != 0)
    {   for(int i = 1; i < c / 2; i++)  printf("\t");   printf("   ");  }
    else
    {   for(int i = 1; i < (c - 1) / 2; i++)  printf("\t");   printf("       ");  }
    printf("N S\n--------");
    for(int i = 0; i < c; i++)  printf("|-------"); printf("\n\t");
    for(int i = 0; i < c; i++)  printf("    %c\t", ip[i]);
    printf("\n********");
    for(int i = 0; i < c; i++)  printf("|*******"); printf("\n");

    for(int i = 0; i < r; i++){
        int n_row[c], max_vals;
        for(int j = 0; j < c; j++){
        	cell *temp = *(ar + (c * i) + j);
        	n_row[j] = temp -> n;
        }
        max_vals = max(n_row, c);
        if(i == 0){	printf("  → %c\t", ('A' + i)); goto skip;	}
        for(int k = 0; fn[k] != '\0'; k++)
        	if(fn[k] == ('A' + i)){
        		printf("  ● %c\t", ('A' + i));
        		goto skip; break;
        	}
        printf("    %c\t", ('A' + i));
        skip:
        for(int k = 0; k < max_vals; k++){
        	if(k != 0)	printf("\t");
        	for(int j = 0; j < c; j++){
        		cell *temp = *(ar + (c * i) + j);
        		if(k < (temp -> n))	printf("|   %c\t", temp -> s[k]);
        		else				printf("|\t");
        	}  	printf("\n");
        }
    	printf("--------");
    	for(int i = 0; i < c; i++)	printf("|-------"); printf("\n");
    }
}

//returns max element of array
int max(int *a, int n){
	int z = INT_MIN;
	for(int i = 0; i < n; i++)
		if(a[i] > z)	z = a[i];
	return z;
}

//returns 1 if string is accepted, 0 is not, -1 if invalid
int checkAccepted(char *s, cell **ar, int c, char *ip, char *fn, int p, int ps){
	if(p == strlen(s)){                    //base class (last state)
		char ends = 'A' + ps;              //converts row number into notation
		for(int i = 0; fn[i] != '\0'; i++) //checks if state is final
			if(ends == fn[i]){   return 1; break;   }
		return 0;                          //returns 0 for not final
	}
	char x = s[p]; int col = -1, row = ps;
	for(int i = 0; ip[i] != '\0'; i++)     //finds column of input in table
		if(x == ip[i]){	col = i; break;	}
	if(col == -1)	return -1;             //invalid character in string
	cell *temp = *(ar + (c * row) + col);  //locates required cell in table
	int status = 0;
	for(int i = 0; i < temp -> n; i++){
        if(temp -> s[i] == '-') return 0;   //returns 0 for null state
		int next = (temp -> s[i]) - (int)'A'; //locates row of next state
            //recurs into the next state and does OR operation on status
		status |= checkAccepted(s, ar, c, ip, fn, p + 1, next);
	}	return status;
}