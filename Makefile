CC = gcc
CFLAGS = -Wall -Wextra -std=c11

SRC_DIR = src
CORE_DIR = src/core
INC_DIR = src/include
BUILD_DIR = build

CORE_SRCS = $(wildcard $(CORE_DIR)/*.c)
CORE_OBJS = $(patsubst $(CORE_DIR)/%.c, $(BUILD_DIR)/%.o, $(CORE_SRCS))

GERAR = gerar
EXTRAIR = extrair

all: $(GERAR) $(EXTRAIR)

$(BUILD_DIR)/%.o: $(CORE_DIR)/%.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(GERAR): $(SRC_DIR)/gerar.c $(CORE_OBJS)
	$(CC) $(CFLAGS) -I$(INC_DIR) $^ -o $(GERAR)

$(EXTRAIR): $(SRC_DIR)/extrair.c $(CORE_OBJS)
	$(CC) $(CFLAGS) -I$(INC_DIR) $^ -o $(EXTRAIR)

clean:
	rm -rf $(BUILD_DIR) *.o $(GERAR) $(EXTRAIR)
