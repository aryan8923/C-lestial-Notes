#include "c_lestial_library/array/array.h"
#include "c_lestial_library/prec.h"

int main() {
  Vector *A;

  A = ones_vector(INT, 4);

  view_vector(A);

  return 0;
}
