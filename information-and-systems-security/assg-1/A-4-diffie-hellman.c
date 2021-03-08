#include <stdio.h>
#include <math.h>

// returns a ^ b (mod P)
long long int power(long long int a, long long int b, long long int P)
{
    return b == 1 ? a : (((long long int)pow(a, b)) % P);
}

int main(int argc, char *argv[])
{
    printf("\nDiffie-Hellman key exchange\n--------\n");

    // Public keys (prime) P and (primitive root) G are agreed upon
    long long int P = 23;
    printf("The value of P taken is %lld\n", P);
    long long int G = 9;
    printf("The value of G taken is %lld\n\n", G);

    long long int a;
    // Private key a
    printf("Enter private key of a: ");
    scanf("%lld", &a);

    long long int b;
    // Private key b
    printf("Enter private key of b: ");
    scanf("%lld", &b);

    printf("\n");
    // Generated key from a
    long long int x = power(G, a, P);
    printf("Generated key from a is G^a (mod P) = %lld\n", x);
    // Generated key from b
    long long int y = power(G, b, P);
    printf("Generated key from b is G^b (mod P) = %lld\n", y);

    // Generate secret key after key exchange
    long long int ka = power(y, a, P); // secret key for a
    long long int kb = power(x, b, P); // secret key for b

    printf("\n");
    printf("Secret key for a is %lld\n", ka);
    printf("Secret Key for b is %lld\n", kb);
    printf("\n");

    return 0;
}
