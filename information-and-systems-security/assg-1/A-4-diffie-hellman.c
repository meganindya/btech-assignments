#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <math.h>

// returns value of a ^ b (mod P)
long long int power(long long int a, long long int b, long long int P)
{
    return b == 1 ? a : (((long long int)pow(a, b)) % P);
}

int main()
{
    printf("\nDiffie-Hellman key exchange\n--------\n");
    long long int P, G, x, a, y, b, ka, kb;

    // Public keys G and P are agreed upon
    P = 23; // A prime number P is taken
    printf("The value of P taken is %lld\n", P);

    G = 9; // A primitve root for P, G is taken
    printf("The value of G taken is %lld\n\n", G);

    // Choose the private key a
    printf("Enter private key of a: ");
    scanf("%lld", &a);
    x = power(G, a, P); // generated key from a

    // Choose the private key b
    printf("Enter private key of b: ");
    scanf("%lld", &b);
    y = power(G, b, P); // generated key from b

    // Generating the secret key after the exchange of keys
    ka = power(y, a, P); // Secret key for a
    kb = power(x, b, P); // Secret key for b

    printf("\n");
    printf("Secret key for a is %lld\n", ka);
    printf("Secret Key for b is %lld\n", kb);
    printf("\n");

    return 0;
}
