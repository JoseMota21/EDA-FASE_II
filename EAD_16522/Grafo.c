#define _CRT_SECURE_NO_DEPRECATE 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "Grafo.h"  

//Função para criar vértices 
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
	
	guardarVertices(*g); 

	return (*g)->vertices;
}

//Função para encontrar os vertices 
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

	// Criar a nova aresta (Origem - Destino)
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

	// Criar a aresta adicional do último vértice para o vértice de origem
	if (destino == g->numeroVertices - 1 && origem == 0) { 
	
		Aresta* novaArestaDestino = malloc(sizeof(Aresta)); 
		if (novaArestaDestino == NULL) { 
			printf("ERRO: Falha ao alocar memoria para a nova aresta.\n"); 
			return NULL; 
		}

		novaArestaDestino->vertice_adjacente = origem; 
		novaArestaDestino->peso = peso; 
		novaArestaDestino->proximo = NULL; 

		g->matrizadj[destino][origem] = novaArestaDestino; 
	}

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

					printf("|%-6d | %-7d | %-10.2f|\n", origem, aresta->vertice_adjacente, aresta->peso);
					 
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

//Conetar todos os vertices 
void conetarVertices(Grafo* g) {

	Vertice* verticeAtual = g->vertices; 

	while (verticeAtual != NULL) { 
		Vertice* proximoVertice = verticeAtual->seguinte; 

		while (proximoVertice != NULL) {
			// Converter 3 palavras do what3words em coordenadas (latitude e longitude)
			float lat1, lng1, lat2, lng2; 
			get_coordinates(verticeAtual->geocodigo, API_KEY, &lat1, &lng1); 
			get_coordinates(proximoVertice->geocodigo, API_KEY, &lat2, &lng2); 

			// Calcular a distância entre os vértices 
			float distancia = haversine_distance(lat1, lng1, lat2, lng2); 

			// Criar as arestas entre os vértices
			criarAresta(g, verticeAtual->VerticeID, proximoVertice->VerticeID, distancia); 

			proximoVertice = proximoVertice->seguinte; 
		}

		verticeAtual = verticeAtual->seguinte; 
	}
}

