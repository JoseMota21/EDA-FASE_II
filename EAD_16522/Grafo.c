#define _CRT_SECURE_NO_DEPRECATE 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "Grafo.h"  

Vertice* criarVertices(Grafo** g, Transporte* meios) {
	// Identificação do vértice
	int VerticeID = 1;

	// Lista ligada dos meios de transporte
	Transporte* atual = meios;

	// Criar o vértice com ID 0
	Vertice* vertice0 = malloc(sizeof(Vertice));
	strcpy(vertice0->geocodigo, "///cantarola.sondado.nevoeiro");
	strcpy(vertice0->Tipo, "ARMAZEM");
	vertice0->ID = 0;
	vertice0->bateria = 0.0;
	vertice0->meios = NULL;
	vertice0->VerticeID = 0;
	vertice0->seguinte = NULL;
	vertice0->adjacencias = NULL;
	

	// Criar o grafo e adicionar o vértice 0 como o primeiro da lista
	*g = criarGrafo(100);
	if (*g == NULL) {
		free(vertice0);
		return NULL;
	}
	(*g)->vertices = vertice0;  
	(*g)->meios = meios; 

	// Percorrer os meios de transporte até o fim
	while (atual != NULL) {
		// Alocar memória para o novo vértice
		Vertice* novo = malloc(sizeof(Vertice));

		// Copiar os campos do meio de transporte para o vértice 
		strcpy(novo->geocodigo, atual->geocodigo); 
		strcpy(novo->Tipo, atual->tipo); 
		novo->ID = atual->codigo;
		novo->bateria = atual->bateria;
		novo->meios = atual;
		novo->VerticeID = VerticeID; 
		novo->seguinte = NULL;
		novo->adjacencias = NULL;  
	
		// Adicionar o novo vértice ao final da lista
		Vertice* ultimo = (*g)->vertices;
		while (ultimo->seguinte != NULL) {
			ultimo = ultimo->seguinte;
		}
		ultimo->seguinte = novo;

		// Incrementar a identificação dos vértices
		VerticeID++;

		// Apontar para o próximo meio de transporte da lista dos meios de transporte
		atual = atual->seguinte;
	}

	(*g)->numeroVertices = VerticeID;
	
	guardarVertices(g);

	return (*g)->vertices;
}

//Função para encontrar vértices 
Vertice* encontrarVertice(Grafo* g, int id) {

	Vertice* atual = g->vertices;

	while (atual != NULL) {
			if (atual->VerticeID == id) {
				return atual;
			}

		atual = atual->seguinte;
	}
	return NULL;
} 

//Função para criar grafo
Grafo* criarGrafo(int numeroVertices) {

	// Aloca memória para a estrutura do grafo
	Grafo* g = malloc(sizeof(Grafo));
	if (g == NULL) {
		// Tratamento de erro na alocação de memória
		return NULL;
	}

	// Inicializa o número de vértices
	g->numeroVertices = numeroVertices;

	// Aloca memória para a matriz de visitados
	g->visitados = malloc(numeroVertices * sizeof(bool*));
	if (g->visitados == NULL) {
		// Tratamento de erro na alocação de memória
		free(g);
		return NULL;
	}

	// Aloca memória para a matriz de adjacência
	g->matrizadj = malloc(numeroVertices * sizeof(Aresta*));
	if (g->matrizadj == NULL) {
		// Tratamento de erro na alocação de memória
		free(g->visitados);
		free(g);
		return NULL;
	}

	// Inicializa a matriz de visitados e a matriz de adjacência
	for (int i = 0; i < numeroVertices; i++) {
		g->visitados[i] = calloc(numeroVertices, sizeof(bool));
		g->matrizadj[i] = calloc(numeroVertices, sizeof(Aresta*));
		if (g->visitados[i] == NULL || g->matrizadj[i] == NULL) {
			
			// Tratamento de erro na alocação de memória
			// Libera a memória alocada anteriormente
			for (int j = 0; j < i; j++) {
				free(g->visitados[j]);
				free(g->matrizadj[j]);
			}
			free(g->visitados);
			free(g->matrizadj);
			free(g);
			return NULL;
		}
	}

	// Inicializa os vértices como NULL
	g->vertices = NULL;

	return g;
}

