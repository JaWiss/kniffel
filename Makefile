# Compiler
CC = gcc
CFLAGS = -Wall -g -Iutilities   # -I to include utilities headers

# Files
SRC = main.c utilities/sheet.c utilities/calculations.c utilities/helper.c utilities/game.c
OBJ = $(SRC:.c=.o)

# Name of executable
TARGET = kniffel3

# Default rule
all: $(TARGET)

# Link object files into the executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

# Compile each .c file into a .o file
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up object files and executable
clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean

