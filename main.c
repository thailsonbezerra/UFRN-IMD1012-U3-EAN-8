#include <stdio.h>
#include <string.h>
#include "validar.c"
#include "gerar_barras.c"

int main() {
    printf("=== TESTE: VALIDAÇÃO + GERAÇÃO DE BARRAS ===\n\n");

    const char *ids[] = {
        "40170725", "40170726", "12345670",
        "12345678", "abc12345", "1234567"
    };

    for (int i = 0; i < 6; i++) {
        const char *id = ids[i];
        printf("%s - ", id);

        char *barras = gerar_barras(id);

        if (barras) {
            printf("VÁLIDO - %s (67 bits)\n", barras);
            free(barras);
        } else {
            printf("INVÁLIDO\n");
        }
    }

    printf("\n=== FIM DO TESTE ===\n");
    return 0;
}