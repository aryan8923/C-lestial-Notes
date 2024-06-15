#include "../prec.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  DataType dtype;
  int size;
  Data values;
} Vector;

/* function to view array and vector elements */

void view_vector(Vector *A) {
  printf("\n%d-element Vector {", A->size);
  switch (A->dtype) {
  case INT:
    printf("int}\n\n[ %d", A->values.int_data[0]);
    for (int i = 1; i < A->size - 1; i++) {
      printf(" , %d", A->values.int_data[i]);
    }
    printf(" , %d ]\n", A->values.int_data[A->size - 1]);
    break;
  case PREC:
    printf("precision_t}\n\n[ %lf", A->values.prec_data[0]);
    for (int i = 1; i < A->size - 1; i++) {
      printf(" , %lf", A->values.prec_data[i]);
    }
    printf(" , %lf ]\n", A->values.prec_data[A->size - 1]);
    break;
  case STRING:
    printf("string}\n\n[ %s", A->values.string_data[0]);
    for (int i = 1; i < A->size - 1; i++) {
      printf(" , %s", A->values.string_data[i]);
    }
    printf(" , %s ]\n", A->values.string_data[A->size - 1]);
    break;
  }
}

/*functions to initialise array and vectors */

Vector *zero_vector(DataType dtype, int size) {
  Vector *V = (Vector *)malloc(sizeof(Vector));

  if (V == NULL) {
    fprintf(stderr, "Memory allocation failed for Vector");
    exit(EXIT_FAILURE);
  }

  switch (dtype) {
  case INT:
    V->values.int_data = (int *)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
      V->values.int_data[i] = 0;
    }
    break;
  case PREC:
    V->values.prec_data = (precision_t *)malloc(size * sizeof(precision_t));
    for (int i = 0; i < size; i++) {
      V->values.prec_data[i] = 0.0;
    }
    break;
  }

  V->dtype = dtype;
  V->size = size;

  return V;
}

Vector *ones_vector(DataType dtype, int size) {
  Vector *V = (Vector *)malloc(sizeof(Vector));

  if (V == NULL) {
    fprintf(stderr, "Memory allocation failed for Vector");
    exit(EXIT_FAILURE);
  }

  switch (dtype) {
  case INT:
    V->values.int_data = (int *)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
      V->values.int_data[i] = 1;
    }
    break;
  case PREC:
    V->values.prec_data = (precision_t *)malloc(size * sizeof(precision_t));
    for (int i = 0; i < size; i++) {
      V->values.prec_data[i] = 1.0;
    }
    break;
  }

  V->size = size;
  V->dtype = dtype;

  return V;
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
