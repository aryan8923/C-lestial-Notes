#include "c_lestial_library/array/array.h"
#include "c_lestial_library/prec.h"
#include <stdio.h>

int main() {
  Vector *A;
  precision_t arr[] = {1.0, 2.0, 3.0, 4.0};

  A = array_to_vector_prec(4, arr);

  printf("\nA : ");
  view_vector(A);

  printf("\nmean A : %lf", mean_vector(A));

  printf("\nsum A : %lf", sum_vector(A));
  printf("\nmin A : %lf", min_vector(A));
  printf("\nmax A : %lf\n", max_vector(A));
  return 0;
}
