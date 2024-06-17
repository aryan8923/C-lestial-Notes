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
#include <math.h>
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
    fprintf(stderr, "Memory allocation failed for Vector\n");
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
  case STRING:
    V->values.string_data = (char **)malloc(size * sizeof(char *));
    for (int i = 0; i < size; i++) {
      V->values.string_data[i] = "0";
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
    fprintf(stderr, "Memory allocation failed for Vector\n");
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
  case STRING:
    V->values.string_data = (char **)malloc(size * sizeof(char **));
    for (int i = 0; i < size; i++) {
      V->values.string_data[i] = "1";
    }
  }

  V->size = size;
  V->dtype = dtype;

  return V;
}

Vector *array_to_vector_prec(int size, precision_t arr[]) {
  Vector *V = zero_vector(PREC, size);
  V->dtype = PREC;
  V->size = size;
  for (int i = 0; i < size; i++) {
    V->values.prec_data[i] = arr[i];
  }

  return V;
}

/* Functions for basic arithmetic of arrays */

Vector *scale_vector_int(Vector *V, int scalar) {
  Vector *A = zero_vector(INT, V->size);

  // make it so that it does not modify the original vector
  if (V->dtype == INT) {
    for (int i = 0; i < V->size; i++) {
      A->values.int_data[i] = scalar * V->values.int_data[i];
    }
  } else {
    fprintf(stderr, "Type Mismatch error when scaling the int type Vector\n");
    exit(EXIT_FAILURE);
  }

  return A;
}

Vector *scale_vector_prec(Vector *V, precision_t scalar) {
  Vector *A = zero_vector(PREC, V->size);

  // make it so that it does not modify the original vector
  if (V->dtype == PREC) {
    for (int i = 0; i < V->size; i++) {
      A->values.prec_data[i] = scalar * V->values.prec_data[i];
    }
  } else {
    fprintf(stderr, "Type Mismatch error when scaling the int type Vector\n");
    exit(EXIT_FAILURE);
  }

  return A;
}

Vector *elem_arith_op_vectors(Vector *A, Vector *B, arith_oper o) {
  Vector *C = zero_vector(A->dtype, A->size);

  if (A->size == B->size) {
    if (A->dtype == B->dtype) {
      switch (A->dtype) {
      case INT:
        switch (o) {
        case ADD:
          for (int i = 0; i < A->size; i++) {
            C->values.int_data[i] =
                A->values.int_data[i] + B->values.int_data[i];
          }
          break;
        case SUB:
          for (int i = 0; i < A->size; i++) {
            C->values.int_data[i] =
                A->values.int_data[i] - B->values.int_data[i];
          }
          break;
        case MUL:
          for (int i = 0; i < A->size; i++) {
            C->values.int_data[i] =
                A->values.int_data[i] * B->values.int_data[i];
          }
          break;
        case DIV:
          for (int i = 0; i < A->size; i++) {
            C->values.int_data[i] =
                A->values.int_data[i] / B->values.int_data[i];
          }
          break;
        case POW:
          for (int i = 0; i < A->size; i++) {
            C->values.int_data[i] =
                pow(A->values.int_data[i], B->values.int_data[i]);
          }
          break;
        }
        break;

      case PREC:
        switch (o) {
        case ADD:
          for (int i = 0; i < A->size; i++) {
            C->values.prec_data[i] =
                A->values.prec_data[i] + B->values.prec_data[i];
          }
          break;
        case SUB:
          for (int i = 0; i < A->size; i++) {
            C->values.prec_data[i] =
                A->values.prec_data[i] - B->values.prec_data[i];
          }
          break;
        case MUL:
          for (int i = 0; i < A->size; i++) {
            C->values.prec_data[i] =
                A->values.prec_data[i] * B->values.prec_data[i];
          }
          break;
        case DIV:
          for (int i = 0; i < A->size; i++) {
            C->values.prec_data[i] =
                A->values.prec_data[i] / B->values.prec_data[i];
          }
          break;
        case POW:
          for (int i = 0; i < A->size; i++) {
            C->values.prec_data[i] =
                pow(A->values.prec_data[i], B->values.prec_data[i]);
          }
          break;
        }
        break;

      case STRING:
        fprintf(stderr, "Type error: function elem_arith_op_vectors is not "
                        "compatible with string type vector as of now");
      }
    } else {
      fprintf(stderr, "Type mismatch error for the arithmetic operation of the "
                      "two vectors\n");
    }
  } else {
    fprintf(stderr, "Size mismatch error for the arithmetic operation of the "
                    "two vectors\n");
  }
  return C;
}

/* functions for basic statistics for arrays*/

precision_t mean_vector(Vector *V) {
  int count;
  precision_t sum = 0.0;

  for (count = 0; count < V->size; count++)
    sum += V->values.prec_data[count];

  return sum / (precision_t)V->size;
}

precision_t sum_vector(Vector *V) {
  precision_t sum = 0.0;

  for (int count = 0; count < V->size; count++) {
    sum += V->values.prec_data[count];
  }

  return sum;
}

precision_t min_vector(Vector *V) {
  precision_t min = V->values.prec_data[0];

  for (int i = 1; i < V->size; i++) {
    if (min > V->values.prec_data[i]) {
      min = V->values.prec_data[i];
    }
  }
  return min;
}

precision_t max_vector(Vector *V) {
  precision_t max = V->values.prec_data[0];

  for (int i = 1; i < V->size; i++) {
    if (max < V->values.prec_data[i]) {
      max = V->values.prec_data[i];
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
