#include <stdio.h>
#include <stdbool.h> 
#include "Transporte.h" 

// Representa��o de um grafo orientado e pesado
typedef struct registo2
{
    char vertice[100]; // geoc�digo what3words
    float peso;
    struct registo2* seguinte;
} *Adjacente;

typedef struct registo1 {
    char vertice[100]; // geoc�digo what3words
    Adjacente adjacentes;
    Transporte* meios; // Lista ligada com os c�digos dos meios de transporte existente
    // neste geoc�digo
    struct registo1* seguinte;
} *Grafo; 


//Criar vertices 
int criarVertice(Grafo* g, char novoId[]); 

