#include <stdio.h>
#include <string.h>


int main(int argc, char *argv[]) {
    FILE *fi = fopen("input-2.txt", "r");
    FILE *fo = fopen("output-2.txt", "w");
    if (fi == NULL) goto exit;

    char c;
    int state = 0;
    char comment[1024]; int i = 0;
    while ((c = fgetc(fi)) != EOF) {
        switch (state) {
            case 0:
                if (c == '/')
                    state = 1;
            break;

            case 1:
                if (c == '/')
                    state = 2;
                else if (c == '*')
                    state = 3;
                else
                    state = 0;
            break;

            case 2:
                if (c == '\n') {
                    comment[i++] = '\0';
                    fprintf(fo, "%s\n\n", comment);
                    state = i = 0;
                }
                else
                    comment[i++] = c;
            break;

            case 3:
                if (c == '*') {
                    comment[i++] = '*';
                    state = 4;
                }
                else
                    comment[i++] = c;
            break;

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
        }
    }


    fclose(fi);
    fclose(fo);
    exit: return 0;
}
