#include <stdio.h>
#include <stdbool.h> 
#include "Transporte.h" 
#include "Cliente.h" 

#define NUMEROVERTICE 3

//Estrutura para vertices
typedef struct vertice {
    char geocodigo[100]; // What3Words
    int ID;              // ID do meio de transporte
    int VerticeID;
    float bateria;       // Bateria do meio de transporte
    char Tipo[20];

    Cliente* clientes;
    Transporte* meios;

    struct aresta* adjacencias; // Lista de adjacências
    struct vertice* seguinte;
} Vertice;

//Estrutura para as arestas
typedef struct Aresta {
    int vertice_adjacente;
    float peso;
    struct Aresta* proximo;
} Aresta;

//Estrutura para grafo
typedef struct grafo {

    int numeroVertices;

    Aresta* arestas;
    Vertice* vertices;
} Grafo; 

typedef struct reg {
    int vertice;
    struct reg* proximo;
} *Pilha;

//Guardar vertices em ficheiro txt
void guardarVertices(Grafo** g);

//Criar vertices para os meios de transporte
Vertice* criarVertices(Grafo** g, Transporte* meios);

//Lista os vertices na consola dos meios de transporte
Vertice* listarVertices(Grafo* g);

//Criar arestas nos meios de transporte
Aresta* criarAresta(Grafo* g, int origem, int destino, float peso);

//Criar grafo dos meios de transporte
Grafo* criarGrafo();

//Imprimir o grafo dos meios de transporte
void imprimirGrafo(Grafo* g);

//Guardar grafo em ficheiro txt
Grafo* guardarGrafo(Grafo* g);

//Percorrer o grafo todo 
void dijkstra(Grafo* g); 

Pilha push(Pilha pilha, int vertice); 

Pilha pop(Pilha pilha); 

