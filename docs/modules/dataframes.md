### dataframes.h / dataframes.c

The `dataframes` module provides a structure and a set of functions for handling tabular data, similar to dataframes in other high-level languages. It allows for the creation of tables with named columns, where each column can store a different **DataType**. The module includes utilities for manual data entry, CSV file loading, and basic data inspection.

--------------------------------------------------------------------------------

#### Column
A structure representing a single column in a `DataFrame`.
- `char *label`: The name or header of the column.
- `DataType dtype`: The type of data contained in this column.
- `Data data`: The union holding the actual array of values.

--------------------------------------------------------------------------------

#### DataFrame
A structure used to represent a 2-D table of data.
- `Column *columns`: An array of `Column` structures.
- `int num_rows`: The total number of rows in the table.
- `int num_columns`: The total number of columns in the table.

--------------------------------------------------------------------------------

## Functions to Initialise and View DataFrames 

#### init_df
`DataFrame *init_df(int nrows, int ncolumns)`
Allocates memory for a new `DataFrame` structure and its columns. It initializes the metadata, sets default values, and calculates the total memory allocated for the structure.

--------------------------------------------------------------------------------

#### load_csv
`DataFrame *load_csv(const char *filename, const char *sep)`
Reads a CSV file and reconstructs it as a `DataFrame` object. It automatically infers the data types of the columns and handles header parsing and row allocation.

**Note**: If a line in the csv file is empty (generally at the last), it will still be interpreted and added to the dataframes with values set to default (NULL etc).


--------------------------------------------------------------------------------

#### free_df
`void free_df(DataFrame *df)`
Deallocates all memory associated with the `DataFrame`, including column labels, internal data arrays, and the structures themselves. It also prints a message indicating the total amount of memory freed.

--------------------------------------------------------------------------------

#### set_column_df
`void set_column_df(DataFrame *df, int col_index, const char *label, DataType dtype)`
Configures a specific column by setting its label and data type, and allocates the necessary memory for that column's data based on the number of rows in the `DataFrame`.

--------------------------------------------------------------------------------

### Value Setters
Functions to set individual cell values within the `DataFrame`:
- `void set_int_value_df(DataFrame *df, int row_index, int col_index, int value)`: Sets an integer value at the specified row and column.
- `void set_prec_value_df(DataFrame *df, int row_index, int col_index, precision_t value)`: Sets a precision floating-point value.
- `void set_str_value_df(DataFrame *df, int row_index, int col_index, const char *value)`: Sets a string value (automatically duplicates the input string).
- `void set_value_df(DataFrame *df, int row_index, int col_index, const char *value)`: A generic setter that converts the string input to the column's required type (INT, PREC, or STRING) before assignment.


--------------------------------------------------------------------------------

### Inspection Functions
- `view_df(DataFrame *df)`: Prints the entire contents of the `DataFrame` to the console in a formatted table with calculated padding.
- `info_df(DataFrame *df)`: Displays summary information about the `DataFrame`, including the total number of entries and a list of columns with their respective data types.
- `head_df(DataFrame *df, int nrows)`: Prints the first `nrows` rows of the table.
- `tail_df(DataFrame *df, int nrows)`: Prints the last `nrows` rows of the table.

--------------------------------------------------------------------------------

#### infer_dtype
`DataType infer_dtype(const char *value)`
A utility function that examines a string value to determine if it should be treated as an `INT`, `PREC`, or `STRING`.
Used in load_csv