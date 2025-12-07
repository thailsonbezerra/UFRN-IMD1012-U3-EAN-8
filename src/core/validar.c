#include <stdio.h>
#include <string.h>
#include <ctype.h>

int valida_digitos_ean8 (const char *id) {
    if (strlen(id) != 8) {
        return 0;
    }

    for (int i = 0; i < 8; i++) {
        if (!isdigit(id[i])) {
            return 0;
        }
    }
    return 1;
}

int valida_digito_verificar_ean8(const char *id) {
    int soma = 0;

    for (int i = 0; i < 7; i++) {
        int digito = id[i] - '0';
        if (i % 2 == 0) {
            soma += digito * 3;
        } else {
            soma += digito * 1;
        }
    }

    int proximo_multiplo_dez = ((soma / 10) + 1) * 10;
    int digito_correto = proximo_multiplo_dez - soma; 

    if (digito_correto == 10) digito_correto = 0;

    return digito_correto;
}

int valida_padrao_ean8(const char *id) {
    if (!valida_digitos_ean8(id)) {
        return 0;
    }

    int digito_verificador = id[7] - '0';
    int digito_correto = valida_digito_verificar_ean8(id);

    return (digito_verificador == digito_correto);
}