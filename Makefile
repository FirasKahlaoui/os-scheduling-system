CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude -Isrc
LDFLAGS = -lncurses -ldl -rdynamic

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
	@if [ -w "/usr/local/bin" ]; then \
		echo "Installing system-wide to /usr/local/bin..."; \
		cp $(EXEC) /usr/local/bin/scheduler; \
		echo "Installation successful."; \
	else \
		echo "Notice: No write access to /usr/local/bin (try 'sudo make install' for system-wide)."; \
		echo "Falling back to local installation in ~/.local/bin..."; \
		mkdir -p ~/.local/bin; \
		cp $(EXEC) ~/.local/bin/scheduler; \
		echo "Installation successful. Ensure ~/.local/bin is in your PATH."; \
	fi

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

run:
	./$(EXEC) config_examples/test1.conf FIFO

test:
	./$(EXEC) config_examples/test1.conf FIFO
	./$(EXEC) config_examples/test2.conf RoundRobin 4

.PHONY: all install clean run test