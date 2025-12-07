#ifndef PBM_H
#define PBM_H

char **criar_matriz(int altura, int largura);
void preencher_barras(char **matriz, const char *barras, int margem, int px, int altura);
int escrever_pbm(const char *arquivo, char **matriz, int altura, int largura);
void liberar_matriz(char **matriz, int altura);

#endif
