#include <stdio.h>  // printf, scanf
#include <stdlib.h> // abs, srand, rand
#include <string.h> // strlen
#include <time.h>   // time

#include "../utils.h"
#define MOD 26

/*
 * Cipher permutation encrypts (in place) all characters of a string w.r.t a key.
 *
 * s: the string
 * ord_key: order of cipher key matrix
 * key: cipher key matrix
 */
void encrypt(char *s, int ord_key, int **key)
{
    int len = strlen(s);
    int rlen = len / ord_key + (len % ord_key == 0 ? 0 : 1);

    int mat[rlen][ord_key];
    for (int r = 0; r < rlen; r++)
    {
        for (int c = 0; c < ord_key; c++)
        {
            int pos = r * ord_key + c;
            mat[r][c] = pos < len ? s[pos] - 'A' : 25;
        }
    }

    printf("  Initial:\n");
    for (int r = 0; r < rlen; r++)
    {
        printf("    ");
        for (int c = 0; c < ord_key; c++)
        {
            printf("%c (%2d)  ", mat[r][c] + 'A', mat[r][c]);
        }
        printf("\n");
    }

    int temp[rlen][ord_key];

    printf("\n  Multiplied:\n");
    for (int r = 0; r < rlen; r++)
    {
        for (int c = 0; c < ord_key; c++)
        {
            int sum = 0;
            for (int m = 0; m < ord_key; m++)
            {
                sum += mat[r][m] * key[m][c];
            }
            temp[r][c] = sum;
        }
    }

    for (int r = 0; r < rlen; r++)
    {
        printf("    ");
        for (int c = 0; c < ord_key; c++)
        {
            printf("%c (%2d)  ", temp[r][c] + 'A', temp[r][c]);
        }
        printf("\n");
    }

    for (int r = 0; r < rlen; r++)
    {
        for (int c = 0; c < ord_key; c++)
        {
            s[r * ord_key + c] = temp[r][c] + 'A';
        }
    }
    s[ord_key * rlen] = '\0';
}

/*
 * Cipher permutation decrypts (in place) all characters of a string w.r.t a key.
 *
 * s: the string
 * ord_key: order of cipher key matrix
 * key: cipher key matrix
 */
void decrypt(char *s, int ord_key, int **key)
{
    int len = strlen(s);
    int rlen = len / ord_key + (len % ord_key == 0 ? 0 : 1);

    int mat[rlen][ord_key];
    for (int r = 0; r < rlen; r++)
    {
        for (int c = 0; c < ord_key; c++)
        {
            mat[r][c] = s[r * ord_key + c] - 'A';
        }
    }

    int temp[rlen][ord_key];

    char k[ord_key];
    for (int c = 0; c < ord_key; c++)
    {
        for (int r = 0; r < ord_key; r++)
        {
            if (key[r][c] == 1)
            {
                k[c] = r + '1';
                break;
            }
        }
    }
    char ki[ord_key];
    for (int i = 0; i < ord_key; i++)
    {
        ki[k[i] - '1'] = i + '1';
    }

    int **key_inv;
    key_inv = malloc((ord_key) * sizeof *key_inv);
    for (int i = 0; i < ord_key; i++)
    {
        key_inv[i] = malloc(ord_key * sizeof *key_inv[i]);
    }

    // mat_invert(ord_key, key, key_inv);

    for (int c = 0; c < ord_key; c++)
    {
        for (int r = 0; r < ord_key; r++)
        {
            key_inv[r][c] = 0;
        }
    }
    for (int i = 0; i < ord_key; i++)
    {
        key_inv[ki[i] - '1'][i] = 1;
    }

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

    printf("\n  Multiplied:\n");
    for (int r = 0; r < rlen; r++)
    {
        for (int c = 0; c < ord_key; c++)
        {
            int sum = 0;
            for (int m = 0; m < ord_key; m++)
            {
                sum += mat[r][m] * key_inv[m][c];
            }
            temp[r][c] = sum;
        }
    }

    for (int r = 0; r < rlen; r++)
    {
        printf("    ");
        for (int c = 0; c < ord_key; c++)
        {
            printf("%c (%2d)  ", temp[r][c] + 'A', temp[r][c]);
        }
        printf("\n");
    }

    for (int r = 0; r < rlen; r++)
    {
        for (int c = 0; c < ord_key; c++)
        {
            s[r * ord_key + c] = temp[r][c] + 'A';
        }
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
    printf("\nImplementation of Permutation Cipher\n--------\n");
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

    char ks[] = "41627385";
    int ord_key = 8;
    int **key;
    key = malloc((ord_key) * sizeof *key);
    for (int i = 0; i < ord_key; i++)
    {
        key[i] = malloc(ord_key * sizeof *key[i]);
    }

    for (int i = 0; i < ord_key; i++)
    {
        for (int j = 0; j < ord_key; j++)
        {
            key[i][j] = 0;
        }
    }
    for (int i = 0; i < ord_key; i++)
    {
        key[ks[i] - '1'][i] = 1;
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

    printf("\n--------\n\n");

    char sx[256] = "TGEEMNELNNTDROEOAAHDOETCSHAEIRLM";
    printf("For encrypted string: %s", sx);
    printf("\nDecryption:\n");
    decrypt(sx, ord_key, key);
    printf("\nDecrypted string: %s\n", sx);
    printf("\n");

    for (int i = 0; i < ord_key; i++)
    {
        free(key[i]);
    }
    free(key);
}
