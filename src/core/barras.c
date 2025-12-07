#include <stdlib.h>
#include <string.h>
#include "codificacoes.h"
#include "validar.h"

char* gerar_barras(const char *id) {
    if (!valida_padrao_ean8(id)) return NULL;

    char *barras = malloc(68);
    if (!barras) return NULL;

    strcpy(barras, "101");

    for (int i = 0; i < 4; i++) {
        int d = id[i] - '0';
        strcat(barras, L_CODE[d]);
    }

    strcat(barras, "01010");

    for (int i = 4; i < 8; i++) {
        int d = id[i] - '0';
        strcat(barras, R_CODE[d]);
    }

    strcat(barras, "101");

    return barras;
}
