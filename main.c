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
#include "c_lestial_library/prec.h"

#define ID_SIZE 3

int main() {

  precision_t A_arr[] = {10, 20, 30, 40, 50};
  int index_A[ID_SIZE] = {2, 3, 1};

  Vector *V = array_to_vector_prec(LENGTH_ARR(A_arr), A_arr);

  view_vector(slice_vector(V, index_A, LENGTH_ARR(index_A)));

  return 0;
}
