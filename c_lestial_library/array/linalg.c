#include "../prec.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/* functions for viewing matrices */

void view_matrix(int rows, int cols, precision_t matrix[rows][cols]) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      printf("%f  ", matrix[i][j]);
    }
    printf("\n");
  }
  return;
}

/* functions to initialise a matrix */

void init_identity_matrix(int r, int c, precision_t m[r][c]) {
  if (r != c) {
    printf("\n Error: Given matrix is not a square matrix");
    exit(1);
  } else {
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) {
        if (i == j)
          m[i][j] = 1.0;
        else {
          m[i][j] = 0.0;
        }
      }
    }
  }
  return;
}

void init_zeros_matrix(int r, int c, precision_t m[r][c]) {
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      m[i][j] = 0.0;
    }
  }
}

/* Basic matrix operations */
void scalar_mul_matrix(int r, int c, precision_t m[r][c], precision_t constant,
                       precision_t result[r][c]) {
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++)
      result[i][j] = constant * m[i][j];
  }
  return;
}

void matmul(int r1, int c1, precision_t m1[r1][c1], int r2, int c2,
            precision_t m2[r2][c2], precision_t result[r1][c2]) {

  if (c1 != r2) {
    printf("\n Error: Invalid dimensions for function matmul\n");
    exit(1);
  } else {
    for (int i = 0; i < r1; i++) {
      for (int j = 0; j < c2; j++) {
        result[i][j] = 0;

        for (int k = 0; k < r2; k++) {
          result[i][j] += m1[i][k] * m2[k][j];
        }
      }
    }
    return;
  }
}

void flatten_matrix(int nrow, int ncol, precision_t mat[nrow][ncol],
                    precision_t *arr) { // flattens a matrix to an array
  int index = 0;

  for (int i = 0; i < nrow; i++) {
    for (int j = 0; j < ncol; j++) {
      arr[index++] = mat[i][j];
    }
  }
  return;
}

precision_t trace_matrix(int N, precision_t A[N][N]) {
  precision_t trace = 0.0;

  for (int i = 0; i < N; i++) {
    trace += A[i][i];
  }
  return trace;
}

/* Functions to solve linear equations */

void lin_system_gauss_elim(int n, precision_t A[n][n], precision_t B[n],
                           precision_t X[n]) {
  /* This function solves the linear equation AX = B */

  for (int i = 0; i < n; i++) {
    // Pivoting
    // This works by comparing the ith element of all rows and sees which one of
    // them have the highest absolute values Once it sees that kth row has
    // greatest ith element (absolute), then it exchanges kth row with ith.
    int maxRow = i;
    for (int k = i + 1; k < n; k++) {
      if (fabs(A[k][i]) > fabs(A[maxRow][i])) {
        maxRow = k;
      }
    }

    // Now you know which row has the greatest ith element (absolute)
    // Swap rows in A
    for (int k = 0; k < n; k++) {
      precision_t temp = A[i][k];
      A[i][k] = A[maxRow][k];
      A[maxRow][k] = temp;
    }

    // Swap values in B
    precision_t temp = B[i];
    B[i] = B[maxRow];
    B[maxRow] = temp;

    // Elimination
    for (int j = i + 1; j < n; j++) {
      precision_t m = A[j][i] / A[i][i];
      for (int k = i; k < n; k++) {
        A[j][k] -= m * A[i][k];
      }
      B[j] -= m * B[i];
    }
  }

  // Back Substitution
  for (int i = n - 1; i >= 0; i--) {
    X[i] = B[i];
    for (int j = i + 1; j < n; j++) {
      X[i] -= A[i][j] * X[j];
    }
    X[i] /= A[i][i];
  }
}

