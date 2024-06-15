#include "../prec.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

typedef struct {
  DataType dtype;
  int *dim;
  Data values;
} Array;

/* function to view array elements */
void view_array(int size, precision_t arr[]) {
  printf("\n[ %f", arr[0]);
  for (int i = 1; i < size - 1; i++)
    printf(" , %f", arr[i]);
  printf(" , %f ]\n", arr[size - 1]);
  return;
}
/*functions to initialise array */
void init_array(int size, precision_t arr[], precision_t fill_value) {
  for (int i = 0; i < size; i++)
    arr[i] = fill_value;
  return;
}

void init_zeros_array(int size, precision_t arr[]) {
  init_array(size, arr, 0.0);
  return;
}
void init_ones_array(int size, precision_t arr[]) {
  init_array(size, arr, 1.0);
  return;
}

/* Functions for basic arithmetic of arrays */

/* functions for basic statistics for arrays*/

precision_t mean_array(int size, precision_t array[]) {
  int count;
  precision_t sum = 0.0;

  for (count = 0; count < size; count++)
    sum += array[count];

  return sum / (precision_t)size;
}

precision_t sum_array(int size, precision_t array[]) {
  precision_t sum = 0.0;

  for (int count = 0; count < size; count++) {
    sum += array[count];
  }

  return sum;
}

precision_t min_array(int size, precision_t array[]) {
  precision_t min = array[0];

  for (int i = 1; i < size; i++) {
    if (min > array[i]) {
      min = array[i];
    }
  }
  return min;
}

precision_t max_array(int size, precision_t array[]) {
  precision_t max = array[0];

  for (int i = 1; i < size; i++) {
    if (max < array[i]) {
      max = array[i];
    }
  }
  return max;
}

// int null_present_array(precision_t array[], int size){
//   int null_present[size];
//
//   for (int i =0 ; i<size; i++) {
//     if (array[i]==NULL) {
//
//     }
//   }
// }
