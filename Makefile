# ============================================================
# C-lestial Library
# ============================================================

CC = gcc

# User settings
MAIN = main.c
TARGET = main

# Library
SRC_DIR = c_lestial_library

CFLAGS = -I$(SRC_DIR) -std=c11 -O3 -g -Wall -Wextra -Wpedantic
LDFLAGS = -lm

SOURCES = \
	$(MAIN) \
	$(SRC_DIR)/array/array.c \
	$(SRC_DIR)/array/linalg.c \
	$(SRC_DIR)/mathfuncs.c \
$(SRC_DIR)/DataFrames.c \
	$(SRC_DIR)/approx.c \
	$(SRC_DIR)/plots.c

OBJECTS = $(SOURCES:.c=.o)
DEPS = $(OBJECTS:.o=.d)


# ============================================================
# Build
# ============================================================

.PHONY: all clean rebuild run

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

-include $(DEPS)


# ============================================================
# Utilities
# ============================================================

clean:
	rm -f $(OBJECTS) $(DEPS) $(TARGET)

rebuild: clean all

run: $(TARGET)
	./$(TARGET)
