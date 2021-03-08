#include <stdio.h>

int gcd(int a, int b)
{
    printf("\nSteps:\n----\n");
    if (a == 0)
    {
        printf("a: %d, b: %d\n", a, b);
        return b;
    }
    while (b != 0)
    {
        printf("a: %d, b: %d\n", a, b);
        if (a > b)
            a = a - b;
        else
            b = b - a;
    }
    printf("a: %d, b: %d\n", a, b);
    return a;
}

int main(int argc, char *argv[])
{
    int a, b;
    printf("\nCalculation of GCD by Euclid's algorithm\n--------\n");
    printf("Enter number (a): ");
    scanf("%d", &a);
    printf("Enter number (b): ");
    scanf("%d", &b);
    printf("\nGCD(%d, %d) = %d\n\n", a, b, gcd(a, b));
}
