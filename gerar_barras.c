#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "codificacoes.h"

extern int valida_padrao_ean8(const char *id);

char* gerar_barras(const char *id) {
    if (!valida_padrao_ean8(id)) {
        return NULL;
    }

    char *barras = malloc(68);
    if (!barras) {
        return NULL;
    }

    // Início do código de barras
    strcpy(barras, "101");

    for (int i = 0; i < 4; i++) {
        int d = id[i] - '0';
        strcat(barras, L_CODE[d]);
    }

    // Meio do código de barras
    strcat(barras, "01010");
    
    for (int i = 4; i < 8; i++) {
        int d = id[i] - '0';
        strcat(barras, R_CODE[d]);
    }

    // Fim do código de barras
    strcat(barras, "101");

    return barras;
}