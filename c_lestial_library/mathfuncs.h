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

#ifndef MATHFUNCS_H
#define MATHFUNCS_H

#include "prec.h"

/* Functions related to polynomials */

void view_polynomial(int coeff_array_size, precision_t coeff[coeff_array_size],
                     char variable);
precision_t polynomial_value(precision_t x, int coeff_array_size,
                             precision_t coeff[coeff_array_size]);

#endif
