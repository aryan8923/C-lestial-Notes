# array.c

The `array.c` module contains functions for creating, manipulating, and performing statistical analysis on 1-D arrays, referred to as **Vectors**. It supports multiple data types including integers, precision floating-point numbers, and strings.

--------------------------------------------------------------------------------
## Vector
A structure used to represent a 1-D array. It contains metadata about the data type and size, alongside the actual data values.
- `DataType dtype`: The type of data stored (INT, PREC, or STRING).
- `int size`: The number of elements in the vector.
- `Data values`: A union holding the pointer to the actual data array.

--------------------------------------------------------------------------------

## percentile_method
An enumeration used to specify the mathematical approach for calculating percentiles.
##### Values
| Value | Description |
| ------ | ------ |
| INVERTED_CDF | Uses the inverted cumulative distribution function method. |
| LINEAR | Uses linear interpolation between data points. |

--------------------------------------------------------------------------------

## Functions to view array and vector elements

### view_vector
`void view_vector(Vector *A)`
Prints the contents of a vector to the console, including its size, data type, and all elements formatted as a list.

### view_array
`void view_array(int size, precision_t arr[])`
(not written yet)

Prints the contents of an array to the console. 

--------------------------------------------------------------------------------

## Functions to initialise array and vectors
#### zero_vector
`Vector *zero_vector(DataType dtype, int size)`
Allocates memory for a new vector of a specified size and initializes all elements to zero (or "0" for strings).

--------------------------------------------------------------------------------

#### ones_vector
`Vector *ones_vector(DataType dtype, int size)`
Allocates memory for a new vector and initializes all elements to one (or "1" for strings).

--------------------------------------------------------------------------------

#### free_vector
`void free_vector(Vector *V)`
Deallocates all memory associated with a vector, including its internal data array and any dynamically allocated strings.

--------------------------------------------------------------------------------

#### array_to_vector
Functions to convert standard C arrays into `Vector` objects. 
- `Vector *array_to_vector_prec(int size, precision_t arr[])`: Converts a `precision_t` array.
- `Vector *array_to_vector_int(int size, int arr[])`: Converts an `int` array.

**Tip**: Use the `LENGTH_ARR(arr)` macro to get the array's length if needed. 

--------------------------------------------------------------------------------

#### copy_vector
`Vector *copy_vector(Vector *V)`
Creates and returns a new `Vector` that is a deep copy of the provided vector.

--------------------------------------------------------------------------------

#### range_vector
`Vector *range_vector(precision_t start, precision_t stop, precision_t step)`
Generates a `PREC` type vector containing a sequence of numbers from `start` up to (but not including) `stop`, incremented by `step`.

--------------------------------------------------------------------------------

#### linspace_vector
`Vector *linspace_vector(precision_t start, precision_t stop, int N)`
Generates a `PREC` type vector of `N` equally spaced points between `start` and `stop` inclusive.

--------------------------------------------------------------------------------

#### slice_vector
`Vector *slice_vector(Vector *V, int *indices, int indices_size)`
Creates a new vector containing elements from `V` at the specific positions defined in the `indices` array.

--------------------------------------------------------------------------------
## Functions for manipulation of vectors and arrays
#### concat_vector
`Vector *concat_vector(Vector *first_vector, ...)`
Combines multiple vectors of the same `DataType` into a single new vector. The list of vectors must be terminated with `NULL`.

--------------------------------------------------------------------------------

#### append_vector
`void append_vector(Vector *first_vector, ...)`
Modifies the `first_vector` by appending additional vectors to it. This function reallocates memory for the original vector to accommodate the new data.

--------------------------------------------------------------------------------

## Vector I/O

Functions for saving and loading vectors to binary files:
- `void save_vector(const char *filename, Vector *vec)`: Saves the vector metadata and data to a file.
- `Vector *load_vector(const char *filename)`: Reads a vector from a file and reconstructs it in memory.

--------------------------------------------------------------------------------
## Mathematical Operations
#### Arithmetic Operations
- `Vector *scale_vector_int(Vector *V, int scalar)`: Multiplies every element in an integer vector by a scalar.
- `Vector *scale_vector_prec(Vector *V, precision_t scalar)`: Multiplies every element in a precision vector by a scalar.
- `Vector *elem_arith_op_vectors(Vector *A, Vector *B, arith_oper o)`: Performs element-wise operations (ADD, SUB, MUL, DIV, POW) between two vectors of equal size and type.
- `precision_t dot_vector_prec(Vector *A, Vector *B)`: Calculates the dot product of two precision vectors.

--------------------------------------------------------------------------------

#### map_vector
`Vector *map_vector(precision_t (*func)(precision_t), Vector *V)`
Applies a provided mathematical function to every element of a precision vector and returns a new vector with the results.

--------------------------------------------------------------------------------

## Functions for sorting , searching, counting and statistics
#### sort_vector
`void sort_vector(Vector *v, int ascending)`
Sorts the elements of a vector in place. The `ascending` parameter determines if the sort is ascending (non-zero) or descending (zero).

--------------------------------------------------------------------------------

#### Statistics
Functions for performing statistical analysis on `PREC` type vectors:
- `mean_vector`: Returns the average value.
- `sum_vector`: Returns the total sum of elements.
- `min_vector` / `max_vector`: Returns the minimum or maximum value.
- `ptp_vector`: Returns the "peak-to-peak" range (max - min).
- `median_vector`: Returns the median value.
- `std_vector`: Returns the standard deviation.
- `variance_vector(Vector *V, int ddof)`: Returns the variance, where `ddof` (Delta Degrees of Freedom) determines if it is a sample or population variance.
- `percentile_vector(Vector *V, precision_t q, percentile_method method)`: Returns the q-th percentile using the specified method.
- `weighted_average_vector(Vector *V, Vector *weights)`: Calculates the weighted average based on a secondary weights vector.

--------------------------------------------------------------------------------

## Functions for plotting

#### plot_vector_y

`void plot_vector_y(Vector *V, PlotAttr *gp_attr)`
Generates a plot of the vector values using Gnuplot. The values are plotted on the Y-axis against their index on the X-axis, using specified plot attributes.

--------------------------------------------------------------------------------