#include <stdlib.h> // abs

/*
 * Utility function that returns modulo of a number w.r.t. another.
 *
 * a: input number
 * m: number to take modulus with
 * 
 * returns: a mod m
 */
int mod(int a, int m)
{
    return a < 0 ? m - (abs(a) % m) : (a) % m;
}

/*
 * Utility function that returns modulo of a number w.r.t. 26.
 *
 * a: input number
 * 
 * returns: a mod 26
 */
int mod_26(int a)
{
    return mod(a, 26);
}

/*
 * Utility function that calculates the modular additive inverse of a number w.r.t. another.
 *
 * a: input number
 * m: number to take modulus with
 *
 * returns: additive inverse of a (mod m)
 */
int mod_add_inv(int a, int m)
{
    return -mod(a, m);
}

/*
 * Utility function that calculates the modular additive inverse of a number w.r.t. 26.
 *
 * a: input number
 *
 * returns: additive inverse of a (mod 26)
 */
int mod_26_add_inv(int a)
{
    return mod_add_inv(a, 26);
}

/*
 * Utility function that calculates the modular multiplicative inverse of a number w.r.t. another.
 *
 * a: input number
 * m: number to take modulus with
 *
 * returns: multiplicative inverse of a (mod m)
 */
int mod_mul_inv(int a, int m)
{
    for (int x = 1; x < m; x++)
    {
        if (mod(mod(a, m) * mod(x, m), m) == 1)
        {
            return x;
        }
    }
    return -1;
}

/*
 * Utility function that calculates the modular multiplicative inverse of a number w.r.t. 26.
 *
 * a: input number
 *
 * returns: multiplicative inverse of a (mod 26)
 */
int mod_26_mul_inv(int a)
{
    return mod_mul_inv(a, 26);
}
