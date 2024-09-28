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

typedef enum {
  INVERTED_CDF,
  AVERAGED_INVERTED_CDF,
  CLOSEST_OBSERVATION,
  INTERPOLATED_INVERTED_CDF,
  HAZEN,
  WEIBULL,
  LINEAR,
  MEDIAN_UNBIASED,
  NORMAL_UNBIASED,
  LOWER,
  HIGHER,
  MIDPOINT,
  NEAREST
} percentile_method;

#define LENGTH_ARR(arr) sizeof(arr) / sizeof(*arr) /* get size of array */

void view_array(int size, precision_t arr[]);
void view_vector(Vector *A);

/* functions to initialise array and vectors */
Vector *zero_vector(DataType dtype, int size);
void free_vector(Vector *V);
Vector *ones_vector(DataType dtype, int size);
Vector *array_to_vector_prec(int size, precision_t arr[]);
Vector *array_to_vector_int(int size, int arr[]);
Vector *copy_vector(Vector *V);
Vector *range_vector(precision_t start, precision_t stop, precision_t step);
Vector *linspace_vector(precision_t start, precision_t stop, precision_t N);
Vector *slice_vector(Vector *V, int *indices, int indices_size);

/* Functions for manipulation of vectors and arrays */
Vector *concat_vector(Vector *first_vector, ...);
void append_vector(Vector *first_vector, ...);

/* Function to load and save a vector from files */
void save_vector(const char *filename, Vector *vec);
Vector *load_vector(const char *filename);

/* Functions for basic arithmetic of arrays and vectors*/
Vector *scale_vector_int(Vector *V, int scalar);
Vector *scale_vector_prec(Vector *V, precision_t scalar);
Vector *elem_arith_op_vectors(Vector *A, Vector *B, arith_oper o);
Vector *map_vector(precision_t (*func)(precision_t), Vector *V);
precision_t dot_vector_prec(Vector *A, Vector *B);

/* functions for sorting , searching and counting */

int compare_int(const void *a, const void *b);
int compare_int_desc(const void *a, const void *b);
int compare_precision(const void *a, const void *b);
int compare_precision_desc(const void *a, const void *b);
int compare_string(const void *a, const void *b);
int compare_string_desc(const void *a, const void *b);

void sort_vector(Vector *v, int ascending);

/* functions for statistics */
precision_t mean_vector(Vector *V);
precision_t sum_vector(Vector *V);
precision_t min_vector(Vector *V);
precision_t max_vector(Vector *V);
precision_t ptp_vector(Vector *V);
precision_t percentile_vector(Vector *V, precision_t q,
                              percentile_method method);
precision_t median_vector(Vector *V);
precision_t weighted_average_vector(Vector *V, Vector *weights);
precision_t std_vector(Vector *V);
precision_t variance_vector(Vector *V, int ddof);

#endif
