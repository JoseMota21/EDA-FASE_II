#include <stdio.h>
#include <stdbool.h> 
#include "Transporte.h"

typedef struct vertice {

	int ID; //ID do meio de transporte
	float latitude; 
	float longitude; 
	struct vertice* proximo; 
	struct adjacente* adjacente; // lista ligada de vértices adjacentes 
} Vertice; 

typedef struct adjacente {
	float peso; // Peso da aresta

	Vertice* vertice; // vértice adjacente 
	struct adjacente* proximo;

} Adjacente;

typedef struct grafo {
	int num_vertices;
	Vertice* primeiro;
} Grafo;


int criarAresta(Grafo* g, char origem[], char destino[], float peso); 

Vertice* criarVertice(int novoID, float latitude, float longitude); 

Grafo* criarGrafo(); 

int adicionarVertice(Grafo* g, int novoID, float latitude, float longitude); 