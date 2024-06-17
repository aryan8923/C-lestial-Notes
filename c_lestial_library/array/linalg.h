#ifndef LINALG_H
#define LINALG_H

#include "../prec.h"

#define NROWS_MATRIX(matrix) sizeof(matrix) / sizeof(matrix[0])
#define NCOLS_MATRIX(matrix) sizeof(matrix[0]) / sizeof(matrix[0][0])
typedef struct {
  DataType dtype;
  int nrows;
  int ncols;
  Data2d values;
} Matrix;

/* functions to initialise matrices */
Matrix *init_matrix(DataType dtype, int rows, int cols);
void free_matrix(Matrix *mat);
void view_matrix(Matrix *mat);
Matrix *identity_matrix(DataType dtype, int nrows);
Matrix *zeros_matrix(DataType dtype, int nrows, int ncols);

/* Basic matrix operations */
void scalar_mul_matrix(int r, int c, precision_t m[r][c], precision_t constant,
                       precision_t result[r][c]);
void matmul(int r1, int c1, precision_t m1[r1][c1], int r2, int c2,
            precision_t m2[r2][c2], precision_t result[r1][c2]);
void flatten_matrix(int nrow, int ncol, precision_t mat[nrow][ncol],
                    precision_t *arr);
precision_t trace_matrix(int N, precision_t A[N][N]);

/*functions to solve linear systems*/
void lin_system_gauss_elim(int n, precision_t A[n][n], precision_t B[n],
                           precision_t X[n]);
void LU_decomp(int N, precision_t A[N][N], precision_t Lower[N][N],
               precision_t Upper[N][N]);
precision_t determinant(int N, precision_t A[N][N]);
void lin_system_LU_decomp(int N, precision_t A[N][N], precision_t B[N],
                          precision_t X[N]);
void inverse_matrix(int N, precision_t A[N][N], precision_t Inverse[N][N]);

#endif
