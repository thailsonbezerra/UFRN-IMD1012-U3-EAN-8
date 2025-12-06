#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "validar.c"
#include "gerar_barras.c"
#include "pbm.c"

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

    // Validar o ID
    if (!valida_padrao_ean8(id)) {
        printf("Erro: Identificador inválido (verifique dígitos ou verificador).\n");
        return 1;
    }

    // Verificar se arquivo existe e perguntar sobrescrita
    FILE *f = fopen(arquivo, "r");
    if (f) {
        fclose(f);
        printf("Arquivo %s já existe. Sobrescrever (s/n)? ", arquivo);
        char resp;
        scanf("%c", &resp);
        if (resp != 's' && resp != 'S') {
            printf("Erro: arquivo resultante já existe.\n");
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

    // Imprimir para teste
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
    if (escrever_pbm(arquivo, matriz, altura_total, largura_total) != 0) {
        printf("Erro: Falha ao escrever o arquivo %s.\n", arquivo);
        liberar_matriz(matriz, altura_total);
        return 1;
    }

    liberar_matriz(matriz, altura_total);
    printf("Imagem gerada: %s\n", arquivo);

    return 0;
}