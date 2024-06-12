TARGET=test.c
CC=gcc
CFLAGS=-Ic_lestial_library/ -O3 -g -Wall -lm
LIBRARYFILES=c_lestial_library/array/array.c c_lestial_library/array/linalg.c c_lestial_library/mathfuncs.c c_lestial_library/DataFrames.c
LIBRARYOBJFILES=c_lestial_library/array/array.c c_lestial_library/array/linalg.c c_lestial_library/mathfuncs.c


make: $(TARGET)
	$(CC) -o output $(TARGET) $(LIBRARYFILES) $(CFLAGS)  