//Guardar vertices em ficheiro txt 
Grafo* guardarVertices (Grafo* g) {

	// Abrir o ficheiro dos vértices 
	FILE* ficheiroVertice = fopen("Vertices.txt", "w");
	
	//Se o ficheiro for NULL informa o utilizador 
	if (ficheiroVertice == NULL) {
		printf("ERRO AO ABRIR O FICHEIRO!\n");
		return;
	}
	 
	//Se o grafo estiver vazio informa o utilizador 
	if (g == NULL) {
		printf("GRAFO VAZIO\n"); 
		
		//Fechar o ficheiro 
		fclose(ficheiroVertice);
		return;
	} 
	Vertice* atual = g->vertices;

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

//Percuros minimo de recolha dos meios de transporte 
void percursoMinimo(Grafo* g, int origem) { 

	int numeroVertices = g->numeroVertices; 

	// Inicializar o vetor de visitados
	bool* visitados = malloc(numeroVertices * sizeof(bool)); 

	for (int i = 0; i < numeroVertices; i++) { 
		visitados[i] = false;
	} 

	// Inicializar o vetor de caminho
	int caminho[100 + 1]; // colcoar contstante   
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

	//Limpar a consola 
	system("cls");

	//Imprimir o caminho a ser percorrido para a recolha dos meios de transporte
	imprimirCaminho(caminho, posicao);

	system("pause");
	system("cls");

	//Declharar variáveis
	int capacidadeCamiao = 20;
	int capacidadeDisponivel = capacidadeCamiao;

	Transporte* Recolhidos[100];
	int numeroRecolhidos = 0;

	//Função para a recolha dos meios 
	recolherMeios(g, origem, Recolhidos, &numeroRecolhidos, capacidadeCamiao, caminho, posicao);

	printf("\n \n");

	//Imprimir na consola os meios de transporte recolhidos 
	imprimirRecolhidos(Recolhidos, numeroRecolhidos);

	//Libertar a memoria dos visitados (apoio na construção do percurso a ser recolhido)
	free(visitados);
}

//Recolher os meios de transporte 
void recolherMeios(Grafo* g, int origem, Transporte* recolhidos[], int* numeroRecolhidos, int capacidadeCamiao, int caminho[], int posicao) {  
	
	int capacidadeDisponivel = capacidadeCamiao;
	int naoRecolhidos = 0;
	Transporte* naoRecolhidosArray[100]; // Tamanho máximo de 100, ajuste conforme necessário

	for (int i = 0; i <= posicao && capacidadeDisponivel > 0; i++) {
		int vertice = caminho[i];

		Transporte* transporte = encontrarTransportePorVertice(g, vertice);

		if (transporte != NULL) {
			int volumeCamiao = (strcmp(transporte->tipo, "TROTINETE") == 0) ? 2 : 5;  

			if (volumeCamiao <= capacidadeDisponivel) {
				transporte->bateria = 100.0;  
				transporte->autonomia = 80.0;  
				strcpy(transporte->geocodigo, "///cantarola.sondado.nevoeiro"); 
	
				capacidadeDisponivel -= volumeCamiao; 

				recolhidos[*numeroRecolhidos] = transporte; 
				(*numeroRecolhidos)++; 
			}
			else {
				naoRecolhidosArray[naoRecolhidos] = transporte; 
				naoRecolhidos++; 
			}
		}
		else {
			if (vertice != 0) {
				printf("TRANSPORTE NAO ENCONTRADO PARA O VERTICE %d\n", vertice);  
			}
		}
		
		//Guardar a lista de meios de transporte no ficheiro .bin
		saveAlterarDadosTransportes(g->meios);
		//Atualizar o ficheiro dos não recolhidos 
		atualizarFicheiroNaoRecolhidos ("NRecolhidos.bin", naoRecolhidosArray, naoRecolhidos);
	}

	if (naoRecolhidos > 0) { 

		//Imprimir os transportes nao recolhidos
		imprimirNaoRecolhidos(naoRecolhidosArray, naoRecolhidos); 
		//Guardar os dados nao recolhidos em formato .bin 
		saveNaoRecolhidos(naoRecolhidosArray, naoRecolhidos, "NRecolhidos.bin"); 
	}
}

//Imprimir na consola o caminho a ser percorrido
void imprimirCaminho(int caminho[], int posicao) { 

	// Imprimir Percuros a ser percorrido 
	printf("------------------------- ITENERAIO MAIS CURTO -------------------\n"); 
	printf("ITENERARIO: ");
	for (int i = 0; i <= posicao; i++) {
		printf("%d ", caminho[i]);
	}

	printf("\n"); 
} 

//Imprimir na consola os meios de transporte que foram recolhidos
void imprimirRecolhidos(Transporte* recolhidos[], int numeroRecolhidos) {

	// Imprimir os transportes recolhidos 
	printf("\t++++++++ MEIOS DE TRANSPORTE RECOLHIDOS ++++++++++\n");
	printf("\n"); 

	//Cabeçalho da tabela
	printf("| %-5s | %-10s |\n", "ID", "TIPO");
	printf("|--------------------|\n");
	
	for (int i = 0; i < numeroRecolhidos; i++) { 
		Transporte* transporte = recolhidos[i]; 

		//Imprimir na consola os dados
		printf("| %-5d | %-10s |\n", transporte->codigo, transporte->tipo);
	}

	printf("\n"); 
}  

//Imprimir na consola os meios de transporte nao recolhidos 
void imprimirNaoRecolhidos(Transporte* naoRecolhidos[], int numeroNaoRecolhidos) {

	printf("\t++++++++ MEIOS DE TRANSPORTE NAO RECOLHIDOS ++++++++++\n");

	printf("\n| %-5s | %-10s |\n", "ID", "TIPO");
	printf("|--------------------|\n"); 

	for (int i = 0; i < numeroNaoRecolhidos; i++) {

		printf("| %-5d | %-10s |\n", naoRecolhidos[i]->codigo, naoRecolhidos[i]->tipo); 
	}

	printf("\n\n");  
} 

//Encotrar o meio de transporte no vertice 
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

//Função para encontrar os meios de transporte mais próximos com a bateria inferior a 50% 
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
		
	return vizinhoProximo;
} 

