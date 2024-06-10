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

#ifndef DATAFRAMES_H
#define DATAFRAMES_H

#include "prec.h"

// Definitions related to data frames
typedef enum { INT, PREC, STRING } DataType;

typedef union { // stores the value of Data in a column depending on the
                // specified data datatype. Union because the column can only be
                // of one of the following type
  int *int_data;
  precision_t *prec_data;
  char **string_data;
} Data;

typedef struct { // stores data in a "Column" struct that is suitable to be
                 // stored in DataFrame
  char *label;
  DataType dtype; // The datatype of this particular Column is given by this
                  // field
  Data data;      // This is where the data is to be stored in an array
} Column;

typedef struct {
  Column *columns; // Array of columns
  int num_rows;
  int num_columns;
} DataFrame;

// basic function related to initialising DataFrames and freeing memory

DataFrame *init_df(int nrows, int ncolumns);
void set_column_df(DataFrame *df, int col_index, const char *label,
                   DataType dtype);

void set_int_value_df(DataFrame *df, int row_index, int col_index, int value);
void set_prec_value_df(DataFrame *df, int row_index, int col_index,
                       precision_t value);
void set_str_value_df(DataFrame *df, int row_index, int col_index,
                      const char *value);

void free_df(DataFrame *df);
void view_df(DataFrame *df);
DataFrame *load_csv(const char *filename, const char *sep);

#endif
#define DATAFRAMES_H
