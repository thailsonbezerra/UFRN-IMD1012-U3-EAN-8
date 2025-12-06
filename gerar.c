#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "validar.c"
#include "gerar_barras.c"

int main(int argc, char *argv[]) {
    // Verifica se tem o ID obrigatório
    if (argc < 2) {
        printf("Uso: %s <id> [margem] [pixels_por_area] [altura] [arquivo.pbm]\n", argv[0]);
        return 1;
    }

    const char *id = argv[1];

    // Padrões do PDF
    int margem = 4;
    int pixels_por_area = 3;
    int altura = 50;
    const char *arquivo = "barcode.pbm";

    // Lê argumentos opcionais
    if (argc > 2) margem = atoi(argv[2]);
    if (argc > 3) pixels_por_area = atoi(argv[3]);
    if (argc > 4) altura = atoi(argv[4]);
    if (argc > 5) arquivo = argv[5];

    printf("ID: %s\n", id);
    printf("Margem: %d\n", margem);
    printf("Pixels por área: %d\n", pixels_por_area);
    printf("Altura: %d\n", altura);
    printf("Arquivo: %s\n", arquivo);

    return 0;
}