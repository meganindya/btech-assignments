#include <stdio.h>  // printf, scanf
#include <stdlib.h> // abs
#include <string.h> // strlen

#include "utils.h"
#define MOD 26

/*
 * Cipher playfair encrypts (in place) all characters of a string w.r.t a key.
 *
 * s: the string
 * key: cipher key matrix
 */
void encrypt(char *s, int **key)
{
    int len = strlen(s);
    if ((len & 1) == 1)
    {
        printf("  Salting odd length string with 'Z' at end\n\n");
        s[len] = 'Z';
        s[len + 1] = '\0';
    }

    int map[26][2];
    map[9][0] = -1; // row of 'J'
    map[9][1] = -1; // col of 'J'
    for (int r = 0; r < 5; r++)
    {
        for (int c = 0; c < 5; c++)
        {
            map[key[r][c]][0] = r;
            map[key[r][c]][1] = c;
        }
    }

    printf("  Pairwise transformation:\n");
    for (int i = 0; s[i] != '\0'; i += 2)
    {
        int a_r = map[s[i] - 'A'][0];
        int a_c = map[s[i] - 'A'][1];
        int b_r = map[s[i + 1] - 'A'][0];
        int b_c = map[s[i + 1] - 'A'][1];

        int r_a, r_b;

        if (a_r == b_r)
        {
            r_a = key[a_r][mod(a_c + 1, 5)];
            printf("    %c (%d, %d) -> %c (%d, %d)\n", s[i], a_r, a_c, r_a + 'A', a_r, mod(a_c + 1, 5));
            r_b = key[a_r][mod(b_c + 1, 5)];
            printf("    %c (%d, %d) -> %c (%d, %d)\n", s[i + 1], b_r, b_c, r_b + 'A', a_r, mod(b_c + 1, 5));
        }
        else if (a_c == b_c)
        {
            r_a = key[mod(a_r + 1, 5)][a_c];
            printf("    %c (%d, %d) -> %c (%d, %d)\n", s[i], a_r, a_c, r_a + 'A', mod(a_r + 1, 5), a_c);
            r_b = key[mod(b_r + 1, 5)][a_c];
            printf("    %c (%d, %d) -> %c (%d, %d)\n", s[i + 1], b_r, b_c, r_b + 'A', mod(b_r + 1, 5), a_c);
        }
        else
        {
            r_a = key[a_r][b_c];
            printf("    %c (%d, %d) -> %c (%d, %d)\n", s[i], a_r, a_c, r_a + 'A', a_r, b_c);
            r_b = key[b_r][a_c];
            printf("    %c (%d, %d) -> %c (%d, %d)\n", s[i + 1], b_r, b_c, r_b + 'A', b_r, a_c);
        }

        s[i] = r_a + 'A';
        s[i + 1] = r_b + 'A';
    }
}

/*
 * Cipher playfair decrypts (in place) all characters of a string w.r.t a key.
 *
 * s: the string
 * key: cipher key matrix
 */
void decrypt(char *s, int **key)
{
    int map[26][2];
    map[9][0] = -1; // row of 'J'
    map[9][1] = -1; // col of 'J'
    for (int r = 0; r < 5; r++)
    {
        for (int c = 0; c < 5; c++)
        {
            map[key[r][c]][0] = r;
            map[key[r][c]][1] = c;
        }
    }

    printf("  Pairwise transformation:\n");
    for (int i = 0; s[i] != '\0'; i += 2)
    {
        int a_r = map[s[i] - 'A'][0];
        int a_c = map[s[i] - 'A'][1];
        int b_r = map[s[i + 1] - 'A'][0];
        int b_c = map[s[i + 1] - 'A'][1];

        int r_a, r_b;

        if (a_r == b_r)
        {
            r_a = key[a_r][mod(a_c - 1, 5)];
            printf("    %c (%d, %d) -> %c (%d, %d)\n", s[i], a_r, a_c, r_a + 'A', a_r, mod(a_c - 1, 5));
            r_b = key[a_r][mod(b_c - 1, 5)];
            printf("    %c (%d, %d) -> %c (%d, %d)\n", s[i + 1], b_r, b_c, r_b + 'A', a_r, mod(b_c - 1, 5));
        }
        else if (a_c == b_c)
        {
            r_a = key[mod(a_r - 1, 5)][a_c];
            printf("    %c (%d, %d) -> %c (%d, %d)\n", s[i], a_r, a_c, r_a + 'A', mod(a_r - 1, 5), a_c);
            r_b = key[mod(b_r - 1, 5)][a_c];
            printf("    %c (%d, %d) -> %c (%d, %d)\n", s[i + 1], b_r, b_c, r_b + 'A', mod(b_r - 1, 5), a_c);
        }
        else
        {
            r_a = key[a_r][b_c];
            printf("    %c (%d, %d) -> %c (%d, %d)\n", s[i], a_r, a_c, r_a + 'A', a_r, b_c);
            r_b = key[b_r][a_c];
            printf("    %c (%d, %d) -> %c (%d, %d)\n", s[i + 1], b_r, b_c, r_b + 'A', b_r, a_c);
        }

        s[i] = r_a + 'A';
        s[i + 1] = r_b + 'A';
    }
}

// -----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    char s[256], key_s[16];
    printf("\nImplementation of Playfair Cipher\n--------\n");
    int repeat;
    do
    {
        printf("Enter a string (A-Z) to encrypt: ");
        scanf("%s", s);
        repeat = 0;
        for (int i = 0; s[i] != '\0'; i++)
        {
            if (s[i] < 'A' || s[i] > 'Z')
            {
                printf("  Invalid string, retry\n");
                repeat = 1;
                break;
            }
        }
    } while (repeat);
    do
    {
        printf("Enter cipher key string (A-Z except J): ");
        scanf("%s", key_s);
        repeat = 0;
        for (int i = 0; s[i] != '\0'; i++)
        {
            if (s[i] < 'A' || s[i] > 'Z' || s[i] == 'J')
            {
                printf("  Invalid string, retry\n");
                repeat = 1;
                break;
            }
        }
    } while (repeat);

    int **key;
    key = malloc(5 * sizeof *key);
    for (int i = 0; i < 5; i++)
    {
        key[i] = malloc(5 * sizeof *key[i]);
    }
    int flags[26];
    for (int i = 0; i < 26; i++)
    {
        flags[i] = 0;
    }
    flags[9] = 1;
    for (int i = 0; i < strlen(key_s); i++)
    {
        key[i / 5][i % 5] = key_s[i] - 'A';
        flags[key_s[i] - 'A'] = 1;
    }
    int k = strlen(key_s), ki = 0;
    while (k < 25)
    {
        while (flags[ki] == 1)
        {
            ki++;
        }
        key[k / 5][k % 5] = ki++;
        k++;
    }

    printf("\nKey:\n");
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            printf("%3d (%c) ", key[i][j], key[i][j] + 'A');
        }
        printf("\n");
    }

    printf("\nEncryption:\n");
    encrypt(s, key);
    printf("\nEncrypted string: %s\n", s);
    printf("\nDecryption:\n");
    decrypt(s, key);
    printf("\nDecrypted string: %s\n", s);
    printf("\n");

    for (int i = 0; i < 5; i++)
    {
        free(key[i]);
    }
    free(key);
}
