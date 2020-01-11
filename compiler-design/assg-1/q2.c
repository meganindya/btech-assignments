// inline comments: begin with // and stretch until end of line
// multiline comments: enclosed between /* and */


#include <stdio.h>
#include <string.h>


int main(int argc, char *argv[]) {
    FILE *fi = fopen("input-2.txt", "r");   // input file
    FILE *fo = fopen("output-2.txt", "w");  // output file
    if (fi == NULL)
        goto exit;                  // exit if no input file


    char c;
    int state = 0;
    char comment[1024]; int i = 0;  // comment buffer and iterator

    // loop for characters until END OF FILE
    while ((c = fgetc(fi)) != EOF) {
        /*
        state 0: initial state (end state)
        state 1: one / has been encountered
        state 2: // has been encountered
        state 3: /* has been encountered
        state 4: * has been encountered after n number of
                 characters have followed /*
        state 5: // ' or " has been encountered
        */

        switch (state) {
            // initial state
            case 0:
                if (c == '/')
                    state = 1;
                else if (c == '\'' || c == '\"')
                    state = 5;
            break;                  // else no state change

            // one / has been encountered
            case 1:
                if (c == '/')
                    state = 2;
                else if (c == '*')
                    state = 3;
                else
                    state = 0;
            break;

            // two consecutive // have been encountered
            case 2:
                if (c == '\n') {
                    comment[i++] = '\0';
                    fprintf(fo, "%s\n\n", comment);
                    state = i = 0;
                }
                else                  // no state change
                    comment[i++] = c;
            break;

            // /* has been encountered
            case 3:
                if (c == '*') {
                    comment[i++] = '*';
                    state = 4;
                }
                else                  // no state change
                    comment[i++] = c;
            break;

            // * has been encountered after n number of
            // characters have followed /*
            case 4:
                if (c == '/') {
                    comment[i - 1] = '\0';
                    fprintf(fo, "%s\n\n", comment);
                    state = i = 0;
                }
                else {
                    comment[i++] = c;
                    state = 3;
                }
            break;

            // ' or " has been encountered
            case 5:
                if (c == '\'' || c == '\"')
                    state = 0;
            break;                  // else no state change
        }
    }


    fclose(fi);
    fclose(fo);
    exit: return 0;
}
