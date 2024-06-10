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

#ifndef ARRAY_H
#define ARRAY_H

#include "../prec.h"

#define LENGTH_ARR(arr) sizeof(arr) / sizeof(*arr) /* get size of array */

void view_array(int size, precision_t arr[]);

/* functions to initialise array */
void init_array(precision_t arr[], int size, precision_t fill_value);
void init_zeros_array(precision_t arr[], int size);
void init_ones_array(precision_t arr[], int size);

/* functions for basic statistics */
precision_t mean_array(precision_t array[], int size);

#endif
