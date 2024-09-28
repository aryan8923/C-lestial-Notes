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

typedef enum {
  INVERTED_CDF,
  LINEAR,
} percentile_method;

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

void free_vector(Vector *V) {
  if (V == NULL) {
    return;
  }

  switch (V->dtype) {
  case INT:
    free(V->values.int_data);
    break;
  case PREC:
    free(V->values.prec_data);
    break;
  case STRING:
    if (V->values.string_data != NULL) {
      for (int i = 0; i < V->size; i++) {
        free(V->values.string_data[i]);
      }
      free(V->values.string_data);
    }
    break;
  default:
    break;
  }

  free(V);
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
Vector *array_to_vector_int(int size, int arr[]) {
  Vector *V = zero_vector(INT, size);
  V->dtype = INT;
  V->size = size;
  for (int i = 0; i < size; i++) {
    V->values.int_data[i] = arr[i];
  }

  return V;
}

Vector *copy_vector(Vector *V) {
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

Vector *linspace_vector(precision_t start, precision_t stop, int N) {
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

/* Functions for manipulation of vectors and arrays */

Vector *concat_vector(Vector *first_vector, ...) {
  va_list args;
  va_start(args, first_vector);

  // Initialize
  Vector *current_vector = first_vector;
  DataType dtype = current_vector->dtype;
  int total_size = 0;

  // Calculate total size and check dtype
  Vector *temp_vector;
  while (current_vector != NULL) {
    if (current_vector->dtype != dtype) {
      fprintf(stderr, "Error: All vectors must have the same DataType\n");
      exit(EXIT_FAILURE);
    }
    total_size += current_vector->size;
    temp_vector = va_arg(args, Vector *);
    current_vector = temp_vector;
  }
  va_end(args);

  // Create zero vector of total size
  Vector *result = zero_vector(dtype, total_size);
  int offset = 0;

  // Concatenate all vectors into result
  current_vector = first_vector;
  while (current_vector != NULL) {
    switch (dtype) {
    case INT:
      memcpy(result->values.int_data + offset, current_vector->values.int_data,
             current_vector->size * sizeof(int));
      break;
    case PREC:
      memcpy(result->values.prec_data + offset,
             current_vector->values.prec_data,
             current_vector->size * sizeof(precision_t));
      break;
    case STRING:
      for (int i = 0; i < current_vector->size; i++) {
        result->values.string_data[offset + i] =
            strdup(current_vector->values.string_data[i]);
      }
      break;
    }
    offset += current_vector->size;
    temp_vector = va_arg(args, Vector *);
    current_vector = temp_vector;
  }

  va_end(args);

  return result;
}
void append_vector(Vector *first_vector, ...) {
  va_list args;
  va_start(args, first_vector);

  // Initialize
  Vector *current_vector = first_vector;
  DataType dtype = current_vector->dtype;
  int total_size = current_vector->size;

  // Calculate total size of appended vectors
  Vector *temp_vector;
  while ((temp_vector = va_arg(args, Vector *)) != NULL) {
    if (temp_vector->dtype != dtype) {
      fprintf(stderr, "Error: All vectors must have the same DataType\n");
      exit(EXIT_FAILURE);
    }
    total_size += temp_vector->size;
  }
  va_end(args);

  // Allocate memory for new combined data
  Data new_data;
  switch (dtype) {
  case INT:
    new_data.int_data = (int *)malloc(total_size * sizeof(int));
    break;
  case PREC:
    new_data.prec_data =
        (precision_t *)malloc(total_size * sizeof(precision_t));
    break;
  case STRING:
    new_data.string_data = (char **)malloc(total_size * sizeof(char *));
    break;
  }
  if (((new_data.int_data == NULL) && (dtype == INT)) ||
      ((new_data.prec_data == NULL) && (dtype == PREC)) ||
      ((new_data.string_data == NULL) && (dtype == STRING))) {
    fprintf(stderr, "Error: Memory allocation failed\n");
    exit(EXIT_FAILURE);
  }

  // Copy the values from the first vector
  switch (dtype) {
  case INT:
    memcpy(new_data.int_data, first_vector->values.int_data,
           first_vector->size * sizeof(int));
    break;
  case PREC:
    memcpy(new_data.prec_data, first_vector->values.prec_data,
           first_vector->size * sizeof(precision_t));
    break;
  case STRING:
    for (int i = 0; i < first_vector->size; i++) {
      new_data.string_data[i] = strdup(first_vector->values.string_data[i]);
    }
    break;
  }

  int offset = first_vector->size;

  // Append the values from the additional vectors
  va_start(args, first_vector);
  while ((temp_vector = va_arg(args, Vector *)) != NULL) {
    switch (dtype) {
    case INT:
      memcpy(new_data.int_data + offset, temp_vector->values.int_data,
             temp_vector->size * sizeof(int));
      break;
    case PREC:
      memcpy(new_data.prec_data + offset, temp_vector->values.prec_data,
             temp_vector->size * sizeof(precision_t));
      break;
    case STRING:
      for (int i = 0; i < temp_vector->size; i++) {
        new_data.string_data[offset + i] =
            strdup(temp_vector->values.string_data[i]);
      }
      break;
    }
    offset += temp_vector->size;
  }
  va_end(args);

  // Free the old values and update the first vector
  switch (dtype) {
  case INT:
    free(first_vector->values.int_data);
    first_vector->values.int_data = new_data.int_data;
    break;
  case PREC:
    free(first_vector->values.prec_data);
    first_vector->values.prec_data = new_data.prec_data;
    break;
  case STRING:
    for (int i = 0; i < first_vector->size; i++) {
      free(first_vector->values.string_data[i]);
    }
    free(first_vector->values.string_data);
    first_vector->values.string_data = new_data.string_data;
    break;
  }
  first_vector->size = total_size;
}

/* Function to load and save a vector from files */

void save_vector(const char *filename, Vector *vec) {
  FILE *file = fopen(filename, "wb");
  if (file == NULL) {
    fprintf(stderr, "Error opening file for writing\n");
    exit(EXIT_FAILURE);
  }

  // Write metadata
  fwrite(&(vec->dtype), sizeof(DataType), 1, file);
  fwrite(&(vec->size), sizeof(int), 1, file);

  // Write data based on dtype
  switch (vec->dtype) {
  case INT:
    fwrite(vec->values.int_data, sizeof(int), vec->size, file);
    break;
  case PREC:
    fwrite(vec->values.prec_data, sizeof(precision_t), vec->size, file);
    break;
  case STRING:
    for (int i = 0; i < vec->size; i++) {
      size_t len = strlen(vec->values.string_data[i]) + 1;
      fwrite(&len, sizeof(size_t), 1, file);
      fwrite(vec->values.string_data[i], sizeof(char), len, file);
    }
    break;
  }

  fclose(file);
}

Vector *load_vector(const char *filename) {
  FILE *file = fopen(filename, "rb");
  if (file == NULL) {
    fprintf(stderr, "Error opening file for reading\n");
    exit(EXIT_FAILURE);
  }

  Vector *vec = (Vector *)malloc(sizeof(Vector));
  if (vec == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    fclose(file);
    exit(EXIT_FAILURE);
  }

  // Read metadata
  fread(&(vec->dtype), sizeof(DataType), 1, file);
  fread(&(vec->size), sizeof(int), 1, file);

  // Allocate memory for data
  switch (vec->dtype) {
  case INT:
    vec->values.int_data = (int *)malloc(vec->size * sizeof(int));
    if (vec->values.int_data == NULL) {
      fprintf(stderr, "Memory allocation failed\n");
      free(vec);
      fclose(file);
      exit(EXIT_FAILURE);
    }
    fread(vec->values.int_data, sizeof(int), vec->size, file);
    break;
  case PREC:
    vec->values.prec_data =
        (precision_t *)malloc(vec->size * sizeof(precision_t));
    if (vec->values.prec_data == NULL) {
      fprintf(stderr, "Memory allocation failed\n");
      free(vec);
      fclose(file);
      exit(EXIT_FAILURE);
    }
    fread(vec->values.prec_data, sizeof(precision_t), vec->size, file);
    break;
  case STRING:
    vec->values.string_data = (char **)malloc(vec->size * sizeof(char *));
    if (vec->values.string_data == NULL) {
      fprintf(stderr, "Memory allocation failed\n");
      free(vec);
      fclose(file);
      exit(EXIT_FAILURE);
    }
    for (int i = 0; i < vec->size; i++) {
      size_t len;
      fread(&len, sizeof(size_t), 1, file);
      vec->values.string_data[i] = (char *)malloc(len * sizeof(char));
      if (vec->values.string_data[i] == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(vec);
        fclose(file);
        exit(EXIT_FAILURE);
      }
      fread(vec->values.string_data[i], sizeof(char), len, file);
    }
    break;
  }

  fclose(file);
  return vec;
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
  Vector *V_copy = copy_vector(V);

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

/* functions for sorting , searching and counting */

// Comparison function for integers (ascending)
int compare_int(const void *a, const void *b) {
  return (*(int *)a - *(int *)b);
}

// Comparison function for integers (descending)
int compare_int_desc(const void *a, const void *b) {
  return (*(int *)b - *(int *)a);
}

// Comparison function for precision_t (ascending)
int compare_precision(const void *a, const void *b) {
  return (*(precision_t *)a > *(precision_t *)b) -
         (*(precision_t *)a < *(precision_t *)b);
}

// Comparison function for precision_t (descending)
int compare_precision_desc(const void *a, const void *b) {
  return (*(precision_t *)b > *(precision_t *)a) -
         (*(precision_t *)b < *(precision_t *)a);
}

// Comparison function for strings (ascending)
int compare_string(const void *a, const void *b) {
  return strcmp(*(const char **)a, *(const char **)b);
}

// Comparison function for strings (descending)
int compare_string_desc(const void *a, const void *b) {
  return strcmp(*(const char **)b, *(const char **)a);
}

void sort_vector(Vector *v, int ascending) {
  int (*compare_func)(const void *, const void *) = NULL;

  // Select the appropriate comparison function
  switch (v->dtype) {
  case INT:
    compare_func = ascending ? compare_int : compare_int_desc;
    qsort(v->values.int_data, v->size, sizeof(int), compare_func);
    break;
  case PREC:
    compare_func = ascending ? compare_precision : compare_precision_desc;
    qsort(v->values.prec_data, v->size, sizeof(precision_t), compare_func);
    break;
  case STRING:
    compare_func = ascending ? compare_string : compare_string_desc;
    qsort(v->values.string_data, v->size, sizeof(char *), compare_func);
    break;
  default:
    printf("Unsupported data type for sorting.\n");
    break;
  }
}

/* functions for statistics for arrays*/

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

precision_t ptp_vector(Vector *V) { return max_vector(V) - min_vector(V); }

precision_t percentile_vector(Vector *V, precision_t q,
                              percentile_method method) {
  // Check if Percentile q is in the range [0, 100]
  if (q < 0 || q > 100) {
    fprintf(stderr, "ValueError: Percentiles must be in the range [0, 100]\n");
    exit(EXIT_FAILURE);
  }

  precision_t rank, frac, percentile = 0;
  int rank_rounded;

  // Create a copy of the vector and sort it
  Vector *V_copy = copy_vector(V);
  sort_vector(V_copy, 1);

  switch (method) {
  case INVERTED_CDF:
    rank = (q * V_copy->size) / 100.0;
    rank_rounded = (int)ceil(rank);
    if (rank_rounded <= 0) {
      percentile = V_copy->values.prec_data[0];
    } else if (rank_rounded >= V_copy->size) {
      percentile = V_copy->values.prec_data[V_copy->size - 1];
    } else {
      percentile = V_copy->values.prec_data[rank_rounded - 1];
    }
    break;

  case LINEAR:
    rank = (q * (V_copy->size - 1)) / 100.0;
    rank_rounded = (int)floor(rank);
    frac = rank - rank_rounded;
    percentile = V_copy->values.prec_data[rank_rounded] +
                 frac * (V_copy->values.prec_data[rank_rounded + 1] -
                         V_copy->values.prec_data[rank_rounded]);
    break;

  default:
    fprintf(stderr, "Unsupported percentile method.\n");
    free_vector(V_copy);
    exit(EXIT_FAILURE);
  }

  free_vector(V_copy);
  return percentile;
}

precision_t median_vector(Vector *V) {
  Vector *V_copy = copy_vector(V);

  sort_vector(V_copy, 1);

  precision_t median;

  if (V_copy->size % 2 == 1) {
    int middle_index = V_copy->size / 2;
    median = V_copy->values.prec_data[middle_index];
  } else {
    int middle_index1 = (V_copy->size / 2) - 1;
    int middle_index2 = V_copy->size / 2;
    median = (V_copy->values.prec_data[middle_index1] +
              V_copy->values.prec_data[middle_index2]) /
             2.0;
  }

  free_vector(V_copy);

  return median;
}

precision_t weighted_average_vector(Vector *V, Vector *weights) {
  if (V == NULL || weights == NULL || V->size == 0 || weights->size == 0) {
    fprintf(stderr, "Error: Vector or weights are NULL or empty.\n");
    return 0;
  }

  if (V->size != weights->size) {
    fprintf(stderr, "Error: Vector and weights must have the same size.\n");
    return 0;
  }

  precision_t sum = 0;
  precision_t weight_sum = 0;

  for (int i = 0; i < V->size; i++) {
    sum += V->values.prec_data[i] * weights->values.prec_data[i];
    weight_sum += weights->values.prec_data[i];
  }

  if (weight_sum == 0) {
    fprintf(stderr, "Error: Sum of weights is zero.\n");
    return 0;
  }

  return sum / weight_sum;
}

precision_t std_vector(Vector *V) {
  if (V->size <= 1) {
    return 0.0; // Standard deviation is not defined for a vector of size 1
  }

  precision_t mean = mean_vector(V);
  precision_t sum_squared_diff = 0.0;
  precision_t diff;

  for (int i = 0; i < V->size; i++) {
    diff = V->values.prec_data[i] - mean;
    sum_squared_diff += diff * diff;
  }

  return sqrt(sum_squared_diff / (V->size));
}

precision_t variance_vector(Vector *V, int ddof) {
  precision_t mean = mean_vector(V);
  precision_t variance_sum = 0.0;
  precision_t diff;
  for (int i = 0; i < V->size; i++) {
    diff = V->values.prec_data[i] - mean;
    variance_sum += diff * diff;
  }

  if (ddof) {
    return variance_sum / (V->size - 1); // Sample variance
  } else {
    return variance_sum / V->size; // Population variance
  }
}
