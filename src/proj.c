#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

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

matrix *creeMatrix(int rows, int columns)
{
    matrix *m = malloc(sizeof(matrix));
    m->columns = columns;
    m->rows = rows;
    m->coefs = (double **)malloc(rows * sizeof(double *));
    for (int i = 0; i < rows; i++)
    {
        m->coefs[i] = malloc(columns * sizeof(double));
    }

    return m;
}

void naiveMultMat(matrix *A, matrix *B, matrix *result)
{
    for (int i = 0; i < A->rows; i++)
    {
        for (int j = 0; j < B->columns; j++)
        {
            result->coefs[i][j] = 0;
            for (int k = 0; k < A->columns; k++)
            {
                result->coefs[i][j] += A->coefs[i][k] * B->coefs[k][j];
            }
        }
    }
}

void matrice_add(matrix *A, matrix *B, matrix *result)
{
    if (A->rows != B->rows || A->columns != B->columns)
    {
        printf("impossible addition");
        return;
    }

    for (int i = 0; i < A->rows; i++)
    {
        for (int j = 0; j < A->columns; j++)
        {
            result->coefs[i][j] = A->coefs[i][j] + B->coefs[i][j];
        }
    }
}

void subMatrixAddition(matrix *A, matrix *B, matrix *result,
                       int startRowA, int startColA, int endRowA, int endColA,
                       int startRowB, int startColB, int endRowB, int endColB)
{
    int rowsA = endRowA - startRowA + 1;
    int colsA = endColA - startColA + 1;
    int rowsB = endRowB - startRowB + 1;
    int colsB = endColB - startColB + 1;

    if (rowsA != rowsB || colsA != colsB)
    {
        printf("impossible addition\n");
        return;
    }

    if (endRowA >= A->rows || endColA >= A->columns || startRowA < 0 || startColA < 0 ||
        endRowB >= B->rows || endColB >= B->columns || startRowB < 0 || startColB < 0)
    {
        printf("impossible addition\n");
        return;
    }

    for (int i = 0; i < rowsA; i++)
    {
        for (int j = 0; j < colsA; j++)
        {
            result->coefs[i][j] = A->coefs[startRowA + i][startColA + j] + B->coefs[startRowB + i][startColB + j];
        }
    }
}

void matrice_substract(matrix *A, matrix *B, matrix *result)
{
    if (A->rows != B->rows || A->columns != B->columns)
    {
        printf("impossible soustraction");
        return;
    }

    for (int i = 0; i < A->rows; i++)
    {
        for (int j = 0; j < A->columns; j++)
        {
            result->coefs[i][j] = A->coefs[i][j] - B->coefs[i][j];
        }
    }
}

void subMatrixSubtraction(matrix *A, matrix *B, matrix *result,
                          int row1_start, int col1_start, int row1_end, int col1_end,
                          int row2_start, int col2_start, int row2_end, int col2_end)
{
    int rows = row1_end - row1_start + 1;
    int cols = col1_end - col1_start + 1;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            result->coefs[i][j] = A->coefs[row1_start + i][col1_start + j] - B->coefs[row2_start + i][col2_start + j];
        }
    }
}

void subMatrix(matrix *original, matrix *result, int startRow, int startCol, int endRow, int endCol)
{
    int newRows = endRow - startRow + 1;
    int newCols = endCol - startCol + 1;

    for (int i = 0; i < newRows; i++)
    {
        for (int j = 0; j < newCols; j++)
        {
            result->coefs[i][j] = original->coefs[startRow + i][startCol + j];
        }
    }
}

void identity(matrix *A)
{
    for (int i = 0; i < A->columns; i++)
    {
        A->coefs[i][i] = 1;
    }
}

// copie source dsourcens destination
void copyMatrix(matrix *source, matrix *destination)
{
    for (int i = 0; i < source->rows; i++)
    {
        for (int j = 0; j < source->columns; j++)
        {
            destination->coefs[i][j] = source->coefs[i][j];
        }
    }
}

void LU(matrix *A, matrix *L, matrix *U)
{
    identity(L);
    copyMatrix(A, U);
    for (int i = 0; i < U->rows; i++)
    {
        if (U->coefs[i][i] == 0)
        {
            printf("LU impossible pivot 0\n");
            return;
        }
        for (int j = i + 1; j < U->rows; j++)
        {
            double coeff = U->coefs[j][i];
            for (int k = i; k < U->columns; k++)
            {
                U->coefs[j][k] -= coeff / U->coefs[i][i] * U->coefs[i][k];
            }
            L->coefs[j][i] = coeff / U->coefs[i][i];
        }
    }
}

