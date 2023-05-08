#include <stdio.h>
#include <stdbool.h> 
#include "Transporte.h" 
#include "Cliente.h"


typedef struct vertice {
    char geocodigo[100]; // What3Words
    int ID; // ID do meio de transporte 
    int VerticeID;
    float bateria; // Bateria do meio de transporte
    char Tipo[20];

    Cliente* clientes; 
    Transporte* meios;
    
    struct aresta* adjacencias; // Lista de adjacências
    struct vertice* seguinte;
} Vertice;


typedef struct Aresta {
    int vertice_adjacente;
    //int origem; 
   // int destino; 
    float peso;
    struct Aresta* proximo;
} Aresta;


//Estrutura para grafo 
typedef struct grafo {
    
    int numeroVertices; 

    Aresta* arestas; 
    Vertice* vertices;  
} Grafo;
 
//Criar vertices 
int criarVertices(Grafo** g, Transporte* meios); 

//Lista os vertices na consola 
void listarVertices(Grafo* g); 

void criarArestas(Grafo* g); 

void imprimirArestas(Grafo* g); 

Grafo* criarGrafo(); 

