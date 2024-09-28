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

#include "../prec.h"
#include "array.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define STRING_NOT_SUPP_ERROR                                                  \
  fprintf(stderr, "String elements not yet supported for Matrices\n")

typedef struct {
  DataType dtype;
  int nrows;
  int ncols;
  Data2d values;
} Matrix;

/* functions to initialise a matrix */
Matrix *init_matrix(DataType dtype, int nrows, int ncols) {
  Matrix *mat = (Matrix *)malloc(sizeof(Matrix));
  if (!mat) {
    fprintf(stderr, "Memory allocation failed for Matrix\n");
    exit(EXIT_FAILURE);
  }

  mat->dtype = dtype;
  mat->nrows = nrows;
  mat->ncols = ncols;

  switch (dtype) {
  case INT:
    mat->values.int_data = (int **)malloc(nrows * sizeof(int *));
    for (int i = 0; i < nrows; i++) {
      mat->values.int_data[i] = (int *)malloc(ncols * sizeof(int));
    }
    break;
  case PREC:
    mat->values.prec_data =
        (precision_t **)malloc(nrows * sizeof(precision_t *));
    for (int i = 0; i < nrows; i++) {
      mat->values.prec_data[i] =
          (precision_t *)malloc(ncols * sizeof(precision_t));
    }
    break;
  case STRING:
    STRING_NOT_SUPP_ERROR;
    break;
  }

  return mat;
}

void free_matrix(Matrix *mat) {
  if (!mat)
    return;

  switch (mat->dtype) {
  case INT:
    for (int i = 0; i < mat->nrows; i++) {
      free(mat->values.int_data[i]);
    }
    free(mat->values.int_data);
    break;
  case PREC:
    for (int i = 0; i < mat->nrows; i++) {
      free(mat->values.prec_data[i]);
    }
    free(mat->values.prec_data);
    break;
  case STRING:
    STRING_NOT_SUPP_ERROR;
    break;
  }

  free(mat);
}

void view_matrix(Matrix *mat) {
  if (!mat) {
    fprintf(stderr, "Invalid matrix\n");
    return;
  }
  switch (mat->dtype) {
  case INT:
    printf("\n%d x %d Matrix{INT}\n", mat->nrows, mat->ncols);
    break;
  case PREC:
    printf("\n%d x %d Matrix{precision_t}\n", mat->nrows, mat->ncols);
    break;
  case STRING:
    STRING_NOT_SUPP_ERROR;
    break;
  }

  for (int i = 0; i < mat->nrows; i++) {
    for (int j = 0; j < mat->ncols; j++) {
      switch (mat->dtype) {
      case INT:
        printf("%d\t", mat->values.int_data[i][j]);
        break;
      case PREC:
        printf("%lf\t", mat->values.prec_data[i][j]);
        break;
      case STRING:
        STRING_NOT_SUPP_ERROR;
        break;
      default:
        fprintf(stderr, "Unknown data type\n");
        return;
      }
    }
    printf("\n");
  }
}

Matrix *identity_matrix(DataType dtype, int nrows) {
  // issue with this function is that it initialises the matrix at some address
  // and returns that address that it creates. So if you are using it inside a
  // function, where you are taking an input matrix, if you try to convert that
  // matrix to identity, this function will instead change the input pointer's
  // address to this new one and not to the older one. So it does not make
  // change to already existing matrix. It returns a newly initialsed one

  Matrix *M = init_matrix(dtype, nrows, nrows);

  M->dtype = dtype;
  M->nrows = nrows;
  M->ncols = nrows;

  switch (dtype) {
  case INT:
    for (int i = 0; i < nrows; i++) {
      for (int j = 0; j < nrows; j++) {
        if (i == j) {
          M->values.int_data[i][i] = 1;
        } else {
          M->values.int_data[i][j] = 0;
        }
      }
    }
    break;
  case PREC:
    for (int i = 0; i < nrows; i++) {
      for (int j = 0; j < nrows; j++) {
        if (i == j) {
          M->values.prec_data[i][i] = 1.0;
        } else {
          M->values.prec_data[i][j] = 0.0;
        }
      }
    }
    break;
  case STRING:
    STRING_NOT_SUPP_ERROR;
    break;
  }

  return M;
}

