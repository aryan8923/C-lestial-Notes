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
