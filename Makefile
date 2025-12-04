CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude -Isrc
LDFLAGS = -lncurses

SRC_DIR = src
POLICY_DIR = policies
OBJ_DIR = obj
BIN_DIR = bin

SRCS = $(wildcard $(SRC_DIR)/*.c)
POLICY_SRCS = $(wildcard $(POLICY_DIR)/*.c)

OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
POLICY_OBJS = $(patsubst $(POLICY_DIR)/%.c, $(OBJ_DIR)/%.o, $(POLICY_SRCS))

EXEC = $(BIN_DIR)/scheduler

all: $(EXEC)

$(EXEC): $(OBJS) $(POLICY_OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(POLICY_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

install:
	@echo "Installing to ~/.local/bin"
	@mkdir -p ~/.local/bin
	cp $(EXEC) ~/.local/bin/scheduler

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

run:
	./$(EXEC) config_examples/test1.conf FIFO

test:
	./$(EXEC) config_examples/test1.conf FIFO
	./$(EXEC) config_examples/test2.conf RoundRobin 4

.PHONY: all install clean run test
# Improved rules
# install target + ~/.local/bin support