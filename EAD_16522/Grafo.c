#define _CRT_SECURE_NO_DEPRECATE 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Grafo.h"  

//Criar vértices atraves da lista ligado dos meios de transporte 
//cada meio de transporte represente um vértice (1 ponto de recolha) 
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
			*g = criarGrafo();
			//Se a criação do grafo falhar por algum motivo
			//o apontador do vértice é libertado
			if (*g == NULL) {
				free(novo);
				return 0;
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
	//Guardar os vértices em um ficheiro 
	guardarVertices(g);

	return (*g)->vertices;
}

//Criar grafo 
Grafo* criarGrafo() {

	//Aloca memória para a estrutura 
	Grafo* g = malloc(sizeof(Grafo));   

	//Se for null return null (g será NULL), o que significa que houve problema na alocação da memória 
	if (g != NULL) { 

		//Se for diferente de null inicia os vértices como NULL 
		g->vertices = NULL;
	}
	return g;
}

//Criar arestas lista ligada simples 
Aresta* criarAresta(Grafo* g, int origem, int destino, float peso) {

	//Declarar variáveis apontam para o inicio da lista ligada dos vértices 
	Vertice* atualOrigem = g->vertices;
	Vertice* atualDestino = g->vertices;

	// Percorre a lista de vértices do grafo e 
	//verifica se o ID do vértice atual é diferente do ID do vértice de Origem, a lista de vértices não pode ser vazia
	while (atualOrigem != NULL && atualOrigem->ID != origem) {
		atualOrigem = atualOrigem->seguinte;
	}
	//Se vertice origem não for encontrado, informa o utilizador com uma mensagem 
	if (atualOrigem == NULL) {

		printf("VERTICE ORIGEM NAO ENCONTRADO.\n");
		return NULL; //Caso haja erro
	}

	// Percorre a lista de vértices do grafo e 
	//verifica se o ID do vértice atual é diferente do ID do vértice de Destino, a lista de vértices não pode ser vazia
	while (atualDestino != NULL && atualDestino->ID != destino) {
		//Passa para o seguinte vértice
		atualDestino = atualDestino->seguinte;
	}
	//Se não encontrar o vertice de destino informa o utilizador 
	if (atualDestino == NULL) {
		printf("VERTICE DE DESTINO NAO ENCONTRADO\n");
		return NULL;	 // caso haja erro
	}

	// Aloca memória
	Aresta* novaAresta = malloc(sizeof(Aresta)); 

	//Atribui ao vértice adjacente o ID do vértice de destino 
	novaAresta->vertice_adjacente = atualDestino->ID; 
	novaAresta->peso = peso;
	novaAresta->proximo = NULL; //Indica que não possui outra aresta de adjacencia 

	//Verifica se a lista de adjacencias do vertice de origem está vazia
	if (atualOrigem->adjacencias == NULL) {
		//Se estiver vazia a nova aresta é adiciona como primeira 
		atualOrigem->adjacencias = novaAresta;
	}
	else {

		Aresta* atual = atualOrigem->adjacencias; 
		//Senão percorre a lista de adjacencias do vértice de origem até encontrar a última aresta adjacente 
		while (atual->proximo != NULL) {

			atual = atual->proximo;
		}
		//A nova aresta é adicionada como a próxima aresta adjacente
		atual->proximo = novaAresta;
	}

	//Guarda o grafo em ficheiro 
	guardarGrafo(g); 

	return novaAresta; // Função executada com sucesso
}

