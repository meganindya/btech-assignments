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

/*
 * Calculates the determinant of a matrix.
 *
 * ord_mat: order of the matrix
 * mat: supplied matrix
 *
 * returns: determinant of mat
 */
int mat_determinant(int ord_mat, int **mat)
{
    if (ord_mat == 1)
    {
        return mat[0][0];
    }

    int det = 0;
    for (int z = 0; z < ord_mat; z++)
    {
        int sign = ((1 - (z & 1)) << 1) - 1;

        int **sub_mat;
        sub_mat = malloc((ord_mat - 1) * sizeof *sub_mat);
        for (int i = 0; i < ord_mat - 1; i++)
        {
            sub_mat[i] = malloc((ord_mat - 1) * sizeof *sub_mat[i]);
        }

        int kr = 0, kc = 0;
        for (int r = 1; r < ord_mat; r++)
        {
            for (int c = 0; c < ord_mat; c++)
            {
                if (c != z)
                {
                    sub_mat[kr][kc] = mat[r][c];
                    kc = (kc + 1) % ord_mat;
                }
            }
            kr++;
        }

        det += sign * mat[0][z] * mat_determinant(ord_mat - 1, sub_mat);

        for (int i = 0; i < ord_mat - 1; i++)
        {
            free(sub_mat[i]);
        }
        free(sub_mat);
    }

    return det;
}

/*
 * Calculates and fills the cofactors for a matrix.
 *
 * ord_mat: order of the matrix
 * mat: supplied matrix
 * cof_mat: matrix to fill cofactors in
 */
void mat_cofactor(int ord_mat, int **mat, int **cof_mat)
{
    for (int r = 0; r < ord_mat; r++)
    {
        for (int c = 0; c < ord_mat; c++)
        {
            int sign = ((1 - ((r + c) & 1)) << 1) - 1;

            int **sub_mat;
            sub_mat = malloc((ord_mat - 1) * sizeof *sub_mat);
            for (int i = 0; i < ord_mat - 1; i++)
            {
                sub_mat[i] = malloc((ord_mat - 1) * sizeof *sub_mat[i]);
            }

            int ki = 0, kj = 0;
            for (int i = 0; i < ord_mat; i++)
            {
                for (int j = 0; j < ord_mat; j++)
                {
                    if (i != r && j != c)
                    {
                        sub_mat[ki][kj] = mat[i][j];
                        kj = (kj + 1) % (ord_mat - 1);
                    }
                }
                if (i != r)
                    ki++;
            }

            cof_mat[r][c] = sign * mat_determinant(ord_mat - 1, sub_mat);

            for (int i = 0; i < ord_mat - 1; i++)
            {
                free(sub_mat[i]);
            }
            free(sub_mat);
        }
    }
}

/*
 * Transposes a square matrix in place.
 *
 * ord_mat: order of the matrix
 * mat: supplied matrix
 */
void mat_transpose(int ord_mat, int **mat)
{
    for (int r = 0; r < ord_mat; r++)
    {
        for (int c = 0; c < r; c++)
        {
            int temp = mat[r][c];
            mat[r][c] = mat[c][r];
            mat[c][r] = temp;
        }
    }
}

/*
 * Checks whether a square matrix is invertible.
 *
 * ord_mat: order of the matrix
 * mat: supplied matrix
 * 
 * Returns 0 if invertible; -1 otherwise.
 */
int mat_invert_check(int ord_mat, int **mat)
{
    /* Stores the determinant of the matrix. */
    int det = mat_determinant(ord_mat, mat);
    /* Stores the modular multiplicative inverse of the determinant. */
    int det_inv = mod_26_mul_inv(det);

    return det_inv == -1 ? -1 : 0;
}

/*
 * Calculates the inverse (mod 26) of a matrix.
 *
 * ord_mat: order of the matrix
 * mat: supplied matrix
 * inv_mat: matrix to fill inverse in
 */
void mat_invert(int ord_mat, int **mat, int **inv_mat)
{
    /* Stores the determinant of the matrix. */
    int det = mat_determinant(ord_mat, mat);
    /* Stores the modular multiplicative inverse of the determinant. */
    int det_inv = mod_26_mul_inv(det);

    mat_cofactor(ord_mat, mat, inv_mat);
    mat_transpose(ord_mat, inv_mat);

    for (int i = 0; i < ord_mat; i++)
    {
        for (int j = 0; j < ord_mat; j++)
        {
            inv_mat[i][j] = mod_26(inv_mat[i][j] * det_inv);
        }
    }
}
