#ifndef matriz_h
#define matriz_h

typedef struct celula {
    float valor;
    int coluna;
    struct celula* prox;
} Celula;

typedef struct linha {
    int numero;  // Número da linha
    Celula* primeiraColuna;  // Ponteiro para a lista encadeada de colunas
    struct linha* proxLinha;  // Próxima linha
} Linha;

typedef struct {
    int linhas;  // Número de linhas (para referência)
    int colunas;  // Número de colunas (para referência)
    Linha* primeiraLinha;  // Ponteiro para a lista encadeada de linhas
} MatrizEsparsa;

//CADA LINHA TEM UMA CELULA COM VALOR E COLUNA E CADA MATRIZ TEM UMA LINHA COM SUAS RESPECTIVAS CELULAS

MatrizEsparsa* AlocarMatriz(int d);
int InsereValor(MatrizEsparsa* m, int lin, int col, float val);
float RetornaValor(MatrizEsparsa* m, int lin, int col);
void DesalocaMatriz(MatrizEsparsa* m);
void ImprimeMatriz(MatrizEsparsa* m);

//obs:cada linha é armazenada como uma litsa encadeada

#endif