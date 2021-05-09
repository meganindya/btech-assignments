#include <stdio.h>  // printf, scanf
#include <stdlib.h> // abs
#include <string.h> // strlen

#include "../utils.h"
#define MOD 26

/*
 * Cipher Vigenere encrypts (in place) all input string and generates a key string.
 *
 * s: the string
 * key: key string
 */
void encrypt(char *s, char *key)
{
    int len = strlen(s);

    int len_k = strlen(key);
    char k[256];
    for (int i = 0; i < len; i++)
    {
        k[i] = key[i % len_k];
    }
    k[len] = '\0';

    printf("  Key:\n");
    printf("    ");
    for (int i = 0; i < len; i++)
    {
        printf(" %c  ", k[i]);
    }
    printf("\n    ");
    for (int i = 0; i < len; i++)
    {
        printf("%2d  ", k[i] - 'A');
    }
    printf("\n\n");

    for (int i = 0; i < len; i++)
    {
        char c = s[i];
        int c_n = c - 'A';
        char r = k[i];
        int r_n = r - 'A';
        int add_n = c_n + r_n;
        int enc_n = mod_26(add_n);
        char enc = enc_n + 'A';
        printf(
            "    %c (%2d)  ->  [(%2d + %2d) mod %d] = [%2d mod %d]  %c (%2d)\n",
            c,
            c_n,
            c_n,
            r_n,
            MOD,
            add_n,
            MOD,
            enc,
            enc_n);
        s[i] = enc;
    }
}

/*
 * Cipher Vigenere decrypts (in place) all characters of a string.
 *
 * s: the string
 * key: key string
 */
void decrypt(char *s, char *key)
{
    int len = strlen(s);

    int len_k = strlen(key);
    char k[256];
    for (int i = 0; i < len; i++)
    {
        k[i] = key[i % len_k];
    }
    k[len] = '\0';

    for (int i = 0; i < len; i++)
    {
        char c = s[i];
        int c_n = c - 'A';
        char r = k[i];
        int r_n = r - 'A';
        int sub_n = c_n - r_n;
        int enc_n = mod_26(sub_n);
        char enc = enc_n + 'A';
        printf(
            "    %c (%2d)  ->  [(%2d - %2d) mod %d] = [%3d mod %d]  %c (%2d)\n",
            c,
            c_n,
            c_n,
            r_n,
            MOD,
            sub_n,
            MOD,
            enc,
            enc_n);
        s[i] = enc;
    }
}

// -----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    char s[256];
    char k[256];

    printf("\nImplementation of Vigenere Cipher\n--------\n");
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
        repeat = 0;
        for (int i = 0; k[i] != '\0'; i++)
        {
            if (k[i] < 'A' || k[i] > 'Z')
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
