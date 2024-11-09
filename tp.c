#include <stdio.h>
#include <stdlib.h>
#include "automato.h"
#include "matriz.h"

int main(){

    int dimensao;
    int geracoes;

    // Solicitar a dimensão do autômato celular e o número de gerações
    scanf("%d", &dimensao);
    scanf("%d", &geracoes);

    // Alocar espaço para o autômato celular
    AutomatoCelular *autcel = alocarreticulado(dimensao);

    // Verificar se a alocação foi bem-sucedida
    if (autcel == NULL) {
        printf("Erro ao alocar memória para o autômato celular.\n");
        return 1; // Encerrar o programa com código de erro
    }

    // Ler os valores para as células do autômato celular
    LeituraReticulado(autcel);
    evoluirReticulado(autcel, geracoes);
    // Imprimir o autômato celular
    imprimeReticulado(autcel);

    // Desalocar a memória do autômato celular
    desalocarReticulado(autcel);

    return 0;
}
