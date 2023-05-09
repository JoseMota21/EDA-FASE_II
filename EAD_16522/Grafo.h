#include <stdio.h>
#include <stdbool.h> 
#include "Transporte.h" 
#include "Cliente.h"

//Estrutura para vertices
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

//Estrutura para as arestas
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
 
//Criar vertices para os meios de transporte
int criarVertices(Grafo** g, Transporte* meios); 

//Lista os vertices na consola dos meios de transporte
void listarVertices(Grafo* g);  

//Criar arestas nos meios de transporte
int criarAresta(Grafo* g, int origem, int destino, float peso); 

//Criar grafo dos meios de transporte
Grafo* criarGrafo(); 

//Imprimir o grafo dos meios de transporte
void imprimirGrafo(Grafo* g); 