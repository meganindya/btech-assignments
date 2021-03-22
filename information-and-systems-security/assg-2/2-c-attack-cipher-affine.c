#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#define MOD 26

/*
 * Performs shift cipher decripytion against all valid multiplicative inverse values in [0, m - 1].
 *
 * s: the encoded string
 */
void attack(char *s)
{
    for (int i = 0; i < MOD; i++)
    {
        int key_mul_inv = mod_26_mul_inv(i);
        if (key_mul_inv == -1)
        {
            printf("for multiplicative key = %d\n", i);
            printf("key multiplicative inverse doesn't exist, this key isn't valid\n\n");
            continue;
        }
        for (int j = 0; j < MOD; j++)
        {
            int key_add_inv = mod_26_add_inv(j);
            printf("    for key (a, b) = (%d, %d)\n", i, j);
            printf("    key (a = %d) multiplicative inverse (mod %d) = %d\n", i, MOD, key_mul_inv);
            printf("    key (b = %d) additive inverse (mod %d) = %d\n", j, MOD, key_add_inv);

            char enc[80];
            strcpy(enc, s);
            for (int x = 0; enc[x] != '\0'; x++)
            {
                enc[x] = 'A' + mod_26(((enc[x] - 'A') + key_add_inv) * key_mul_inv);
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
