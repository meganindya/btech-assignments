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
 * Utility function that calculates the modular additive inverse of a number w.r.t. another.
 *
 * a: input number
 * m: number to take modulus with
 *
 * returns: additive inverse of a (mod 26)
 */
int mod_add_inv(int a, int m)
{
    return -mod(a, m);
}

/*
 * Performs shift cipher decripytion against all additive inverse values in [0, m - 1].
 *
 * s: the encoded string
 */
void attack(char *s)
{
    for (int i = 0; i < MOD; i++)
    {
        int key_inv = mod_add_inv(i, MOD);
        printf("    for key = %d\n    key additive inverse (mod %d) = %d\n", i, MOD, key_inv);

        char enc[64];
        strcpy(enc, s);
        for (int j = 0; enc[j] != '\0'; j++)
        {
            enc[j] = 'A' + mod((enc[j] - 'A') + key_inv, MOD);
        }
        printf("decoded string: %s\n\n", enc);
    }
}

// -----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    char s[64] = "BMMTDXLTANZXXYYHKMMHYKXXRHNKLXEYYKHFFXFHKR";
    printf("\nencoded string: %s\n\n", s);
    attack(s);
}