Matrix *zeros_matrix(DataType dtype, int nrows, int ncols) {
  Matrix *M = init_matrix(dtype, nrows, ncols);

  M->dtype = dtype;
  M->nrows = nrows;
  M->ncols = ncols;

  switch (dtype) {
  case INT:
    for (int i = 0; i < nrows; i++) {
      for (int j = 0; j < ncols; j++) {
        M->values.int_data[i][j] = 0;
      }
    }
    break;
  case PREC:
    for (int i = 0; i < nrows; i++) {
      for (int j = 0; j < ncols; j++) {
        M->values.prec_data[i][j] = 0.0;
      }
    }
    break;
  case STRING:
    STRING_NOT_SUPP_ERROR;
    break;
  }

  return M;
}

Vector *matrix_to_vector(Matrix *M, int index, int axis) {
  // axis = 0 means index'th column is to be chosen

  switch (M->dtype) {
  case INT:
    if (axis == 0) {
      Vector *V = zero_vector(INT, M->nrows);
      for (int i = 0; i < M->nrows; i++) {
        V->values.int_data[i] = M->values.int_data[index][i];
      }
      return V;
    } else if (axis == 1) {
      Vector *V = zero_vector(INT, M->ncols);
      for (int i = 0; i < M->ncols; i++) {
        V->values.int_data[i] = M->values.int_data[i][index];
      }
    } else {
      fprintf(stderr, "Incomatible value of axis in matrix_to_vector "
                      "(Allowed axis is 0 or 1)\n");
      return NULL;
      exit(EXIT_FAILURE);
    }

  case PREC:
    if (axis == 0) {
      Vector *V = zero_vector(PREC, M->nrows);
      for (int i = 0; i < M->nrows; i++) {
        V->values.prec_data[i] = M->values.prec_data[index][i];
      }
      return V;
    } else if (axis == 1) {
      Vector *V = zero_vector(PREC, M->ncols);
      for (int i = 0; i < M->ncols; i++) {
        V->values.prec_data[i] = M->values.prec_data[i][index];
      }
    } else {
      fprintf(stderr, "Incomatible value of axis in matrix_to_vector "
                      "(Allowed axis is 0 or 1)\n");
      return NULL;
      exit(EXIT_FAILURE);
    }
  case STRING:
    STRING_NOT_SUPP_ERROR;
    return NULL;
  }
  return NULL;
}

Matrix *Array2d_to_Matrix_prec(int nrows, int ncols,
                               precision_t arr[nrows][ncols]) {
  Matrix *M = zeros_matrix(PREC, nrows, ncols);

  for (int i = 0; i < nrows; i++) {
    for (int j = 0; j < ncols; j++) {
      M->values.prec_data[i][j] = arr[i][j];
    }
  }

  return M;
}

Matrix *copy_Matrix(Matrix *M) {
  Matrix *M_copy = zeros_matrix(M->dtype, M->nrows, M->ncols);

  switch (M->dtype) {
  case INT:
    for (int i = 0; i < M->nrows; i++) {
      for (int j = 0; j < M->ncols; j++) {
        M_copy->values.int_data[i][j] = M->values.int_data[i][j];
      }
    }
    break;
  case PREC:
    for (int i = 0; i < M->nrows; i++) {
      for (int j = 0; j < M->ncols; j++) {
        M_copy->values.prec_data[i][j] = M->values.prec_data[i][j];
      }
    }
    break;
  case STRING:
    STRING_NOT_SUPP_ERROR;
    break;
  }

  return M_copy;
}

/* Basic matrix operations */

Matrix *scale_matrix_int(Matrix *M, int scalar) {
  Matrix *M_scaled = zeros_matrix(M->dtype, M->nrows, M->ncols);

  if (M->dtype == INT) {
    for (int i = 0; i < M->nrows; i++) {
      for (int j = 0; j < M->ncols; j++) {
        M_scaled->values.int_data[i][j] = scalar * M->values.int_data[i][j];
      }
    }
  } else {
    fprintf(stderr, "Type Mismatch error when scaling the int type Matrix\n");
    exit(EXIT_FAILURE);
  }

  return M_scaled;
}

