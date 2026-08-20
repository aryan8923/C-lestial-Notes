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
#include "c_lestial_library/defs.h"
#include <bits/types/struct_timeval.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

float timediff(struct timeval *start, struct timeval *end) {
  return (end->tv_sec - start->tv_sec) + 1e-6 * (end->tv_usec - start->tv_usec);
}

int main() {

  struct timeval start, end;
  gettimeofday(&start, NULL);
  // ------------------------------------------------------------------------------------------------------
  //   CODE BETWEEEN THESE LINES
  precision_t raw_data[3][3] = {
      {6.0, 2.0, 3.0}, {0.0, 0.0, 4.0}, {2.0, 0.0, 0.0}};
  Matrix *A = Array2d_to_Matrix_prec(3, 3, raw_data);

  printf("Matrix A: \n");
  view_matrix(A);

  Matrix *inv_A = inverse_matrix(A);
  printf("Inverse: \n");
  view_matrix(inv_A);

  // ------------------------------------------------------------------------------------------------------

  gettimeofday(&end, NULL);
  printf("\n\nTime Elapsed : %0.6f seconds\n", timediff(&start, &end));

  return 0;
}
