#include <stdio.h>

int mod_inv_mul(int a, int m)
{
    for (int x = 1; x < m; x++)
    {
        if (((a % m) * (x % m)) % m == 1)
        {
            return x;
        }
    }
}

int main(int argc, char *argv[])
{
    int a, m;
    printf("\nCalculation of modular multiplicative inverse\n--------\n");
    printf("Enter number (a): ");
    scanf("%d", &a);
    printf("Enter number to take mod with (m): ");
    scanf("%d", &m);
    printf("\nAdditive inverse of %d (mod %d) is %d\n\n", a, m, mod_inv_mul(a, m));
}
