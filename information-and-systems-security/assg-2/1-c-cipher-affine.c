#include <stdio.h>  // printf, scanf
#include <stdlib.h> // abs
#define MOD 26

/*
 * Utility function that returns modulo of a number w.r.t. another.
 *
 * a: input number
 * m: number to take modulus with
 * 
 * returns: a mod m
 */
int mod(int a, int m)
{
    return a < 0 ? m - (abs(a) % m) : (a) % m;
}

/*
 * Utility function that calculates the modular additive inverse of a number w.r.t. another.
 *
 * a: input number
 * m: number to take modulus with
 *
 * returns: additive inverse of a (mod 26)
 */
int mod_mul_add(int a, int m)
{
    return -mod(a, m);
}

/*
 * Utility function that calculates the modular multiplicative inverse of a number w.r.t. 26.
 *
 * a: input number
 *
 * returns: multiplicative inverse of a (mod 26)
 */
int mod_mul_inv(int a, int m)
{
    for (int x = 1; x < m; x++)
    {
        if (mod(mod(a, m) * mod(x, m), m) == 1)
        {
            return x;
        }
    }
    return -1;
}

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
        char enc_char = 'A' + mod((s[i] - 'A') * key_mul + key_add, MOD);
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
    int key_add_inv = mod_mul_add(key_add, MOD);
    int key_mul_inv = mod_mul_inv(key_mul, MOD);
    printf("    for key = %d\n", key_mul);
    printf("    key additive inverse (mod %d) = %d\n", MOD, key_add_inv);
    printf("    key multiplicative inverse (mod %d) = %d\n\n", MOD, key_mul_inv);
    for (int i = 0; s[i] != '\0'; i++)
    {
        char dec_char = 'A' + mod((((s[i] - 'A') + key_add_inv) * key_mul_inv), MOD);
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
        if (mod_mul_inv(key_mul, MOD) == -1)
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