void LU_decomp(int N, precision_t A[N][N], precision_t Lower[N][N],
               precision_t Upper[N][N]) {
  // This function takes a square matrix and finds it "LU decomposed" form:
  // LU = A.
  // The L and U matrices are to be stored in Lower and Upper Matrix.

  // Note to self: Make a more storage optimised function since this requires 2
  // extra NxN matrices even though both of them are half zeros
  //// This may be achieved using sparse matrices. Add a function
  /// LU_decomp_sparse that instead stores the L and U matrices in sparse
  /// matrices.

  precision_t sum;

  init_identity_matrix(N, N, Lower);
  init_zeros_matrix(N, N, Upper);

  for (int j = 0; j < N; j++) {
    for (int i = 0; i < j + 1; i++) {
      if (i == 0)
        sum = 0.0;
      else {
        sum = 0.0;
        for (int k = 0; k < i; k++) {
          sum += (Lower[i][k] * Upper[k][j]);
        }
      }
      Upper[i][j] = A[i][j] - sum;
    }
    for (int i = j + 1; i < N; i++) {
      sum = 0.0;
      for (int k = 0; k < j; k++) {
        sum += (Lower[i][k] * Upper[k][j]);
      }
      Lower[i][j] = (A[i][j] - sum) / (Upper[j][j]);
    }
  }
}

precision_t determinant(int N, precision_t A[N][N]) {
  precision_t Lower[N][N], Upper[N][N];
  precision_t det = 1.0;

  LU_decomp(N, A, Lower, Upper);

  // calculating the determinant using the fact that
  // det(A) = product(diagonal elements of Upper Matrix of A)

  for (int i = 0; i < N; i++) {
    det *= Upper[i][i];
  }
  return det;
}

void lin_system_LU_decomp(int N, precision_t A[N][N], precision_t B[N],
                          precision_t X[N]) {
  // Function to solve AX=B

  precision_t sum;

  precision_t Upper[N][N], Lower[N][N], Z[N];

  LU_decomp(N, A, Lower, Upper);

  // Forward Substitution to solve for Z in LZ = B where Z = UA
  Z[0] = B[0];
  for (int i = 1; i < N; i++) {
    sum = 0.0;
    for (int j = 0; j < i; j++) {
      sum += (Lower[i][j] * Z[j]);
    }
    Z[i] = B[i] - sum;
  }

  // Backward Substitution to solve for X in UX = Z
  X[N - 1] = Z[N - 1] / Upper[N - 1][N - 1];
  for (int i = N - 2; i >= 0; i--) {
    sum = 0.0;
    for (int j = N - 1; j > i; j--) {
      sum += (Upper[i][j] * X[j]);
    }
    X[i] = (Z[i] - sum) / (Upper[i][i]);
  }
  return;
}

void inverse_matrix(int N, precision_t A[N][N], precision_t Inverse[N][N]) {
  precision_t Upper[N][N], Lower[N][N], inv_Upper[N][N], inv_Lower[N][N];
  precision_t sum;
  // This function can still not give correct results.
  // For eg for : {{6, 2, 3},{0, 0, 4}, {2, 0, 0}}
  // the final result is a matrix will all elements = nan

  LU_decomp(N, A, Lower, Upper);

  // Note to self: combine the two loops for forward and backward Substitution

  // Finding inverse of Lower using Forward Substitution

  for (int col = 0; col < N; col++) {

    if (col == 0) {
      inv_Lower[0][col] = 1.0;
    } else {
      inv_Lower[0][col] = 0.0;
    }

    for (int i = 1; i < N; i++) {
      sum = 0.0;
      for (int j = 0; j < i; j++) {
        sum += (Lower[i][j] * inv_Lower[j][col]);
      }
      if (i == col) {
        inv_Lower[i][col] = (1.0 - sum);
      } else {
        inv_Lower[i][col] = -sum;
      }
    }
  }

  // Backward Substitution to get inverse_Upper
  for (int col = 0; col < N; col++) {

    if (col == N - 1) {
      inv_Upper[N - 1][col] = 1.0 / (Upper[N - 1][col]);
    } else {
      inv_Upper[N - 1][col] = 0.0;
    }

    for (int i = N - 2; i >= 0; i--) {
      sum = 0.0;
      for (int j = N - 1; j > i; j--) {
        sum += (Upper[i][j] * inv_Upper[j][col]);
      }
      if (i == col) {
        inv_Upper[i][col] = (1.0 - sum) / (Upper[i][i]);
      } else {
        inv_Upper[i][col] = -sum / Upper[i][i];
      }
    }
  }

  // Note to self: create a function that uses sparse matrix multiplication
  // instead
  matmul(N, N, inv_Upper, N, N, inv_Lower, Inverse);

  return;
}