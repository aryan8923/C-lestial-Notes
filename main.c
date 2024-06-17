#include "c_lestial_library/array/linalg.h"
#include "c_lestial_library/prec.h"
#include <stdio.h>

int main() {

  // Example usage
  Matrix *mat_int = zeros_matrix(INT, 3, 5);
  Matrix *mat_prec = zeros_matrix(PREC, 3, 4);

  // Print matrices
  view_matrix(mat_int);

  view_matrix(mat_prec);

  // Free matrices
  free_matrix(mat_int);
  free_matrix(mat_prec);
  return 0;
}
