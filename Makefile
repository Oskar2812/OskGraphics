CC = gcc
CFLAGS = -Wall -Wextra
LINK_FLAGS = -luser32 -lgdi32 -lopengl32
OPT = -O0

SRC_DIR = src
BUILD_DIR = build
EXAMPLES_DIR = examples
EXAMPLES_BUILD_DIR = bin

EXAMPLE_SRC = $(wildcard $(EXAMPLES_DIR)/*.c)
EXAMPLE_EXE = $(patsubst $(EXAMPLES_DIR)/%.c,$(EXAMPLES_BUILD_DIR)/%.exe,$(EXAMPLE_SRC))

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC))

MAIN = main.c

LIB = libOskGraphics.a

all: lib

lib: $(LIB)

$(LIB): $(OBJ)
	ar rcs $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
	$(CC) $(CFLAGS) $(OPT) -c $< -o $@	

main: lib
	$(CC) $(CFLAGS) $(OPT) main.c $(LIB) -o app.exe $(LINK_FLAGS)

run_main: main
	./app

debug: OPT = -O0
debug: CFLAGS += -g
debug: clean main

examples: lib $(EXAMPLE_EXE)

$(EXAMPLES_BUILD_DIR)/%.exe: $(EXAMPLES_DIR)/%.c lib
	@if not exist $(EXAMPLES_BUILD_DIR) mkdir bin
	$(CC) $(CFLAGS) $(OPT) $< $(LIB) -o $@ $(LINK_FLAGS)

clean:
	-rmdir /s /q $(BUILD_DIR) 
	-rmdir /s /q $(EXAMPLES_BUILD_DIR) 
	del $(LIB)
	del app.exe