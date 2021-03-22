#include <stdio.h>  // printf, scanf
#include <stdlib.h> // abs

#include "utils.h"
#define MOD 26

/*
 * Cipher shifts (in place) all characters of a string by a distance.
 *
 * s: the string
 * z: shift distance
 */
void encrypt(char *s, int z)
{
    for (int i = 0; s[i] != '\0'; i++)
    {
        char c = s[i];
        int c_n = c - 'A';
        int add_n = c_n + z;
        int n_enc = mod_26(add_n);
        char c_enc = n_enc + 'A';
        printf(
            "    %c (%2d)  ->  [(%2d + %d) mod %d] = [%2d mod %d]  %c (%2d)\n",
            c,
            c_n,
            c_n,
            z,
            MOD,
            add_n,
            MOD,
            c_enc,
            n_enc);
        s[i] = c_enc;
    }
}

/*
 * Cipher unshifts (in place) all characters of a string by a distance.
 *
 * s: the string
 * z: shift distance
 */
void decrypt(char *s, int z)
{
    for (int i = 0; s[i] != '\0'; i++)
    {
        char c = s[i];
        int c_n = c - 'A';
        int sub_n = c_n - z;
        int n_dec = mod_26(sub_n);
        char c_dec = n_dec + 'A';
        printf(
            "    %c (%2d)  ->  [(%2d + (-%d)) mod %d] = [%2d mod %d]  %c (%2d)\n",
            c,
            c_n,
            c_n,
            z,
            MOD,
            sub_n,
            MOD,
            c_dec,
            n_dec);
        s[i] = c_dec;
    }
}

// -----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    char s[256];
    int z;
    printf("\nImplementation of Shift (Caesar) Cipher\n--------\n");
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
    printf("Enter cipher shift key: ");
    scanf("%d", &z);
    printf("\nEncryption:\n");
    encrypt(s, z);
    printf("\nEncrypted string: %s\n", s);
    printf("\nDecryption:\n");
    decrypt(s, z);
    printf("\nDecrypted string: %s\n", s);
    printf("\n");
}
