// @meganindya

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 128

enum tokens {
    INITIAL, INVALID, INTEGER, FLOAT, OPERATOR, COMMENT,
    STRING, CHARACTER, IDENTIFIER, WHITESPACE, KEYWORD, SEPARATOR
};

typedef struct {
    int state;
    enum tokens type;
} node;


void fillBuffer(int, char *);
int isDelimiter(char);
int isOperatorSymbol(char);
int isKeyword(char *);
node getNextNode(node, char, int *, int *);
void print_token(char *, int, int, enum tokens);




// global variables
FILE *fi, *fo;


int main(int argc, char *argv[]) {
    fi = fopen("input-3.txt", "r");   // input file
    fo = fopen("output-3.txt", "w");  // output file
    if (fi == NULL)
        goto exit;                  // exit if no input file


    char buffer[2 * BUFFER_SIZE];   // double buffer
    fillBuffer(0, buffer);
    fillBuffer(1, buffer);

    int buffer_no = 0;              // indicates buffer number
    int fp = 0, bp = 0;             // front and back pointer
    int state = 0;                  // state variable
    node next = { 0, INITIAL };

    char c;
    // parse buffer
    int z = 0;
    while ((c = buffer[bp]) != EOF) {
        if (next.state == 0 &&
            next.type != INITIAL &&
            next.type != SEPARATOR &&
            next.type != OPERATOR &&
            next.type != COMMENT) {
            print_token(buffer, fp, bp, next.type);
            fp = bp;
            next = (node) { 0, INITIAL };
        } else if (next.state != 0 && isDelimiter(c) &&
            next.type != COMMENT && next.type != OPERATOR &&
            next.type != STRING && next.type != CHARACTER) {
            print_token(buffer, fp, bp, next.type);
            fp = bp;
            next = (node) { 0, INITIAL };
        }

        if (isDelimiter(c) && !isOperatorSymbol(c) &&
            c != ' ' && c != '\"' && c != '\'') {
            fprintf(fo, "SEPARATOR\t%c\n", c);
            bp = (bp + 1) % (2 * BUFFER_SIZE);
            fp = bp;
            next = (node) { 0, SEPARATOR };
            continue;
        }

        next = getNextNode(next, c, &fp, &bp);
        
        bp = (bp + 1) % (2 * BUFFER_SIZE);
        if (!feof(fi) && bp % BUFFER_SIZE == 0)
            fillBuffer((1 + (bp / BUFFER_SIZE)) % 2, buffer);
    }


    fclose(fi);
    fclose(fo);
    exit: return 0;
}


// fills next N characters in specified buffer from file pointer
void fillBuffer(int buffer_no, char *buffer) {
    char c; int i = 0;
    
    // loop for characters until END OF BUFFER or END OF FILE
    while (!feof(fi) && i != BUFFER_SIZE && (c = fgetc(fi)) != EOF)
        buffer[(BUFFER_SIZE * buffer_no) + (i++)] = c;
    
    if (c == EOF)
        buffer[(BUFFER_SIZE * buffer_no) + (i++)] = c;

    while (i < BUFFER_SIZE)
        buffer[(BUFFER_SIZE * buffer_no) + (i++)] = EOF;
}


// returns true if character is a delimiter, else returns false
int isDelimiter(char c) {
    if (c == '(' || c == ')' || c == '{' || c == '}' ||
        c == '[' || c == ']' || c == '<' || c == '>' ||
        c == ';' || c == ',' || c == '|' || c == '=' ||
        c == '+' || c == '-' || c == '*' || c == '/' ||
        c == '%' || c == ' ' || c == '\"' || c == '\'')
        return 1;
    return 0;
}

// returns true if character belongs to an operator, else returns false
int isOperatorSymbol(char c) {
    if (c == '+' || c == '-' || c == '*' || c == '/' ||
        c == '<' || c == '>' || c == '%' || c == '=' ||
        c == '&' || c == '|' || c == '^' || c == '!' || c == '~')
        return 1;
    return 0;
}

