#define _CRT_SECURE_NO_DEPRECATE 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "Grafo.h"  

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
			*g = criarGrafo(3);
			//Se a cria��o do grafo falhar por algum motivo
			//o apontador do v�rtice � libertado
			if (*g == NULL) {
				free(novo);
				return NULL;
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
	(*g)->numeroVertices = VerticeID - 1;
	//Guardar os v�rtices em um ficheiro 
	guardarVertices(g);
	return (*g)->vertices;
}

//Fun��o para encontrar v�rtices 
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

Grafo* criarGrafo(int numeroVertices) {
	// Aloca mem�ria para a estrutura do grafo
	Grafo* g = malloc(sizeof(Grafo));
	if (g == NULL) {
		// Tratamento de erro na aloca��o de mem�ria
		return NULL;
	}

	// Inicializa o n�mero de v�rtices
	g->numeroVertices = numeroVertices;

	// Aloca mem�ria para a matriz de visitados
	g->visitados = malloc(numeroVertices * sizeof(bool*));
	if (g->visitados == NULL) {
		// Tratamento de erro na aloca��o de mem�ria
		free(g);
		return NULL;
	}

	// Aloca mem�ria para a matriz de adjac�ncia
	g->matrizad = malloc(numeroVertices * sizeof(bool*));
	if (g->matrizad == NULL) {
		// Tratamento de erro na aloca��o de mem�ria
		free(g->visitados);
		free(g);
		return NULL;
	} 

	// Inicializa a matriz de visitados e a matriz de adjac�ncia
	for (int i = 0; i < numeroVertices; i++) {
		g->visitados[i] = calloc(numeroVertices, sizeof(bool));
		g->matrizad[i] = calloc(numeroVertices, sizeof(bool));
		if (g->visitados[i] == NULL || g->matrizad[i] == NULL) {
			// Tratamento de erro na aloca��o de mem�ria
			// Libere a mem�ria alocada anteriormente
			for (int j = 0; j < i; j++) {
				free(g->visitados[j]);
				free(g->matrizad[j]);
			}
			free(g->visitados);
			free(g->matrizad);
			free(g);
			return NULL;
		}
	}

	// Inicializa os v�rtices como NULL
	g->vertices = NULL;

	return g;
}

Aresta* criarAresta(Grafo* g, int origem, int destino, float peso) {

	Vertice* verticeOrigem = encontrarVertice(g, origem);
	Vertice* verticeDestino = encontrarVertice(g, destino); 

	// Verificar se a origem e o destino s�o v�lidos
	if (origem < 0 || origem >= g->numeroVertices || destino < 0 || destino >= g->numeroVertices) {
		printf("V�RTICES INV�LIDOS.\n");
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

	// Verificar se a aresta j� existe entre os v�rtices
	if (g->matrizad[origem][destino] != NULL) {
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
	 
	// Atualizar a matriz de adjac�ncia para refletir a presen�a da aresta
	g->matrizad[origem][destino] = true; 

	// Armazenar a nova aresta na matriz de adjac�ncia
	g->matrizadj[origem][destino] = novaAresta; 

	// Acessar o peso da aresta
	float pesoAresta = g->matrizadj[origem][destino]->peso;
	printf("Peso da aresta entre os vertices %d e %d: %f\n", origem, destino, pesoAresta); 


	/*
	
		// Percorrer a matriz de adjac�ncia
	for (int i = 0; i < g->numeroVertices; i++) {
		for (int j = 0; j < g->numeroVertices; j++) {
			printf("Aresta entre os vertices %d e %d: %d\n", i, j, g->matrizad[i][j]);
		}
	}

	*/ 
	
	 
	system("pause"); 

	guardarGrafo(g); 

return novaAresta;
}

//Imprimir na consola o grafo
void imprimirGrafo(Grafo* g) {

	Vertice* atualVertice = g->vertices;
	Aresta* atualAresta; 

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

//Imprimir a lista de adjacencias 
void imprimirListaAdjacencias(Grafo* g) {
	
	Vertice* verticeAtual = g->vertices;

	while (verticeAtual != NULL) {
		printf("Vertice %d:\n", verticeAtual->ID); 

		Aresta* adjacenciaAtual = verticeAtual->adjacencias;

		while (adjacenciaAtual != NULL) {
			printf("Vertice Adjacente: %d\n", adjacenciaAtual->vertice_adjacente);
			printf("Peso da Aresta: %.2f\n", adjacenciaAtual->peso);

			adjacenciaAtual = adjacenciaAtual->proximo;
		}

		verticeAtual = verticeAtual->seguinte;
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

	// Percorrer a matriz de adjac�ncia
	for (int origem = 0; origem < g->numeroVertices; origem++) {
		for (int destino = 0; destino < g->numeroVertices; destino++) {
			// Verificar se h� uma aresta entre os v�rtices de origem e destino
			if (g->matrizad[origem][destino] != NULL) { 

				// Escrever no arquivo as informa��es do grafo: origem, destino e peso da aresta
				fprintf(ficheiroGrafo, "%d;%d;\n", origem, destino);
			} 
		}
	}

	// Fechar o arquivo
	fclose(ficheiroGrafo);

	return g;
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


void dfs(Grafo* g, int vertice) {
	
	g->visitados[vertice] = true;
	printf("%d\n ", g->vertices[vertice].ID);

	Aresta* arestaAtual = g->vertices[vertice].adjacencias;
	while (arestaAtual != NULL) {
		int verticeAdjacente = arestaAtual->vertice_adjacente;
		if (!g->visitados[verticeAdjacente]) {
			dfs(g, verticeAdjacente);
		}
		arestaAtual = arestaAtual->proximo;
	}
}

void travessiaProfundidade(Grafo* g, int verticeInicial) {
	// Inicializar o array de visitados como falso
	for (int i = 0; i < g->numeroVertices; i++) {
		g->visitados[i] = false;
	}

	// Chamar a fun��o dfs para o v�rtice inicial
	dfs(g, verticeInicial);
}


