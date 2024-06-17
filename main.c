#include "c_lestial_library/array/array.h"
#include "c_lestial_library/prec.h"
#include <stdio.h>

int main() {
  Vector *B;
  Vector *A;
  Vector *sum, *diff, *prod, *div, *power;

  A = scale_vector_prec(ones_vector(PREC, 4), 2.0);
  B = scale_vector_prec(ones_vector(PREC, 4), 3.0);

  printf("\nA : ");
  view_vector(A);
  printf("\nB : ");
  view_vector(B);

  sum = elem_arith_op_vectors(B, A, ADD);
  printf("\n\nA + B = ");
  view_vector(sum);
  diff = elem_arith_op_vectors(A, B, SUB);
  printf("\n\nA - B = ");
  view_vector(diff);
  prod = elem_arith_op_vectors(A, B, MUL);
  printf("\n\nA * B = ");
  view_vector(prod);
  div = elem_arith_op_vectors(A, B, DIV);
  printf("\n\nA / B = ");
  view_vector(div);
  power = elem_arith_op_vectors(A, B, POW);
  printf("\n\nA ^ B = ");
  view_vector(power);

  return 0;
}
