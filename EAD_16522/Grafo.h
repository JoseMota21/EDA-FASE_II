#include <stdio.h>
#include <stdbool.h> 
#include "Transporte.h" 
#include "Cliente.h"

//Estrutura para a definição da matriz de adjacencia 
typedef struct adjacente
{
    char vertice[100]; // geocódigo what3words
    float peso;
    struct adjacente* seguinte;
} Adjacente;

//Estrutura para definição de vertices 
typedef struct vertice {
    float lat; 
    float lng; 
    char vertice[100];
    Adjacente adjacentes;
    Cliente* clientes; 
    Transporte* meios; 

    struct vertice* seguinte; 
} Vertice;

//Estrutura para grafo 
typedef struct grafo {
    Vertice* vertices; 
} Grafo;

//Criar vertices 
int criarVertice(Grafo* g, Transporte* meios); 

