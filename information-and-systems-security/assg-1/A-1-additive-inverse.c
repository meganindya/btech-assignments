#include <stdio.h>

int mod_inv_add(int a, int m)
{
    return m - (a % m);
}

int main(int argc, char *argv[])
{
    int a, m;
    printf("\nCalculation of modular additive inverse\n--------\n");
    printf("Enter number (a): ");
    scanf("%d", &a);
    printf("Enter number to take mod with (m): ");
    scanf("%d", &m);
    printf("\nAdditive inverse of %d (mod %d) is %d\n\n", a, m, mod_inv_add(a, m));
}
