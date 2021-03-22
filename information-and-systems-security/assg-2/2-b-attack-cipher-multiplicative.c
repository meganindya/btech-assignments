#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
 * Performs shift cipher decripytion against all valid multiplicative inverse values in [0, m - 1].
 *
 * s: the encoded string
 */
void attack(char *s)
{
    for (int i = 0; i < MOD; i++)
    {
        int key_inv = mod_mul_inv(i, MOD);
        if (key_inv == -1)
        {
            printf("for key = %d\nkey multiplicative inverse doesn't exist, this key isn't valid\n\n", i);
            continue;
        }
        printf("for key = %d\nkey multiplicative inverse (mod %d) = %d\n", i, MOD, key_inv);

        char enc[64];
        strcpy(enc, s);
        for (int j = 0; enc[j] != '\0'; j++)
        {
            enc[j] = 'A' + mod((enc[j] - 'A') * key_inv, MOD);
        }
        printf("decoded string: %s\n\n", enc);
    }
}

// -----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    char s[64] = "WFEJBYOFAJZEYDCMRBKJRKWABKXSWKJZSFQ";
    printf("\nencoded string: %s\n\n", s);
    attack(s);
}
