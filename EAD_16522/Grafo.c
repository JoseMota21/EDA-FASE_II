#define _CRT_SECURE_NO_DEPRECATE 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Grafo.h"  

// Criar novos v�rtices em que cada meio de transporte representa um v�rtice
int criarVertices(Grafo** g, Transporte* meios) {

	//Vari�vel para ID do vertice
	int VerticeID = 1; 

	Transporte* atual = meios; 

	//Percorre a lista dos meios de transporte
	while (atual != NULL) {
		
		Vertice* novo = malloc(sizeof(Vertice));  

		// Preencher os dados do v�rtice
		strcpy(novo->geocodigo, atual->geocodigo);
		strcpy(novo->Tipo, atual->tipo);
		novo->ID = atual->codigo;
		novo->bateria = atual->bateria;
		novo->meios = atual;
		novo->VerticeID = VerticeID; 

		novo->clientes = NULL;
		novo->seguinte = NULL;

		// Criar uma nova estrutura Grafo se ainda n�o existir
		if (*g == NULL) {
			*g = malloc(sizeof(Grafo));
			if (*g == NULL) {
				free(novo);
				return 0;
			}
			(*g)->vertices = novo;
		}
		else {

			Vertice* ultimo = (*g)->vertices; 

			while (ultimo->seguinte != NULL){
				ultimo = ultimo->seguinte; 

			}

			ultimo->seguinte = novo; 

		}

		VerticeID++; 

		// Avan�ar para o pr�ximo transporte
		atual = atual->seguinte;
	}

	return 1;
}

//Listar na consola os vertices que representam os meios de transporte 
void listarVertices(Grafo* g) {
	Vertice* vertice = g->vertices; 

	while (vertice != NULL) {

		printf("VERTICES: %d, %d, %s, %.2f, %s\n",vertice->VerticeID, vertice->ID, vertice->Tipo, vertice->bateria, vertice->geocodigo); 
		
		vertice = vertice->seguinte; 

	}

}

/// Em constru��o 

//Encontrar Vertice 
Vertice* encontrarVertice(Grafo* g, int ID) {

	Vertice* atual = g->vertices; 

	// Percorre a lista de v�rtices
	while (atual != NULL) {
		// Se encontrar o v�rtice com o ID correto, retorna o ponteiro para ele
		if (atual->ID == ID) {
			return atual;
		}
		atual = atual->seguinte;
	}
	// Se n�o encontrar, retorna NULL
	return NULL;
}

// Criar uma nova aresta
int criarAresta(Grafo* g, char vOrigem[], char vDestino[], float peso) {
	

	Vertice* origem = encontrarVertice(g, vOrigem);
	Vertice* destino = encontrarVertice(g, vDestino);

	if (origem != NULL && destino != NULL) {
		Aresta* novaAresta = malloc(sizeof(Aresta)); 

		
		if (novaAresta != NULL) {
			novaAresta->peso = peso;
			novaAresta->vertice_adjacente = destino; 
			novaAresta->proximo = origem->adjacentes;
			origem->adjacentes = novaAresta;
			return 1;
		}
	}

	return 0;
}

void imprimirGrafo(Grafo* g) {

	Vertice* atual = g->vertices;
	
	printf("Grafo:\n");

	// Percorre todos os v�rtices do grafo
	while (atual != NULL) {

		// Imprime o v�rtice
		printf("V�rtice %s:\n", atual->geocodigo);

		// Percorre todas as arestas do v�rtice
		Aresta* a = atual->adjacentes;

		while (a != NULL) {
			printf("    Aresta para v�rtice %s com peso %.2f\n", a->vertice_adjacente->geocodigo, a->peso); 
			a = a->proximo;
		}

		atual = atual->seguinte;
	}
}





// Vai ser util para quando recolher o camiao 
//Visita cada vertice e ajacentes 
void dfs(Grafo* g, Vertice* v) { 
	v->visitado = 1;

	printf("Visitando v�rtice %s\n", v->geocodigo);
	Aresta* adj = v->adjacentes;
	while (adj != NULL) {
		Vertice* adj_v = adj->vertice_adjacente;
		if (adj_v->visitado == 0) {
			dfs(g, adj_v);
		}
		adj = adj->proximo;
	}
}

//Encontra o vertice com o geocodigo 
void TravessiaProfundidade(Grafo* g, char geocodigo[]) {

	Vertice* v = encontrarVertice(g, geocodigo); 
	if (v != NULL) {
		dfs(g, v);
	}
}
