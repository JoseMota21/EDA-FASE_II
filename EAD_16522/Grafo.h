#include <stdio.h>
#include <stdbool.h> 
#include "Transporte.h" 
#include "Cliente.h"

//Estrutura para a definição da matriz de adjacencia 
typedef struct adjacente {

    //char vertice[100]; // geocódigo what3words
    float peso;
    int IDvertices; 
    struct adjacente* seguinte;

} MatrizAdjacente;

//Estrutura para definição de vertices 
typedef struct vertice {
    float lat; //Para converter para coordenadas 
    float lng; //Para converter para coordenadas 
    char geocodigo[100];// What3Words 
    int ID; //ID do meio de transporte 
    int VerticeID; 
    float bateria; // Bateria do meio de transporte 
    char Tipo[80]; 

    int visitado; 

   MatrizAdjacente* adjacentes;
    Cliente* clientes; 
    Transporte* meios; 

    struct vertice* seguinte; 
} Vertice;

//Estrutura para grafo 
typedef struct grafo {
    Vertice* vertices; 
} Grafo;

typedef struct Aresta {
    Vertice* vertice_adjacente;
    float peso;
    struct Aresta* proximo;
} Aresta; 

//Criar vertices 
int criarVertices(Grafo** g, Transporte* meios); 

//Lista os vertices na consola 
void listarVertices(Grafo* g);  

//Criar aresta 
int criarAresta(Grafo* g, char vOrigem[], char vDestino[], float peso); 

void imprimirGrafo(Grafo* g); 

