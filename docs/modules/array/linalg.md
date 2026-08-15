### linalg.h / linalg.c

The `linalg` module provides structures and functions for linear algebra operations, specifically focused on 2-D **Matrices**. It includes tools for matrix initialization, basic arithmetic operations (like matrix multiplication), and advanced solvers for linear systems using Gaussian elimination and LU decomposition.

---

#### Matrix

A structure used to represent a 2-D array. It stores dimensions and data type metadata alongside a pointer to the matrix values.

- `DataType dtype`: The type of data stored (INT or PREC).
- `int nrows`: The number of rows in the matrix.
- `int ncols`: The number of columns in the matrix.
- `Data2d values`: A union holding pointers to the 2-D data array (e.g., `int **` or `precision_t **`).

---

#### view_matrix

`void view_matrix(Matrix *mat)` Prints the matrix to the console in a formatted grid. It identifies the data type and dimensions before listing the elements.

---

## Functions to initialise matrices

#### init_matrix

`Matrix *init_matrix(DataType dtype, int nrows, int ncols)` Allocates the memory for a `Matrix` structure and its underlying 2-D data pointers based on the specified data type and dimensions.

---

#### free_matrix

`void free_matrix(Matrix *mat)` Properly deallocates the memory for the matrix structure, including individual row pointers and the main data pointer.

---

#### zeros_matrix

`Matrix *zeros_matrix(DataType dtype, int nrows, int ncols)` Creates a new matrix of the specified type and size, initializing all elements to zero.

---

#### identity_matrix

`Matrix *identity_matrix(DataType dtype, int nrows)` Creates a square identity matrix where diagonal elements are 1 and all other elements are 0.

**issue** with this function is that it initialises the matrix at some address and returns that address that it creates. So if you are using it inside a function, where you are taking an input matrix, if you try to convert that matrix to identity, this function will instead change the input pointer's address to this new one and not to the older one. So it does not make change to already existing matrix. It returns a newly initialsed one.

---

## Matrix Conversion and Utilities

- `Matrix *Array2d_to_Matrix_prec(int nrows, int ncols, precision_t arr[nrows][ncols])`: Converts a standard 2-D precision array into a `Matrix` structure.
- `Matrix *copy_Matrix(Matrix *M)`: Creates a new `Matrix` that is a copy of the original.
- `Vector *matrix_to_vector(Matrix *M, int index, int axis)`: Extracts a single row or column from a matrix and returns it as a `Vector`. `axis=0` selects a column, while `axis=1` selects a row.
- `Vector *flatten_matrix(Matrix *M)`: Flattens a 2-D matrix into a 1-D `Vector`.

---

## Basic Arithmetic Operations

- `Matrix *scale_matrix_int(Matrix *M, int scalar)`: Returns a new matrix where every element is multiplied by an integer scalar.
- `Matrix *scale_matrix_prec(Matrix *M, precision_t scalar)`: Returns a new matrix where every element is multiplied by a precision scalar.
- `Matrix *matmul(Matrix *A, Matrix *B)`: Performs standard matrix multiplication $C = A \times B$.
- `precision_t trace_matrix(Matrix *A)`: Calculates the sum of the diagonal elements for square matrices.

---

## Linear System Solvers and Matrix operations

### Solvers

- `Vector *lin_system_gauss_elim(Matrix *A, Vector *B)`: Solves the linear equation $AX = B$ using Gaussian elimination with pivoting to improve numerical stability.
- `Vector *lin_system_LU_decomp(Matrix *A, Vector *B)`: Solves $AX = B$ using LU decomposition combined with forward and backward substitution.

### Matrix Operations
- `void LU_decomp(Matrix *A, Matrix *Lower, Matrix *Upper)`: Decomposes a square matrix into a product of a lower triangular matrix $L$ and an upper triangular matrix $U$. Since this required two outputs, I have added L and U matrix in the input variables. One must initialise the L and U before this function and then input them in the function. 
- `precision_t determinant(Matrix *M)`: Calculates the determinant of a square matrix by first performing LU decomposition and then multiplying the diagonal elements of the \(U\) matrix.
- `Matrix *inverse_matrix(Matrix *A)`: Computes the inverse of a matrix using LU decomposition and substitution.

