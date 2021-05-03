#include <stdio.h>  // printf, scanf
#include <stdlib.h> // abs
#include <string.h> // strlen

#include "../utils.h"
#define MOD 26

/*
 * Utility function that converts an integer (base 10) to binary (base 2) string.
 * There is a condition that the integers represent alphabets and are therefore confined in the
 * range [0, 25], which can be covered in 5 bits.
 *
 * n: integer number
 * s: character array to fill (binary) bits in (array length assumed to be 5)
 */
void int_to_binary(int n, char *s)
{
    int mask = 1;
    for (int i = 0; i < 5; i++)
    {
        s[4 - i] = (n & mask) == 0 ? '0' : '1';
        mask <<= 1;
    }
}

/*
 * Utility function that converts a binary (base 2) string to integer (base 10).
 * There is a condition that the integers represent alphabets and are therefore confined in the
 * range [0, 25], which can be covered in 5 bits.
 *
 * s: character array of bits representing the binary (array length assumed to be 5)
 *
 * returns:
 * integer (base 10) equivalent
 */
int binary_to_int(char *s)
{
    int n = 0, mask = 1;
    for (int i = 0; i < 5; i++)
    {
        n += (s[4 - i] - '0') * mask;
        mask <<= 1;
    }
    return n;
}

/*
 * Utility function that returns the XOR of two bits represented as characters ('0' or '1'),
 *
 * a: operand 1
 * b: operand 2
 *
 * returns:
 * a ^ b (as character)
 */
char xor (char a, char b) {
    return a == b ? '0' : '1';
}

    /*
 * Cipher One Time Pad encrypts (in place) all input string and generates a key string.
 *
 * s: the string
 * k: cipher key
 */
    void encrypt(char *s, char *k)
{
    int len_s = strlen(s);
    int len_k = strlen(k);

    printf("  ");
    for (int i = 0; i < 5; i++)
    {
        printf(" (%c)  ", s[i]);
    }

    printf("\n  ");
    char a[len_k];
    for (int i = 0; i < len_s; i++)
    {
        int x = s[i] - 'A';
        char bin[5];
        int_to_binary(x, bin);
        printf("%s ", bin);
        for (int j = i * 5; j < (i + 1) * 5; j++)
        {
            a[j] = bin[j - (i * 5)];
        }
    }

    printf("\n  ");
    for (int i = 0; i < len_s; i++)
    {
        for (int j = i * 5; j < (i + 1) * 5; j++)
        {
            printf("%c", k[j]);
        }
        printf(" ");
    }

    printf("\n  ");
    for (int i = 1; i < 6 * len_s; i++)
    {
        printf("-");
    }

    for (int i = 0; i < len_k; i++)
    {
        a[i] = xor(a[i], k[i]);
    }
    printf("\n  ");
    for (int i = 0; i < len_s; i++)
    {
        for (int j = i * 5; j < (i + 1) * 5; j++)
        {
            printf("%c", a[j]);
        }
        printf(" ");
    }

    for (int i = 0; i < len_s; i++)
    {
        char bin[5];
        for (int j = i * 5; j < (i + 1) * 5; j++)
        {
            bin[j - (i * 5)] = a[j];
        }
        s[i] = binary_to_int(bin) + 'A';
    }

    printf("\n  ");
    for (int i = 0; i < len_s; i++)
    {
        printf(" (%2d) ", s[i] - 'A');
    }
    printf("\n");
}

/*
 * Cipher One Time Pad decrypts (in place) all characters of a string.
 *
 * s: the string
 * k: cipher key
 */
