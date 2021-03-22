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
        int key_mul_inv = mod_mul_inv(i, MOD);
        if (key_mul_inv == -1)
        {
            printf("for multiplicative key = %d\n", i);
            printf("key multiplicative inverse doesn't exist, this key isn't valid\n\n");
            continue;
        }
        for (int j = 0; j < MOD; j++)
        {
            int key_add_inv = mod_add_inv(j, MOD);
            printf("    for key (a, b) = (%d, %d)\n", i, j);
            printf("    key (a = %d) multiplicative inverse (mod %d) = %d\n", i, MOD, key_mul_inv);
            printf("    key (b = %d) additive inverse (mod %d) = %d\n", j, MOD, key_add_inv);

            char enc[80];
            strcpy(enc, s);
            for (int x = 0; enc[x] != '\0'; x++)
            {
                enc[x] = 'A' + mod(((enc[x] - 'A') + key_add_inv) * key_mul_inv, MOD);
            }
            printf("decoded string: %s\n\n", enc);
        }
    }
}

// -----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    char s[80] = "EFXECFBDQGGXRADQTFFUFSPGAHQTDGGAFZDJFGHJFBDQGHGDCCGXSFJDHQGAFZDJF";
    printf("\nencoded string: %s\n\n", s);
    attack(s);
}
