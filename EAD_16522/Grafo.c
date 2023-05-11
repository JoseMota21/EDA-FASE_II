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

			if (ultimo == NULL) {
				(*g)->vertices = novo; 
			}
			else {
				while (ultimo->seguinte != NULL) {
					ultimo = ultimo->seguinte;
				}
				ultimo->seguinte = novo;
			}
		}
		VerticeID++;
		atual = atual->seguinte;
	}
	guardarVertices(g); 

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
		return NULL; //Caso haja erro
	}

	// Procurar o vértice de destino 
	while (atualDestino != NULL && atualDestino->ID != destino) {
		atualDestino = atualDestino->seguinte;
	}
	if (atualDestino == NULL) {
		printf("VERTICE DE DESTINO NAO ENCONTRADO\n");
		return NULL;	 // caso haja erro
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

//Guardar vertices em ficheiro txt 
void guardarVertices (Grafo** g) {
	// abrir o arquivo para escrita

	FILE* arquivo = fopen("Vertices.txt", "w");
	if (arquivo == NULL) {
		printf("Erro ao abrir o arquivo!\n");
		return;
	}
	 
	if (*g == NULL) {
		printf("Grafo vazio!\n");
		fclose(arquivo);
		return;
	} 

	// percorrer a lista de vértices e escrever no arquivo
	Vertice* atual = (*g)->vertices;

	while (atual != NULL) {
		fprintf(arquivo, "%d;%d;%s;%.2f;%s\n",atual->VerticeID, atual->ID, atual->Tipo, atual->bateria, atual->geocodigo);
		atual = atual->seguinte;
	}

	// fechar o arquivo
	fclose(arquivo);
} 

void dijkstra(Grafo* g, int origem) {
	int* distancia = malloc(g->numeroVertices * sizeof(int));
	int* visitado = malloc(g->numeroVertices * sizeof(int));
	int* predecessor = malloc(g->numeroVertices * sizeof(int));

	if (!distancia || !visitado || !predecessor) {
		printf("Erro de alocacao de memoria\n");
		return;
	}

	for (int i = 0; i < g->numeroVertices; i++) {
		distancia[i] = INT_MAX;
		visitado[i] = 0;
		predecessor[i] = -1;
	}

	distancia[origem] = 0;

	for (int count = 0; count < g->numeroVertices - 1; count++) {
		int u = menorDistancia(distancia, visitado, g->numeroVertices);
		visitado[u] = 1;
		Aresta* a = g->vertices[u].adjacencias;
		while (a != NULL) {
			int v = a->vertice_adjacente;
			if (!visitado[v] && distancia[u] + a->peso < distancia[v]) {
				distancia[v] = distancia[u] + a->peso;
				predecessor[v] = u;
			}
			a = a->proximo;
		}
	}

	printf("Distancias mais curtas da fonte %d:\n", origem);
	for (int i = 0; i < g->numeroVertices; i++) {
		printf("%d para %d: %d\n", origem, i, distancia[i]);
	}

	// imprimir caminho percorrido
	for (int i = 0; i < g->numeroVertices; i++) {
		if (i != origem && distancia[i] != INT_MAX) {
			printf("Caminho de %d para %d: ", origem, i);
			imprimirCaminho(predecessor, origem, i);
		}
	}

	free(distancia);
	free(visitado);
	free(predecessor);
}


void imprimirCaminho(int* predecessor, int origem, int destino) {
	int atual = destino;

	Pilha* pilha = criarPilha();
	empilhar (pilha, atual); // empilhar push (adiciono um elemento ao topo) // desempilhar (pop) remove o elemento que esta no topo da pilha
	while (atual != origem) {
		atual = predecessor[atual];
		empilhar(pilha, atual);
	}
	printf("Caminho percorrido: ");
	while (!estaVazia(pilha)) {
		int v = desempilhar(pilha);
		printf("%d ", v);
	}
	printf("\n");
}


Pilha* criarPilha() {
	Pilha* pilha = (Pilha*)malloc(sizeof(Pilha));
	pilha->topo = NULL;
	pilha->tamanho = 0;
	return pilha;
}


int menorDistancia(int* distancia, int* visitado, int numeroVertices) {
	int min = INT_MAX, indiceMin;

	for (int i = 0; i < numeroVertices; i++) {
		if (visitado[i] == 0 && distancia[i] <= min) {
			min = distancia[i];
			indiceMin = i;
		}
	} 

	return indiceMin;
}

