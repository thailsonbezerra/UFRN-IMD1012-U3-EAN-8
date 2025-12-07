# README --- Projeto EAN-8

Geração e Extração de Código de Barras em PBM (P1)

Este documento apresenta os testes de caso utilizados para validar o
funcionamento dos programas **gerar** e **extrair**, conforme os
requisitos definidos no projeto.

------------------------------------------------------------------------

# Testes de Caso

## 1. Argumentos em linha de comando

### Caso 1 --- Os programas consideram argumentos passados na linha de comando?

Teste:

    ./gerar 55123457 8 4 60 meu.pbm

Resultado esperado:\
Os parâmetros opcionais (margem, pixels_por_area, altura e nome do
arquivo) devem ser utilizados.

------------------------------------------------------------------------

### Caso 2 --- Se argumentos não forem passados, valores padrão serão utilizados?

Teste:

    ./gerar 55123457

Resultado esperado:\
O programa deve usar os valores padrão definidos internamente (ex.:
margem 4, pixels_por_area 3, altura 50, arquivo barcode.pbm).

------------------------------------------------------------------------

## 2. Geração do código de barra

### Caso 3 --- O dígito verificador é validado?

Teste:

    ./gerar 55123458

Resultado esperado:\
Mensagem de erro informando que o identificador é inválido.

------------------------------------------------------------------------

### Caso 4 --- O identificador é codificado corretamente?

Teste:

    ./gerar 55123457

Resultado esperado:\
O programa imprime a sequência de barras geradas e elas devem
corresponder à junção: - marcador inicial\
- 4 dígitos via L-code\
- marcador central\
- 4 dígitos via R-code\
- marcador final

------------------------------------------------------------------------

### Caso 5 --- A codificação é transformada em imagem de forma adequada?

Teste:

    ./gerar 55123457

Resultado esperado:\
A imagem PBM deve conter: - Cabeçalho "P1"\
- Largura e altura calculadas corretamente\
- Matriz contendo apenas zeros e uns equivalentes à codificação gerada

------------------------------------------------------------------------

### Caso 6 --- O arquivo de imagem é gerado com o código de barras correto?

Teste:

    ./gerar 55123457
    ./extrair codigos_ean8/barcode.pbm

Resultado esperado:\
A extração retorna **55123457**, comprovando que a imagem contém o
código correto.

------------------------------------------------------------------------

## 3. Extração do identificador

### Caso 7 --- O arquivo de imagem é lido corretamente?

Teste:

    ./extrair arquivo_inexistente.pbm

Resultado esperado:\
Mensagem de erro indicando que o arquivo é inválido ou não existe.

------------------------------------------------------------------------

### Caso 8 --- O programa consegue verificar se há um código de barras na imagem?

Criar manualmente um PBM válido sem barras e testar:

    ./extrair branco.pbm

Resultado esperado:\
Mensagem informando que o código de barras não foi encontrado.

------------------------------------------------------------------------

### Caso 9 --- Foi possível calcular o número de pixels para definir a largura do módulo?

Teste: Modificar um PBM gerado, corrompendo o primeiro módulo (101).

    ./extrair corrompido.pbm

Resultado esperado:\
Mensagem como:

    Erro: não encontrou o primeiro módulo.

ou

    Marcador inicial 101 não encontrado.

------------------------------------------------------------------------

### Caso 10 --- O programa conseguiu extrair o identificador?

Teste final:

    ./gerar 55123457
    ./extrair codigos_ean8/barcode.pbm

Resultado esperado:

    55123457

------------------------------------------------------------------------

Este conjunto de testes cobre todos os 10 itens solicitados na seção de
funcionalidades do projeto.