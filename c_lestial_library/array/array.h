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

/* functions to initialise array */
Vector *zero_vector(DataType dtype, int size);
Vector *ones_vector(DataType dtype, int size);
void init_array(int size, precision_t arr[], precision_t fill_value);
void init_zeros_array(int size, precision_t arr[]);
void init_ones_array(int size, precision_t arr[]);

/* Functions for basic arithmetic of arrays */
void scalar_mul_array(int size, precision_t arr[], precision_t scalar,
                      precision_t result[]);

/* functions for basic statistics */
precision_t mean_array(int size, precision_t array[]);
precision_t sum_array(int size, precision_t array[]);
precision_t min_array(int size, precision_t array[]);
precision_t max_array(int size, precision_t array[]);

#endif
