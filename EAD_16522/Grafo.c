#define _CRT_SECURE_NO_DEPRECATE 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Grafo.h"  

//Criar vertices lista ligada de vertices 
Vertice* criarVertices(Grafo** g, Transporte* meios) {

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
		//novo->clientes = NULL;
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
	return atual;
} 

//Criar Grafo  lista ligada 
Grafo* criarGrafo() {
	Grafo* g = malloc(sizeof(Grafo));
	if (g != NULL) {
		g->vertices = NULL;
	}
	return g;
}

//Criar arestas lista ligada simples 
Aresta* criarAresta(Grafo* g, int origem, int destino, float peso) {

	Vertice* atualOrigem = g->vertices;
	Vertice* atualDestino = g->vertices;

	// Procurar o vértice de origem
	while (atualOrigem != NULL && atualOrigem->ID != origem) {
		atualOrigem = atualOrigem->seguinte;
	}
	if (atualOrigem == NULL) {

		printf("VERTICE ORIGEM NAO ENCONTRADO.\n");
		return -1; //Caso haja erro
	}

	// Procurar o vértice de destino 
	while (atualDestino != NULL && atualDestino->ID != destino) {
		atualDestino = atualDestino->seguinte;
	}
	if (atualDestino == NULL) {
		printf("VERTICE DE DESTINO NAO ENCONTRADO\n");
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

	guardarGrafo(g); 

	return novaAresta; // Função executada com sucesso
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
Vertice* listarVertices(Grafo* g) {

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

	return vertice; 

}

//Guardar grafo em ficheiro txt 
Grafo* guardarGrafo(Grafo* g) {

	Vertice* atualVertice = g->vertices;
	Aresta* atualAresta;


	//Abrir o arquivo para escrita 
	FILE* ficheiroGrafo = fopen("Grafo.txt", "w");

	if (ficheiroGrafo == NULL) {
		printf("Erro ao criar arquivo!\n");
		return 0;
	}

	//Escrever os dados formatados do grafo no arquivo
	fprintf(ficheiroGrafo, "ORIGEM;DESTINO;DISTANCIA\n");

	while (atualVertice != NULL) {
		atualAresta = atualVertice->adjacencias;

		while (atualAresta != NULL) {
			fprintf(ficheiroGrafo, "%d;%d;%.2f\n", atualVertice->ID, atualAresta->vertice_adjacente, atualAresta->peso);
			atualAresta = atualAresta->proximo;
		}

		atualVertice = atualVertice->seguinte;
	}

	//Fechar o arquivo
	fclose(ficheiroGrafo);
	return 1; 
} 

void adicionarVertice(Grafo* g, int id, char tipo[], float bateria, char geocodigo[]) {

	Vertice* novoVertice = malloc(sizeof(Vertice));

	novoVertice->ID = id;
	strcpy(novoVertice->Tipo, tipo);
	novoVertice->bateria = bateria;
	strcpy(novoVertice->geocodigo, geocodigo);
	novoVertice->adjacencias = NULL;
	novoVertice->seguinte = NULL;

	// Verificar se o grafo está vazio
	if (g->vertices == NULL) {
		g->vertices = novoVertice;
	}
	else {
		Vertice* atual = g->vertices;
		while (atual->seguinte != NULL) {
			atual = atual->seguinte;
		}
		atual->seguinte = novoVertice;
	}
}