//Guardados os meios de transporte não recolhidos 
void saveNaoRecolhidos(Transporte* naoRecolhidos[], int numeroNaoRecolhidos, const char* TransportesNaoRecolhidos) {

	FILE* ficheiro = fopen(TransportesNaoRecolhidos, "wb"); 

	if (ficheiro == NULL) {
		printf("ERRO AO ABRIR O FICHEIRO %s \n", TransportesNaoRecolhidos); 
	}

	fwrite(&numeroNaoRecolhidos, sizeof(int), 1, ficheiro);

	for (int i = 0; i < numeroNaoRecolhidos; i++) {
		fwrite(naoRecolhidos[i], sizeof(Transporte), 1, ficheiro);  
	}

	fclose(ficheiro); 

	//printf("GUARDADO COM SUCESSO NO FICHEIRO %s\n", TransportesNaoRecolhidos);  
	printf("\n");
}

//Função para ler os dados do ficheiro 
void lerDadosDeArquivo(const char* TransportesNaoRecolhidos) {
	FILE* arquivo = fopen(TransportesNaoRecolhidos, "rb");
	if (arquivo == NULL) { 
		printf("Erro ao abrir o arquivo %s.\n", TransportesNaoRecolhidos);
		return; 
	}

	// Ler o número de meios não recolhidos do arquivo
	int numeroNaoRecolhidos;
	fread(&numeroNaoRecolhidos, sizeof(int), 1, arquivo);

	// Criar um array temporário para armazenar os meios não recolhidos
	Transporte* naoRecolhidosArray = malloc(numeroNaoRecolhidos * sizeof(Transporte));

	// Ler os dados dos meios não recolhidos do arquivo
	for (int i = 0; i < numeroNaoRecolhidos; i++) {
		fread(&naoRecolhidosArray[i], sizeof(Transporte), 1, arquivo);
	}

	fclose(arquivo);

	// Imprimir os dados lidos na console
	printf("\t+++++++++++ MEIOS DE TRANSPORTE NAO RECOLHIDOS +++++++++++++\n");
	printf("\n| %-5s | %-10s |\n", "ID", "TIPO");
	printf("|--------------------|\n");

	for (int i = 0; i < numeroNaoRecolhidos; i++) {
		printf("| %-5d | %-10s |\n", naoRecolhidosArray[i].codigo, naoRecolhidosArray[i].tipo);
	}

	printf("\n%d meio(s) de transporte nao foram possiveis de recolher \n\n", numeroNaoRecolhidos);

	// Liberar a memória alocada para o array de meios não recolhidos
	free(naoRecolhidosArray);
}

//Atualziar o ficheiro de não recolhidos 
void atualizarFicheiroNaoRecolhidos (const char* nomeArquivo, Transporte* naoRecolhidosArray, int numeroNaoRecolhidos) {
	FILE* arquivo = fopen(nomeArquivo, "wb");
	if (arquivo == NULL) {
		printf("Erro ao abrir o arquivo %s para atualizacao.\n", nomeArquivo);
		return;
	}

	// Escrever o número de meios não recolhidos no arquivo
	fwrite(&numeroNaoRecolhidos, sizeof(int), 1, arquivo);

	// Escrever os dados dos meios não recolhidos no arquivo
	for (int i = 0; i < numeroNaoRecolhidos; i++) {
		fwrite(&naoRecolhidosArray[i], sizeof(Transporte), 1, arquivo);
	}

	fclose(arquivo);
}
