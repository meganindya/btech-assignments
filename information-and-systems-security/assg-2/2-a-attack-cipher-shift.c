#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#define MOD 26

/*
 * Performs shift cipher decripytion against all additive inverse values in [0, m - 1].
 *
 * s: the encoded string
 */
void attack(char *s)
{
    for (int i = 0; i < MOD; i++)
    {
        int key_inv = mod_26_add_inv(i);
        printf("    for key = %d\n    key additive inverse (mod %d) = %d\n", i, MOD, key_inv);

        char enc[64];
        strcpy(enc, s);
        for (int j = 0; enc[j] != '\0'; j++)
        {
            enc[j] = 'A' + mod_26((enc[j] - 'A') + key_inv);
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
