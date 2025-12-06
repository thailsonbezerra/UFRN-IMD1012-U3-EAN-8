#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <arquivo.pbm>\n", argv[0]);
        return 1;
    }

    const char *arquivo = argv[1];
    FILE *f = fopen(arquivo, "r");
    if (!f) {
        printf("Erro: arquivo não encontrado ou inválido.\n");
        return 1;
    }

    char magic[3];
    if (fscanf(f, "%2s", magic) != 1 || strcmp(magic, "P1") != 0) {
        printf("Erro: arquivo não é PBM válido (deve começar com P1).\n");
        fclose(f);
        return 1;
    }

    printf("Arquivo aberto: %s → Formato PBM válido!\n", arquivo);

    fclose(f);
    return 0;
}