Matrix *scale_matrix_prec(Matrix *M, precision_t scalar) {
  Matrix *M_scaled = zeros_matrix(M->dtype, M->nrows, M->ncols);

  if (M->dtype == INT) {
    for (int i = 0; i < M->nrows; i++) {
      for (int j = 0; j < M->ncols; j++) {
        M_scaled->values.prec_data[i][j] = scalar * M->values.prec_data[i][j];
      }
    }
  } else {
    fprintf(stderr, "Type Mismatch error when scaling the int type Matrix\n");
    exit(EXIT_FAILURE);
  }

  return M_scaled;
}

Matrix *matmul(Matrix *A, Matrix *B) {
  Matrix *C = zeros_matrix(A->dtype, A->nrows, B->ncols);
  if (A->ncols != B->nrows) {
    fprintf(stderr, "Invalid dimensions for mat_mul");
    exit(EXIT_FAILURE);
  } else {

    switch (A->dtype) {
    case INT:
      for (int i = 0; i < A->nrows; i++) {
        for (int k = 0; k < B->ncols; k++) {
          for (int j = 0; j < B->ncols; j++) {
            C->values.int_data[i][j] +=
                A->values.int_data[i][k] * B->values.int_data[k][j];
          }
        }
      }
    case PREC:
      for (int i = 0; i < A->nrows; i++) {
        for (int k = 0; k < B->ncols; k++) {
          for (int j = 0; j < B->ncols; j++) {
            C->values.prec_data[i][j] +=
                A->values.prec_data[i][k] * B->values.prec_data[k][j];
          }
        }
      }
    case STRING:
      STRING_NOT_SUPP_ERROR;
    }
  }

  return C;
}

Vector *flatten_matrix(Matrix *M) { // flattens a matrix to an array
  int index = 0;
  Vector *V = zero_vector(M->dtype, M->nrows * M->ncols);

  switch (M->dtype) {
  case INT:
    for (int i = 0; i < M->nrows; i++) {
      for (int j = 0; j < M->ncols; j++) {
        V->values.int_data[index++] = M->values.int_data[i][j];
      }
    }
    break;
  case PREC:
    for (int i = 0; i < M->nrows; i++) {
      for (int j = 0; j < M->ncols; j++) {
        V->values.prec_data[index++] = M->values.prec_data[i][j];
      }
    }
    break;
  case STRING:
    STRING_NOT_SUPP_ERROR;
    break;
  }

  return V;
}

precision_t trace_matrix(Matrix *A) {
  precision_t trace = 0.0;

  if (A->nrows == A->ncols) {
    switch (A->dtype) {
    case INT:
      for (int i = 0; i < A->nrows; i++) {
        trace += A->values.int_data[i][i];
      }
      break;
    case PREC:
      for (int i = 0; i < A->nrows; i++) {
        trace += A->values.prec_data[i][i];
      }
      break;
    case STRING:
      STRING_NOT_SUPP_ERROR;
      break;
    }

    return trace;
  } else {
    fprintf(stderr, "given matrix not square matrix, to calculate trace\n");
    exit(EXIT_FAILURE);
  }

  return trace;
}

/* Functions to solve linear equations */

Vector *lin_system_gauss_elim(Matrix *A, Vector *B) {
  /* This function solves the linear equation AX = B */
  // This function makes changes to

  Matrix *A_copy = copy_Matrix(A);
  Vector *B_copy = copy_Vector(B);

  Vector *X = zero_vector(PREC, B->size);

  if (A->nrows != A->ncols) {
    fprintf(stderr,
            "Error: \"A\" Matrix in lin_system_gauss_elim not square.\n");
    exit(EXIT_FAILURE);
  }
  if (A->nrows != B->size) {
    fprintf(stderr,
            "Error: Matrix \"A\" and Vector \"B\" have unequal sizes. \n");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < A->nrows; i++) {
    // Pivoting
    // This works by comparing the ith element of all rows and sees which
    // one of them have the highest absolute values Once it sees that kth
    // row has greatest ith element (absolute), then it exchanges kth row
    // with ith.
    int maxRow = i;
    for (int k = i + 1; k < A_copy->nrows; k++) {
      if (fabs(A_copy->values.prec_data[k][i]) >
          fabs(A_copy->values.prec_data[maxRow][i])) {
        maxRow = k;
      }
    }

    // Now you know which row has the greatest ith element (absolute)
    // Swap rows in A
    for (int k = 0; k < A_copy->nrows; k++) {
      precision_t temp = A_copy->values.prec_data[i][k];
      A_copy->values.prec_data[i][k] = A_copy->values.prec_data[maxRow][k];
      A_copy->values.prec_data[maxRow][k] = temp;
    }

    // Swap values in B
    precision_t temp = B_copy->values.prec_data[i];
    B_copy->values.prec_data[i] = B_copy->values.prec_data[maxRow];
    B_copy->values.prec_data[maxRow] = temp;

    // Elimination
    for (int j = i + 1; j < A_copy->nrows; j++) {
      precision_t m =
          A_copy->values.prec_data[j][i] / A_copy->values.prec_data[i][i];
      for (int k = i; k < A_copy->nrows; k++) {
        A_copy->values.prec_data[j][k] -= m * A_copy->values.prec_data[i][k];
      }
      B_copy->values.prec_data[j] -= m * B_copy->values.prec_data[i];
    }
  }

  // Back Substitution
  for (int i = A_copy->nrows - 1; i >= 0; i--) {
    X->values.prec_data[i] = B_copy->values.prec_data[i];
    for (int j = i + 1; j < A_copy->nrows; j++) {
      X->values.prec_data[i] -=
          A_copy->values.prec_data[i][j] * X->values.prec_data[j];
    }
    X->values.prec_data[i] /= A_copy->values.prec_data[i][i];
  }

  return X;
}