int nextPowerOfTwo(int n)
{
    int power = 1;
    while (power < n)
    {
        power <<= 1;
    }
    return power;
}

void ajusteMatrix(matrix *A, matrix *padded)
{
    int newSize = nextPowerOfTwo(A->rows > A->columns ? A->rows : A->columns);

    for (int i = 0; i < A->rows; i++)
    {
        for (int j = 0; j < A->columns; j++)
        {
            padded->coefs[i][j] = A->coefs[i][j];
        }
    }

    for (int i = A->rows; i < newSize; i++)
    {
        for (int j = 0; j < newSize; j++)
        {
            padded->coefs[i][j] = 0;
        }
    }
    for (int i = 0; i < A->rows; i++)
    {
        for (int j = A->columns; j < newSize; j++)
        {
            padded->coefs[i][j] = 0;
        }
    }
}

void extractResult(matrix *paddedResult, matrix *result, int originalRows, int originalColumns)
{
    for (int i = 0; i < originalRows; i++)
    {
        for (int j = 0; j < originalColumns; j++)
        {
            result->coefs[i][j] = paddedResult->coefs[i][j];
        }
    }
}

void strassenRecursive(matrix *A, matrix *B, matrix *result, int limite)
{
    if (A->rows <= limite || A->columns <= limite || B->rows <= limite || B->columns <= limite)
    {
        naiveMultMat(A, B, result);
        return;
    }

    int size = A->rows;
    int halfSize = size / 2;

    matrix *M1 = creeMatrix(halfSize, halfSize);
    matrix *M2 = creeMatrix(halfSize, halfSize);
    matrix *M3 = creeMatrix(halfSize, halfSize);
    matrix *M4 = creeMatrix(halfSize, halfSize);
    matrix *M5 = creeMatrix(halfSize, halfSize);
    matrix *M6 = creeMatrix(halfSize, halfSize);
    matrix *M7 = creeMatrix(halfSize, halfSize);

    matrix *A11 = creeMatrix(halfSize, halfSize);
    matrix *A12 = creeMatrix(halfSize, halfSize);
    matrix *A21 = creeMatrix(halfSize, halfSize);
    matrix *A22 = creeMatrix(halfSize, halfSize);
    matrix *B11 = creeMatrix(halfSize, halfSize);
    matrix *B12 = creeMatrix(halfSize, halfSize);
    matrix *B21 = creeMatrix(halfSize, halfSize);
    matrix *B22 = creeMatrix(halfSize, halfSize);

    subMatrix(A, A11, 0, 0, halfSize - 1, halfSize - 1);
    subMatrix(A, A12, 0, halfSize, halfSize - 1, size - 1);
    subMatrix(A, A21, halfSize, 0, size - 1, halfSize - 1);
    subMatrix(A, A22, halfSize, halfSize, size - 1, size - 1);

    subMatrix(B, B11, 0, 0, halfSize - 1, halfSize - 1);
    subMatrix(B, B12, 0, halfSize, halfSize - 1, size - 1);
    subMatrix(B, B21, halfSize, 0, size - 1, halfSize - 1);
    subMatrix(B, B22, halfSize, halfSize, size - 1, size - 1);

    matrice_add(A11, A22, M1);
    matrice_add(A21, A22, M2);
    matrice_substract(B12, B22, M3);
    matrice_substract(B21, B11, M4);
    matrice_add(A11, A12, M5);
    matrice_substract(A21, A11, M6);
    matrice_substract(A12, A22, M7);

    strassenRecursive(M1, M1, M1, limite);
    strassenRecursive(M2, B11, M2, limite);
    strassenRecursive(A11, M3, M3, limite);
    strassenRecursive(A22, M4, M4, limite);
    strassenRecursive(M5, B22, M5, limite);
    strassenRecursive(M6, M6, M6, limite);
    strassenRecursive(M7, M7, M7, limite);

    for (int i = 0; i < halfSize; i++)
    {
        for (int j = 0; j < halfSize; j++)
        {
            result->coefs[i][j] = M1->coefs[i][j] + M4->coefs[i][j] - M5->coefs[i][j] + M7->coefs[i][j];
            result->coefs[i][j + halfSize] = M3->coefs[i][j] + M5->coefs[i][j];
            result->coefs[i + halfSize][j] = M2->coefs[i][j] + M4->coefs[i][j];
            result->coefs[i + halfSize][j + halfSize] = M1->coefs[i][j] - M2->coefs[i][j] + M3->coefs[i][j] + M6->coefs[i][j];
        }
    }

    freeMatrix(*M1);
    freeMatrix(*M2);
    freeMatrix(*M3);
    freeMatrix(*M4);
    freeMatrix(*M5);
    freeMatrix(*M6);
    freeMatrix(*M7);

    freeMatrix(*A11);
    freeMatrix(*A12);
    freeMatrix(*A21);
    freeMatrix(*A22);
    freeMatrix(*B11);
    freeMatrix(*B12);
    freeMatrix(*B21);
    freeMatrix(*B22);
}

