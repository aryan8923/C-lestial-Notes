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

#include "c_lestial_library/array/array.h"
#include "c_lestial_library/array/linalg.h"
#include "c_lestial_library/prec.h"
#include <stdio.h>

#define SIZE 3

int main() {
  precision_t A_arr[SIZE][SIZE] = {{1, 2, 3}, {2, 3, 5}, {1, 2, 1}};
  Matrix *A = Array2d_to_Matrix_prec(SIZE, SIZE, A_arr);
  precision_t B_arr[SIZE] = {0, 1, 3};
  Vector *B = array_to_vector_prec(SIZE, B_arr);

  Matrix *Lower = zeros_matrix(PREC, SIZE, SIZE);
  Matrix *Upper = zeros_matrix(PREC, SIZE, SIZE);

  printf("\nGauss Elimination:");
  Vector *X = lin_system_gauss_elim(A, B);

  view_vector(X);

  printf("\nLU decomposed :");
  LU_decomp(A, Lower, Upper);
  view_matrix(Lower);
  view_matrix(Upper);

  X = lin_system_LU_decomp(A, B);

  view_vector(X);

  printf("determinant A = %lf\n", determinant(A));
  view_matrix(inverse_matrix(A));

  return 0;
}