void LU_decomp(Matrix *A, Matrix *Lower, Matrix *Upper) {
  // This function takes a square matrix and finds its "LU decomposed" form:
  // LU = A.
  // The L and U matrices are to be stored in Lower and Upper Matrix.

  int N = A->nrows;

  if (A->nrows != A->ncols) {
    fprintf(stderr,
            "Error: Matrix \"A\" in LU_decomp function is not square\n");
    exit(EXIT_FAILURE);
  }
  if (Lower->ncols != Lower->nrows) {
    fprintf(stderr,
            "Error: Matrix \"Lower\" in LU_decomp function is not square\n");
    exit(EXIT_FAILURE);
  }
  if (Upper->ncols != Upper->nrows) {
    fprintf(stderr,
            "Error: Matrix \"Upper\" in LU_decomp function is not square\n");
    exit(EXIT_FAILURE);
  }
  if ((A->nrows != Lower->nrows) || (A->nrows != A->ncols)) {
    fprintf(stderr, "Error: Dimension mismatch between Matrix \"A\" and the "
                    "other matrix in LU_decomp function\n");
    exit(EXIT_FAILURE);
  }

  precision_t sum;

  // Initialize Lower to identity matrix and Upper to zero matrix
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (i == j) {
        Lower->values.prec_data[i][j] = 1.0;
      } else {
        Lower->values.prec_data[i][j] = 0.0;
      }
      Upper->values.prec_data[i][j] = 0.0;
    }
  }

  for (int j = 0; j < N; j++) {
    for (int i = 0; i < j + 1; i++) {
      sum = 0.0;
      for (int k = 0; k < i; k++) {
        sum += (Lower->values.prec_data[i][k] * Upper->values.prec_data[k][j]);
      }
      Upper->values.prec_data[i][j] = A->values.prec_data[i][j] - sum;
    }
    for (int i = j + 1; i < N; i++) {
      sum = 0.0;
      for (int k = 0; k < j; k++) {
        sum += (Lower->values.prec_data[i][k] * Upper->values.prec_data[k][j]);
      }
      Lower->values.prec_data[i][j] =
          (A->values.prec_data[i][j] - sum) / (Upper->values.prec_data[j][j]);
    }
  }
}

precision_t determinant(Matrix *M) {
  if (M->nrows != M->ncols) {
    fprintf(stderr,
            "Error: Given matrix in determinant function is not square.");
    exit(EXIT_FAILURE);
  }

  Matrix *Lower = zeros_matrix(PREC, M->nrows, M->ncols);
  Matrix *Upper = zeros_matrix(PREC, M->nrows, M->ncols);
  precision_t det = 1.0;

  LU_decomp(M, Lower, Upper);

  // calculating the determinant using the fact that
  // det(A) = product(diagonal elements of Upper Matrix of A)

  for (int i = 0; i < M->nrows; i++) {
    det *= Upper->values.prec_data[i][i];
  }
  return det;
}

