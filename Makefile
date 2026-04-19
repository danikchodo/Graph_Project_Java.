CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g -Iinclude

SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
TEST_DIR = tests

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

TEST_SRCS = $(wildcard $(TEST_DIR)/*.c)
TEST_OBJS = $(patsubst $(TEST_DIR)/%.c, $(OBJ_DIR)/%.o, $(TEST_SRCS))

OBJS_NO_MAIN = $(filter-out $(OBJ_DIR)/main.o, $(OBJS))

TARGET = grafy
TEST_TARGET = run_tests

all: $(OBJ_DIR) $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -lm

test: $(OBJ_DIR) $(OBJS_NO_MAIN) $(TEST_OBJS)
	$(CC) $(CFLAGS) -o $(TEST_TARGET) $(OBJS_NO_MAIN) $(TEST_OBJS)
	./$(TEST_TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR) $(TARGET) $(TEST_TARGET)

run: all
	./$(TARGET)

.PHONY: all clean run test