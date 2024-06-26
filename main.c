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
#include <math.h>
#include <stdio.h>

#define N_PTS 4

precision_t f(precision_t i) { return cos(i * M_PI / (N_PTS + 1)); }

int main() {
  precision_t arr[4] = {1, 2, 3, 4};
  Vector *V = array_to_vector_prec(4, arr);

  view_vector(linspace_vector(1.0, 5, 10));
  printf("\nV:");
  view_vector(V);
  printf("\nmap(V):");
  view_vector(map_vector(&f, V));

  return 0;
}
