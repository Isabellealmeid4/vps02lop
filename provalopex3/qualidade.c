#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <locale.h>

typedef struct {
    int numero_de_serie;
    int resistencia;
    int durabilidade;
} Produto;

int main() {
    setlocale(LC_ALL, "");
    FILE *arquivo;
    char linha[100];
    int resistencia_total = 0, durabilidade_total = 0;
    int maior_resistencia = INT_MIN, menor_resistencia = INT_MAX;
    int maior_durabilidade = INT_MIN, menor_durabilidade = INT_MAX;
    int num_produtos = 0;
    int num_produto_maior_resistencia = -1, num_produto_menor_resistencia = -1;
    int num_produto_maior_durabilidade = -1, num_produto_menor_durabilidade = -1;

    
    arquivo = fopen("parametros.csv", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    // Ignora a primeira linha (cabeçalho)
    fgets(linha, sizeof(linha), arquivo);

   
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        Produto produto;
        sscanf(linha, "%d;%d;%d", &produto.numero_de_serie, &produto.resistencia, &produto.durabilidade);

        resistencia_total += produto.resistencia;
        durabilidade_total += produto.durabilidade;

        if (produto.resistencia > maior_resistencia) {
            maior_resistencia = produto.resistencia;
            num_produto_maior_resistencia = produto.numero_de_serie;
        }
        if (produto.resistencia < menor_resistencia) {
            menor_resistencia = produto.resistencia;
            num_produto_menor_resistencia = produto.numero_de_serie;
        }

        if (produto.durabilidade > maior_durabilidade) {
            maior_durabilidade = produto.durabilidade;
            num_produto_maior_durabilidade = produto.numero_de_serie;
        }
        if (produto.durabilidade < menor_durabilidade) {
            menor_durabilidade = produto.durabilidade;
            num_produto_menor_durabilidade = produto.numero_de_serie;
        }

        num_produtos++;
    }

    fclose(arquivo);

    
    float media_resistencia = (float)resistencia_total / num_produtos;
    float media_durabilidade = (float)durabilidade_total / num_produtos;


    arquivo = fopen("qualidade.md", "w");
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo qualidade.md.\n");
        return 1;
    }


    fprintf(arquivo, "# Analise de Qualidade dos Produtos\n\n");
    fprintf(arquivo, "Numero total de produtos: %d\n\n", num_produtos);
    fprintf(arquivo, "## Resistencia\n");
    fprintf(arquivo, "- Media de resistencia: %.2f\n", media_resistencia);
    fprintf(arquivo, "- Maior resistencia (Numero de serie: %d): %d\n", num_produto_maior_resistencia, maior_resistencia);
    fprintf(arquivo, "- Menor resistencia (Numero de serie: %d): %d\n\n", num_produto_menor_resistencia, menor_resistencia);

    fprintf(arquivo, "## Durabilidade\n");
    fprintf(arquivo, "- Media de durabilidade: %.2f\n", media_durabilidade);
    fprintf(arquivo, "- Maior durabilidade (Numero de serie: %d): %d\n", num_produto_maior_durabilidade, maior_durabilidade);
    fprintf(arquivo, "- Menor durabilidade (Numero de serie: %d): %d\n\n", num_produto_menor_durabilidade, menor_durabilidade);

    fprintf(arquivo, "Existem mais produtos acima das medias.\n");

  
    fclose(arquivo);

    printf("Analise salva com sucesso no arquivo qualidade.md\n");

    return 0;
}

