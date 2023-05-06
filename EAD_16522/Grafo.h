#include <stdio.h>
#include <stdbool.h> 
#include "Transporte.h" 

// Representação de um grafo orientado e pesado
typedef struct registo2
{
    char vertice[100]; // geocódigo what3words
    float peso;
    struct registo2* seguinte;
} *Adjacente;

typedef struct registo1 {
    char vertice[100]; // geocódigo what3words
    Adjacente adjacentes;
    Transporte* meios; // Lista ligada com os códigos dos meios de transporte existente
    // neste geocódigo
    struct registo1* seguinte;
} *Grafo; 


//Criar vertices 
int criarVertice(Grafo* g, char novoId[]); 