Vector *lin_system_LU_decomp(Matrix *A, Vector *B) {
  // Function to solve AX=B

  precision_t sum;
  int N = A->nrows;

  Vector *X = zero_vector(PREC, B->size);

  if (A->nrows != A->ncols) {
    fprintf(stderr,
            "Error: \"A\" Matrix in lin_system_gauss_elim not square.\n");
    exit(EXIT_FAILURE);
  }
  if (A->nrows != B->size) {
    fprintf(stderr,
            "Error: Matrix \"A\" and Vector \"B\" have unequal sizes. \n");
    exit(EXIT_FAILURE);
  }

  Matrix *Upper = zeros_matrix(PREC, A->nrows, A->ncols);
  Matrix *Lower = zeros_matrix(PREC, A->nrows, A->ncols);
  Vector *Z = zero_vector(PREC, A->nrows);

  LU_decomp(A, Lower, Upper);

  // Forward Substitution to solve for Z in LZ = B where Z = UA
  Z->values.prec_data[0] = B->values.prec_data[0];
  for (int i = 1; i < N; i++) {
    sum = 0.0;
    for (int j = 0; j < i; j++) {
      sum += (Lower->values.prec_data[i][j] * Z->values.prec_data[j]);
    }
    Z->values.prec_data[i] = B->values.prec_data[i] - sum;
  }

  // Backward Substitution to solve for X in UX = Z
  X->values.prec_data[N - 1] =
      Z->values.prec_data[N - 1] / Upper->values.prec_data[N - 1][N - 1];
  for (int i = N - 2; i >= 0; i--) {
    sum = 0.0;
    for (int j = N - 1; j > i; j--) {
      sum += (Upper->values.prec_data[i][j] * X->values.prec_data[j]);
    }
    X->values.prec_data[i] =
        (Z->values.prec_data[i] - sum) / (Upper->values.prec_data[i][i]);
  }
  return X;
}

Matrix *inverse_matrix(Matrix *A) {

  Matrix *Inverse = zeros_matrix(PREC, A->nrows, A->ncols);
  Matrix *Upper = zeros_matrix(PREC, A->nrows, A->ncols);
  Matrix *Lower = zeros_matrix(PREC, A->nrows, A->ncols);
  Matrix *inv_Upper = zeros_matrix(PREC, A->nrows, A->ncols);
  Matrix *inv_Lower = zeros_matrix(PREC, A->nrows, A->ncols);
  precision_t sum;
  int N = A->ncols;
  // This function can still not give correct results.
  // For eg for : {{6, 2, 3},{0, 0, 4}, {2, 0, 0}}
  // the final result is a matrix will all elements = nan

  LU_decomp(A, Lower, Upper);

  // Note to self: combine the two loops for forward and backward
  // Substitution

  // Finding inverse of Lower using Forward Substitution

  for (int col = 0; col < N; col++) {

    if (col == 0) {
      inv_Lower->values.prec_data[0][col] = 1.0;
    } else {
      inv_Lower->values.prec_data[0][col] = 0.0;
    }

    for (int i = 1; i < N; i++) {
      sum = 0.0;
      for (int j = 0; j < i; j++) {
        sum += (Lower->values.prec_data[i][j] *
                inv_Lower->values.prec_data[j][col]);
      }
      if (i == col) {
        inv_Lower->values.prec_data[i][col] = (1.0 - sum);
      } else {
        inv_Lower->values.prec_data[i][col] = -sum;
      }
    }
  }

  // Backward Substitution to get inverse_Upper
  for (int col = 0; col < N; col++) {

    if (col == N - 1) {
      inv_Upper->values.prec_data[N - 1][col] =
          1.0 / (Upper->values.prec_data[N - 1][col]);
    } else {
      inv_Upper->values.prec_data[N - 1][col] = 0.0;
    }

    for (int i = N - 2; i >= 0; i--) {
      sum = 0.0;
      for (int j = N - 1; j > i; j--) {
        sum += (Upper->values.prec_data[i][j] *
                inv_Upper->values.prec_data[j][col]);
      }
      if (i == col) {
        inv_Upper->values.prec_data[i][col] =
            (1.0 - sum) / (Upper->values.prec_data[i][i]);
      } else {
        inv_Upper->values.prec_data[i][col] =
            -sum / Upper->values.prec_data[i][i];
      }
    }
  }

  // Note to self: create a function that uses sparse matrix multiplication
  // instead

  Inverse = matmul(inv_Upper, inv_Lower);

  return Inverse;
}
