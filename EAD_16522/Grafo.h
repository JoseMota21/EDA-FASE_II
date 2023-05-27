#include <stdio.h>
#include <stdbool.h> 
#include "Transporte.h" 
#include <float.h>
#include "Cliente.h" 

//Estrutura para os vértices
typedef struct Vertice {
    char geocodigo[100];
    int ID;             
    int VerticeID;
    float bateria;       
    char Tipo[20];

    Transporte* meios; 

    struct Aresta* adjacencias; 
    struct Vertice* seguinte;
} Vertice;

//Estrutura para as arestas 
typedef struct Aresta {
    int vertice_adjacente; 
    float peso;
    struct Aresta* proximo;
} Aresta;

//Estrutura do grafo
typedef struct Grafo {
    int numeroVertices;
    bool** visitados;

    float* distancias;  

    Transporte* meios; 

    struct Aresta*** matrizadj;     
    struct Vertice* vertices;
} Grafo; 


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

bool grafoCompleto(Grafo* g); 

//Percurso minimo para percurrer todos os vértices 
void recolherTrotinetes(Grafo* g, int origem);   

Transporte* encontrarTransportePorVertice(Grafo* g, int verticeID); 
