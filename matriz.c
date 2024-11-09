#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "matriz.h" 


MatrizEsparsa* AlocarMatriz(int tam) {
    // Aloca memória para a estrutura da matriz
    MatrizEsparsa* m = (MatrizEsparsa*) malloc(sizeof(MatrizEsparsa));
    if (m == NULL) {
        // Tratamento de erro em caso de falha na alocação
        return NULL;
    }

    m->linhas = tam;  // Define o número de linhas
    m->colunas = tam;  // Define o número de colunas
    m->primeiraLinha = NULL;  // Inicializa a lista de linhas como vazia

    // Criar as linhas
    Linha* ultimaLinha = NULL;
    for (int i = 0; i < tam; i++) {
        Linha* novaLinha = (Linha*) malloc(sizeof(Linha));
        if (novaLinha == NULL) {
            // Em caso de falha na alocação, liberar tudo já alocado
            Linha* aux = m->primeiraLinha;
            while (aux != NULL) {
                Linha* temp = aux;
                aux = aux->proxLinha;
                free(temp);
            }
            free(m);//verificações pra liberar caso haja erro
            return NULL;
        }

        novaLinha->numero = i;
        novaLinha->primeiraColuna = NULL;  // Nenhuma coluna ainda
        novaLinha->proxLinha = NULL; //proxima linha não existe ainda

        // Conectar a nova linha à lista de linhas da matriz
        if (ultimaLinha == NULL) {
            m->primeiraLinha = novaLinha;  // Se for a primeira linha, ela é a primeira da lista
        } else {
            ultimaLinha->proxLinha = novaLinha;  // se ja existir uma linha ,cria uma nova onde a anterior aponta para ela
        }
        ultimaLinha = novaLinha;  // Atualiza a última linha
    }

    return m;
}


int InsereValor(MatrizEsparsa* m, int lin, int col, float val) {
    if (lin < 0 || lin >= m->linhas || col < 0 || col >= m->colunas) {
        return 0; // Verificação de índice inválido
    }

    Linha* linhaAtual = m->primeiraLinha;//linha atual
    Linha* linhaAnterior = NULL;//a anterior por enquanto vazia

    // Buscar a linha correta
    while (linhaAtual != NULL && linhaAtual->numero < lin) {//while vai rodar toda linha procurando a posição do usuario
        linhaAnterior = linhaAtual;//substitui a anterior por atual
        linhaAtual = linhaAtual->proxLinha; //a atual é a proxima dela mesmo devido a rotação do while
    }

    // Se a linha não existir, criar uma nova
    if (linhaAtual == NULL || linhaAtual->numero > lin) {
        Linha* novaLinha = (Linha*) malloc(sizeof(Linha));//criando a nova linha
        if (novaLinha == NULL) return false; // Verificação de falha na alocação

        novaLinha->numero = lin;//valor da linha
        novaLinha->primeiraColuna = NULL;//coluna vazia por enquanto
        novaLinha->proxLinha = linhaAtual;//valor da nova linha é o da posição do usuario

        if (linhaAnterior == NULL) {//se linha anterior não existe uma linha ainda nessa posição
            m->primeiraLinha = novaLinha; //cria essa linha
        } 
        else {
            linhaAnterior->proxLinha = novaLinha;//se já existir  nova linha sera a proxima da linha anterior
        }
        linhaAtual = novaLinha;//linha atual recebe seu novo valor
    }

    Celula* ant = NULL;
    Celula* atual = linhaAtual->primeiraColuna;//agora a posição da coluna

    // Buscar a célula na coluna correta
    while (atual != NULL && atual->coluna < col) {
        ant = atual;
        atual = atual->prox;
    }

    // Se a célula já existir
    if (atual != NULL && atual->coluna == col) {
        if (val == 0) { // Excluir a célula se o valor for 0(matriz esparsa)
            if (ant == NULL) {//ant sendo null não tem uma coluna ainda
                linhaAtual->primeiraColuna = atual->prox;//adiciona primeira coluna
            } else {//ant não é nulo ja existe valor
                ant->prox = atual->prox; //coluna ficaa no prox
            }
            free(atual);//libera atual que foi alocado como aux,já que nao tem valor
        } 
        else {// se o valor da coluna não for 0(valor valido)
            atual->valor = val; //atual recebe o valor
        }
    } 
    else { // Criar uma nova célula,já que atual é nula,não existe ainda
        Celula* novaCelula = (Celula*) malloc(sizeof(Celula));//faz alocação
        if (novaCelula == NULL) return false; // Verificação de falha na alocação

        novaCelula->coluna = col;
        novaCelula->valor = val;
        novaCelula->prox = atual;

        if (ant == NULL) {//se anterior não existir começa do inicio
            linhaAtual->primeiraColuna = novaCelula;
        } 
        else {//anterior existe? coloca no proximo
            ant->prox = novaCelula;
        }
    }
    return 1;
}

float RetornaValor(MatrizEsparsa* m, int lin, int col) {
    if (lin < 0 || lin >= m->linhas || col < 0 || col >= m->colunas) {
        return 0; // Verificação de índices inválidos
    }

    Linha* linhaAtual = m->primeiraLinha;//aponta para primeira linha da matriz

    // Procurar a linha correta
    while (linhaAtual != NULL && linhaAtual->numero < lin) {
        linhaAtual = linhaAtual->proxLinha;
    }

    // Se a linha não for encontrada, retornar 0
    if (linhaAtual == NULL || linhaAtual->numero != lin) {
        return 0;
    }

    Celula* colunaAtual = linhaAtual->primeiraColuna;//aponta para primeira coluna

    // Procurar a coluna correta na linha
    while (colunaAtual != NULL && colunaAtual->coluna < col) {
        colunaAtual = colunaAtual->prox;
    }

    // Se a célula for encontrada, retornar o valor; caso contrário, retornar 0
    if (colunaAtual != NULL && colunaAtual->coluna == col) {//coluna valida?retorna
        return colunaAtual->valor;
    } 
    else {//coluna invalida? retorna 0
        return 0;
    }
}


void DesalocaMatriz(MatrizEsparsa* m) {
    if (m == NULL) return; // Se a matriz já for NULL, não há nada a fazer

    Linha* linhaAtual = m->primeiraLinha;

    // Percorrer todas as linhas da matriz
    while (linhaAtual != NULL) {
        Celula* colunaAtual = linhaAtual->primeiraColuna;//percorrendo cada coluna da linha

        // Percorrer todas as colunas na linha atual
        while (colunaAtual != NULL) {
            Celula* colunaParaLiberar = colunaAtual;//usa aux para liberar
            colunaAtual = colunaAtual->prox;
            free(colunaParaLiberar); // Liberar a memória de cada coluna da linha
        }

        Linha* linhaParaLiberar = linhaAtual;
        linhaAtual = linhaAtual->proxLinha;
        free(linhaParaLiberar); // Liberar a memória de cada linha da matriz
    }

    free(m); // Liberar a memória da estrutura da matriz esparsa
}


void ImprimeMatriz(MatrizEsparsa* m) {
    for (int i = 0; i < m->linhas; i++) {
        for (int j = 0; j < m->colunas; j++) {
            int valor = RetornaValor(m, i, j);
            //if (valor != 0) {
                printf("%d ", valor);
            }
            printf("\n");
        }
    }



