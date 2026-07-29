CC = gcc
CFLAGS = -Wall -Wextra
LINK_FLAGS = -luser32 -lgdi32 -lopengl32
OPT = -O0

SRC_DIR = src
BUILD_DIR = build

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