#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "codificacoes.h"

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

void liberar_matriz() {
    if (matriz) {
        for (int y = 0; y < altura; y++) {
            free(matriz[y]);
        }
        free(matriz);
        matriz = NULL;
    }
}

int decodificar(const char *bits, const char *tabela[10]) {
    for (int d = 0; d < 10; d++) {
        if (strncmp(bits, tabela[d], 7) == 0) return d;
    }
    return -1;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <arquivo.pbm>\n", argv[0]);
        return 1;
    }

    if (carregar_pbm(argv[1]) != 0) {
        printf("Erro ao carregar o arquivo.\n");
        return 1;
    }

    int meio = altura / 2;

    // Procurar o primeiro pixel preto (ignora margem)
    int x;
    for (x = 0; x < largura; x++) {
        if (matriz[meio][x] == '1') break;
    }

    // Calcular tamanho do módulo (largura do primeiro bloco preto)
    int modulo = 0;
    while (x + modulo < largura && matriz[meio][x + modulo] == '1') {
        modulo++;
    }

    if (modulo == 0) {
        printf("Erro: não encontrou o primeiro módulo.\n");
        liberar_matriz();
        return 1;
    }

    // Verificar se é o marcador inicial 101 (3 módulos: preto, branco, preto)
    if (x + 3*modulo >= largura ||
        matriz[meio][x + modulo] != '0' ||
        matriz[meio][x + 2*modulo] != '1') {
        printf("Marcador inicial 101 não encontrado.\n");
        liberar_matriz();
        return 1;
    }

    // Ler os 67 bits
    char bits[68];
    int pos = x;
    for (int i = 0; i < 67; i++) {
        bits[i] = matriz[meio][pos + modulo/2];  // pixel central do módulo
        pos += modulo;
    }
    bits[67] = '\0';

    // Decodificar ID
    char id[9];
    for (int i = 0; i < 4; i++) {
        int d = decodificar(bits + 3 + i*7, L_CODE);
        if (d == -1) { printf("Erro L-code\n"); liberar_matriz(); return 1; }
        id[i] = '0' + d;
    }
    for (int i = 0; i < 4; i++) {
        int d = decodificar(bits + 36 + i*7, R_CODE);
        if (d == -1) { printf("Erro R-code\n"); liberar_matriz(); return 1; }
        id[4+i] = '0' + d;
    }
    id[8] = '\0';

    printf("%s\n", id);

    liberar_matriz();
    return 0;
}