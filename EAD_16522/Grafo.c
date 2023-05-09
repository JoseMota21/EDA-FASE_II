#define _CRT_SECURE_NO_DEPRECATE 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Grafo.h"  

//Criar vertices 
int criarVertices(Grafo** g, Transporte* meios) {

	int VerticeID = 1;
	Transporte* atual = meios;

	while (atual != NULL) {

		Vertice* novo = malloc(sizeof(Vertice));

		strcpy(novo->geocodigo, atual->geocodigo);
		strcpy(novo->Tipo, atual->tipo);
		novo->ID = atual->codigo;

		novo->bateria = atual->bateria;
		novo->meios = atual;
		novo->VerticeID = VerticeID;
		novo->clientes = NULL;
		novo->seguinte = NULL;
		novo->adjacencias = NULL; // inicializar as adjacências como NULL


		if (*g == NULL) {
			*g = criarGrafo();
			if (*g == NULL) {
				free(novo);
				return 0;
			}
			(*g)->vertices = novo;
		}
		else {
			Vertice* ultimo = (*g)->vertices;
			while (ultimo->seguinte != NULL) {
				ultimo = ultimo->seguinte;
			}
			ultimo->seguinte = novo;
		}
		VerticeID++;
		atual = atual->seguinte;
	}
	return 1;
}

//Criar Grafo 
Grafo* criarGrafo() {
	Grafo* g = malloc(sizeof(Grafo));
	if (g != NULL) {
		g->vertices = NULL;
	}
	return g;
}

//Criar arestas
int criarAresta(Grafo* g, int origem, int destino, float peso) {
	Vertice* atualOrigem = g->vertices;
	Vertice* atualDestino = g->vertices;

	// Procurar o vértice de origem
	while (atualOrigem != NULL && atualOrigem->ID != origem) {
		atualOrigem = atualOrigem->seguinte;
	}
	if (atualOrigem == NULL) {

		printf("Erro: vértice de origem não encontrado.\n");
		return -1; //Caso haja erro
	}

	// Procurar o vértice de destino
	while (atualDestino != NULL && atualDestino->ID != destino) {
		atualDestino = atualDestino->seguinte;
	}
	if (atualDestino == NULL) {
		printf("Erro: vértice de destino não encontrado.\n");
		return -1; // caso haja erro
	}

	// Adicionar a aresta
	Aresta* novaAresta = malloc(sizeof(Aresta));
	novaAresta->vertice_adjacente = atualDestino->ID; 
	novaAresta->peso = peso;
	novaAresta->proximo = NULL;

	if (atualOrigem->adjacencias == NULL) {
		atualOrigem->adjacencias = novaAresta;
	}
	else {
		Aresta* atual = atualOrigem->adjacencias;
		while (atual->proximo != NULL) {
			atual = atual->proximo;
		}
		atual->proximo = novaAresta;
	}

	return 0; // Função executada com sucesso
}

//Imprimir na consola o grafo
void imprimirGrafo(Grafo* g) {

	Vertice* atualVertice = g->vertices;

	printf("------------------------- GRAFO-------------------\n"); 
	printf("\n"); 

	//Cabeçalho da tabela
	printf("|%-5s | %-5s | %-10s|\n", "ORIGEM", "DESTINO", "DISTANCIA"); 

	//Percorrer os vertces
	while (atualVertice != NULL) {
				 
		Aresta* atualAresta = atualVertice->adjacencias; 

		//Percorrer as arestas 
		while (atualAresta != NULL) {

			printf("|%-5d | %-5d | %-10.2f|\n", atualVertice->ID, atualAresta->vertice_adjacente, atualAresta->peso);
			atualAresta = atualAresta->proximo;
		}

		atualVertice = atualVertice->seguinte; 
	}
} 

//Listar na consola os vertices que representam os meios de transporte 
void listarVertices(Grafo* g) {

	Vertice* vertice = g->vertices; //primeiro vertice  

	printf("------------------------------------- VERTICES--------------------------------\n");
	printf("\n");

	//Cabeçalho da tabela
	printf("|%-12s | %-5s | %-10s | %-10s | %-30s|\n", "ID VERTICE", "ID", "TIPO", "BATERIA", "LOCALIZACAO");

	while (vertice != NULL) {

		printf("|%-12d | %-5d | %-10s | %-10.2f | %-30s|\n", vertice->VerticeID, vertice->ID, vertice->Tipo, vertice->bateria, vertice->geocodigo);

		vertice = vertice->seguinte;
	}

	printf("\n");

}