void strassen(matrix *A, matrix *B, matrix *result, int limite)
{
    matrix *Aajuste = creeMatrix(nextPowerOfTwo(A->rows > A->columns ? A->rows : A->columns), nextPowerOfTwo(A->rows > A->columns ? A->rows : A->columns));
    matrix *Bajuste = creeMatrix(nextPowerOfTwo(B->rows > B->columns ? B->rows : B->columns), nextPowerOfTwo(B->rows > B->columns ? B->rows : B->columns));
    matrix *paddedResult = creeMatrix(nextPowerOfTwo(A->rows > A->columns ? A->rows : A->columns), nextPowerOfTwo(A->rows > A->columns ? A->rows : A->columns));

    ajusteMatrix(A, Aajuste);
    ajusteMatrix(B, Bajuste);

    strassenRecursive(Aajuste, Bajuste, paddedResult, limite);

    extractResult(paddedResult, result, A->rows, B->columns);

    freeMatrix(*Aajuste);
    freeMatrix(*Bajuste);
    freeMatrix(*paddedResult);
}

void solveUpperTriangular(matrix *U, matrix *B, matrix *result)
{
    for (int i = U->rows - 1; i >= 0; i--)
    {
        result->coefs[i][0] = B->coefs[i][0];
        for (int j = i + 1; j < U->rows; j++)
        {
            result->coefs[i][0] -= U->coefs[i][j] * result->coefs[j][0];
        }
        result->coefs[i][0] /= U->coefs[i][i];
    }
}

void solveLowerTriangular(matrix *L, matrix *B, matrix *result)
{
    for (int i = 0; i < L->rows; i++)
    {
        result->coefs[i][0] = B->coefs[i][0];
        for (int j = 0; j < i; j++)
        {
            result->coefs[i][0] -= L->coefs[i][j] * result->coefs[j][0];
        }
        result->coefs[i][0] /= L->coefs[i][i];
    }
}

void extractColumn(matrix *A, matrix *result, int col)
{
    if (col < 0 || col > A->columns)
    {
        printf("impossible d'extraire la colonne");
        return;
    }

    for (int i = 0; i < A->rows; i++)
    {
        result->coefs[i][0] = A->coefs[i][col];
    }
}

void setColumn(matrix *A, matrix *col, int num)
{
    for (int i = 0; i < A->rows; i++)
    {
        A->coefs[i][num] = col->coefs[i][0];
    }
}

void inverse_LU(matrix *A, matrix *result)
{
    matrix *L = creeMatrix(A->rows, A->columns);
    matrix *U = creeMatrix(A->rows, A->columns);
    matrix *I = creeMatrix(A->rows, A->columns);
    identity(I);

    LU(A, L, U);

    for (int i = 0; i < A->rows; i++)
    {
        matrix *y = creeMatrix(A->rows, 1);
        matrix *x = creeMatrix(A->rows, 1);

        extractColumn(I, y, i);
        solveLowerTriangular(L, y, y);
        solveUpperTriangular(U, y, x);

        setColumn(result, x, i);

        freeMatrix(*y);
        freeMatrix(*x);
    }

    freeMatrix(*L);
    freeMatrix(*U);
    freeMatrix(*I);
}

void createSubmatrix(matrix *A, matrix *result, int begin_row, int begin_col)
{

    for (int i = 0; i < result->rows; i++)
    {
        for (int j = 0; j < result->columns; j++)
        {
            result->coefs[i][j] = A->coefs[i + begin_row][j + begin_col];
        }
    }
}

