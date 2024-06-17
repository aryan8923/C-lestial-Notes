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

#include "c_lestial_library/array/linalg.h"
#include "c_lestial_library/prec.h"
#include <stdio.h>

int main() {

  // Example usage
  Matrix *mat_int = zeros_matrix(INT, 3, 5);
  Matrix *mat_prec = zeros_matrix(PREC, 3, 4);

  // Print matrices
  view_matrix(mat_int);

  view_matrix(mat_prec);

  // Free matrices
  free_matrix(mat_int);
  free_matrix(mat_prec);
  return 0;
}
