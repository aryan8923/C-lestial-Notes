#ifndef PRECISION_H
#define PRECISION_H

#ifndef PRECISION
#define PRECISION double
#endif

typedef PRECISION precision_t;

typedef union { // stores the value of Data in a column depending on the
                // specified data datatype. Union because the column can only be
                // of one of the following type
  int *int_data;
  precision_t *prec_data;
  char **string_data;
} Data;

typedef enum { INT, PREC, STRING } DataType;

typedef enum { ADD, SUBTR, MULT, DIV, POW } arith_oper;

#endif // PRECISION_H