void negativeMatrix(matrix *A)
{
    int col = A->columns;
    int rows = A->rows;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < col; j++)
        {
            A->coefs[i][j] = -A->coefs[i][j];
        }
    }
}

// remplit A avec les coefs de B
void fillSubmatrix(matrix *A, matrix *B, int startRow, int startCol)
{
    for (int i = 0; i < B->rows; i++)
    {
        for (int j = 0; j < B->columns; j++)
        {
            A->coefs[startRow + i][startCol + j] = B->coefs[i][j];
        }
    }
}


void find_greatest_in_sub_matrix(matrix *A, int depart, int *facteur_ligne, int *facteur_colonne)
{
    int indice = 0;
    double biggest = A->coefs[A->rows - 1][A->columns - 1];
    *facteur_ligne = A->rows - 1;
    *facteur_colonne = A->columns - 1;
    for (int i = depart; i < A->rows; i++)
    {
        for (int j = depart; j < A->columns; j++)
        {
            if (A->coefs[i][j] > biggest)
            {
                biggest = A->coefs[i][j];
                *facteur_ligne = i;
                *facteur_colonne = j;
            }
        }
    }
}

void PLUQ(matrix *A, matrix *P, matrix *L, matrix *U, matrix *Q)
{
    int size = A->rows;
    // U = A
    copyMatrix(A, U);

    identity(L);
    identity(P);
    identity(Q);
    // L = Id, P = Id, Q = Id

    for (int i = 0; i < size - 1; i++)
    {

        int facteur_ligne;
        int facteur_colonne;

        find_greatest_in_sub_matrix(U, i, &facteur_ligne, &facteur_colonne);

        P->coefs[i][i] = 0;
        P->coefs[facteur_colonne][facteur_colonne] = 0;
        P->coefs[facteur_colonne][i] = 1;
        P->coefs[i][facteur_colonne] = 1;

        Q->coefs[i][i] = 0;
        Q->coefs[facteur_ligne][facteur_ligne] = 0;
        Q->coefs[facteur_ligne][i] = 1;
        Q->coefs[i][facteur_ligne] = 1;

        for (int k = 0; k < size; k++)
        {
            // Échange ligne i et indice_ligne
            double temp = U->coefs[i][k];
            U->coefs[i][k] = U->coefs[facteur_ligne][k];
            U->coefs[facteur_ligne][k] = temp;
        }

        for (int k = 0; k < size; k++)
        {
            // Échange colonne i et indice_ligne
            double temp = U->coefs[k][facteur_colonne];
            U->coefs[k][facteur_colonne] = U->coefs[k][i];
            U->coefs[k][i] = temp;
        }

        for (int j = i + 1; j < size; j++)
        {
            double facteur = U->coefs[j][i] / U->coefs[i][i];
            L->coefs[j][i] = facteur;
            for (int a = 0; a < size; a++)
            {
                U->coefs[j][a] -= U->coefs[i][a] * facteur;
            }
        }
    }
}

