#define _CRT_SECURE_NO_DEPRECATE 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Grafo.h"  


// Criar novos vértices em que cada meio de transporte representa um vértice
int criarVertices(Grafo** g, Transporte* meios) {

	//Variável para ID do vertice
	int VerticeID = 1; 

	Transporte* atual = meios; 

	//Percorre a lista dos meios de transporte
	while (atual != NULL) {
		
		Vertice* novo = malloc(sizeof(Vertice));  

		// Preencher os dados do vértice
		strcpy(novo->geocodigo, atual->geocodigo);
		strcpy(novo->Tipo, atual->tipo);
		novo->ID = atual->codigo;
		novo->bateria = atual->bateria;
		novo->meios = atual;
		novo->VerticeID = VerticeID; 

		novo->clientes = NULL;
		novo->seguinte = NULL;

		// Criar uma nova estrutura Grafo se ainda não existir
		if (*g == NULL) {
			*g = malloc(sizeof(Grafo));
			if (*g == NULL) {
				free(novo);
				return 0;
			}
			(*g)->vertices = novo;
		}
		else {
			novo->seguinte = (*g)->vertices;
			(*g)->vertices = novo;
		}

		VerticeID++; 

		// Avançar para o próximo transporte
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