// returns true if string is a keyword, else returns false
int isKeyword(char *s) {
    if (!strcmp(s, "auto") || !strcmp(s, "break") || !strcmp(s, "case") ||
        !strcmp(s, "char") || !strcmp(s, "const") || !strcmp(s, "continue") ||
        !strcmp(s, "default") || !strcmp(s, "do") || !strcmp(s, "double") ||
        !strcmp(s, "else") || !strcmp(s, "enum") || !strcmp(s, "extern") ||
        !strcmp(s, "float") || !strcmp(s, "for") || !strcmp(s, "goto") ||
        !strcmp(s, "if") || !strcmp(s, "int") || !strcmp(s, "long") ||
        !strcmp(s, "register") || !strcmp(s, "return") || !strcmp(s, "short") ||
        !strcmp(s, "signed") || !strcmp(s, "sizeof") || !strcmp(s, "static") ||
        !strcmp(s, "struct") || !strcmp(s, "switch") || !strcmp(s, "typedef") ||
        !strcmp(s, "union") || !strcmp(s, "unsigned") || !strcmp(s, "void") ||
        !strcmp(s, "volatile") || !strcmp(s, "while"))
        return 1;
    return 0;
}


// returns output of finite automata
node getNextNode(node curr, char c, int *fp, int *bp) {
    node next = { -1, INVALID };

    switch (curr.state) {
        case -1:
        break;
        // initial state
        case 0:
            // whitespace or newline
            if (c == ' ' || c == '\n')
                next = (node) { 0, WHITESPACE };
            // numeric
            else if (c >= '1' && c <= '9')
                next = (node) { 1, INTEGER };
            else if (c == '.')
                next = (node) { 2, INVALID };
            else if (c == '0')
                next = (node) { 4, INVALID };
            // comment, division
            else if (c == '/')
                next = (node) { 5, OPERATOR };
            // string, character
            else if (c == '\"')
                next = (node) { 9, STRING };
            else if (c == '\'')
                next = (node) { 10, CHARACTER };
            // identifier
            else if (c == '_' ||
                    (c >= 'a' && c <= 'z') ||
                    (c >= 'A' && c <= 'Z'))
                next = (node) { 11, IDENTIFIER };
            // operator
            else if (c == '+')
                next = (node) { 12, OPERATOR };
            else if (c == '-')
                next = (node) { 13, OPERATOR };
            else if (c == '*')
                next = (node) { 14, OPERATOR };
            else if (c == '%')
                next = (node) { 15, OPERATOR };
            else if (c == '=')
                next = (node) { 16, OPERATOR };
            else if (c == '&')
                next = (node) { 17, OPERATOR };
            else if (c == '|')
                next = (node) { 18, OPERATOR };
            else if (c == '^')
                next = (node) { 19, OPERATOR };
            else if (c == '!')
                next = (node) { 20, OPERATOR };
            else if (c == '<')
                next = (node) { 21, OPERATOR };
            else if (c == '>')
                next = (node) { 23, OPERATOR };
        break;
        
        /* NUMERIC STATES
           ============== */

        case 1:
            if (c >= '0' && c <= '9')
                next = (node) { 1, INTEGER };
            else if (c == '.')
                next = (node) { 2, INVALID };
        break;

        case 2:
            if (c >= '0' && c <= '9')
                next = (node) { 3, FLOAT };
        break;

        case 3:
            if (c >= '0' && c <= '9')
                next = (node) { 3, FLOAT };
        break;

        case 4:
            if (c == '.')
                next = (node) { 2, INVALID };
        break;

        /* COMMENT STATES
           ============== */

        case 5:
            if (c == '=')
                next = (node) { 0, OPERATOR };
            else if (c == '/')
                next = (node) { 6, COMMENT };
            else if (c == '*')
                next = (node) { 7, COMMENT };
            else {
                fprintf(fo, "OPERATOR\t/\n");
                *fp = *bp;
                next = getNextNode((node) { 0, OPERATOR }, c, fp, bp);
            }
        break;

        case 6:
            if (c == '\n')
                next = (node) { 0, COMMENT };
            else
                next = (node) { 6, COMMENT };
        break;

        case 7:
            if (c == '*')
                next = (node) { 8, COMMENT };
            else
                next = (node) { 7, COMMENT };
        break;

        case 8:
            if (c == '/')
                next = (node) { 0, COMMENT };
            else
                next = (node) { 7, COMMENT };
        break;

        /* STRING STATES
           ============= */

        case 9:
            if (c == '\"')
                next = (node) { 0, STRING };
            else
                next = (node) { 9, STRING };
        break;

        case 10:
            if (c == '\'')
                next = (node) { 0, CHARACTER };
            else
                next = (node) { 10, CHARACTER };
        break;

        /* IDENTIFIER
           ==================== */
        case 11:
            if (c == '_' ||
                (c >= 'a' && c <= 'z') ||
                (c >= 'A' && c <= 'Z') ||
                (c >= '0' && c <= '9'))
                next = (node) { 11, IDENTIFIER };
        break;

        /* MULTICHARACTER OPERATOR
           ======================= */
        
        case 12:
            if (c == '+') {
                fprintf(fo, "OPERATOR\t++\n");
                next = (node) { 0, OPERATOR };
            } else if (c == '=') {
                fprintf(fo, "OPERATOR\t+=\n");
                next = (node) { 0, OPERATOR };
            } else {
                fprintf(fo, "OPERATOR\t+\n");
                *fp = *bp;
                next = getNextNode((node) { 0, OPERATOR }, c, fp, bp);
            }
        break;

        case 13:
            if (c == '-') {
                fprintf(fo, "OPERATOR\t--\n");
                next = (node) { 0, OPERATOR };
            } else if (c == '=') {
                fprintf(fo, "OPERATOR\t-=\n");
                next = (node) { 0, OPERATOR };
            } else {
                fprintf(fo, "OPERATOR\t-\n");
                *fp = *bp;
                next = getNextNode((node) { 0, OPERATOR }, c, fp, bp);
            }
        break;

        case 14:
            if (c == '=') {
                fprintf(fo, "OPERATOR\t*=\n");
                next = (node) { 0, OPERATOR };
            } else {
                fprintf(fo, "OPERATOR\t*\n");
                *fp = *bp;
                next = getNextNode((node) { 0, OPERATOR }, c, fp, bp);
            }
        break;

        case 15:
            if (c == '=') {
                fprintf(fo, "OPERATOR\t%c=\n", '%');
                next = (node) { 0, OPERATOR };
            } else {
                fprintf(fo, "OPERATOR\t%c\n", '%');
                *fp = *bp;
                next = getNextNode((node) { 0, OPERATOR }, c, fp, bp);
            }
        break;

        case 16:
            if (c == '=') {
                fprintf(fo, "OPERATOR\t==\n");
                next = (node) { 0, OPERATOR };
            } else {
                fprintf(fo, "OPERATOR\t=\n");
                *fp = *bp;
                next = getNextNode((node) { 0, OPERATOR }, c, fp, bp);
            }
        break;

        case 17:
            if (c == '&') {
                fprintf(fo, "OPERATOR\t&&\n");
                next = (node) { 0, OPERATOR };
            } else if (c == '=') {
                fprintf(fo, "OPERATOR\t&=\n");
                next = (node) { 0, OPERATOR };
            } else {
                fprintf(fo, "OPERATOR\t&\n");
                *fp = *bp;
                next = getNextNode((node) { 0, OPERATOR }, c, fp, bp);
            }
        break;

        case 18:
            if (c == '|') {
                fprintf(fo, "OPERATOR\t||\n");
                next = (node) { 0, OPERATOR };
            } else if (c == '=') {
                fprintf(fo, "OPERATOR\t|=\n");
                next = (node) { 0, OPERATOR };
            } else {
                fprintf(fo, "OPERATOR\t|\n");
                *fp = *bp;
                next = getNextNode((node) { 0, OPERATOR }, c, fp, bp);
            }
        break;

        case 19:
            if (c == '=') {
                fprintf(fo, "OPERATOR\t^=\n");
                next = (node) { 0, OPERATOR };
            } else {
                fprintf(fo, "OPERATOR\t^\n");
                *fp = *bp;
                next = getNextNode((node) { 0, OPERATOR }, c, fp, bp);
            }
        break;

        case 20:
            if (c == '=') {
                fprintf(fo, "OPERATOR\t!=\n");
                next = (node) { 0, OPERATOR };
            } else {
                fprintf(fo, "OPERATOR\t!\n");
                *fp = *bp;
                next = getNextNode((node) { 0, OPERATOR }, c, fp, bp);
            }
        break;

        case 21:
            if (c == '<')
                next = (node) { 22, OPERATOR };
            else if (c == '=') {
                fprintf(fo, "OPERATOR\t<=\n");
                next = (node) { 0, OPERATOR };
            } else {
                fprintf(fo, "OPERATOR\t<\n");
                *fp = *bp;
                next = getNextNode((node) { 0, OPERATOR }, c, fp, bp);
            }
        break;

        case 22:
            if (c == '=') {
                fprintf(fo, "OPERATOR\t<<=\n");
                next = (node) { 0, OPERATOR };
            } else {
                fprintf(fo, "OPERATOR\t<<\n");
                *fp = *bp;
                next = getNextNode((node) { 0, OPERATOR }, c, fp, bp);
            }
        break;

        case 23:
            if (c == '>')
                next = (node) { 24, OPERATOR };
            else if (c == '=') {
                fprintf(fo, "OPERATOR\t>=\n");
                next = (node) { 0, OPERATOR };
            } else {
                fprintf(fo, "OPERATOR\t>\n");
                *fp = *bp;
                next = getNextNode((node) { 0, OPERATOR }, c, fp, bp);
            }
        break;

        case 24:
            if (c == '=') {
                fprintf(fo, "OPERATOR\t>>=\n");
                next = (node) { 0, OPERATOR };
            } else {
                fprintf(fo, "OPERATOR\t>>\n");
                *fp = *bp;
                next = getNextNode((node) { 0, OPERATOR }, c, fp, bp);
            }
        break;
    }

    return next;
}



void print_token(char *buffer, int fp, int bp, enum tokens type) {
    if (type == INITIAL || type == COMMENT || type == WHITESPACE)
        return;
    
    char token[2 * BUFFER_SIZE];
    memset(token, '\0', sizeof(token));
    int i = fp, k = 0;
    while (i < bp) {
        token[k++] = buffer[i];
        i = (i + 1) % (2 * BUFFER_SIZE);
    }

    if (isKeyword(token))
        type = KEYWORD;

    switch (type) {
        case INVALID:
            fprintf(fo, "INVALID\t\t");
        break;

        case INTEGER:
            fprintf(fo, "INTEGER\t\t");
        break;

        case FLOAT:
            fprintf(fo, "FLOAT\t\t");
        break;

        case OPERATOR:
            fprintf(fo, "OPERATOR\t");
        break;

        case STRING:
            fprintf(fo, "STRING\t\t");
        break;

        case CHARACTER:
            fprintf(fo, "CHARACTER\t");
        break;

        case IDENTIFIER:
            fprintf(fo, "IDENTIFIER\t");
        break;

        case KEYWORD:
            fprintf(fo, "KEYWORD\t\t");
        break;
    }

    fprintf(fo, "%s\n", token);
}