// si A11 non inversible on doit utiliser A22
// https://www.researchgate.net/publication/3499047_A_Strassen-Newton_algorithm_for_high-speed_parallelizable_matrixinversion
void strassen_inverse_recursive_naive(matrix *A, matrix *result)
{
    if (A->columns == 1)
    {
        printf("col=1\n");
        result->coefs[0][0] = 1.0 / A->coefs[0][0];
        printf("result[0][0] = %lf ", result->coefs[0][0]);
        return;
    }

    int col = A->columns;
    int row = A->rows;

    printf("creation abcd\n");
    matrix *a = creeMatrix(row / 2, col / 2);
    matrix *b = creeMatrix(row / 2, col / 2);
    matrix *c = creeMatrix(row / 2, col / 2);
    matrix *d = creeMatrix(row / 2, col / 2);

    printf("\remplissage abdc\n");
    createSubmatrix(A, a, 0, 0);
    createSubmatrix(A, b, 0, col / 2);
    createSubmatrix(A, c, row / 2, 0);
    createSubmatrix(A, d, row / 2, col / 2);

    printf("a=\n");
    printMatrix(*a);
    printf("b=\n");
    printMatrix(*b);
    printf("c=\n");
    printMatrix(*c);
    printf("d=\n");
    printMatrix(*d);

    printf("e\n");
    matrix *e = creeMatrix(row / 2, col / 2);
    strassen_inverse_recursive_naive(a, e);

    printf("Z\n");
    matrix *Z = creeMatrix(row / 2, col / 2);
    naiveMultMat(c, e, Z);
    naiveMultMat(Z, b, Z);
    subMatrixSubtraction(d, Z, Z, 0, 0, Z->rows - 1, Z->columns - 1, 0, 0, Z->rows - 1, Z->columns - 1);

    printf("t\n");
    matrix *t = creeMatrix(row / 2, col / 2);
    strassen_inverse_recursive_naive(Z, t);

    // on utilise plus a b c d
    // donc on les reutilise pour eviter malloc
    // on a besoin de (eb) et (tce) deux fois

    // b= e*b
    naiveMultMat(e, b, b);

    // a=tc
    // a = ae = tce = -z
    naiveMultMat(t, c, a);
    naiveMultMat(a, e, a);

    // c = bt = ebt = -y
    naiveMultMat(b, t, c);

    // d = ba = ebtce
    // d =e+d = e+ebtce = x
    naiveMultMat(b, a, d);
    matrice_add(e, d, d);

    // c = y
    negativeMatrix(c);
    // a=z
    negativeMatrix(a);

    // on remplit avec les coefs la matrice result

    fillSubmatrix(result, d, 0, 0);
    fillSubmatrix(result, c, 0, result->columns / 2);
    fillSubmatrix(result, a, result->rows / 2, 0);
    fillSubmatrix(result, t, result->rows / 2, result->columns / 2);

    freeMatrix(*a);
    freeMatrix(*b);
    freeMatrix(*c);
    freeMatrix(*d);
    freeMatrix(*e);
    freeMatrix(*Z);
    freeMatrix(*t);
}

void strassen_inverse_naive(matrix *A, matrix *result)
{
    matrix *Aajuste = creeMatrix(nextPowerOfTwo(A->rows > A->columns ? A->rows : A->columns), nextPowerOfTwo(A->rows > A->columns ? A->rows : A->columns));
    matrix *paddedResult = creeMatrix(nextPowerOfTwo(A->rows > A->columns ? A->rows : A->columns), nextPowerOfTwo(A->rows > A->columns ? A->rows : A->columns));

    ajusteMatrix(A, Aajuste);

    strassen_inverse_recursive_naive(Aajuste, paddedResult);

    extractResult(paddedResult, result, A->rows, A->columns);

    freeMatrix(*Aajuste);
    freeMatrix(*paddedResult);
}

int main(int argc, char const *argv[])
{
    int n = 3;

    matrix *A = creeMatrix(n, n);
    matrix *B = creeMatrix(n, n);

    srand(time(NULL));

    for (int i = 0; i < A->rows; i++)
    {
        for (int j = 0; j < A->columns; j++)
        {
            A->coefs[i][j] = i * A->rows + j + 1;
        }
    }

    for (int i = 0; i < B->rows; i++)
    {
        for (int j = 0; j < B->columns; j++)
        {

            B->coefs[i][j] = i + j;
        }
    }

    printf("A=\n");
    printMatrix(*A);
    printf("\n");

    int facl;
    int facc;

    find_greatest_in_sub_matrix(A, 4, &facl, &facc);

    printf("facl=%d facc=%d\n", facl, facc);

    matrix *P = creeMatrix(n, n);
    matrix *L = creeMatrix(n, n);
    matrix *U = creeMatrix(n, n);
    matrix *Q = creeMatrix(n, n);
    matrix *R = creeMatrix(n, n);
    matrix *R1 = creeMatrix(n, n);
    matrix *R2 = creeMatrix(n, n);
    // createSubmatrix(A, C, 0, 5, 0, 5);

    clock_t start = clock();
    PLUQ(A, P, L, U, Q);
    clock_t end = clock();

    printf("temps pris = %ld\n", end - start);

    printf("P=\n");
    printMatrix(*P);

    printf("L=\n");
    printMatrix(*L);

    printf("U=\n");
    printMatrix(*U);

    printf("Q=\n");
    printMatrix(*Q);

    printf("\n");

    naiveMultMat(P, L, R);
    printMatrix(*R);
    naiveMultMat(R, U, R1);
    printMatrix(*R);
    naiveMultMat(R1, Q, R2);

    printf("resultat main\n");
    printMatrix(*R2);

    freeMatrix(*A);
    freeMatrix(*B);
    freeMatrix(*P);
    freeMatrix(*L);
    freeMatrix(*U);
    freeMatrix(*Q);

    return 0;
}
