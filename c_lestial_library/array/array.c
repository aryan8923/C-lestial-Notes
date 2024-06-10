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
#include <stdarg.h>
#include <stdio.h>

/* function to view array elements */
void view_array(int size, precision_t arr[]) {
  printf("\n[ %f", arr[0]);
  for (int i = 1; i < size - 1; i++)
    printf(" , %f", arr[i]);
  printf(" , %f ]\n", arr[size - 1]);
  return;
}
/*functions to initialise array */
void init_array(precision_t arr[], int size, precision_t fill_value) {
  for (int i = 0; i < size; i++)
    arr[i] = fill_value;
  return;
}

void init_zeros_array(precision_t arr[], int size) {
  init_array(arr, size, 0.0);
  return;
}
void init_ones_array(precision_t arr[], int size) {
  init_array(arr, size, 1.0);
  return;
}

/* functions for basic statistics for arrays*/

precision_t mean_array(precision_t array[], int size) {
  int count;
  precision_t sum = 0.0;

  for (count = 0; count < size; count++)
    sum += array[count];

  return sum / (precision_t)size;
}
