#include <stdio.h>  // printf, scanf
#include <stdlib.h> // abs, srand, rand
#include <string.h> // strlen
#include <time.h>   // time

#include "utils.h"
#define MOD 26

/*
 * Cipher hill encrypts (in place) all characters of a string w.r.t a key.
 *
 * s: the string
 * ord_key: order of cipher key matrix
 * key: cipher key matrix
 */
void encrypt(char *s, int ord_key, int **key)
{
    printf("  Original string:\n");
    for (int i = 0; i < strlen(s); i++)
    {
        printf("    %c (%2d)\n", s[i], s[i] - 'A');
    }

    int temp[ord_key];

    printf("\n  Multiplied:\n");
    for (int r = 0; r < ord_key; r++)
    {
        printf("    ");
        for (int c = 0; c < ord_key; c++)
        {
            printf("%3d ", key[r][c]);
        }
        printf("%7d", s[r] - 'A');

        int sum = 0;
        for (int c = 0; c < ord_key; c++)
        {
            sum += key[r][c] * (s[c] - 'A');
        }
        temp[r] = sum;
        printf("   |    %3d\n", sum);
    }

    printf("\n  Multiplied matrix (mod 26):\n");
    for (int i = 0; i < ord_key; i++)
    {
        s[i] = mod_26(temp[i]) + 'A';
        printf("    %c (%2d)\n", s[i], s[i] - 'A');
    }
}

/*
 * Cipher hill decrypts (in place) all characters of a string w.r.t a key.
 *
 * s: the string
 * ord_key: order of cipher key matrix
 * key: cipher key matrix
 */
void decrypt(char *s, int ord_key, int **key)
{
    int **key_inv;
    key_inv = malloc((ord_key) * sizeof *key_inv);
    for (int i = 0; i < ord_key; i++)
    {
        key_inv[i] = malloc(ord_key * sizeof *key_inv[i]);
    }
    mat_invert(ord_key, key, key_inv);

    printf("  Inverted key:\n");
    for (int r = 0; r < ord_key; r++)
    {
        printf("    ");
        for (int c = 0; c < ord_key; c++)
        {
            printf("%3d ", key_inv[r][c]);
        }
        printf("\n");
    }

    int temp[ord_key];

    printf("\n  Multiplied:\n");
    for (int r = 0; r < ord_key; r++)
    {
        printf("    ");
        for (int c = 0; c < ord_key; c++)
        {
            printf("%3d ", key_inv[r][c]);
        }
        printf("%7d", s[r] - 'A');

        int sum = 0;
        for (int c = 0; c < ord_key; c++)
        {
            sum += key_inv[r][c] * (s[c] - 'A');
        }
        temp[r] = sum;
        printf("   |    %3d\n", sum);
    }

    printf("\n  Multiplied matrix (mod 26):\n");
    for (int i = 0; i < ord_key; i++)
    {
        s[i] = mod_26(temp[i]) + 'A';
        printf("    %c (%2d)\n", s[i], s[i] - 'A');
    }

    for (int i = 0; i < ord_key; i++)
    {
        free(key_inv[i]);
    }
    free(key_inv);
}

// -----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    char s[256];
    printf("\nImplementation of Hill Cipher\n--------\n");
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

    int ord_key = strlen(s);
    int **key;
    key = malloc((ord_key) * sizeof *key);
    for (int i = 0; i < ord_key; i++)
    {
        key[i] = malloc(ord_key * sizeof *key[i]);
    }

    // Key manually provided for cases 2 and 3 for debugging and reviewing
    if (ord_key == 2)
    {
        key[0][0] = 25;
        key[0][1] = 22;
        key[1][0] = 4;
        key[1][1] = 21;
    }
    else if (ord_key == 3)
    {
        key[0][0] = 6;
        key[0][1] = 24;
        key[0][2] = 1;
        key[1][0] = 13;
        key[1][1] = 16;
        key[1][2] = 10;
        key[2][0] = 20;
        key[2][1] = 17;
        key[2][2] = 15;
    }
    else
    {
        srand(time(0));
        do
        {
            for (int i = 0; i < ord_key; i++)
            {
                for (int j = 0; j < ord_key; j++)
                {
                    key[i][j] = rand() % 26;
                }
            }

            repeat = mat_invert_check(ord_key, key);
        } while (repeat);
    }

    printf("\nKey:\n");
    for (int i = 0; i < ord_key; i++)
    {
        for (int j = 0; j < ord_key; j++)
        {
            printf("%3d ", key[i][j]);
        }
        printf("\n");
    }

    printf("\nEncryption:\n");
    encrypt(s, ord_key, key);
    printf("\nEncrypted string: %s\n", s);
    printf("\nDecryption:\n");
    decrypt(s, ord_key, key);
    printf("\nDecrypted string: %s\n", s);
    printf("\n");

    for (int i = 0; i < ord_key; i++)
    {
        free(key[i]);
    }
    free(key);
}
