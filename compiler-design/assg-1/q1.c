/*
Valid Integers:
  begins with 1 - 9, followed by any number
    of digits between 0 - 9
Valid Floating Point numbers:
  begins with 0., followed by any number of
    digits between 0 - 9
  begins with ., followed by any number of
    digits between 0 - 9
  begins with 1 - 9, followed by any number
    of digits between 0 - 9, followed by .,
    followed any whole number of digits
    between 0 - 9
*/


#include <stdio.h>
#include <string.h>


int getType(int, char *);


int main(int argc, char *argv[]) {
    FILE *fi = fopen("input-1.txt", "r");   // input file
    FILE *fo = fopen("output-1.txt", "w");  // output file
    if (fi == NULL) 
        goto exit;                  // exit if no input file

    // run until input strings exist
    while (!feof(fi)) {
        char string[64];
        fscanf(fi, "%s", string);
        
        int flag = getType(strlen(string), string);
        if (flag == 1)
            fprintf(fo, "Integer\n");
        else if (flag == 2)
            fprintf(fo, "Float\n");
        else
            fprintf(fo, "Invalid\n");
    }

    fclose(fi);
    fclose(fo);
    exit: return 0;
}


// function to determine whether passed string is
// an Integer, Float, or Invalid
int getType(int len, char *s) {
    int state = 0, p = 0;

    /*
    state 0: initial state
    state 1: first digit is between 1 - 9
             (end state)
    state 2: decimal has been encountered
    state 3: there is atleast one digit after decimal
             (end state)
    state 4: first digit is 0
    state 5: string isn't an integer or float
             (dead state)
    */

    // loop until end of string or dead state reached
    while (state != 5 && p < len) {
        char c = *(s + p);

        switch (state) {
            // initial state
            case 0:
                if (c == '0')
                    state = 4;
                else if (c >= '1' && c <= '9')
                    state = 1;
                else if (c == '.')
                    state = 2;
                else
                    state = 5;
            break;

            // first digit is between 1 - 9
            case 1:
                if (c >= '0' && c <= '9')
                    state = 1;
                else if (c == '.')
                    state = 2;
                else
                    state = 5;
            break;

            // decimal has been encountered
            case 2:
                if (c >= '0' && c <= '9')
                    state = 3;
                else
                    state = 5;
            break;

            // there is atleast one digit after decimal
            case 3:
                if (c >= '0' && c <= '9')
                    state = 3;
                else
                    state = 5;
            break;

            // first digit is 0
            case 4:
                if (c == '.')
                    state = 2;
                else
                    state = 5;
            break;
        }

        p++;
    }


    if (state == 1 || state == 4)
        return 1;
    else if (state == 3)
        return 2;
    else
        return 0;
}
