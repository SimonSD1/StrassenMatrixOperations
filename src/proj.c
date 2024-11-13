#include <stdlib.h>
#include <stdio.h>

typedef struct matrix
{
    double **coefs;
    int columns;
    int rows;
} matrix;

void printMatrix(matrix A)
{
    for (int i = 0; i < A.rows; i++)
    {
        for (int j = 0; j < A.columns; j++)
        {
            printf("%lf ", A.coefs[i][j]);
        }
        printf("\n");
    }
}

void freeMatrix(matrix m)
{
    for (int i = 0; i < m.rows; i++)
    {
        free(m.coefs[i]);
    }
    free(m.coefs);
}

matrix creeMatrix(int rows, int columns)
{
    matrix m;
    m.columns = columns;
    m.rows = columns;
    m.coefs = (double **)malloc(rows * sizeof(double *));
    for (int i = 0; i < rows; i++)
    {
        m.coefs[i] = malloc(columns * sizeof(double));
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            m.coefs[i][j] = 0;
        }
    }
    return m;
}

void naiveMultMat(matrix A, matrix B, matrix result)
{
    for (int i = 0; i < A.rows; i++)
    {
        for (int j = 0; j < B.rows; j++)
        {
            result.coefs[i][j] = 0;
            for (int k = 0; k < A.rows; k++)
            {
                result.coefs[i][j] += A.coefs[i][k] * B.coefs[k][j];
            }
        }
    }
}

void strassen(matrix A, matrix B, matrix C){
    
}



int main(int argc, char const *argv[])
{
    
    return 0;
}
