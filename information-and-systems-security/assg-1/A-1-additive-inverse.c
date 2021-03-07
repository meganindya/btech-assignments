#include <stdio.h>

int add_inv_mod(int a, int n)
{
    return n - (a % n);
}

int main(int argc, char *argv[])
{
    int a, n;
    printf("Calculation of modular additive inverse\n--------\n");
    printf("Enter number (a): ");
    scanf("%d", &a);
    printf("Enter number to take mod with (n): ");
    scanf("%d", &n);
    printf("\nAdditive inverse of %d (mod %d) is %d\n", a, n, add_inv_mod(a, n));
}
