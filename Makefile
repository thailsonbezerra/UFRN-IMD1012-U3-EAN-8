CC = gcc
CFLAGS = -Wall -Wextra -std=c11
BUILD = build
SRC = src

OBJS = \
    $(BUILD)/codificacoes.o \
    $(BUILD)/validar.o \
    $(BUILD)/pbm.o \
    $(BUILD)/barras.o

all: extrair gerar

extrair: $(BUILD)/extrair.o $(OBJS)
	$(CC) $(CFLAGS) -o extrair $(BUILD)/extrair.o $(OBJS)

gerar: $(BUILD)/gerar.o $(OBJS)
	$(CC) $(CFLAGS) -o gerar $(BUILD)/gerar.o $(OBJS)

$(BUILD)/%.o: $(SRC)/%.c
	mkdir -p $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build extrair gerar
