#include <stdio.h>  // printf, scanf
#include <stdlib.h> // abs

#include "utils.h"
#define MOD 26

/*
 * Cipher multiplicative encrypts (in place) all characters of a string w.r.t a key.
 *
 * s: the string
 * key: cipher key
 */
void encrypt(char *s, int key_mul, int key_add)
{
    printf("    for key (a, b) = (%d, %d)\n\n", key_mul, key_add);
    for (int i = 0; s[i] != '\0'; i++)
    {
        char enc_char = 'A' + mod_26((s[i] - 'A') * key_mul + key_add);
        printf(
            "    %c (%2d)  ->  [(%2d × %d + %d) mod %d] = [%2d mod %d]  %c (%2d)\n",
            s[i],
            s[i] - 'A',
            s[i] - 'A',
            key_mul,
            key_add,
            MOD,
            (s[i] - 'A') * key_mul + key_add,
            MOD,
            enc_char,
            enc_char - 'A');
        s[i] = enc_char;
    }
}

/*
 * Cipher multiplicative decrypts (in place) all characters of a string w.r.t a key.
 *
 * s: the string
 * key: cipher key
 */
void decrypt(char *s, int key_mul, int key_add)
{
    int key_add_inv = mod_26_add_inv(key_add);
    int key_mul_inv = mod_26_mul_inv(key_mul);
    printf("    for key (a, b) = (%d, %d)\n", key_mul, key_add);
    printf("    key (a = %d) multiplicative inverse (mod %d) = %d\n", key_mul, MOD, key_mul_inv);
    printf("    key (b = %d) additive inverse (mod %d) = %d\n", key_add, MOD, key_add_inv);
    for (int i = 0; s[i] != '\0'; i++)
    {
        char dec_char = 'A' + mod_26(((s[i] - 'A') + key_add_inv) * key_mul_inv);
        printf(
            "    %c (%2d)  ->  [((%2d + (%d)) × %d) mod %d] = [%3d mod %d]  %c (%2d)\n",
            s[i],
            s[i] - 'A',
            s[i] - 'A',
            key_add_inv,
            key_mul_inv,
            MOD,
            ((s[i] - 'A') + key_add_inv) * key_mul_inv,
            MOD,
            dec_char,
            dec_char - 'A');
        s[i] = dec_char;
    }
}

// -----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    char s[256];
    int key_add, key_mul;
    printf("\nImplementation of Affine Cipher\n--------\n");
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
    printf("Enter cipher additive key: ");
    scanf("%d", &key_add);
    do
    {
        printf("Enter cipher multiplicative key: ");
        scanf("%d", &key_mul);
        repeat = 0;
        if (mod_26_mul_inv(key_mul) == -1)
        {
            printf("  Invalid key, retry\n");
            repeat = 1;
        }
    } while (repeat);
    printf("\nEncryption:\n");
    encrypt(s, key_mul, key_add);
    printf("\nEncrypted string: %s\n", s);
    printf("\nDecryption:\n");
    decrypt(s, key_mul, key_add);
    printf("\nDecrypted string: %s\n", s);
    printf("\n");
}
