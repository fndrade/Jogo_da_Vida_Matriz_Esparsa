#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "matriz.h" 
#include "automato.h"

struct automatocelular{
    int d;
    MatrizEsparsa *matriz;
};


AutomatoCelular *alocarreticulado (int d){ //ALOCAÇÃO DO RETICULADO

    AutomatoCelular *autcel = (AutomatoCelular *) malloc (sizeof(AutomatoCelular));
    if(autcel == NULL){//teste caso de erro na alocação
        return NULL;
    }
    autcel -> d = d; //alocando variavel tamanho matriz
    
    autcel->matriz = AlocarMatriz(d);
    if (autcel->matriz == NULL) {
        // Verifica se a alocação da matriz foi bem-sucedida
            free(autcel);
        return NULL;
    }

    return autcel;
}
 
void desalocarReticulado(AutomatoCelular *autcel) {
    DesalocaMatriz(autcel->matriz);
    free(autcel);
}


void LeituraReticulado(AutomatoCelular *autcel) {
    int valor;

    for (int i = 0; i < autcel->d; i++) {
        for (int j = 0; j < autcel->d; j++) {
            scanf("%d", &valor);

            if (InsereValor(autcel->matriz, i, j, valor) != 1) {
                printf("Erro ao inserir valor na matriz.\n");
                return;
            }
        }
    }
}


void imprimeReticulado(AutomatoCelular *autcel){
    ImprimeMatriz(autcel->matriz);
}

void confereReticulado(AutomatoCelular *autcel, MatrizEsparsa *matrizaux) {
    // Verificar a matriz esparsa
    for (int i = 0; i < autcel->d; i++) {
        for (int j = 0; j < autcel->d; j++) {
            int vizinhos = 0; // Valor dos vizinhos (se eles estão mortos ou vivos)

            // Verificando ao redor
            for (int x = -1; x <= 1; x++) {
                for (int y = -1; y <= 1; y++) {
                    if (x == 0 && y == 0) {
                        continue;
                    }

                    int auxX = i + x;
                    int auxY = j + y;

                    if (auxX >= 0 && auxX < autcel->d && auxY >= 0 && auxY < autcel->d) {
                        // Usar a função MatrizInsere para obter o valor da célula
                        if (RetornaValor(autcel->matriz, auxX, auxY)) // Inserir valor zero para verificar se existe ou não
                            vizinhos += 1;
                    }
                }
            }

            // Aplicar as regras do jogo da vida
            //confere se a celula atual tem um valor valido para a matriz ou seja 1(valido) ou 0(invalido)
            int celulaAtual = RetornaValor(autcel->matriz, i, j);

            if (celulaAtual == 1) {
                if (vizinhos < 2 || vizinhos > 3) {
                   //0, valor invalido, ou seja, fica vazio
                } else {
                    InsereValor(matrizaux, i, j, 1); //valor valido, valor = 1
                }
            } else {
                if (vizinhos == 3) {
                    InsereValor(matrizaux, i, j, 1); //valor valido, valor = 1
                } else {
                    //0, valor invalido, ou seja, fica vazio
                }
            }
        }
    }
}


 void evoluirReticulado(AutomatoCelular *autcel, int geracoes) {
    if (geracoes == 0) {
        return;
    }

    MatrizEsparsa *matrizaux = AlocarMatriz(autcel->d); //aloca a matriz auxiliar como uma matriz esparsa
    confereReticulado(autcel, matrizaux); //faz todas as conferencias utilizando aux 

    DesalocaMatriz(autcel->matriz); //libera memoria
    autcel->matriz = matrizaux; //autcel recebe a matriz aux com as modificações corretas

    evoluirReticulado(autcel, geracoes - 1); //chamada recursiva 
}
