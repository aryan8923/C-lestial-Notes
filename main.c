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
#include <stdio.h>

int main() {
  int data1[] = {1, 2, 3};
  int data2[] = {4, 5, 6};
  int data3[] = {7, 8, 9};

  Vector *vector1 = array_to_vector_int(LENGTH_ARR(data1), data1);
  Vector *vector2 = array_to_vector_int(LENGTH_ARR(data2), data2);
  Vector *vector3 = array_to_vector_int(LENGTH_ARR(data3), data3);

  // Concatenate vectors
  Vector *result_vector = concat_vector(vector1, vector2, vector3, NULL);

  // Print result
  view_vector(result_vector);
  printf("\n");
  view_vector(vector1);

  // Free result vector
  free_vector(result_vector);
  return 0;
}
