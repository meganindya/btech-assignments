#include <stdio.h>
#include <stdlib.h>

int mod_inv_mul(int a, int m)
{
    for (int x = 1; x < m; x++)
    {
        if (a < 0)
        {
            if (((m - (abs(a) % m)) * (x % m)) % m == 1)
            {
                return x;
            }
        }
        else
        {
            if (((a % m) * (x % m)) % m == 1)
            {
                return x;
            }
        }
    }
    return -1;
}

int main(int argc, char *argv[])
{
    int a, m;
    printf("\nCalculation of modular multiplicative inverse\n--------\n");
    printf("Enter number (a): ");
    scanf("%d", &a);
    printf("Enter number to take mod with (m): ");
    scanf("%d", &m);
    int inv = mod_inv_mul(a, m);
    if (inv == -1)
    {
        printf("\nMultiplicative inverse of %d (mod %d) does not exist\n\n", a, m);
    }
    else
    {
        printf("\nMultiplicative inverse of %d (mod %d) is %d\n\n", a, m, mod_inv_mul(a, m));
    }
}
