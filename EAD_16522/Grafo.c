#define _CRT_SECURE_NO_DEPRECATE 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Grafo.h"  

// Criar um novo vértice 
int criarVertice(Grafo* g, char novoId[], Transporte* meios) { 
 	
	//Alocar memória 
	Grafo novo = malloc(sizeof(struct registo1));
	
	if (novo != NULL)
	{
		strcpy(novo->vertice, novoId);
		novo->meios = meios;
		novo->adjacentes = NULL;
		novo->seguinte = *g;
		*g = novo;

		// Percorre a lista ligada de meios de transporte e imprimir os IDs
		Transporte* meio = novo->meios;
		while (meio != NULL) {
			printf("Meio de transporte existente: %d;%s\n", meio->codigo, meio->tipo); 
			meio = meio->seguinte;
		}
		return 1;

	} else {
		return 0;
	}
}


	