//Função para criar arestas 
Aresta* criarAresta(Grafo* g, int origem, int destino, float peso) {

	Vertice* verticeOrigem = encontrarVertice(g, origem);
	Vertice* verticeDestino = encontrarVertice(g, destino);


	// Verificar se a origem e o destino são válidos
	if (origem < 0 || origem >= g->numeroVertices || destino < 0 || destino >= g->numeroVertices) {
		printf("VERTICES INVALIDOS.\n"); 

		return NULL;
	}
	 
	if (verticeOrigem == NULL) {
		printf("VERTICE ORIGEM NAO ENCONTRADO.\n");
		return NULL;
	}

	if (verticeDestino == NULL) {
		printf("VERTICE DE DESTINO NAO ENCONTRADO\n");
		return NULL;
	}

	// Verificar se a aresta já existe entre os vértices
	if (g->matrizadj[origem][destino] != NULL) {
		printf("ARESTA JA EXISTE ENTRE OS VERTICES %d e %d\n", origem, destino);
		return NULL;
	}

	// Criar a nova aresta (Origem - Destino - Grafo bidirecional)
	Aresta* novaArestaOrigem = malloc(sizeof(Aresta));

	if (novaArestaOrigem == NULL) {
		printf("ERRO: Falha ao alocar memoria para a nova aresta.\n");
		return NULL;
	}

	novaArestaOrigem->vertice_adjacente = destino;
	novaArestaOrigem->peso = peso;
	novaArestaOrigem->proximo = NULL; 

	// Atualizar a matriz de adjacência para refletir a presença da aresta
	g->matrizadj[origem][destino] = novaArestaOrigem;

	Aresta* novaArestaDestino = malloc(sizeof(Aresta)); 

	novaArestaDestino->vertice_adjacente = origem; 
	novaArestaDestino->peso = peso; 
	novaArestaDestino->proximo = NULL;

	g->matrizadj[destino][origem] = novaArestaDestino; 

	guardarGrafo(g);

	return novaArestaOrigem; 
}
 