void decrypt(char *s, char *k)
{
    int len_s = strlen(s);
    int len_k = strlen(k);

    printf("  ");
    for (int i = 0; i < len_s; i++)
    {
        printf(" (%2d) ", s[i] - 'A');
    }

    printf("\n  ");
    char a[len_k];
    for (int i = 0; i < len_s; i++)
    {
        int x = s[i] - 'A';
        char bin[5];
        int_to_binary(x, bin);
        for (int j = i * 5; j < (i + 1) * 5; j++)
        {
            a[j] = bin[j - (i * 5)];
            printf("%c", a[j]);
        }
        printf(" ");
    }

    printf("\n  ");
    for (int i = 0; i < len_s; i++)
    {
        for (int j = i * 5; j < (i + 1) * 5; j++)
        {
            printf("%c", k[j]);
        }
        printf(" ");
    }

    printf("\n  ");
    for (int i = 1; i < 6 * len_s; i++)
    {
        printf("-");
    }

    for (int i = 0; i < len_k; i++)
    {
        a[i] = xor(a[i], k[i]);
    }
    printf("\n  ");
    for (int i = 0; i < len_s; i++)
    {
        for (int j = i * 5; j < (i + 1) * 5; j++)
        {
            printf("%c", a[j]);
        }
        printf(" ");
    }

    printf("\n  ");
    for (int i = 0; i < len_s; i++)
    {
        char bin[5];
        for (int j = i * 5; j < (i + 1) * 5; j++)
        {
            bin[j - (i * 5)] = a[j];
        }
        s[i] = binary_to_int(bin) + 'A';
    }
    for (int i = 0; i < len_s; i++)
    {
        printf(" (%c)  ", s[i]);
    }
    printf("\n");
}

/*
 * Cryptanalyses One Time Pad from first 3 blocks of plaintext and ciphertext and generates key
 * stream of same length as full plaintext for decryption.
 *
 * s: cipher string
 * p: 3 blocks (15 bits) of plaintext
 * k: array to fill generated key stream in
 */
void cryptanalyze(char *s, char *p, char *k)
{
    int len_s = strlen(s);
    int len_p = strlen(p);

    printf("  XOR-ing:\n    ");
    char r[len_p];
    int r_n[len_p];
    for (int i = 0; i < 3; i++)
    {
        int x = s[i] - 'A';
        char bin[5];
        int_to_binary(x, bin);
        for (int j = i * 5; j < (i + 1) * 5; j++)
        {
            r[j] = bin[j - (i * 5)];
            printf("%c", r[j]);
        }
        printf(" ");
    }

    printf("\n    ");
    for (int i = 0; i < 3; i++)
    {
        for (int j = i * 5; j < (i + 1) * 5; j++)
        {
            printf("%c", p[j]);
        }
        printf(" ");
    }

    printf("\n    ");
    for (int i = 1; i < 6 * 3; i++)
    {
        printf("-");
    }

    for (int i = 0; i < len_p; i++)
    {
        r[i] = xor(r[i], p[i]);
    }
    for (int i = 0; i < 3; i++)
    {
        char bin[5];
        for (int j = i * 5; j < (i + 1) * 5; j++)
        {
            bin[j - (i * 5)] = r[j];
        }
        r_n[i] = binary_to_int(bin);
    }
    printf("\n    ");
    for (int i = 0; i < 3; i++)
    {
        for (int j = i * 5; j < (i + 1) * 5; j++)
        {
            printf("%c", r[j]);
        }
        printf(" ");
    }
    printf("\n    ");
    for (int i = 0; i < 3; i++)
    {
        printf(" (%2d) ", r_n[i]);
    }

    printf("\n\n  Keys:\n");
    printf("    s_0 = %2d\n", r_n[0]);
    printf("    s_1 = %2d\n", r_n[1]);
    printf("    s_2 = %2d\n", r_n[2]);

    int s0 = r_n[0];
    int s1 = r_n[1];
    int s2 = r_n[2];

    printf("\n  Equations:\n");
    printf("    (a * %2d + b) mod %d = %d\n", s0, MOD, s1);
    printf("    (a * %2d + b) mod %d = %d\n", s1, MOD, s2);

    int a, b;
    if (mod_26_mul_inv(s1 - s0) == -1)
    {
        printf("\n  Cryptanalysis failed!\n\n");
        exit(-1);
    }

    a = mod_26(mod_26_mul_inv(s1 - s0) * mod_26(s2 - s1));
    b = mod_26(mod_26_mul_inv(s1 - s0) * mod_26(s1 * s1 - s0 * s2));

    printf("\n  Solution:\n");
    printf("    a = %d\n    b = %d\n", a, b);

    int random_s = s0, k_n[len_s];
    for (int i = 0; i < strlen(s); i++)
    {
        k_n[i] = random_s;
        char bin[5];
        int_to_binary(random_s, bin);
        for (int j = i * 5; j < (i + 1) * 5; j++)
        {
            k[j] = bin[j - (i * 5)];
        }
        random_s = mod_26(a * random_s + b);
    }
    printf("\n  Key Stream:\n    ");
    for (int i = 0; i < strlen(s); i++)
    {
        printf(" (%2d) ", k_n[i]);
    }
    printf("\n    ");
    for (int i = 0; i < strlen(s); i++)
    {
        for (int j = i * 5; j < (i + 1) * 5; j++)
        {
            printf("%c", k[j]);
        }
        printf(" ");
    }
    printf("\n");
}

