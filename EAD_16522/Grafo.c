#define _CRT_SECURE_NO_DEPRECATE 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "Grafo.h"  

//Criar vertices 
Vertice* criarVertices(Grafo** g, Transporte* meios) {
	//Identificação do vértice 
	int VerticeID = 1;
	//Lista ligado dos meios de transportes 
	Transporte* atual = meios;
	//Percorre todos os meios de transporte até ao fim 
	while (atual != NULL) {
		//Aloca a memória 
		Vertice* novo = malloc(sizeof(Vertice));
		//O vértice é criado para cada meio de transporte 
		// Copia o campo do meio de transporte para os vértices 
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
			//Se o grafo não exister cria um grafo
			*g = criarGrafo(100);
			//Se a criação do grafo falhar por algum motivo
			//o apontador do vértice é libertado
			if (*g == NULL) {
				free(novo);
				return NULL;
			}
			(*g)->vertices = novo;
		}
		else {
			//Criado um apontado para o último vértice da lista ligada dos vértices 
			Vertice* ultimo = (*g)->vertices;
			//Se o ultimo vertice for NULL 
			if (ultimo == NULL) {
				//O primeiro vertice é inserido como o primeiro da lista 
				(*g)->vertices = novo;
			}
			else {
				//Se já exista vértices na lista, o ultimo aponta para o seguinte até ser NULL
				while (ultimo->seguinte != NULL) {
					//O novo vértice é adicionado no fim da lista 
					ultimo = ultimo->seguinte;
				}
				ultimo->seguinte = novo;
			}
		}
		//Incrementa a identação dos vértices  
		VerticeID++;
		//Aponta para o próximo meio de transporte da lista dos meios de transporte 
		atual = atual->seguinte;
	}
	(*g)->numeroVertices = VerticeID - 1;
	//Guardar os vértices em um ficheiro 
	guardarVertices(g);
	return (*g)->vertices;
}

