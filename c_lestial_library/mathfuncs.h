#ifndef MATHFUNCS_H
#define MATHFUNCS_H

#include "prec.h"

/* Functions related to polynomials */

void view_polynomial(int coeff_array_size, precision_t coeff[coeff_array_size],
                     char variable);
precision_t polynomial_value(precision_t x, int coeff_array_size,
                             precision_t coeff[coeff_array_size]);

#endif
