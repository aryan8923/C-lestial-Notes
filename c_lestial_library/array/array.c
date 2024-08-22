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

Vector *copy_Vector(Vector *V) {
  Vector *V_copy = zero_vector(V->dtype, V->size);

  switch (V->dtype) {
  case INT:
    for (int i = 0; i < V->size; i++) {
      V_copy->values.int_data[i] = V->values.int_data[i];
    }
    break;
  case PREC:
    for (int i = 0; i < V->size; i++) {
      V_copy->values.prec_data[i] = V->values.prec_data[i];
    }
    break;
  case STRING:
    for (int i = 0; i < V->size; i++) {
      V_copy->values.prec_data[i] = V->values.prec_data[i];
    }
    break;
  }

  return V_copy;
}

Vector *range_vector(precision_t start, precision_t stop, precision_t step) {

  // TODO : fix this function. The end point in the array is not matching with
  //  the one in Python

  int vec_size = (int)((stop - start) / step);
  if (vec_size <= 0) {
    fprintf(stderr,
            "Error: Invalid start/stop/step input in function range_vector.\n");
    exit(EXIT_FAILURE);
  }
  Vector *V = zero_vector(PREC, vec_size);

  for (int i = 0; i < vec_size; i++) {
    V->values.prec_data[i] = start + ((precision_t)i * step);
  }

  return V;
}

Vector *linspace_vector(precision_t start, precision_t stop, precision_t N) {
  Vector *V = zero_vector(PREC, N);

  precision_t step = ((stop - start) / (precision_t)N);

  for (int i = 0; i < N; i++) {
    V->values.prec_data[i] = start + ((precision_t)i * step);
  }

  return V;
}

Vector *slice_vector(Vector *V, int *indices, int indices_size) {
  // Create a new vector with the same dtype and the size of the indices array
  Vector *new_vector = zero_vector(V->dtype, indices_size);

  // Switch based on the dtype of the vector
  switch (V->dtype) {
  case INT:
    for (int i = 0; i < indices_size; i++) {
      if (indices[i] >= 0 && indices[i] < V->size) {
        new_vector->values.int_data[i] = V->values.int_data[indices[i]];
      } else {
        fprintf(stderr, "Index out of bounds: %d\n", indices[i]);
        exit(EXIT_FAILURE);
      }
    }
    break;

  case PREC:
    for (int i = 0; i < indices_size; i++) {
      if (indices[i] >= 0 && indices[i] < V->size) {
        new_vector->values.prec_data[i] = V->values.prec_data[indices[i]];
      } else {
        fprintf(stderr, "Index out of bounds: %d\n", indices[i]);
        exit(EXIT_FAILURE);
      }
    }
    break;

  case STRING:
    for (int i = 0; i < indices_size; i++) {
      if (indices[i] >= 0 && indices[i] < V->size) {
        new_vector->values.string_data[i] = V->values.string_data[indices[i]];
      } else {
        fprintf(stderr, "Index out of bounds: %d\n", indices[i]);
        exit(EXIT_FAILURE);
      }
    }
    break;

  default:
    fprintf(stderr, "Unsupported data type\n");
    exit(EXIT_FAILURE);
  }

  return new_vector;
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

Vector *map_vector(precision_t (*func)(precision_t), Vector *V) {
  Vector *V_copy = copy_Vector(V);

  for (int i = 0; i < V->size; i++) {
    V_copy->values.prec_data[i] = (*func)(V->values.prec_data[i]);
  }
  return V_copy;
}

precision_t dot_vector_prec(Vector *A, Vector *B) {
  precision_t sum = 0.0;

  // test whether the size of the vector matches
  if (A->size != B->size) {
    fprintf(stderr,
            "Size Mismatch Error: Vectors of unequal size found in function "
            "dot_vector\n");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < A->size; i++) {
    sum = sum + (A->values.prec_data[i] * B->values.prec_data[i]);
  }

  return sum;
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
