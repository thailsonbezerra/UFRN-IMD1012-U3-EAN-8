#include <stdlib.h>

// Cria matriz de pixel
char **criar_matriz(int altura, int largura) {
    char **matriz = malloc(altura * sizeof(char*));
    if (!matriz) return NULL;

    for (int y = 0; y < altura; y++) {
        matriz[y] = malloc(largura * sizeof(char));
        if (!matriz[y]) return NULL;
        for (int x = 0; x < largura; x++) {
            matriz[y][x] = '0';
        }
    }
    return matriz;
}

// Preenche as barras na matriz
void preencher_barras(char **matriz, const char *barras, int margem, int pixels_por_area, int altura_barras) {
    int y0 = margem;
    int y1 = margem + altura_barras - 1;
    int x = margem;

    for (int m = 0; m < 67; m++) {
        if (barras[m] == '1') {
            for (int y = y0; y <= y1; y++) {
                for (int p = 0; p < pixels_por_area; p++) {
                    matriz[y][x + p] = '1';
                }
            }
        }
        x += pixels_por_area;
    }
}

int escrever_pbm(const char *arquivo, char **matriz, int altura, int largura) {
    FILE *f = fopen(arquivo, "w");
    if (!f) return -1;

    fprintf(f, "P1\n%d %d\n", largura, altura);

    for (int y = 0; y < altura; y++) {
        for (int x = 0; x < largura; x++) {
            fprintf(f, "%c ", matriz[y][x]);
        }
        fprintf(f, "\n");
    }

    fclose(f);
    return 0;
}

// Libera a matriz
void liberar_matriz(char **matriz, int altura) {
    for (int y = 0; y < altura; y++) free(matriz[y]);
    free(matriz);
}