#include <stdio.h>

int gcd(int a, int b)
{
    printf("\nSteps:\n----\n");

    int t0 = 0;
    int t = 1;
    int s0 = 1;
    int s = 0;
    int q = a / b;
    int r = a - q * b;

    printf(
        "t0 = %2d, t = %2d, s0 = %2d, s = %2d, q = %2d, r = %2d \n",
        t0, t, s0, s, q, r);

    while (r > 0)
    {
        int temp = t0 - q * t;
        t0 = t;
        t = temp;
        temp = s0 - q * s;
        s0 = s;
        s = temp;
        a = b;
        b = r;
        q = a / b;
        r = a - q * b;

        printf(
            "t0 = %2d, t = %2d, s0 = %2d, s = %2d, q = %2d, r = %2d \n",
            t0, t, s0, s, q, r);
    }
    r = b;

    return r;
}

int main(int argc, char *argv[])
{
    int a, b;
    printf("\nCalculation of GCD by Extended Euclidean Algorithm\n--------\n");
    printf("Enter number (a): ");
    scanf("%d", &a);
    printf("Enter number (b): ");
    scanf("%d", &b);
    printf("\nGCD(%d, %d) = %d\n\n", a, b, gcd(a, b));
}
