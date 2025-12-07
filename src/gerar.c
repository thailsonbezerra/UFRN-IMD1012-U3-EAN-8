#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "validar.h"
#include "barras.h"
#include "pbm.h"

void criar_diretorio() {
    struct stat st = {0};

    // Cria a pasta caso não exista
    if (stat("codigos_ean8", &st) == -1) {
        mkdir("codigos_ean8", 0777);
    }
}

int main(int argc, char *argv[]) {
    // Verifica se tem o ID obrigatório
    if (argc < 2) {
        printf("Uso: %s <id> [margem] [pixels_por_area] [altura] [arquivo.pbm]\n", argv[0]);
        return 1;
    }

    const char *id = argv[1];

    // Padrões do PBM
    int margem = 4;
    int pixels_por_area = 3;
    int altura = 50;
    const char *arquivo_usuario = "barcode.pbm";

    // Lê argumentos opcionais
    if (argc > 2) margem = atoi(argv[2]);
    if (argc > 3) pixels_por_area = atoi(argv[3]);
    if (argc > 4) altura = atoi(argv[4]);
    if (argc > 5) arquivo_usuario = argv[5];

    printf("ID: %s\n", id);
    printf("Margem: %d\n", margem);
    printf("Pixels por área: %d\n", pixels_por_area);
    printf("Altura: %d\n", altura);
    printf("Arquivo solicitado: %s\n", arquivo_usuario);

    // Cria pasta automaticamente
    criar_diretorio();

    // Monta o caminho completo dentro da pasta
    char caminho_final[256];
    snprintf(caminho_final, sizeof(caminho_final), "codigos_ean8/%s", arquivo_usuario);

    printf("Arquivo final: %s\n", caminho_final);

    // Validar o ID
    if (!valida_padrao_ean8(id)) {
        printf("Erro: Identificador inválido (verifique dígitos ou verificador).\n");
        return 1;
    }

    // Verificar se arquivo existe e perguntar sobrescrita
    FILE *f = fopen(caminho_final, "r");
    if (f) {
        fclose(f);
        printf("Arquivo %s já existe. Sobrescrever (s/n)? ", caminho_final);
        char resp;
        scanf(" %c", &resp);
        if (resp != 's' && resp != 'S') {
            printf("Cancelado. O arquivo não será sobrescrito.\n");
            return 1;
        }
    }

    char *barras = gerar_barras(id);
    if (!barras) {
        printf("Erro: Falha ao gerar barras.\n");
        return 1;
    }

    // Calcular dimensões da imagem
    int largura_total = 67 * pixels_por_area + 2 * margem;
    int altura_total = altura + 2 * margem;

    printf("Largura total: %d\n", largura_total);
    printf("Altura total: %d\n", altura_total);
    printf("Barras geradas: %s\n", barras);

    char **matriz = criar_matriz(altura_total, largura_total);
    if (!matriz) {
        printf("Erro: Falha ao alocar memória para a imagem.\n");
        free(barras);
        return 1;
    }

    preencher_barras(matriz, barras, margem, pixels_por_area, altura);
    free(barras);

    // Escrever o arquivo
    if (escrever_pbm(caminho_final, matriz, altura_total, largura_total) != 0) {
        printf("Erro: Falha ao escrever o arquivo %s.\n", caminho_final);
        liberar_matriz(matriz, altura_total);
        return 1;
    }

    liberar_matriz(matriz, altura_total);
    printf("Imagem gerada: %s\n", caminho_final);

    return 0;
}
