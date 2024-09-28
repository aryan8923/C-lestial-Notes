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

/* This file is a collection of functions to view or evaluate mathematical
 * functions like Polynomials, Bessel Functions etc */

#include "array/array.h"
#include "prec.h"
#include <math.h>
#include <stdio.h>

/* Functions related to polynomials */

void view_polynomial(Vector *coeff, char variable) {
  /// Prints out the polynomial

  printf("\n ");
  for (int i = 0; i < coeff->size - 1; i++)
    printf("%f%c^%d+ ", coeff->values.prec_data[i], variable, i);
  printf("%f%c^%d", coeff->values.prec_data[coeff->size - 1], variable,
         coeff->size - 1);
  printf("\n");
  return;
}

precision_t eval_polynomial(precision_t x, Vector *coeff) {
  precision_t p = coeff->values.prec_data[coeff->size];
  for (int i = coeff->size - 1; i >= 0; i--) {
    p = (p * x) + coeff->values.prec_data[i];
  }
  return p;
}

precision_t eval_polynomial_dx(precision_t x, Vector *coeff) {
  precision_t dp = 0.0;
  precision_t p = coeff->values.prec_data[coeff->size];
  for (int i = coeff->size - 1; i >= 0; i--) {
    dp = (dp * x) + p;
    p = (p * x) + coeff->values.prec_data[i];
  }

  return dp;
}
