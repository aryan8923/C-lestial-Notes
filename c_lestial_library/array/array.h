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

typedef struct {
  DataType dtype;
  int size;
  Data values;
} Vector;

#define LENGTH_ARR(arr) sizeof(arr) / sizeof(*arr) /* get size of array */

void view_array(int size, precision_t arr[]);
void view_vector(Vector *A);

/* functions to initialise array and vectors */
Vector *zero_vector(DataType dtype, int size);
Vector *ones_vector(DataType dtype, int size);
Vector *array_to_vector_prec(int size, precision_t arr[]);
Vector *copy_Vector(Vector *V);

/* Functions for basic arithmetic of arrays and vectors*/
Vector *scale_vector_int(Vector *V, int scalar);
Vector *scale_vector_prec(Vector *V, precision_t scalar);
Vector *elem_arith_op_vectors(Vector *A, Vector *B, arith_oper o);

/* functions for basic statistics */
precision_t mean_vector(Vector *V);
precision_t sum_vector(Vector *V);
precision_t min_vector(Vector *V);
precision_t max_vector(Vector *V);

#endif
