#ifndef automato_h
#define automato_h

#include "matriz.h" 

typedef struct automatocelular AutomatoCelular;

AutomatoCelular *alocarreticulado (int d);
void desalocarReticulado(AutomatoCelular* autcel);
void LeituraReticulado(AutomatoCelular *autcel);
void imprimeReticulado(AutomatoCelular *autcel);
void evoluirReticulado(AutomatoCelular *autcel, int geracoes);
void confereReticulado(AutomatoCelular *autcel, MatrizEsparsa *matrizaux);


#endif