// -----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    char s[32];
    int s0, a, b;
    char k[256];

    printf("\nImplementation of One Time Pad Cipher\n--------\n");
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

    char bin_s[15];
    for (int i = 0; i < 3; i++)
    {
        char bin[5];
        int_to_binary(s[i] - 'A', bin);
        for (int j = i * 5; j < (i + 1) * 5; j++)
        {
            bin_s[j] = bin[j - (i * 5)];
        }
    }

    printf("\nEnter parameters for PRNG (s_i+1 = a * s_i + b mod 26):\n");
    printf("  seed (s_0):\t");
    scanf("%d", &s0);
    printf("  a:\t\t");
    scanf("%d", &a);
    printf("  b:\t\t");
    scanf("%d", &b);

    int k_n[strlen(s)];
    printf("\nOne Time Key:\n  steps:\n");
    printf("    s_0 = %d\n", s0);
    int random_s = s0;
    for (int i = 0; i < strlen(s); i++)
    {
        k_n[i] = random_s;
        char bin[5];
        int_to_binary(random_s, bin);
        for (int j = i * 5; j < (i + 1) * 5; j++)
        {
            k[j] = bin[j - (i * 5)];
        }
        if (i != strlen(s) - 1)
        {
            printf(
                "    s_%d = (%d * %2d + %d) mod %d = %2d mod %d = %2d\n",
                i + 1,
                a,
                random_s,
                b,
                MOD,
                a * random_s + b,
                MOD,
                mod_26(a * random_s + b));
        }
        random_s = mod_26(a * random_s + b);
    }
    printf("\n  ");
    for (int i = 0; i < strlen(s); i++)
    {
        printf(" (%2d) ", k_n[i]);
    }
    printf("\n  ");
    for (int i = 0; i < strlen(s); i++)
    {
        for (int j = i * 5; j < (i + 1) * 5; j++)
        {
            printf("%c", k[j]);
        }
        printf(" ");
    }
    printf("\n");

    printf("\n----------------------------------------------------------------\nEncryption:\n");
    encrypt(s, k);
    printf("------------------------------------------------\nEncrypted stream:\n  ");
    for (int i = 0; i < strlen(s); i++)
    {
        char bin[5];
        int_to_binary(s[i] - 'A', bin);
        for (int j = i * 5; j < (i + 1) * 5; j++)
        {
            printf("%c", bin[j - (i * 5)]);
        }
        printf(" ");
    }
    printf("\n");

    printf("\n----------------------------------------------------------------\nCryptanalysis:\n");
    printf("  Available plaintext stream:\n    ");
    for (int i = 0; i < 3; i++)
    {
        for (int j = i * 5; j < (i + 1) * 5; j++)
        {
            printf("%c", bin_s[j]);
        }
        printf(" ");
    }
    printf("\n\n");
    char k_g[256];
    cryptanalyze(s, bin_s, k_g);

    printf("\n----------------------------------------------------------------\nDecryption:\n");
    decrypt(s, k_g);
    printf("------------------------------------------------\nDecrypted string: %s\n", s);
    printf("\n");
}
