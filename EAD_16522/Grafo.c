#define _CRT_SECURE_NO_DEPRECATE 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Grafo.h"  

// Criar um novo v�rtice em que cada meio de transporte representa um v�rtice (cria um vertice e associa aos meios de transporte)
int criarVertice(Grafo* g, Transporte* meios) { 

	// Alocar mem�ria para um novo v�rtice
	Vertice* novo = malloc(sizeof(Vertice)); 
	
	// Preencher os dados do v�rtice
	strcpy(novo->vertice, meios->geocodigo);
	novo->meios = meios;
	//novo->adjacentes = NULL;
	novo->clientes = NULL;
	novo->seguinte = NULL;

	// Criar uma nova estrutura Grafo se ainda n�o existir
	if (g == NULL) {
		g = malloc(sizeof(Grafo));
		if (g == NULL) {
			free(novo);
			return 0;
		}
		g->vertices = novo;
	}
	else {
		novo->seguinte = g->vertices;
		g->vertices = novo; 
	}

	// Percorrer a lista ligada dos meios de transporte e imprimir
	Transporte* meio = novo->meios;
	while (meio != NULL) {
		printf("OS MEIOS DE TRANSPORTES SAO: %d;%s;%s\n", meio->codigo, meio->tipo, meio->geocodigo);
		meio = meio->seguinte;
	}
	return 1;
}
