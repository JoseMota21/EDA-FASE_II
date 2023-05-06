#define _CRT_SECURE_NO_DEPRECATE 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Grafo.h"  

// Criar um novo vértice em que cada meio de transporte representa um vértice (cria um vertice e associa aos meios de transporte)
int criarVertice(Grafo* g, Transporte* meios) { 

	//Alocar memória 
	Grafo novo = malloc(sizeof(struct registo1));
	
	if (novo != NULL) {
		novo->meios = meios;
		novo->adjacentes = NULL;
		novo->seguinte = *g;
		*g = novo;

		Transporte* meio = novo->meios;

		//Percorrer a lista ligada dos meios de transporte e imprime
		while (meio != NULL) {
			printf("Meio de transporte existente: %d;%s;%s\n", meio->codigo, meio->tipo, meio->geocodigo); 
			meio = meio->seguinte;
		}
		return 1;

	} else {
		return 0;
	}
} 


