# Compiler and Flags
CC = gcc
CFLAGS = -Wall -Wextra -g -fPIC
## -ldl
##LDFLAGS = -Wl,-Bstatic -L$(LIB_DIR) -lddcutil -Wl,-Bdynamic -lX11 -lm
#LDFLAGS = -Wl,-Bstatic -L$(LIB_DIR) -lddcutil -Wl,-Bdynamic -lglib-2.0 -lX11 -lm -ldl

# Library Directories
LIB_DIR = lib
LIB_DIR_DDCUTIL = $(LIB_DIR)/libddcutil/lib

INCLUDE_DIRS = -I./lib/libddcutil/include -I./$(LIB_DIR)

## the order of libraries and linker flags matters !!!
# LDFLAGS = -L$(LIB_DIR) -lddcutil -static -lX11 -lm -ldl
LDFLAGS = -L$(LIB_DIR) -L$(LIB_DIR_DDCUTIL) -lddcutil  -lX11 -lm

# LDFLAGS += -lX11 -lXext -lXrandr -ljansson -lglib-2.0 -ludev -ldrms -lc -lxcb -ldl -lXrender -lpcre2-8 -lpthread -lXau -lXdmcp -lbsd


# Output Binary
TARGET = lumons

# Source files
SRC = main.c glue.c core.c utils.c ui/ui.c

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
	LD_LIBRARY_PATH=$(LIB_DIR):$(LIB_DIR_DDCUTIL):$$LD_LIBRARY_PATH ./$(TARGET)

# Rule to test the dynamic loading of the library (if needed)
test_ddcutil:
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) $(SRC) -o $(TARGET) $(LDFLAGS)
	./$(TARGET)
