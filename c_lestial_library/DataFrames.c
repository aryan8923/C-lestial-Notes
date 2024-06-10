#include "prec.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

DataFrame *init_df(int nrows, int ncolumns) {
  DataFrame *df = (DataFrame *)malloc(sizeof(DataFrame));

  if (df == NULL) {
    fprintf(stderr, "Memory allocation failed for DataFrame");
    exit(EXIT_FAILURE);
  }

  // Allocate memory for columns in DataFrame
  df->columns = (Column *)malloc(ncolumns * sizeof(Column));
  if (df->columns == NULL) {
    fprintf(stderr, "Memory allocation failed for columns");
    exit(EXIT_FAILURE);
  }

  // initialising the columns

  for (int i = 0; i < ncolumns; i++) {
    df->columns[i].label = NULL;
    df->columns[i].data.int_data = NULL;
    df->columns[i].dtype = INT;
  }

  // Setting the metadata of DataFrame
  df->num_columns = ncolumns;
  df->num_rows = nrows;

  size_t dataframe_size = sizeof(DataFrame) + (ncolumns * sizeof(Column));
  for (int i = 0; i < ncolumns; i++) {
    dataframe_size += sizeof(df->columns[i].label);
    dataframe_size += sizeof(df->columns[i].dtype);
    dataframe_size += sizeof(df->columns[i].data);
  }

  printf("Initialsed DataFrame (%zu bytes (~%.4f MB))\n", dataframe_size,
         dataframe_size / (1024.0 * 1024.0));

  return df;
}
// Function to set column name and type
void set_column_df(DataFrame *df, int col_index, const char *label,
                   DataType dtype) {
  df->columns[col_index].label = strdup(label);
  df->columns[col_index].dtype = dtype;

  // Allocate memory for column data based on the type
  switch (dtype) {
  case INT:
    df->columns[col_index].data.int_data =
        (int *)malloc(df->num_rows * sizeof(int));
    break;
  case PREC:
    df->columns[col_index].data.prec_data =
        (double *)malloc(df->num_rows * sizeof(double));
    break;
  case STRING:
    df->columns[col_index].data.string_data =
        (char **)malloc(df->num_rows * sizeof(char *));
    for (int i = 0; i < df->num_rows; i++) {
      df->columns[col_index].data.string_data[i] = NULL;
    }
    break;
  }
}

void set_int_value_df(DataFrame *df, int row_index, int col_index, int value) {
  if (df->columns[col_index].dtype == INT) {
    df->columns[col_index].data.int_data[row_index] = value;
  } else {
    fprintf(stderr, "Type Misatch error when setting the int value\n");
  }
}

void set_prec_value_df(DataFrame *df, int row_index, int col_index,
                       precision_t value) {
  if (df->columns[col_index].dtype == PREC) {
    df->columns[col_index].data.prec_data[row_index] = value;
  } else {
    fprintf(stderr, "Type Mismatch error when setting the precision_t value\n");
  }
}

void set_str_value_df(DataFrame *df, int row_index, int col_index,
                      const char *value) {
  if (df->columns[col_index].dtype == STRING) {
    df->columns[col_index].data.string_data[row_index] = strdup(value);
  } else {
    fprintf(stderr, "Type Mismatch error when setting the string value\n");
  }
}

void free_df(DataFrame *df) {
  for (int i = 0; i < df->num_columns; i++) {
    free(df->columns[i].label);
    switch (df->columns[i].dtype) {
    case INT:
      free(df->columns[i].data.int_data);
      break;
    case PREC:
      free(df->columns[i].data.prec_data);
      break;
    case STRING:
      for (int j = 0; j < df->num_rows; j++) {
        free(df->columns[i].data.string_data[j]);
      }
      free(df->columns[i].data.string_data);
      break;
    }
  }
  free(df->columns);
  free(df);
}

void view_df(DataFrame *df) {
  // Print column headers
  for (int i = 0; i < df->num_columns; i++) {
    printf("%-10s", df->columns[i].label);
  }
  printf("\n");

  // Print rows
  for (int row = 0; row < df->num_rows; row++) {
    for (int col = 0; col < df->num_columns; col++) {
      switch (df->columns[col].dtype) {
      case INT:
        printf("%-10d", df->columns[col].data.int_data[row]);
        break;
      case PREC:
        printf("%-10.2f", df->columns[col].data.prec_data[row]);
        break;
      case STRING:
        if (df->columns[col].data.string_data[row]) {
          printf("%-10s", df->columns[col].data.string_data[row]);
        } else {
          printf("%-10s", "NULL");
        }
        break;
      }
    }
    printf("\n");
  }
}

DataType infer_dtype(const char *value) {
  char *endptr;
  strtol(value, &endptr, 10);
  if (*endptr == '\0') {
    return INT;
  }

  strtod(value, &endptr);
  if (*endptr == '\0') {
    return PREC;
  }

  return STRING;
}

void set_value_df(DataFrame *df, int row_index, int col_index,
                  const char *value) {
  switch (df->columns[col_index].dtype) {
  case INT:
    set_int_value_df(df, row_index, col_index, atoi(value));
    break;
  case PREC:
    set_prec_value_df(df, row_index, col_index, atof(value));
    break;
  case STRING:
    set_str_value_df(df, row_index, col_index, value);
    break;
  }
}

// Function to load CSV file and return a DataFrame
DataFrame *load_csv(const char *filename, const char *sep) {

  // Note to self: If a line in the csv file is empty (generally at the last),
  // it will still be interpreted and added to the dataframes with values set to
  // default (NULL etc)

  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    fprintf(stderr, "Error opening file %s\n", filename);
    return NULL;
  }

  char line[1024]; // Assuming max line length is 1024 characters
  if (fgets(line, sizeof(line), file) == NULL) {
    fprintf(stderr, "Error reading header from file %s\n", filename);
    fclose(file);
    return NULL;
  }

  int num_columns = 0;
  char *column_names[100];    // Assuming max 100 columns
  DataType column_types[100]; // Assuming max 100 columns
  char *token = strtok(line, sep);
  while (token != NULL) {
    column_names[num_columns] = strdup(token);
    column_types[num_columns] =
        infer_dtype(token); // Assuming infer_dtype is implemented
    num_columns++;
    token = strtok(NULL, sep);
  }

  // Initialize DataFrame with exact number of rows and columns
  int num_rows = 0;
  while (fgets(line, sizeof(line), file) != NULL) {
    num_rows++;
  }
  fseek(file, 0, SEEK_SET); // Reset file pointer to beginning

  DataFrame *df = init_df(num_rows, num_columns);
  if (df == NULL) {
    fclose(file);
    return NULL;
  }

  // Set column names and types
  for (int col = 0; col < num_columns; col++) {
    set_column_df(df, col, column_names[col], column_types[col]);
  }

  // Read remaining rows and populate DataFrame
  int row_index = 0;
  // Skip the first line which contains column names
  fgets(line, sizeof(line), file);
  while (fgets(line, sizeof(line), file) != NULL) {
    token = strtok(line, sep);
    for (int col = 0; col < num_columns && token != NULL; col++) {
      switch (column_types[col]) {
      case INT:
        set_int_value_df(df, row_index, col, atoi(token));
        break;
      case PREC:
        set_prec_value_df(df, row_index, col, atof(token));
        break;
      case STRING:
        set_str_value_df(df, row_index, col, token);
        break;
      }
      token = strtok(NULL, sep);
    }
    row_index++;
  }

  fclose(file);
  return df;
}
