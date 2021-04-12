#include <stdio.h>  // printf, scanf
#include <stdlib.h> // abs
#include <string.h> // strlen

#include "../utils.h"
#define MOD 26

/*
 * Cipher Auto Key encrypts (in place) all input string and generates a key string.
 *
 * s: the string
 * a: auto key
 * k: array to fill generated key in
 */
void encrypt(char *s, char a, char *k)
{
    int len = strlen(s);

    k[0] = a;
    for (int i = 1; i < len; i++)
    {
        k[i] = s[i - 1];
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
 * Cipher Auto Key decrypts (in place) all characters of a string.
 *
 * s: the string
 * k: key string
 */
void decrypt(char *s, char *k)
{
    int len = strlen(k);

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
    char a;
    char k[256];

    printf("\nImplementation of Auto Key Cipher\n--------\n");
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
        printf("Enter auto key: ");
        scanf(" %c", &a);
        repeat = 0;
        if (a < 'A' || a > 'Z')
        {
            printf("  Invalid key, retry\n");
            repeat = 1;
            break;
        }
    } while (repeat);
    printf("\nEncryption:\n");
    encrypt(s, a, k);
    printf("\nEncrypted string: %s\n", s);
    printf("\nDecryption:\n");
    decrypt(s, k);
    printf("\nDecrypted string: %s\n", s);
    printf("\n");
}
