#define _CRT_SECURE_NO_DEPRECATE 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Grafo.h"  

//Função para criar aresta 
int criarAresta(Grafo* g, char origem[], char destino[], float peso) {

	//Vertice* vertOrigem = procurarVertice (g, origem);
	
	Adjacente* novo = malloc(sizeof(Adjacente)); 

	if (!novo) {
		return 0; 
	}

	//novo->vertice = procurarVertice(g, destino);
	if (!novo->vertice) {
		// O vértice de destino não existe no grafo
		free(novo);
		return 0;
	}

	novo->peso = peso; 
	//novo->proximo = vertOrigem->adjacente; 
	//vertOrigem->adjacente = novo; 

	return 1; 
} 

Vertice* criarVertice(int novoID, float latitude, float longitude) {

	Vertice* novo = (Vertice*) malloc(sizeof(Vertice)); 

	if (novo != NULL) {
		novo->ID = novoID; 
		novo->latitude = latitude; 
		novo->longitude = longitude; 

		novo->proximo = NULL; 
		novo->adjacente = NULL; 
	}

	return novo; 
}

Grafo* criarGrafo() {


	Grafo* novo = calloc(1, sizeof(Grafo)); 
	//Grafo* novo = malloc(sizeof(Grafo)); 

	if (novo != NULL) {
		novo->num_vertices = 0; 
		novo->primeiro = NULL; 
	} 

	return novo; 
}

int adicionarVertice(Grafo* g, int novoID, float latitude, float longitude) {

	Vertice* novo = criarVertice(novoID, latitude, longitude); 

	if (novo == NULL) {
		return 0; 
	}

	novo->proximo = g->primeiro; 
	g->num_vertices++; 

	return 1; 

}
