#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int largura, altura;
char **matriz = NULL;

int carregar_pbm(const char *arquivo) {
    FILE *f = fopen(arquivo, "r");
    if (!f) return -1;

    char magic[3];
    if (fscanf(f, "%2s", magic) != 1 || strcmp(magic, "P1") != 0) {
        fclose(f);
        return -1;
    }

    // Pula comentários e espaços
    int c;
    while ((c = fgetc(f)) == '#' || c == ' ' || c == '\n' || c == '\t') {
        if (c == '#') {
            while ((c = fgetc(f)) != '\n' && c != EOF);
        }
    }
    if (c != EOF) ungetc(c, f);  // Devolve o último caractere

    if (fscanf(f, "%d %d", &largura, &altura) != 2) {
        fclose(f);
        return -1;
    }

    // Aloca a matriz (usando malloc)
    matriz = malloc(altura * sizeof(char *));
    if (!matriz) {
        fclose(f);
        return -1;
    }

    for (int y = 0; y < altura; y++) {
        matriz[y] = malloc(largura * sizeof(char));
        if (!matriz[y]) {
            fclose(f);
            return -1;
        }
        for (int x = 0; x < largura; x++) {
            int pixel;
            if (fscanf(f, "%d", &pixel) != 1) {
                fclose(f);
                return -1;
            }
            matriz[y][x] = (pixel == 1) ? '1' : '0';  // Converte para char
        }
    }

    fclose(f);
    return 0;
}

int main(int argc, char *argv[]) {
    // Verifica se tem o arquivo como argumento
    if (argc != 2) {
        printf("Uso: %s <arquivo.pbm>\n", argv[0]);
        return 1;  // Erro: uso inválido
    }

    const char *arquivo = argv[1];

    // Abre o arquivo para leitura
    FILE *f = fopen(arquivo, "r");
    if (!f) {
        printf("Erro: arquivo não encontrado ou inválido: %s\n", arquivo);
        return 1; 
    }

    // Lê o cabeçalho "P1"
    char magic[3];
    if (fscanf(f, "%2s", magic) != 1 || strcmp(magic, "P1") != 0) {
        printf("Erro: arquivo não é PBM válido (deve começar com P1)\n");
        fclose(f);
        return 1;
    }

    printf("Arquivo aberto: %s → Formato PBM válido!\n", arquivo);

    fclose(f);

    return 0;
}