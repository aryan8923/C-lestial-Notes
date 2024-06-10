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
