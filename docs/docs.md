These docs contain the whole set of functions, structures, datatypes, etc that the library has. They are themselves not the "teaching material" part of C-lestial project but contains information on how to implement the modules created for the project. 

**Tip**: Use github outline to navigate the functions in the module docs. 

[defs](modules/defs.md) : contains common definitions and types for the C-lestial library. Other library modules can include this file when they need these definitions.

[array/array](modules/array/array.md) :  contains functions for **Vectors** which are 1-D arrays but support multiple data types including integers, precision floating-point numbers, and strings.

[array/linalg](modules/array/linalg.md) : provides structures and functions for linear algebra operations, specifically focused on 2-D **Matrices**. Has solvers for linear systems etc.

[DataFrames](modules/dataframes.md) : provides a structure and a set of functions for handling tabular data, similar to dataframes in other high-level languages. It allows for the creation of tables with named columns, where each column can store a different **DataType** (see defs.h) and also contains utilities related to data manipulation.