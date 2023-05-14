#define _CRT_SECURE_NO_DEPRECATE 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Grafo.h"  

//Criar v�rtices atraves da lista ligado dos meios de transporte 
//cada meio de transporte represente um v�rtice (1 ponto de recolha) 
Vertice* criarVertices(Grafo** g, Transporte* meios) {

	//Identifica��o do v�rtice 
	int VerticeID = 1;
	
	//Lista ligado dos meios de transportes 
	Transporte* atual = meios;

	//Percorre todos os meios de transporte at� ao fim 
	while (atual != NULL) {

		//Aloca a mem�ria 
		Vertice* novo = malloc(sizeof(Vertice));

		//O v�rtice � criado para cada meio de transporte 
		// Copia o campo do meio de transporte para os v�rtices 
		strcpy(novo->geocodigo, atual->geocodigo); 
		strcpy(novo->Tipo, atual->tipo);
		novo->ID = atual->codigo;
		novo->bateria = atual->bateria;
		novo->meios = atual;
		novo->VerticeID = VerticeID;
		novo->seguinte = NULL;
		novo->adjacencias = NULL; 

		//Se o grafo for NULL (VAZIO) 
		if (*g == NULL) {
			//Se o grafo n�o exister cria um grafo
			*g = criarGrafo();
			//Se a cria��o do grafo falhar por algum motivo
			//o apontador do v�rtice � libertado
			if (*g == NULL) {
				free(novo);
				return 0;
			}
			(*g)->vertices = novo;
		}
		else {
			//Criado um apontado para o �ltimo v�rtice da lista ligada dos v�rtices 
			Vertice* ultimo = (*g)->vertices;

			//Se o ultimo vertice for NULL 
			if (ultimo == NULL) {
				//O primeiro vertice � inserido como o primeiro da lista 
				(*g)->vertices = novo;
			}
			else {
				//Se j� exista v�rtices na lista, o ultimo aponta para o seguinte at� ser NULL
				while (ultimo->seguinte != NULL) {
					//O novo v�rtice � adicionado no fim da lista 
					ultimo = ultimo->seguinte;
				}
				ultimo->seguinte = novo;
			}
		}
		//Incrementa a identa��o dos v�rtices  
		VerticeID++;
		//Aponta para o pr�ximo meio de transporte da lista dos meios de transporte 
		atual = atual->seguinte;
	}
	//Guardar os v�rtices em um ficheiro 
	guardarVertices(g);

	return (*g)->vertices;
}

//Criar grafo 
Grafo* criarGrafo() {

	//Aloca mem�ria para a estrutura 
	Grafo* g = malloc(sizeof(Grafo));   

	//Se for null return null (g ser� NULL), o que significa que houve problema na aloca��o da mem�ria 
	if (g != NULL) { 

		//Se for diferente de null inicia os v�rtices como NULL 
		g->vertices = NULL;
	}
	return g;
}

//Criar arestas lista ligada simples 
Aresta* criarAresta(Grafo* g, int origem, int destino, float peso) {

	Vertice* atualOrigem = g->vertices;
	Vertice* atualDestino = g->vertices;

	// Procurar o v�rtice de origem
	while (atualOrigem != NULL && atualOrigem->ID != origem) {
		atualOrigem = atualOrigem->seguinte;
	}
	if (atualOrigem == NULL) {

		printf("VERTICE ORIGEM NAO ENCONTRADO.\n");
		return NULL; //Caso haja erro
	}

	// Procurar o v�rtice de destino 
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

	return novaAresta; // Fun��o executada com sucesso
}

//Imprimir na consola o grafo
void imprimirGrafo(Grafo* g) {

	Vertice* atualVertice = g->vertices;

	printf("------------------------- GRAFO-------------------\n"); 
	printf("\n");

	//Cabe�alho da tabela
	printf("|%-5s | %-5s | %-10s|\n", "ORIGEM", "DESTINO", "DISTANCIA"); 

	//Percorrer os vertices at� ao fim 
	while (atualVertice != NULL) {
		
		Aresta* atualAresta = atualVertice->adjacencias; 

		//Percorrer as arestas at� ao fim 
		while (atualAresta != NULL) {

			//Imprime o vertice de origem, o vertice de destino e o peso entre ambos 
			printf("|%-5d | %-5d | %-10.2f|\n", atualVertice->ID, atualAresta->vertice_adjacente, atualAresta->peso); 

			//Passa para a pr�xima aresta 
			atualAresta = atualAresta->proximo;
		}

		//Passa para o pr�ximo v�rtice 
		atualVertice = atualVertice->seguinte; 
	}
 
} 

