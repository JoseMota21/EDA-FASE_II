#include <stdio.h>
#include <stdbool.h> 
#include "Transporte.h" 
#include <float.h>
#include "Cliente.h" 

#define MAX 100
#define INFINITY_FLOAT FLT_MAX 

typedef struct Vertice {
    char geocodigo[100]; // What3Words
    int ID;              // ID do meio de transporte
    int VerticeID;
    float bateria;       // Bateria do meio de transporte
    char Tipo[20];

    Transporte* meios;

    float distancia; // utilizado para o Dijkstra
    bool visitado;
    int anterior;

    struct Aresta* adjacencias; // Lista de adjacências
    struct Vertice* seguinte;
} Vertice;

typedef struct Aresta {
    int vertice_adjacente;
    float peso;
    struct Aresta* proximo;
} Aresta;

typedef struct Grafo {
    int numeroVertices;
    bool** visitados;
    bool** matrizad;
    struct Aresta** matrizadj; // Matriz de adjacência
    struct Vertice* vertices;
} Grafo;

void travessiaProfundidade(Grafo* g); 

//Guardar vertices em ficheiro txt
void guardarVertices(Grafo** g);

//Criar vertices para os meios de transporte
Vertice* criarVertices(Grafo** g, Transporte* meios);

//Lista os vertices na consola dos meios de transporte
Vertice* listarVertices(Grafo* g);

//Criar arestas nos meios de transporte
Aresta* criarAresta(Grafo* g, int origem, int destino, float peso);

//Criar grafo dos meios de transporte
Grafo* criarGrafo(int numeroVertices);

//Imprimir o grafo dos meios de transporte
void imprimirGrafo(Grafo* g);

//Guardar grafo em ficheiro txt
Grafo* guardarGrafo(Grafo* g); 
void imprimirListaAdjacencias(Grafo* g);  

Vertice* encontrarVertice(Grafo* g, int id); 

