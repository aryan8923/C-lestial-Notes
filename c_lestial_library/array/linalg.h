/*This file is part of C-lestial library
(https://github.com/aryan8923/C-lestial-Notes).

C-lestial library is free software: you can redistribute it and/or
modify it under the terms of the GNU General Public License as published by the
Free Software Foundation, either version 3 of the License, or (at your option)
any later version.

C-lestial library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
details.

You should have received a copy of the GNU General Public License along with
C-lestial library. If not, see <https://www.gnu.org/licenses/>.'
*/

#ifndef LINALG_H
#define LINALG_H

#include "../prec.h"
#include "array.h"

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
Vector *matrix_to_vector(Matrix *M, int index, int axis);
Matrix *Array2d_to_Matrix_prec(int nrows, int ncols,
                               precision_t arr[nrows][ncols]);
Matrix *copy_Matrix(Matrix *M);
/* Basic matrix operations */

Matrix *scale_matrix_int(Matrix *M, int scalar);
Matrix *scale_matrix_prec(Matrix *M, precision_t scalar);
Matrix *matmul(Matrix *A, Matrix *B);
Vector *flatten_matrix(Matrix *M);
precision_t trace_matrix(Matrix *A);

/*functions to solve linear systems*/
Vector *lin_system_gauss_elim(Matrix *A, Vector *B);
void LU_decomp(Matrix *A, Matrix *Lower, Matrix *Upper);
precision_t determinant(Matrix *M);
Vector *lin_system_LU_decomp(Matrix *A, Vector *B);
Matrix *inverse_matrix(Matrix *A);

#endif
