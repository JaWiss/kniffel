# Compiler
CC = gcc
CFLAGS = -Wall -g -Iutilities -Ibots   # -I to include utilities and bots headers

# Files
SRC = main.c \
      utilities/sheet.c \
      utilities/calculations.c \
      utilities/helper.c \
      utilities/game.c \
      utilities/diceRollResult.c \
      utilities/botRegistry.c \
      bots/randomBot.c \
      bots/improvedRandomBot.c \
      bots/greedyRandomBot.c

OBJ = $(SRC:.c=.o)

# Name of executable
TARGET = kniffelTest

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