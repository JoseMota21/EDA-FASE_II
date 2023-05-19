#define _CRT_SECURE_NO_DEPRECATE 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
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

	(*g)->numeroVertices = VerticeID-1; 

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

	//Declarar vari�veis apontam para o inicio da lista ligada dos v�rtices 
	Vertice* atualOrigem = g->vertices;
	Vertice* atualDestino = g->vertices;

	// Percorre a lista de v�rtices do grafo e 
	//verifica se o ID do v�rtice atual � diferente do ID do v�rtice de Origem, a lista de v�rtices n�o pode ser vazia
	while (atualOrigem != NULL && atualOrigem->ID != origem) {
		atualOrigem = atualOrigem->seguinte;
	}
	//Se vertice origem n�o for encontrado, informa o utilizador com uma mensagem 
	if (atualOrigem == NULL) {

		printf("VERTICE ORIGEM NAO ENCONTRADO.\n");
		return NULL; //Caso haja erro
	}

	// Percorre a lista de v�rtices do grafo e 
	//verifica se o ID do v�rtice atual � diferente do ID do v�rtice de Destino, a lista de v�rtices n�o pode ser vazia
	while (atualDestino != NULL && atualDestino->ID != destino) {
		//Passa para o seguinte v�rtice
		atualDestino = atualDestino->seguinte;
	}
	//Se n�o encontrar o vertice de destino informa o utilizador 
	if (atualDestino == NULL) {
		printf("VERTICE DE DESTINO NAO ENCONTRADO\n");
		return NULL;	 // caso haja erro
	}

	Aresta* existe = atualOrigem->adjacencias; 

	while (existe != NULL){ 
		
		if (existe->vertice_adjacente == destino) {
			printf("ARESTA J� EXISTE ENTRE OS VERTICES %d e %d\n", origem, destino); 

			return NULL; 
		}

		existe = existe->proximo; 

	}

	// Aloca mem�ria 
	Aresta* novaAresta = malloc(sizeof(Aresta)); 

	//Atribui ao v�rtice adjacente o ID do v�rtice de destino 
	novaAresta->vertice_adjacente = atualDestino->ID; 
	novaAresta->peso = peso;
	novaAresta->proximo = NULL; //Indica que n�o possui outra aresta de adjacencia 

	//Verifica se a lista de adjacencias do vertice de origem est� vazia
	if (atualOrigem->adjacencias == NULL) {
		//Se estiver vazia a nova aresta � adiciona como primeira 
		atualOrigem->adjacencias = novaAresta;
		novaAresta->proximo = NULL; 
	}
	else {

		Aresta* atual = atualOrigem->adjacencias; 
		//Sen�o percorre a lista de adjacencias do v�rtice de origem at� encontrar a �ltima aresta adjacente 
		while (atual->proximo != NULL) {

			atual = atual->proximo;
		}
		//A nova aresta � adicionada como a pr�xima aresta adjacente
		atual->proximo = novaAresta;
		novaAresta->proximo = NULL; 
	} 

	//Guarda o grafo em ficheiro 
	guardarGrafo(g); 

	return novaAresta; // Fun��o executada com sucesso
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

Pilha push(Pilha pilha, int vertice) {
	Pilha novo = (Pilha)malloc(sizeof(struct reg));

	if (novo != NULL) {
		novo->vertice = vertice;
		novo->proximo = pilha;
		pilha = novo;

		//printf("Empilhado o vertice: %d\n", vertice); // Imprime o v�rtice empilhado 
	}
	return pilha;
}

Pilha pop(Pilha pilha) { 

	if (pilha != NULL) { 
		Pilha aux = pilha->proximo; 
		//printf("Desempilhado o vertice: %d\n", pilha->vertice); 
		free(pilha); 
		pilha = aux; 
	}
	return pilha; 
} 

Vertice* encontrarVertice(Grafo* g, int id) {
	
	Vertice* atual = g->vertices;
	
	while (atual != NULL) {
		if (atual->ID == id)
			return atual;

		atual = atual->seguinte; 
	}
	return NULL;
}

void dijkstra(Grafo* g, int origem) {
	int i;

	

	// Inicializar todas as dist�ncias como infinito e visitado como falso
	for (i = 0; i < g->numeroVertices; i++) {
		g->vertices[i].distancia = INFINITY_INT;
		g->vertices[i].visitado = 0;
	}

	Vertice* atual = g->vertices;

	while (atual != NULL) {
		atual->distancia = INFINITY_INT;
		atual->visitado = 0;
		atual = atual->seguinte;
	}

	// Definir a dist�ncia da origem como 0
	Vertice* verticeOrigem = encontrarVertice(g, origem);
	verticeOrigem->distancia = 0;

	// Vetor para armazenar o v�rtice anterior no caminho
	int* anterior = (int*)malloc(g->numeroVertices * sizeof(int));

	// Loop principal do algoritmo de Dijkstra
	for (i = 0; i < g->numeroVertices; i++) {
		// Encontrar o v�rtice n�o visitado com a menor dist�ncia
		Vertice* verticeAtual = NULL;
		int menorDistancia = INFINITY_INT;

		Vertice* atual = g->vertices;

		while (atual != NULL) {
			if (!atual->visitado && atual->distancia < menorDistancia) {
				verticeAtual = atual;
				menorDistancia = atual->distancia;
			}
			atual = atual->seguinte;
		}

		if (verticeAtual == NULL) {
			printf("Todos os vertices visitados\n");
			break;
		}

		// Marcar o v�rtice atual como visitado
		verticeAtual->visitado = 1;

		//printf("%d", verticeAtual->visitado); 

		//printf("Vertice %d distancia %d, visitado %d\n", verticeAtual->ID, verticeAtual->distancia, verticeAtual->visitado);

		// Atualizar as dist�ncias dos v�rtices adjacentes ao v�rtice atual
		Aresta* arestaAtual = verticeAtual->adjacencias; 

		while (arestaAtual != NULL) {
			Vertice* verticeAdjacente = encontrarVertice(g, arestaAtual->vertice_adjacente);
			int pesoAresta = arestaAtual->peso;

			if (verticeAdjacente != NULL && !verticeAdjacente->visitado) {
				int distancia = verticeAtual->distancia + pesoAresta;
				if (distancia < verticeAdjacente->distancia) {
					verticeAdjacente->distancia = distancia;
					anterior[verticeAdjacente->ID] = verticeAtual->ID;
				}
			}

			arestaAtual = arestaAtual->proximo;
		}

		Pilha* pilha = NULL; 

		int verticeRastreio = origem; 
		// Rastrear o caminho mais curto
		while (verticeRastreio != verticeAtual->ID) {
			pilha = push(pilha, verticeRastreio); 

			verticeRastreio = verticeAtual->ID;

			Vertice* verticeAnterior = encontrarVertice(g, anterior[verticeRastreio]);
			
		}

		pilha = push(pilha, verticeAtual->ID); 
			

		imprimirCaminhoMaisCurto(pilha);

		// Liberar a mem�ria da pilha
		while (pilha != NULL) {
			pilha = pop(pilha);

		}
	}
}

void imprimirCaminhoMaisCurto(Pilha pilha) {
	
	while (pilha != NULL) {
		printf("%d\n", pilha->vertice);
		pilha = pilha->proximo;
	}
	printf("\n");
} 