//Função para encontrar vértices 
Vertice* encontrarVertice(Grafo* g, int id) {

	Vertice* atual = g->vertices;

	while (atual != NULL) {
			if (atual->ID == id) {
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

	// Criar a nova aresta
	Aresta* novaAresta = malloc(sizeof(Aresta)); 

	if (novaAresta == NULL) {
		printf("ERRO: Falha ao alocar memoria para a nova aresta.\n");
		return NULL;
	}

	novaAresta->vertice_adjacente = destino;
	novaAresta->peso = peso;
	novaAresta->proximo = NULL;
	 
	// Atualizar a matriz de adjacência para refletir a presença da aresta
	g->matrizadj[origem][destino] = novaAresta; 
	
	/*
		// Percorrer a matriz de adjacência
		for (int i = 0; i < g->numeroVertices; i++) {
			for (int j = i + 1; j < g->numeroVertices; j++) {
				Aresta* aresta = g->matrizadj[i][j];
				if (aresta != NULL) {
					printf("ARESTA ENTRE O VERTICE %d E %d TEM UM PESO DE %.2f\n", i, j, aresta->peso);
				}
			}
		}
	*/


	guardarGrafo(g); 

return novaAresta;
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

//Visitar o grafo em profundidade 
void visitaProfun(Grafo* g, int origem, bool* visitados) {

	//Marca o vertice atual como visitado
	visitados[origem] = true; 

	// Imprimir o vértice atual
	printf("%d\n", origem);  

	for (int destino = 0; destino < g->numeroVertices; destino++) {
		if (g->matrizadj[origem][destino] != NULL) {
			
			if (!visitados[destino]) {
				visitaProfun(g, destino, visitados); 
			}
		}
	}
}

//Atravessar o grafo 
void travessia(Grafo* g, int origem) {

	//Verificar se o vertice de origem é valido 
	if (origem < 0 || origem >= g->numeroVertices) {
		printf("VERTICE DE ORIGEM INVALIDO\n"); 
	} 

	//Armazenar o os vertices visitados 
	bool* visitados = calloc(g->numeroVertices, sizeof(bool)); 

	printf("TRAVESSIA A PARTIR DO VERTICE %d\n", origem); 

	visitaProfun(g, origem, visitados); 

	free(visitados); 

}

//Criar uma pilha 
Queue* criarQueue() {
	Queue* fila = malloc(sizeof(Queue)); 

	fila->inicio = NULL; 
	fila->fim = NULL; 

	return fila; 
}

void enqueue(Queue* fila, int valor) {

	Node* novoNo = malloc(sizeof(Node)); 

	novoNo->valor = valor; 
	novoNo->proximo = NULL; 

	if (fila->inicio == NULL) {
		fila->inicio = novoNo; 
		fila->fim = novoNo; 
	}
	else {
		fila->fim->proximo = novoNo; 
		fila->fim = novoNo; 
	}
}

int dequeue(Queue* fila) {
	if (fila->inicio == NULL) {
		printf("FILA VAZIA\n");

		return -1; 
	}

	Node* noRemovido = fila->inicio; 
	int valorRemovido = noRemovido->valor; 

	fila->inicio = fila->inicio->proximo;
	free(noRemovido); 

	if (fila->inicio == NULL) {
		fila->fim = NULL;
	} 

	return valorRemovido; 
} 

//Pilha vazia
int Vazia(Queue* fila) {
	return (fila->inicio == NULL); 
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

//Diz qual é o menor percurso entre dois vértices (da origem até ao vertice)  
void menorPercurso(Grafo* g, int origem) {
	int numeroVertices = g->numeroVertices; 

	float distancias[5];

	for (int i = 0; i < numeroVertices; i++) {

		distancias[i] = FLT_MAX;  
	} 

	distancias[origem] = 0; 

	Queue* fila = criarQueue(); 
	enqueue(fila, origem);

	while (!Vazia(fila)) { 

		int vertice = dequeue(fila); 

		for (int adjacente = 0; adjacente < numeroVertices; adjacente++) { 
			Aresta* aresta = g->matrizadj[vertice][adjacente]; 

			if (aresta != NULL) {
				float peso = aresta->peso;
				float distanciaNova = distancias[vertice] + peso; 
				
					if (distanciaNova < distancias[adjacente]) {
						distancias[adjacente] = distanciaNova;
						enqueue(fila, adjacente);
					}
			}
		}
	}

	// Imprime o resultado
	printf("------------------------- MENOR PERCURSO -------------------\n");
	printf("Origem: %d\n", origem);
	printf("Destino | Distancia\n");
	for (int i = 0; i < numeroVertices; i++) {
		printf("%d       | %.2f\n", i, distancias[i]);
	}
} 

//Função para encontrar qual o vértice mais próximo (Auxilio para excutar a função tspVizinhoMaisProximo )
int EncontrarMaisProximo(Grafo* g, int verticeAtual, bool* visitados) {
	
	int numeroVertices = g->numeroVertices;
	float menorPeso = FLT_MAX;
	int vizinhoProximo = -1;

	for (int i = 0; i < numeroVertices; i++) {
			
		Aresta* aresta = g->matrizadj[verticeAtual][i];
			if (aresta != NULL && !visitados[i] && aresta->peso < menorPeso) {
				menorPeso = aresta->peso;
				vizinhoProximo = i;
			}
	}

	return vizinhoProximo;
}

//Percurso minimo para percorrer todos os vértices desde a orige, 
void tspVizinhoMaisProximo(Grafo* g, int origem) {
	
	int numeroVertices = g->numeroVertices;

	//Inicializar o vetor de visitados 
	bool* visitados = malloc(numeroVertices * sizeof(bool)); 

	// Inicializa o vetor de visitados
	for (int i = 0; i < numeroVertices; i++) {
		visitados[i] = false;
	}
	
	// Inicializa o vetor de caminho
	int caminho[10 + 1];
	int posicao = 0;
	caminho[posicao] = origem; //origem == armazém 
	visitados[origem] = true;

	// Constrói o caminho usando a heurística do vizinho mais próximo
	for (int i = 0; i < numeroVertices - 1; i++) {
		int verticeAtual = caminho[posicao];
		int vizinhoMaisProximo = EncontrarMaisProximo(g, verticeAtual, visitados);
		caminho[++posicao] = vizinhoMaisProximo;
		visitados[vizinhoMaisProximo] = true;
	}

	// Volta para o vértice de origem
	caminho[++posicao] = origem;

	// Imprime o resultado
	printf("------------------------- CAMINHO MAIS CURTO -------------------\n");
	printf("Caminho: ");
	for (int i = 0; i <= numeroVertices; i++) {
		printf("%d ", caminho[i]);
	}
	printf("\n");

	free(visitados); 
}  
