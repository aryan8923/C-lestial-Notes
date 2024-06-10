/* This file is a collection of functions to view or evaluate mathematical
 * functions like Polynomials, Bessel Functions etc */

#include "prec.h"
#include <math.h>
#include <stdio.h>

/* Functions related to polynomials */

void view_polynomial(int coeff_array_size, precision_t coeff[coeff_array_size],
                     char variable) {
  /// Prints out the polynomial

  printf("\n ");
  for (int i = 0; i < coeff_array_size - 1; i++)
    printf("%f%c^%d+ ", coeff[i], variable, i);
  printf("%f%c^%d", coeff[coeff_array_size - 1], variable,
         coeff_array_size - 1);
  printf("\n");
  return;
}

precision_t polynomial_value(precision_t x, int coeff_array_size,
                             precision_t coeff[coeff_array_size]) {
  /// Returns the value of the polynomial, coeffecients given by the coeff array
  /// (index n corresponds to c_n coefficient )
  precision_t p = 0.0;
  for (int i = 0; i < coeff_array_size; i++)
    p += (coeff[i] * pow(x, i));

  return p;
}
