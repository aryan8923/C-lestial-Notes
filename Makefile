TARGET=main.c
OUTPUT=output
CC=gcc
CFLAGS=-Ic_lestial_library/ -O3 -g -Wall -lm
LIBRARYFILES=c_lestial_library/array/array.c c_lestial_library/array/linalg.c c_lestial_library/mathfuncs.c c_lestial_library/DataFrames.c c_lestial_library/approx.c c_lestial_library/plots.c
LIBRARYOBJFILES=c_lestial_library/array/array.c c_lestial_library/array/linalg.c c_lestial_library/mathfuncs.c c_lestial_library/DataFrames.c c_lestial_library/approx.c c_lestial_library/plots.c


make: $(TARGET)
	$(CC) -o $(OUTPUT) $(TARGET) $(LIBRARYFILES) $(CFLAGS)  

