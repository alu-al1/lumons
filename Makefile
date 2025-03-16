# Compiler and Flags
CC = gcc
CFLAGS = -Wall -Wextra -g -fPIC
LDFLAGS = -ldl -lX11 -lm

# Library Directories
LIB_DIR = ./libs/libddcutil/lib
INCLUDE_DIRS = -I./libs/libddcutil/include -I./libs

# Output Binary
TARGET = brlev

# Source files
SRC = main.c utils.c core.c ui.c

# Object files
OBJ = $(SRC:.c=.o)

# Rules for building the program
$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $(OBJ) $(LDFLAGS)

# Rule to generate object files
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c $< -o $@

# Clean rule to remove build artifacts
.PHONY: clean
clean:
	rm -f $(OBJ) $(TARGET)

# Rule to run the program
run: $(TARGET)
	./$(TARGET)

# Rule to test the dynamic loading of the library (if needed)
test_ddcutil:
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) $(SRC) -o $(TARGET) $(LDFLAGS)
	./$(TARGET)
