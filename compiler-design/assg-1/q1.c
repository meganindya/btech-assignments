#include <stdio.h>
#include <string.h>


int getType(int, char *);


int main(int argc, char *argv[]) {
    FILE *fi = fopen("input-1.txt", "r");
    FILE *fo = fopen("output-1.txt", "w");
    if (fi == NULL) goto exit;

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


int getType(int len, char *s) {
    int state = 0, p = 0;

    while (state != 5 && p < len) {
        char c = *(s + p);

        switch (state) {
            case 0:
                if (c == '0')
                    state = 4;
                else if (c >= '1' && c <= '9')
                    state = 1;
                else if (c == '.')
                    state = 2;
                else {
                    state = 5;
                }
            break;

            case 1:
                if (c >= '0' && c <= '9')
                    state = 1;
                else if (c == '.')
                    state = 2;
                else
                    state = 5;
            break;

            case 2:
                if (c >= '0' && c <= '9')
                    state = 3;
                else
                    state = 5;
            break;

            case 3:
                if (c >= '0' && c <= '9')
                    state = 3;
                else
                    state = 5;
            break;

            case 4:
                if (c == '.')
                    state = 2;
                else
                    state = 5;
            break;
        }

        p++;
    }


    if (state == 1)
        return 1;
    else if (state == 3)
        return 2;
    else
        return 0;
}
