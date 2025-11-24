#include "validar.c" 

int main() {
    printf("=== TESTE DE VALIDAÇÃO ===\n\n");

    printf("40170725 → %s\n", valida_padrao_ean8("40170725") ? "VÁLIDO" : "inválido");
    printf("40170726 → %s\n", valida_padrao_ean8("40170726") ? "VÁLIDO" : "inválido");
    printf("12345678 → %s\n", valida_padrao_ean8("12345678") ? "VÁLIDO" : "inválido");
    printf("abc12345 → %s\n", valida_padrao_ean8("abc12345") ? "VÁLIDO" : "inválido");
    printf("1234567  → %s\n", valida_padrao_ean8("1234567")  ? "VÁLIDO" : "inválido");

    return 0;
}