//Imprimir na consola o grafo
void imprimirGrafo(Grafo* g) {

	Vertice* atualVertice = g->vertices;

	printf("------------------------- GRAFO-------------------\n"); 
	printf("\n");

	//Cabeçalho da tabela
	printf("|%-5s | %-5s | %-10s|\n", "ORIGEM", "DESTINO", "DISTANCIA"); 

	//Percorrer os vertices até ao fim 
	while (atualVertice != NULL) {
		
		Aresta* atualAresta = atualVertice->adjacencias; 

		//Percorrer as arestas até ao fim 
		while (atualAresta != NULL) {

			//Imprime o vertice de origem, o vertice de destino e o peso entre ambos 
			printf("|%-5d | %-5d | %-10.2f|\n", atualVertice->ID, atualAresta->vertice_adjacente, atualAresta->peso); 

			//Passa para a próxima aresta 
			atualAresta = atualAresta->proximo;
		}

		//Passa para o próximo vértice 
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

//Guardar grafo em ficheiro txt 
Grafo* guardarGrafo(Grafo* g) {

	//Declarar variáveis 
	Vertice* atualVertice = g->vertices; //Inicio dos vértices 
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

	//Percorre os vértices todos até ao fim 
	while (atualVertice != NULL) { 

		atualAresta = atualVertice->adjacencias;

		//Percorre as arestas todas até ao fim 
		while (atualAresta != NULL) {
			//Escreve no ficheiro dos grafos as informações do grafo, origem, destino e a distancia entre os vertices 
			fprintf(ficheiroGrafo, "%d;%d;%.2f\n", atualVertice->ID, atualAresta->vertice_adjacente, atualAresta->peso);
			
			//Passa para a proxima aresta 
			atualAresta = atualAresta->proximo;
		}
		//Passa para o próximo verice 
		atualVertice = atualVertice->seguinte;
	}

	//Fechar o arquivo
	fclose(ficheiroGrafo);
	return 1; 
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

//Adicionar no valor no topo da pilha 'pilha 
Pilha push(Pilha pilha, int vertice) {

	Pilha novo = (Pilha)malloc(sizeof(struct reg));

	if (novo != NULL) {
		novo->vertice = vertice;
		novo->proximo = pilha;
		return novo;
	}
	else {
		return pilha;
	}
}

Pilha pop(Pilha pilha)
{
	Pilha aux;
	if (pilha != NULL) {
		aux = pilha->proximo;
		free(pilha);
		return(aux);
	}
	else return(pilha);
}

void dijkstra(Grafo* g, int origem, int* predecessores, float* peso) {
	int numeroVertices = g->numeroVertices;
	int visitados[NUMEROVERTICE];

	//Inicializar a estrutura de dados
	for (int i = 0; i < numeroVertices; i++) {
		peso[i] = INFINITY;
		visitados[i] = 0;
		predecessores[i] = -1;
	}

	//Distancia de origem para a origem é 0
	peso[origem] = 0;

	Pilha pilha = NULL;
	pilha = push (pilha, origem);

	while (pilha != NULL) {
		//Retirar o último vértice adicionado à pilha
		int verticeAtual = pop(&pilha);

		//Verifica se o vertice já foi visitado
		if (visitados[verticeAtual]) continue;

		//Marco o vertice como visitado
		visitados[verticeAtual] = 1;

		//Percorre as adjacencias do vértice atual
		Aresta* atualAresta = g->vertices[verticeAtual].adjacencias;

		while (atualAresta != NULL) {
			int verticeAdjacente = atualAresta->vertice_adjacente;
			float pesoAresta = atualAresta->peso;

			if (peso[verticeAtual] + pesoAresta < peso[verticeAdjacente]) {
				peso[verticeAdjacente] = peso[verticeAtual] + pesoAresta;
				predecessores[verticeAdjacente] = verticeAtual;

				//Adiciona o vertice adjacente na pilha
				pilha = push (pilha, verticeAdjacente);
			}
			atualAresta = atualAresta->proximo;
		}
	}

	//Imprime o caminho percorrido a partir da origem
	int destino = 0; //Definir destino 
	pilha = NULL; 
	while (destino != -1) {
		pilha = push(pilha, destino);
		destino = predecessores[destino];
	}

	printf("Caminho percorrido: ");
	while (pilha != NULL) {
		printf("%d ", pilha->vertice);
		pilha = pop(pilha);
	}
	printf("\n");
}

