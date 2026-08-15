# `defs.h`


`defs.h` contains common definitions and types for the C-lestial library. Other library modules can include this file when they need these definitions.

---

## `precision_t`
This handles whether to use double or single float precision everywhere. By default, precision_t is set to double. 
One can edit the line #define PRECISION double to #define PRECISION float to change it to float. 

---

## `Data`

A union that stores a pointer to 1-D array of a type (int,precision_t,string). Used in arrays. 

int stored in *int_data;
precision_t stored in *prec_data;
char stored in **string_data;

Only one datatype of the union represents valid data at a time.
This helps in making more complex types like Vectors, helping us to store different datatypes under the same type "Vector". 

---

## `Data2d`

A union that stores a pointer to 2-D array of a type (int,precision_t). Used in matrices.

int stored in *int_data;
precision_t stored in *prec_data;

Only one datatype of the union represents valid data at a time.
This helps in making more complex types like Matrices, helping us to store different datatypes under the same type "Matrices". 

---

## `DataType`

This helps us to label the dtypes. INT, PREC, STRING corresponds to int, precision_t, string type respectively. 


---

## `arith_oper`

This helps us to label various arithmetic operations like add, subtract, multiply, divide and power as ADD, SUB, MUL, DIV, POW


### Values

| Value | Operation      |
| ----- | -------------- |
| `ADD` | Addition       |
| `SUB` | Subtraction    |
| `MUL` | Multiplication |
| `DIV` | Division       |
| `POW` | Power          |

---


