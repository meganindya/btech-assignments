#include <stdio.h>  // printf, scanf
#include <stdlib.h> // abs
#include <math.h>   // pow

int mod(int, int);
int mod_inv_mul(int, int);
int determinant_mat(int, int **);
void cofactor_mat(int, int **, int **);
void transpose_mat(int, int **);

int main()
{
    printf("\nCalculation of modular matrix inverse\n--------\n");

    printf("Enter the order of the matrix: ");
    /* Stores order of matrix. */
    int ord_mat;
    scanf("%d", &ord_mat);

    printf("Enter the elements of the %d × %d matrix:\n", ord_mat, ord_mat);
    /* Stores the matrix. */
    int **mat;
    mat = malloc((ord_mat) * sizeof *mat);
    for (int i = 0; i < ord_mat; i++)
    {
        mat[i] = malloc(ord_mat * sizeof *mat[i]);
    }
    for (int i = 0; i < ord_mat; i++)
    {
        for (int j = 0; j < ord_mat; j++)
        {
            scanf("%d", &mat[i][j]);
        }
    }

    /* Stores the number to take modulus with. */
    int m;
    printf("Enter the number to take mod with (m): ");
    scanf("%d", &m);

    /* Stores the determinant of the matrix. */
    int det = determinant_mat(ord_mat, mat);
    /* Stores the modular multiplicative inverse of the determinant. */
    int det_inv = mod_inv_mul(det, m);
    if (det_inv == -1)
    {
        printf("\nInverse of entered matrix is not possible\n\n");
        return 0;
    }

    int **new_mat;
    new_mat = malloc((ord_mat) * sizeof *new_mat);
    for (int i = 0; i < ord_mat; i++)
    {
        new_mat[i] = malloc(ord_mat * sizeof *new_mat[i]);
    }

    cofactor_mat(ord_mat, mat, new_mat);
    transpose_mat(ord_mat, new_mat);

    for (int i = 0; i < ord_mat; i++)
    {
        for (int j = 0; j < ord_mat; j++)
        {
            new_mat[i][j] = mod(new_mat[i][j] * det_inv, m);
        }
    }

    printf("\nMatrix is\n");
    for (int i = 0; i < ord_mat; i++)
    {
        for (int j = 0; j < ord_mat; j++)
        {
            printf("%3d ", mat[i][j]);
        }
        printf("\n");
    }

    printf("\nModular matrix inverse is\n");
    for (int i = 0; i < ord_mat; i++)
    {
        for (int j = 0; j < ord_mat; j++)
        {
            printf("%3d ", new_mat[i][j]);
        }
        printf("\n");
    }

    printf("\nSide by side\n");
    for (int i = 0; i < ord_mat; i++)
    {
        for (int j = 0; j < ord_mat; j++)
        {
            printf("%3d ", mat[i][j]);
        }
        printf("    ");
        for (int j = 0; j < ord_mat; j++)
        {
            printf("%3d ", new_mat[i][j]);
        }
        printf("\n");
    }

    printf("\nOn multiplication\n");
    for (int i = 0; i < ord_mat; i++)
    {
        for (int j = 0; j < ord_mat; j++)
        {
            int sum = 0;
            for (int k = 0; k < ord_mat; k++)
            {
                sum += mat[i][k] * new_mat[k][j];
            }
            printf("%3d ", sum);
        }
        printf("\n");
    }

    printf("\nTaking modulus with %d\n", m);
    for (int i = 0; i < ord_mat; i++)
    {
        for (int j = 0; j < ord_mat; j++)
        {
            int sum = 0;
            for (int k = 0; k < ord_mat; k++)
            {
                sum += mat[i][k] * new_mat[k][j];
            }
            printf("%3d ", mod(sum, m));
        }
        printf("\n");
    }
    printf("\n");

    for (int i = 0; i < ord_mat; i++)
    {
        free(new_mat[i]);
    }
    free(new_mat);

    for (int i = 0; i < ord_mat; i++)
    {
        free(mat[i]);
    }
    free(mat);
}

/*
 * Returns the modulus of a number with another. Handles negative case.
 *
 * a: number to take modulus of (can be any integer)
 * m: number to take modulus with (natural number)
 */
int mod(int a, int m)
{
    return a < 0 ? m - (abs(a) % m) : a % m;
}

/*
 * Calculates the modular multiplicative inverse of a number.
 *
 * a: input number
 * m: modulus number
 *
 * returns: multiplicative inverse of a (mod m)
 */
int mod_inv_mul(int a, int m)
{
    for (int x = 1; x < m; x++)
    {
        if ((mod(a, m) * (x % m)) % m == 1)
        {
            return x;
        }
    }
    return -1;
}

/*
 * Calculates the determinant of a matrix.
 *
 * ord_mat: order of the matrix
 * mat: supplied matrix
 *
 * returns: determinant of mat
 */
int determinant_mat(int ord_mat, int **mat)
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

        det += sign * mat[0][z] * determinant_mat(ord_mat - 1, sub_mat);

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
void cofactor_mat(int ord_mat, int **mat, int **cof_mat)
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

            cof_mat[r][c] = sign * determinant_mat(ord_mat - 1, sub_mat);

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
void transpose_mat(int ord_mat, int **mat)
{
    for (int r = 0; r < ord_mat; r++)
    {
        for (int c = 0; c <= ((ord_mat - 1) >> 1); c++)
        {
            int temp = mat[r][c];
            mat[r][c] = mat[c][r];
            mat[c][r] = temp;
        }
    }
}
