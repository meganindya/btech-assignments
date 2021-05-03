#include <stdio.h>  // printf, scanf
#include <stdlib.h> // abs
#include <string.h> // strlen
#include <time.h>   // time

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

// -----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    char s[32];
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

    srand(time(0));
    for (int i = 0; i < strlen(s); i++)
    {
        for (int j = i * 5; j < (i + 1) * 5; j++)
        {
            k[j] = '0' + rand() % 2;
        }
    }
    printf("\nPseudorandom One Time Key:\n  ");
    for (int i = 0; i < strlen(s); i++)
    {
        for (int j = i * 5; j < (i + 1) * 5; j++)
        {
            printf("%c", k[j]);
        }
        printf(" ");
    }
    printf("\n");

    printf("\nEncryption:\n");
    encrypt(s, k);
    printf("\nEncrypted stream:\n  ");
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

    printf("\nDecryption:\n");
    decrypt(s, k);
    printf("\nDecrypted string: %s\n", s);
    printf("\n");
}
