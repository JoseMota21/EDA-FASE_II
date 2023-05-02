#define _CRT_SECURE_NO_DEPRECATE 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Grafo.h"  

//Criar um vertice e adiciona-lo ao grafo 
int criarVertice(Grafo* g, char novoId[]) {

	//Alocar a capacidade necessária de memoria e indica o tamanho de espaço de memoria a ser alocado
	Grafo novo = malloc(sizeof(struct registo1)); 

	if (novo != NULL) {
		strcpy(novo->vertice, novoId);
		novo->transporte = NULL;
		novo->seguinte = *g;
		*g = novo;

		return (1); //Vertice inserido com sucesso 
	}

	else return (0); 
}

//Verifica se exixte o vertice no grafo 
int existeVertice(Grafo g, char vertice[]) {

	while (g != NULL){ 
		if (strcmp(g->vertice, vertice) == 0) {
			return (1);
		}
		else g = g->seguinte; 
	}

	return (0); 
}

//Função para criar arestas 
int criarAresta(Grafo g, char origem[], char destino[], float peso) {
	Adjacente novo; 

	if (existeVertice(g, origem) && existeVertice(g, destino)) {
		while (strcmp(g->vertice, origem) != 0) g = g->seguinte;

		novo = malloc(sizeof(struct registo1));

		if (novo != NULL) {
			strcpy(novo->vertice, destino);
			novo->peso = peso;
			novo->seguinte = g->adjacente;
			g->adjacente = novo;

			return (1);
		}

		else return (0);
	}
	else return (0); 
}

//Listar os vértices adjacentes 
void listarAdjacentes(Grafo g, char vertice[]) {

	Adjacente aux; 

	if (existeVertice(g, vertice)) {
		while (strcmp(g->vertice, vertice) != 0) g = g->seguinte; 
		aux = g->adjacente; 
		while (aux != NULL){
			printf("ADJENTES: %s Peso: %.2f\n", aux->vertice, aux->peso); 

			aux = aux->seguinte; 
		}
	}
}

// Inserir meio de transporte na localização com geocódigo
int inserirMeio(Grafo g, char geocodigo[], int ID)
{
	while ((g != NULL) && (strcmp(g->vertice, ID) != 0))
		g = g->seguinte;
	if (g == NULL) return(0);
	else {
		Transporte novo = malloc(sizeof(struct registo3));
		novo->ID = ID;
		novo->seguinte = g->transporte;
		g->transporte = novo;
		return(1);
	}
}

// Listar os códigos dos meios de transporte presente numa determinada localização passada por parâmetro
void listarMeios(Grafo g, char geocodigo[])
{
	while ((g != NULL) && (strcmp(g->vertice, geocodigo) != 0))
		g = g->seguinte;
	if (g != NULL)
	{
		Transporte aux = g->transporte;
		if (aux == NULL) printf("sem meios de transporte\n");
		else while (aux != NULL)
		{
			printf("Codigo meio: %d\n", aux->ID);
			aux = aux->seguinte;
		}
	}
	else printf("geocodigo inexistente\n");
}