//Imprimir na consola o grafo
void imprimirGrafo(Grafo* g) {

	Vertice* atualVertice = g->vertices;
	Aresta* atualAresta; 

	printf("------------------------- GRAFO-------------------\n"); 
	printf("\n");

	//Cabeçalho da tabela
	printf("|%-5s | %-5s | %-10s|\n", "ORIGEM", "DESTINO", "DISTANCIA"); 


	for (int origem = 0; origem < g->numeroVertices; origem++) {
		for (int destino =0; destino < g->numeroVertices; destino++)

			if (g->matrizadj[origem][destino] != NULL) {
				Aresta* aresta = g->matrizadj[origem][destino]; 

				while (aresta != NULL) {

					printf("|%-5d | %-5d | %-10.2f|\n", origem, aresta->vertice_adjacente, aresta->peso);
					 
					aresta = aresta->proximo;
				}
			}
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

	//Cabeçalho da tabela
	printf("|%-12s | %-5s | %-10s | %-10s | %-30s|\n", "ID VERTICE", "ID", "TIPO", "BATERIA", "LOCALIZACAO");

	//Percorre a lista dos vértices 
	while (vertice != NULL) {

		//Imprime na consola a informação do ID do vértice, ID do meio de transporte, o tipo de transporte, bateria e a sua localização 
		printf("|%-12d | %-5d | %-10s | %-10.2f | %-30s|\n", vertice->VerticeID, vertice->ID, vertice->Tipo, vertice->bateria, vertice->geocodigo);

		//Passa para o próximo vértice
		vertice = vertice->seguinte;
	}

	printf("\n");

	return g->vertices;  
} 

//Guardar o grafo em ficheiro 
Grafo* guardarGrafo(Grafo* g) {
	// Abrir o arquivo para escrita
	FILE* ficheiroGrafo = fopen("Grafo.txt", "w");

	// Verificar se o arquivo foi aberto corretamente
	if (ficheiroGrafo == NULL) {
		printf("ERRO AO CRIAR O ARQUIVO!\n");
		return NULL;
	}

	// Escrever os dados formatados do grafo no arquivo
	fprintf(ficheiroGrafo, "ORIGEM;DESTINO;DISTANCIA\n");

	// Percorrer a matriz de adjacência
	for (int origem = 0; origem < g->numeroVertices; origem++) {
		for (int destino = 0; destino < g->numeroVertices; destino++) {
			// Verificar se há uma aresta entre os vértices de origem e destino
			if (g->matrizadj[origem][destino] != NULL) { 

				Aresta* aresta = g->matrizadj[origem][destino]; 

				while (aresta != NULL) {
					// Escrever no arquivo as informações do grafo: origem, destino e peso da aresta
					fprintf(ficheiroGrafo, "%d;%d;%.2f\n", origem, destino, aresta->peso); 
					aresta = aresta->proximo; 
				}
			} 
		}
	}

	// Fechar o arquivo
	fclose(ficheiroGrafo);

	return g;
}

//Guardar vertices em ficheiro txt 
void guardarVertices (Grafo** g) {

	// Abrir o ficheiro dos vértices 
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

	//Percorre a lista dos vertices até ao fim 
	while (atual != NULL) {
		//Escreve no ficheiro o ID do vértice, o ID do meio de transporte, o tipo de meio de transporte, a bateria e a sua localização 
		fprintf(ficheiroVertice, "%d;%d;%s;%.2f;%s\n",atual->VerticeID, atual->ID, atual->Tipo, atual->bateria, atual->geocodigo);
		
		//Passa para o seguinte
		atual = atual->seguinte;
	}

	// fechar o ficheiro
	fclose(ficheiroVertice);
}   

//Verifica se Grafo está completo 
bool grafoCompleto(Grafo* g) {
	int numeroVertices = g->numeroVertices; 

	//Verifica se todos os vértices estão conetados
	for (int i = 0; i < numeroVertices; i++) {
		for (int j = 0; j < numeroVertices; j++) {
			Aresta* aresta = g->matrizadj[i][j]; 
			if (i != j && aresta == NULL) { 
				//Existe ausencia de aresta
				return false;
			}
		}
	}

	//Verifica se todas as arestas tem pesos atribuidos
	for (int i = 0; i < numeroVertices; i++) {
		for (int j = 0; j < numeroVertices; j++) {
			Aresta* aresta = g->matrizadj[i][j]; 
			if (aresta != NULL && aresta->peso == FLT_MAX) {
				return false;
			}			 
		}
	}

	//Grafo Completo 
	return true; 
}
  
void recolherTrotinetes(Grafo* g, int origem) { 

	int numeroVertices = g->numeroVertices;

	// Inicializar o vetor de visitados
	bool* visitados = malloc(numeroVertices * sizeof(bool));

	for (int i = 0; i < numeroVertices; i++) {
		visitados[i] = false;
	}

	// Inicializar o vetor de caminho
	int caminho[100 + 1];
	int posicao = 0;
	caminho[posicao] = origem;
	visitados[origem] = true;

	// Construir o caminho usando a heurística do vizinho mais próximo
	for (int i = 0; i < numeroVertices - 1; i++) {
		int verticeAtual = caminho[posicao];
		int vizinhoMaisProximo = EncontrarMaisProximo50(g, verticeAtual, visitados);
		if (vizinhoMaisProximo == -1) {
			// Todos os vértices com bateria inferior a 50% já foram visitados
			break;
		}
		caminho[++posicao] = vizinhoMaisProximo;
		visitados[vizinhoMaisProximo] = true;
	}
	// Voltar para o vértice de origem
	caminho[++posicao] = origem;

	// Imprimir o resultado
	printf("------------------------- ITENERAIO MAIS CURTO -------------------\n");
	printf("ITENERARIO: ");
	for (int i = 0; i <= posicao; i++) {
		printf("%d ", caminho[i]);
	}
	printf("\n");
	 
	// Recolher as trotinetes no caminhão
	printf("RECOLHER OS MEIOS DE TRANSPORTE\n"); 

	for (int i = 0; i <= posicao; i++) { 
		 int vertice = caminho[i];

		 if (vertice != 0) {
			 printf("VERTICE %d RECOLHIDO\n", vertice);
		 }
		 
		 Transporte* transporte = encontrarTransportePorVertice(g, vertice);  

		 if (transporte != NULL) {
			 printf("TRANSPORTE COM O ID %d DO TIPO %s ENCONTRADO COM A BATERIA DE %.02f\n", transporte->codigo, transporte->tipo, transporte->bateria);  

			 transporte->bateria = 100.0;  
			 transporte->autonomia = 80.0;  
			 strcpy(transporte->geocodigo, "///cantarola.sondado.nevoeiro");  
			  
		 }
		 else {
			 if (vertice != 0) {
				 printf("TRANSPORTE NAO ENCONTRADO PARA O VERTICE %d\n", vertice); 
			 }
		 }

		 saveAlterarDadosTransportes (g->meios);  
		 atualizarVertices (g);  
	} 
	  
	free(visitados);
}  

Transporte* encontrarTransportePorVertice(Grafo* g, int verticeID) { 
	// Percorrer a lista de vértices
	Vertice* vertice = g->vertices; 
	while (vertice != NULL) { 
		// Verificar se o ID do vértice corresponde ao ID desejado
		if (vertice->VerticeID == verticeID) { 
			return vertice->meios;   
		}
		vertice = vertice->seguinte; 
	}
	return NULL;
} 

void atualizarVertices(Grafo* g) {
	// Percorrer a lista de vértices
	Vertice* vertice = g->vertices;
	while (vertice != NULL) {
		// Percorrer a lista de meios de transporte do vértice
		Transporte* transporte = vertice->meios;
		while (transporte != NULL) {
			// Verificar se o meio de transporte foi removido
			if (transporte->bateria != 100.0) {
				// Atualizar a bateria do vértice com base na bateria do meio de transporte
				if (transporte->bateria > vertice->bateria) { 
					vertice->bateria = transporte->bateria; 
				} 
				// Atualizar a localização do meio de transporte com base na nova localização 
				strcpy(transporte->geocodigo, "///cantarola.sondado.nevoeiro"); 
			}
			transporte = transporte->seguinte; 
		}
		vertice = vertice->seguinte; 
	}
}
 
int EncontrarMaisProximo50(Grafo* g, int verticeAtual, bool* visitados) {

	int numeroVertices = g->numeroVertices;
	float menorPeso = FLT_MAX;
	int vizinhoProximo = -1;

	for (int i = 0; i < numeroVertices; i++) {
		if (i != verticeAtual && !visitados[i]) {  // Verifica se o vértice não é o atual e não foi visitado
			Aresta* aresta = g->matrizadj[verticeAtual][i];
			Vertice* vertice = encontrarVertice(g, i);

			if (aresta != NULL && vertice->bateria < 50.0) {

				if (aresta->peso < menorPeso) {
					menorPeso = aresta->peso;
					vizinhoProximo = i;
				}
			}
		}
	}

	if (vizinhoProximo != -1) {
		Vertice* vertice = encontrarVertice(g, vizinhoProximo);
		printf("Bateria do vertice %d: %.2f\n", vizinhoProximo, vertice->bateria);
	}
	
	return vizinhoProximo;
} 

