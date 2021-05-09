#include <stdio.h>  // printf, scanf
#include <stdlib.h> // abs
#include <string.h> // strlen

#include "../utils.h"
#define MOD 26
#define BLK 5

/*
 * Cipher keyed-transposition encrypts (in place) all input string and generates a key string.
 *
 * s: the string
 * k: key string
 */
void encrypt(char *s, char *k)
{
    int len = strlen(s);
    int rlen = len / BLK + (len % BLK == 0 ? 0 : 1);
    char mat[rlen][BLK];

    for (int r = 0; r < rlen; r++)
    {
        for (int c = 0; c < BLK; c++)
        {
            int pos = r * BLK + c;
            mat[r][c] = pos < len ? s[pos] : 'Z';
        }
    }

    printf("    ");
    for (int i = 0; i < BLK; i++)
    {
        printf("%d  ", i + 1);
    }
    printf("\n\n");

    printf("  Initial:\n");
    for (int r = 0; r < rlen; r++)
    {
        printf("    ");
        for (int c = 0; c < BLK; c++)
        {
            printf("%c  ", mat[r][c]);
        }
        printf("\n");
    }

    int trx[rlen][BLK];
    for (int i = 0; i < BLK; i++)
    {
        int c = k[i] - '1';
        for (int j = 0; j < rlen; j++)
        {
            trx[j][i] = mat[j][c];
        }
    }
    printf("\n  Transposing:\n");
    for (int r = 0; r < rlen; r++)
    {
        printf("    ");
        for (int c = 0; c < BLK; c++)
        {
            printf("%c  ", trx[r][c]);
        }
        printf("\n");
    }

    for (int r = 0; r < rlen; r++)
    {
        for (int c = 0; c < BLK; c++)
        {
            s[r * BLK + c] = trx[r][c];
        }
    }
}

/*
 * Cipher keyed-transposition decrypts (in place) all characters of a string.
 *
 * s: the string
 * k: key string
 */
void decrypt(char *s, char *k)
{
    int len = strlen(s);
    int rlen = len / BLK + (len % BLK == 0 ? 0 : 1);
    char mat[rlen][BLK];

    for (int r = 0; r < rlen; r++)
    {
        for (int c = 0; c < BLK; c++)
        {
            mat[r][c] = s[r * BLK + c];
        }
    }

    printf("    ");
    for (int i = 0; i < BLK; i++)
    {
        printf("%d  ", i + 1);
    }
    printf("\n\n");

    printf("  Initial:\n");
    for (int r = 0; r < rlen; r++)
    {
        printf("    ");
        for (int c = 0; c < BLK; c++)
        {
            printf("%c  ", mat[r][c]);
        }
        printf("\n");
    }

    char ki[BLK];
    for (int i = 0; i < BLK; i++)
    {
        ki[k[i] - '1'] = i + '1';
    }
    printf("\n  Key Inverse: %s\n", ki);

    int trx[rlen][BLK];
    for (int i = 0; i < BLK; i++)
    {
        int c = ki[i] - '1';
        for (int j = 0; j < rlen; j++)
        {
            trx[j][i] = mat[j][c];
        }
    }
    printf("\n  Inverse Transposing:\n");
    for (int r = 0; r < rlen; r++)
    {
        printf("    ");
        for (int c = 0; c < BLK; c++)
        {
            printf("%c  ", trx[r][c]);
        }
        printf("\n");
    }

    for (int r = 0; r < rlen; r++)
    {
        for (int c = 0; c < BLK; c++)
        {
            s[r * BLK + c] = trx[r][c];
        }
    }
}

// -----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    char s[256];
    char k[5];

    printf("\nImplementation of Keyed Transposition Cipher\n--------\n");
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
        printf("Enter key: ");
        scanf(" %s", k);
        if (strlen(k) != BLK)
        {
            repeat = 1;
            continue;
        }
        repeat = 0;
        for (int i = 0; k[i] != '\0'; i++)
        {
            if (k[i] < '1' || k[i] > '5')
            {
                printf("  Invalid string, retry\n");
                repeat = 1;
                break;
            }
        }
    } while (repeat);
    printf("\nEncryption:\n");
    encrypt(s, k);
    printf("\nEncrypted string: %s\n", s);
    printf("\nDecryption:\n");
    decrypt(s, k);
    printf("\nDecrypted string: %s\n", s);
    printf("\n");
}