//Listar na consola os vertices que representam os meios de transporte 
Vertice* listarVertices(Grafo* g) {

	//Se o grafo for NULL informa o utilizador 
	if (g == NULL) {
		printf("GRAFO VAZIO\n"); 
		
		return NULL; 
	}

	// primeiro vertice
	Vertice* vertice = g->vertices; 

	printf("------------------------------------- VERTICES--------------------------------\n");
	printf("\n");

	//Cabe�alho da tabela
	printf("|%-12s | %-5s | %-10s | %-10s | %-30s|\n", "ID VERTICE", "ID", "TIPO", "BATERIA", "LOCALIZACAO");

	//Percorre a lista dos v�rtices 
	while (vertice != NULL) {

		//Imprime na consola a informa��o do ID do v�rtice, ID do meio de transporte, o tipo de transporte, bateria e a sua localiza��o 
		printf("|%-12d | %-5d | %-10s | %-10.2f | %-30s|\n", vertice->VerticeID, vertice->ID, vertice->Tipo, vertice->bateria, vertice->geocodigo);

		//Passa para o pr�ximo v�rtice
		vertice = vertice->seguinte;
	}

	printf("\n");

	return g->vertices;  
} 

//Guardar grafo em ficheiro txt 
Grafo* guardarGrafo(Grafo* g) {

	//Declarar vari�veis 
	Vertice* atualVertice = g->vertices; //Inicio dos v�rtices 
	Aresta* atualAresta; 

	//Abrir o arquivo para escrita 
	FILE* ficheiroGrafo = fopen("Grafo.txt", "w");

	//Se o ficheiro for NULL informa o utilizador 
	if (ficheiroGrafo == NULL) {
		printf("ERRO AO CRIAR O ARQUIVO!\n");
		return 0;
	}

	//Escrever os dados formatados do grafo no arquivo
	fprintf(ficheiroGrafo, "ORIGEM;DESTINO;DISTANCIA\n");

	//Percorre os v�rtices todos at� ao fim 
	while (atualVertice != NULL) { 

		atualAresta = atualVertice->adjacencias;

		//Percorre as arestas todas at� ao fim 
		while (atualAresta != NULL) {
			//Escreve no ficheiro dos grafos as informa��es do grafo, origem, destino e a distancia entre os vertices 
			fprintf(ficheiroGrafo, "%d;%d;%.2f\n", atualVertice->ID, atualAresta->vertice_adjacente, atualAresta->peso);
			
			//Passa para a proxima aresta 
			atualAresta = atualAresta->proximo;
		}
		//Passa para o pr�ximo verice 
		atualVertice = atualVertice->seguinte;
	}

	//Fechar o arquivo
	fclose(ficheiroGrafo);
	return 1; 
}  

//Guardar vertices em ficheiro txt 
void guardarVertices (Grafo** g) {

	// Abrir o ficheiro dos v�rtices 
	FILE* ficheiroVertice = fopen("Vertices.txt", "w");
	
	//Se o ficheiro for NULL informa o utilizador 
	if (ficheiroVertice == NULL) {
		printf("ERRO AO ABRIR O FICHEIRO!\n");
		return;
	}
	 
	//Se o grafo estiver vazio informa o utilizador 
	if (*g == NULL) {
		printf("GRAFO VAZIO\n"); 
		
		//Fechar o ficheiro 
		fclose(ficheiroVertice);
		return;
	} 
	Vertice* atual = (*g)->vertices;

	//Percorre a lista dos vertices at� ao fim 
	while (atual != NULL) {
		//Escreve no ficheiro o ID do v�rtice, o ID do meio de transporte, o tipo de meio de transporte, a bateria e a sua localiza��o 
		fprintf(ficheiroVertice, "%d;%d;%s;%.2f;%s\n",atual->VerticeID, atual->ID, atual->Tipo, atual->bateria, atual->geocodigo);
		
		//Passa para o seguinte
		atual = atual->seguinte;
	}

	// fechar o ficheiro
	fclose(ficheiroVertice);
}  
