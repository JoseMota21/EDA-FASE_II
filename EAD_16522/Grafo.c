#define _CRT_SECURE_NO_DEPRECATE 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "Grafo.h"  

//Criar v�rtices apartir da lista dos meios de transporte 
Vertice* criarVertices(Grafo** g, Transporte* meios) {
	
	// Identifica��o do v�rtice 
	int VerticeID = 1;

	// Lista ligada dos meios de transporte
	Transporte* atual = meios;

	// Alocar a mem�ria para criar o vertice 0 
	Vertice* vertice0 = malloc(sizeof(Vertice)); 

	//Vertice 0 definido como fixo (Localiza��o, Tipo, ID e bateria)
	strcpy(vertice0->geocodigo, "///cantarola.sondado.nevoeiro");  
	strcpy(vertice0->Tipo, "ARMAZEM");
	vertice0->ID = 0;
	vertice0->bateria = 0.0;
	vertice0->meios = NULL;
	vertice0->VerticeID = 0;
	vertice0->seguinte = NULL;
	vertice0->adjacencias = NULL;
	

	// Criar o grafo  
	*g = criarGrafo(100); 
	//Se g null 
	if (*g == NULL) { 
		//Liberta o espa�o alocado ao vertice 0 
		free(vertice0);
		return NULL;
	}

	//Definir o vertice 0 como o primeiro da lista de v�rtices 
	(*g)->vertices = vertice0;  
	//Aponta para a lista de meios de transporte 
	(*g)->meios = meios; 

	// Percorrer os meios de transporte at� o fim  
	while (atual != NULL) {  

		// Alocar mem�ria para o novo v�rtice 
		Vertice* novo = malloc(sizeof(Vertice));

		// Copiar os campos do meio de transporte para o v�rtice  
		strcpy(novo->geocodigo, atual->geocodigo); 
		strcpy(novo->Tipo, atual->tipo); 
		novo->ID = atual->codigo;
		novo->bateria = atual->bateria;
		novo->meios = atual;
		novo->VerticeID = VerticeID; 
		novo->seguinte = NULL;
		novo->adjacencias = NULL;  
	
		//Ultimo v�rtice da lista de v�rtices (Inicialmente o �ltimo v�rtice � o primeiro)
		Vertice* ultimo = (*g)->vertices; 

		//Percorre a lista de v�rtice at� encontrar o �ltimo v�rtice 
		while (ultimo->seguinte != NULL) { 
			//Aponta para o pr�ximo v�rtice da lista 
			ultimo = ultimo->seguinte;
		}
		
		//Ap�s encontrar o ultimo v�rtice aponta para o novo v�rtice 
		ultimo->seguinte = novo;

		// Incrementar a identifica��o dos v�rtices 
		VerticeID++;

		// Apontar para o pr�ximo meio de transporte da lista dos meios de transporte
		atual = atual->seguinte; 
	} 

	//Total de v�rtices na lista 
	(*g)->numeroVertices = VerticeID; 
	
	//Guardar os v�rtices no ficheiro txt  
	guardarVertices(*g); 

	//Retorna o apontador para o primeiro v�rtice 
	return (*g)->vertices;
}

//Fun��o para encontrar os vertices no grafo atrav�s do ID 
Vertice* encontrarVertice(Grafo* g, int id) {

	//Vari�vel que recebe o apontador para o primeiro vertice 
	Vertice* atual = g->vertices;

	//Percorre a lista de v�rtices at� ao fim 
	while (atual != NULL) {
			
			//Se o vertice ID for igual ao desejado retorna o vertice atual 
			if (atual->VerticeID == id) {
				return atual;
			}
		//Avan�a para o pr�ximo vertice da lista 
		atual = atual->seguinte;
	}
	return NULL;
} 

//Criar a estrutura Grafo 
Grafo* criarGrafo(int numeroVertices) {

	// Aloca mem�ria para a estrutura do grafo
	Grafo* g = malloc(sizeof(Grafo));
	//Se grafo for NULL retorna NULL 
	if (g == NULL) {
		
		printf("GRAFO NULO\n"); 
		return NULL;
	}

	// Inicializa o n�mero de v�rtices
	g->numeroVertices = numeroVertices;

	// Aloca um bloco de mem�ria para armazenar a matriz de visitados 
	g->visitados = malloc(numeroVertices * sizeof(bool*)); 

	//Se visitados for NULL (Erro na aloca��o de mem�ria)
	if (g->visitados == NULL) {
		//Liberta a mem�ria do grafo 
		free(g);
		return NULL;
	}

	// Aloca mem�ria para a matriz de adjac�ncia
	g->matrizadj = malloc(numeroVertices * sizeof(Aresta*));

	//Se a matriz de adjancencia for NULL (Erro na aloca��o de mem�ria)
	if (g->matrizadj == NULL) {
		
		//Liberta a memoria dos visitados 
		free(g->visitados);
		free(g);
		return NULL;
	}

	// Percorre a matriz de visitados e a matriz de adjac�ncia (Inicialziar as matrizes)
	for (int i = 0; i < numeroVertices; i++) {

		//Inicializa todos os valores com o valor de zero  
		g->visitados[i] = calloc(numeroVertices, sizeof(bool)); 
		g->matrizadj[i] = calloc(numeroVertices, sizeof(Aresta*));

		//Verificar se aloca��o de memoria foi feito corretamente 
		if (g->visitados[i] == NULL || g->matrizadj[i] == NULL) {
			
			// Liberta a mem�ria alocada anteriormente (visitados e matriz de adjacencia)
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

	// Inicializa os v�rtices como NULL
	g->vertices = NULL;

	//Retorna o grafo 
	return g;
}

//Cria as arestas entre dois pontos (orige e destino)
Aresta* criarAresta(Grafo* g, int origem, int destino, float peso) {

	//Procura os v�rtices de origem e destino (Garantir que os v�rtices existem) 
	Vertice* verticeOrigem = encontrarVertice(g, origem);
	Vertice* verticeDestino = encontrarVertice(g, destino);


	// Verificar se a origem e o destino s�o v�lidos
	if (origem < 0 || origem >= g->numeroVertices || destino < 0 || destino >= g->numeroVertices) {
		printf("VERTICES INVALIDOS.\n"); 

		return NULL;
	}
	
	//Verifica se encontrou o v�rtice de origem
	if (verticeOrigem == NULL) {
		printf("VERTICE ORIGEM NAO ENCONTRADO.\n");
		return NULL;
	}
	//Verifica se encontrou o v�rtice de destino 
	if (verticeDestino == NULL) {
		printf("VERTICE DE DESTINO NAO ENCONTRADO\n");
		return NULL;
	}

	//Verifica se j� existe uma aresta entre a origem e o destino 
	if (g->matrizadj[origem][destino] != NULL) { 
		//Se existir avisa o utilizador 
		printf("ARESTA JA EXISTE ENTRE OS VERTICES %d e %d\n", origem, destino);
		return NULL;
	}

	// Criar a nova aresta (Origem -> Destino)
	Aresta* novaArestaOrigem = malloc(sizeof(Aresta));

	//Se houver erro na aloca��o de mem�ria avisa o utilzador 
	if (novaArestaOrigem == NULL) {
		printf("ERRO: Falha ao alocar memoria para a nova aresta.\n");
		return NULL;
	}
	 
	//Vertice adjacente recebe o valor de destino (V�rtice a ser conectado apartir da origem) 
	novaArestaOrigem->vertice_adjacente = destino; 
	//Peso = distancia entre a origem e o destino 
	novaArestaOrigem->peso = peso; 
	//N�o possui uma aresta adjacente seguinte
	novaArestaOrigem->proximo = NULL;  

	// Atualizar a matriz de adjac�ncia
	g->matrizadj[origem][destino] = novaArestaOrigem;


	// Criar a aresta (Destino -> origem) 
	Aresta* novaArestaDestino = malloc(sizeof(Aresta));  

	//Se falha na aloca��o de mem�ria avisa o utilizador 
	if (novaArestaDestino == NULL) { 
		printf("ERRO: Falha ao alocar memoria para a nova aresta.\n");
		return NULL;
	}

	//Vertice adjacente recebe o valor de origem (V�rtice a ser conectado apartir do destino) 
	novaArestaDestino->vertice_adjacente = origem; 
	// Peso = distancia entre o destino e a origem
	novaArestaDestino->peso = peso; 
	//N�o possui uma aresta adjacente seguinte 
	novaArestaDestino->proximo = NULL; 

	// Atualizar a matriz de adjac�ncia
	g->matrizadj[destino][origem] = novaArestaDestino;  

	//Guardar o grafo em txt 
	guardarGrafo(g); 

	//Retorna a nova aresta criada 
	return novaArestaOrigem;  
}
 
//Imprimir na consola o grafo
void imprimirGrafo(Grafo* g) {

	//Apontador para a lista dos v�rtices 
	Vertice* atualVertice = g->vertices;
	Aresta* atualAresta;  // declarar para percorrer as arestas 

	//Cabe�alho da tabela 
	printf("------------------------- GRAFO-------------------\n"); 
	printf("\n");
	printf("|%-5s | %-5s | %-10s|\n", "ORIGEM", "DESTINO", "DISTANCIA"); 

	//Percorre os v�rtices de origem do grafo 
	for (int origem = 0; origem < g->numeroVertices; origem++) {

		//Percorre os v�rtices de destino do grafo  
		for (int destino = 0; destino < g->numeroVertices; destino++) {

			//Se aresta entre a origem e o destino existir 
			if (g->matrizadj[origem][destino] != NULL) {

				//Apontador para aresta atual 
				Aresta* aresta = g->matrizadj[origem][destino];

				//Enquanto que aresta for != NULL 
				while (aresta != NULL) {
					//Immprime na consola os vertice origem e destino (vizinho) e peso 
					printf("|%-6d | %-7d | %-10.2f|\n", origem, aresta->vertice_adjacente, aresta->peso);

					//Passa para a pr�xima aresta 
					aresta = aresta->proximo;
				}
			}
		}
	}
}  

//Listar na consola os vertices 
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

	//Percorre a lista dos v�rtices at� ao fim 
	while (vertice != NULL) {

		//Imprime na consola a informa��o do ID do v�rtice, ID do meio de transporte, o tipo de transporte, bateria e localiza��o 
		printf("|%-12d | %-5d | %-10s | %-10.2f | %-30s|\n", vertice->VerticeID, vertice->ID, vertice->Tipo, vertice->bateria, vertice->geocodigo);

		//Passa para o pr�ximo v�rtice
		vertice = vertice->seguinte;
	}

	printf("\n");

	//Retorna o apontador para o primeiro v�rtice 
	return g->vertices;  
} 

//Guardar o grafo no ficheiro txt 
Grafo* guardarGrafo(Grafo* g) {

	// Abrir o ficheiro para escrita
	FILE* ficheiroGrafo = fopen("Grafo.txt", "w");

	// Verificar se o arquivo foi aberto corretamente 
	if (ficheiroGrafo == NULL) {
		printf("ERRO AO CRIAR O ARQUIVO!\n");
		return NULL;
	}

	// Escrever os dados formatados do grafo no arquivo
	fprintf(ficheiroGrafo, "ORIGEM;DESTINO;DISTANCIA\n");

	// Percorrer no grafo os vertices de origem 
	for (int origem = 0; origem < g->numeroVertices; origem++) {

		//Percorre no grafo os vertices de destino 
		for (int destino = 0; destino < g->numeroVertices; destino++) {

			// Verificar se h� uma aresta entre os v�rtices de origem e destino
			if (g->matrizadj[origem][destino] != NULL) {  

				//Recebe a aresta entre os v�rtices de origem e destino
				Aresta* aresta = g->matrizadj[origem][destino]; 

				//Percorre as arestaas at� ao fim
				while (aresta != NULL) {

					// Escreve no ficheiro as informa��es do grafo: origem, destino e peso da aresta
					fprintf(ficheiroGrafo, "%d;%d;%.2f\n", origem, destino, aresta->peso);  
					//Passa para a pr�xima aresta 
					aresta = aresta->proximo;  
				}
			} 
		}
	}

	// Fechar o ficheiro 
	fclose(ficheiroGrafo);

	//Retorna o grafo 
	return g;
} 

//Ligar todos os vertices 
void conetarVertices(Grafo* g) {

	//Primeiro vertice do grafo 
	Vertice* verticeAtual = g->vertices; 

	//Percorre a lista dos v�rtice at� ao fim
	while (verticeAtual != NULL) {  

		//Atribuir o endere�o do proximo v�rtice 
		Vertice* proximoVertice = verticeAtual->seguinte; 

		//Executa enquanto houver um proximo v�rtice  
		while (proximoVertice != NULL) {
			
			//Declarar vari�veis para o apoio da convers�o das coordenadas 
			float lat1, lng1, lat2, lng2;  

			//Obtem as coordenadas do v�rtice atual (origem)
			get_coordinates(verticeAtual->geocodigo, API_KEY, &lat1, &lng1);  
			//Obtem as coordenadas do proximo v�rtice (destino)
			get_coordinates(proximoVertice->geocodigo, API_KEY, &lat2, &lng2); 

			// Calcular a dist�ncia entre os v�rtices  (origem e destino)
			float distancia = haversine_distance(lat1, lng1, lat2, lng2); 

			// Criar as arestas entre os v�rtices 
			criarAresta(g, verticeAtual->VerticeID, proximoVertice->VerticeID, distancia); 

			//Passa para o proximo vertice seguinte
			proximoVertice = proximoVertice->seguinte; 
		}

		//Passa para o pr�ximo v�rtice 
		verticeAtual = verticeAtual->seguinte; 
	}
}

//Guardar vertices em ficheiro txt 
Grafo* guardarVertices (Grafo* g) {

	// Abrir o ficheiro dos v�rtices em escrita
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

	//Inicia no primeiro v�rtice
	Vertice* atual = g->vertices;
	 
	//Percorre a lista dos vertices at� ao fim 
	while (atual != NULL) {

		//Escreve no ficheiro o ID do v�rtice, o ID do meio de transporte, o tipo de meio de transporte, a bateria e a sua localiza��o  
		fprintf(ficheiroVertice, "%d;%d;%s;%.2f;%s\n",atual->VerticeID, atual->ID, atual->Tipo, atual->bateria, atual->geocodigo);
		
		//Passa para o seguinte vertice 
		atual = atual->seguinte;
	}

	// fechar o ficheiro
	fclose(ficheiroVertice);
}   

//Percuros minimo de recolha dos meios de transporte 
void percursoMinimo(Grafo* g, int origem) { 

	//Variavel do n�mero de v�rtices existentes no grafo
	int numeroVertices = g->numeroVertices; 

	// Vetor de visitados para registar quais os v�rtices foram visitados 
	bool* visitados = malloc(numeroVertices * sizeof(bool)); 

	//Percorre todos os elementos do vetor e inicializa como false (Como n�o visitados)
	for (int i = 0; i < numeroVertices; i++) { 
		visitados[i] = false;
	} 

	//Declarar vari�veis
	int caminho[100 + 1]; //Array para armazenar o caminho que minimo. (+1 armazena o v�rtice origem (armaz�m)) (Armazena os v�rtices do caminho minimo)
	int posicao = 0; //Posi��o atual  

	caminho[posicao] = origem; //Garantir que o v�rtice origem � o ponto de partida 
	visitados[origem] = true; // Marcar o vertice 0 como visitado (true)


	//Construir o percurso minimo recorrendo ao vizinho mais pr�ximo 
	for (int i = 0; i < numeroVertices - 1; i++) {

		//Atribui o vertice atual ao caminho 
		int verticeAtual = caminho[posicao];
		//Guardar na vari�vel vizinhoMaisProximo o vizinho mais proximo da vari�vel atual 
		int vizinhoMaisProximo = EncontrarMaisProximo50(g, verticeAtual, visitados);

		if (vizinhoMaisProximo == -1) {
			// Todos os v�rtices com bateria inferior a 50% j� foram visitados 
			//Interromper o loop, todos os v�rtices visitados 
			break;
		}

		//Adicionar o vizinhoMaisProximo no array
		//++posi��o incrementa (Avan�ar para a pr�xima posi��o para n�o escrever em cima do que foi escrito) 
		//Cada v�rtice encontrado � adicionado para para a pr�xima posi��o do array
		caminho[++posicao] = vizinhoMaisProximo;
		visitados[vizinhoMaisProximo] = true; // Marcar o v�rtice como visitado 
	}

	//Voltar para a origem (armaz�m) Adiciona a origem ao final do array 
	caminho[++posicao] = origem;

	//Limpar a consola 
	system("cls");

	//Imprimir o caminho a ser percorrido
	//Imprime os valores contidos no array que ser� o percurso minimo 
	imprimirCaminho(caminho, posicao);

	system("pause"); //Pausa no sistema 
	system("cls"); //Limpar a consola 

	//Declharar vari�veis
	int capacidadeCamiao = 20; // Capacidade maxima do cami�o (m3) - volume 
	int capacidadeDisponivel = capacidadeCamiao; //Capacidade disponivel do cami�o 

	Transporte* Recolhidos[100]; //Armazena o n�mero de transporte recolhidos 
	int numeroRecolhidos = 0; // N�mero de transportes recolhidos 

	//Fun��o para a recolha dos meios  
	recolherMeios(g, origem, Recolhidos, &numeroRecolhidos, capacidadeCamiao, caminho, posicao);

	printf("\n \n");

	//Imprimir na consola os meios de transporte recolhidos 
	imprimirRecolhidos(Recolhidos, numeroRecolhidos);

	//Libertar a memoria dos visitados (apoio na constru��o do percurso a ser recolhido)
	free(visitados);
}

//Recolher os meios de transporte ao longo do percurso definido pelo o caminho 
void recolherMeios(Grafo* g, int origem, Transporte* recolhidos[], int* numeroRecolhidos, int capacidadeCamiao, int caminho[], int posicao) {  
	
	//Declarar vari�veis 
	int capacidadeDisponivel = capacidadeCamiao; // Capacidade m�xima do cami�o 
	int naoRecolhidos = 0; //N�mero de recolhidos 
	Transporte* naoRecolhidosArray[100]; //Armazeno os trasportes que n�o foram recolhidos 

	//Percorre at� � posi��o final enquanto houver espa�o no cami�o 
	for (int i = 0; i <= posicao && capacidadeDisponivel > 0; i++) {
		
		int vertice = caminho[i]; // Valor do v�rtice do caminho 

		//Encontrar o meio de transporte associado a esse v�rtice 
		Transporte* transporte = encontrarTransportePorVertice(g, vertice);

		//Se os meios de transporte for diferente de NULL 
		if (transporte != NULL) { 

			//Se o tipo de transporte for trotinete o volume ocupado � de 2 m3, caso o volume de trotinete seja != de trotinete (BIKE)
			//o volume ocupado no camiao ser� de 5 m3 
			int volumeCamiao = (strcmp(transporte->tipo, "TROTINETE") == 0) ? 2 : 5;  

			//Se o volume do cami�o o volume do cami�o necess�rio para transportar o meio de transporte � menor ou igual 
			//� capacidade disponviel do cami�o, o meio de transporte pode ser recolhido 
			if (volumeCamiao <= capacidadeDisponivel) {
				
				transporte->bateria = 100.0;  //Transporte recolhido bateria 100%  
				transporte->autonomia = 80.0;  //Transporte recolhido autonomia 80km 
				strcpy(transporte->geocodigo, "///cantarola.sondado.nevoeiro"); //Meio de transporte com a localiza��o do armaz�m
				
				//Capacidde disponivel � reduzida 
				capacidadeDisponivel -= volumeCamiao; 

				//O meio de transporte � adicionado no array de recolhidos 
				recolhidos[*numeroRecolhidos] = transporte; 
				(*numeroRecolhidos)++; //Incrementa (n�mero de transportes recolhidos ) 

			}
			else {
				//Se o volume do cami�o necess�rio para transportar o meio de transporte for maior do que a capacidade disponivel no cami�o, 
				//o meio de transporte n�o pode ser recolhido 

				naoRecolhidosArray[naoRecolhidos] = transporte;  // O meio de transporte � adicionado ao array dos n�o recolhidos 
				naoRecolhidos++; //N�mero de transporte n�o recolhidos 
			}
		}
		else {
			//Exclui o v�rtice zero caso o meio de transporte n�o for encontrado 
			if (vertice != 0) {
				printf("TRANSPORTE NAO ENCONTRADO PARA O VERTICE %d\n", vertice);  
			}
		}
		
		//Guardar a lista de meios de transporte no ficheiro .bin 
		saveAlterarDadosTransportes(g->meios);

		//Atualizar o ficheiro dos n�o recolhidos 
		atualizarFicheiroNaoRecolhidos ("NRecolhidos.bin", naoRecolhidosArray, naoRecolhidos);
	} 

	//Se existir meios de transporte n�o recolhidos 
	if (naoRecolhidos > 0) { 

		//Imprimir os transportes nao recolhidos 
		imprimirNaoRecolhidos(naoRecolhidosArray, naoRecolhidos); 
		//Guardar os dados nao recolhidos em formato .bin 
		saveNaoRecolhidos(naoRecolhidosArray, naoRecolhidos, "NRecolhidos.bin"); 
	}
}

//Imprimir na consola o caminho minimo (imprime os valores contidos no array caminho)
void imprimirCaminho(int caminho[], int posicao) { 

	//Cabe�alho
	printf("------------------------- ITENERAIO MAIS CURTO -------------------\n"); 
	printf("ITENERARIO: ");
	 
	//Imprimir o caminho 
	for (int i = 0; i <= posicao; i++) {
		printf("%d ", caminho[i]);
	}

	printf("\n"); 
} 

//Imprimir na consola os meios de transporte que foram recolhidos
void imprimirRecolhidos(Transporte* recolhidos[], int numeroRecolhidos) {

	//Cabe�alho da tabela
	printf("\t++++++++ MEIOS DE TRANSPORTE RECOLHIDOS ++++++++++\n");
	printf("\n"); 

	printf("| %-5s | %-10s |\n", "ID", "TIPO");
	printf("|--------------------|\n");
	
	//Percorre o array dos recolhidos e imprime na consola 
	for (int i = 0; i < numeroRecolhidos; i++) {  

		//Apontador para o transporte atual 
		Transporte* transporte = recolhidos[i]; 
		
		//Imprimir na consola os dados (ID do meio de transporte e o tipo de transporte)
		printf("| %-5d | %-10s |\n", transporte->codigo, transporte->tipo); 
	}

	printf("\n"); 
}  

//Imprimir na consola os meios de transporte nao recolhidos 
void imprimirNaoRecolhidos(Transporte* naoRecolhidos[], int numeroNaoRecolhidos) {

	//Cabe�alho da tabela 
	printf("\t++++++++ MEIOS DE TRANSPORTE NAO RECOLHIDOS ++++++++++\n");
	printf("\n| %-5s | %-10s |\n", "ID", "TIPO");
	printf("|--------------------|\n"); 

	//Percorre os meios de transporte que n�o foram recolhidos e impre na consola 
	for (int i = 0; i < numeroNaoRecolhidos; i++) {
		//Imprimir na consola com o ID do meio de transporte e o tipo de transporte (BIKE) (TROTINETE)
		printf("| %-5d | %-10s |\n", naoRecolhidos[i]->codigo, naoRecolhidos[i]->tipo);  
	}

	printf("\n\n");  
} 

//Encotrar o meio de transporte no vertice 
Transporte* encontrarTransportePorVertice(Grafo* g, int verticeID) { 
	
	// Percorrer a lista de v�rtices
	Vertice* vertice = g->vertices; 
	while (vertice != NULL) { 

		// Verificar se o ID do v�rtice corresponde ao ID desejado
		if (vertice->VerticeID == verticeID) { 
			return vertice->meios;   
		}
		vertice = vertice->seguinte; 
	}
	return NULL;
} 

//Fun��o para encontrar os meios de transporte mais pr�ximos com a bateria inferior a 50% 
int EncontrarMaisProximo50(Grafo* g, int verticeAtual, bool* visitados) {

	//Declarar vari�veis 
	int numeroVertices = g->numeroVertices; // N�mero de v�rtices no grafo 
	float menorPeso = FLT_MAX; //Maior valor para o tipo flaot 
	int vizinhoProximo = -1;  //Inicializar como -1 (Nenhum v�rtice encotrado)

	//Percorre todos os v�rtices 
	for (int i = 0; i < numeroVertices; i++) {

		//Verifica se n�o � o v�rtie em que estamos e se ainda n�o foi visitado 
		if (i != verticeAtual && !visitados[i]) {  
			
			//Atribui � aresta a referencia que liga o v�rtice atual ao v�rtice i 
			Aresta* aresta = g->matrizadj[verticeAtual][i]; 

			//Encontrar o v�rtice correspondente ao v�rtice i 
			Vertice* vertice = encontrarVertice(g, i); 

			//Se aresta n�o for nula e a bateria do transporte for inferior a 50% 
			if (aresta != NULL && vertice->bateria < 50.0) {
				
				//Comparar o peso da aresta atual com o peso encontrado at� ao momento 
				if (aresta->peso < menorPeso) {
					menorPeso = aresta->peso;
					vizinhoProximo = i;
				}
			}
		}
	}
	
	//Retorna o v�rtice mais pr�ximo 
	return vizinhoProximo;
} 

//Guardados os meios de transporte n�o recolhidos em ficheiro bin
void saveNaoRecolhidos(Transporte* naoRecolhidos[], int numeroNaoRecolhidos, const char* TransportesNaoRecolhidos) {

	//Abre o ficheiro em modo escrita bin�aria 
	FILE* ficheiro = fopen(TransportesNaoRecolhidos, "wb"); 

	//Se o ficheiro for NULL avisa o utilizador 
	if (ficheiro == NULL) {
		printf("ERRO AO ABRIR O FICHEIRO %s \n", TransportesNaoRecolhidos); 
	}

	//Escreve no ficheiro em bin os n�o recolhidos 
	fwrite(&numeroNaoRecolhidos, sizeof(int), 1, ficheiro);

	//Percorre o arrau dos n�o recolhidos e escreve no ficheiro 
	for (int i = 0; i < numeroNaoRecolhidos; i++) {
		//Escreve no ficheiro 
		fwrite(naoRecolhidos[i], sizeof(Transporte), 1, ficheiro);  
	}

	//Fechar o ficheiro 
	fclose(ficheiro); 
 
	printf("\n");
}

//Fun��o para ler os dados do ficheiro 
void lerDadosDeArquivo(const char* TransportesNaoRecolhidos) {

	//Abir o ficheiro em modo de leitura em .bin
	FILE* ficheiro = fopen(TransportesNaoRecolhidos, "rb");
	
	//Se o ficheiro null avisa o utilizador  
	if (ficheiro == NULL) { 
		printf("Erro ao abrir o arquivo %s.\n", TransportesNaoRecolhidos);
		return; 
	}

	//Declarar vari�vies 
	int numeroNaoRecolhidos;  // Numero de n�o recolhidos 
	fread(&numeroNaoRecolhidos, sizeof(int), 1, ficheiro); //L� o n�mero de meios n�o recolhidos 

	// Criar um array tempor�rio para armazenar os meios n�o recolhidos 
	Transporte* naoRecolhidosArray = malloc(numeroNaoRecolhidos * sizeof(Transporte));

	// Ler os dados dos meios n�o recolhidos do ficheiro  
	for (int i = 0; i < numeroNaoRecolhidos; i++) {
		fread(&naoRecolhidosArray[i], sizeof(Transporte), 1, ficheiro); // Os dados do ficheiro e guardar no array tempor�rio 
	}
	//Fechar o ficheiro 
	fclose(ficheiro); 

	//Imprimir na consola os meios de transporte n�o recolhidos 
	imprimirMeiosNaoRecolhidos(naoRecolhidosArray, numeroNaoRecolhidos); 

	//Libertar a mem�ria do array temporario 
	free(naoRecolhidosArray);
}
 
//Fun��o para imprimir os meis de transporte n�o recolhidos 
void imprimirMeiosNaoRecolhidos(Transporte* naoRecolhidosArray, int numeroNaoRecolhidos) { 
	
	//Cabe�alho da tabela 
	printf("\t+++++++++++ MEIOS DE TRANSPORTE NAO RECOLHIDOS +++++++++++++\n"); 
	printf("\n| %-5s | %-10s |\n", "ID", "TIPO"); 
	printf("|--------------------|\n"); 

	//Percorre o array e imprime cada meio de transporte n�o recolhido na consola 
	for (int i = 0; i < numeroNaoRecolhidos; i++) { 
		printf("| %-5d | %-10s |\n", naoRecolhidosArray[i].codigo, naoRecolhidosArray[i].tipo); //Imprime o transporte n�o recolhido 
	}
	
	//Alera o utilizador dos meios de transporte n�o recolhidos 
	printf("\n%d meio(s) de transporte nao foram possiveis de recolher \n\n", numeroNaoRecolhidos);  
}

//Atualziar o ficheiro de n�o recolhidos 
void atualizarFicheiroNaoRecolhidos (const char* nomeFicheiro, Transporte* naoRecolhidosArray, int numeroNaoRecolhidos) {
	
	//Abrir o ficheiro em modo de escrito em .bin 
	FILE* ficheiro = fopen(nomeFicheiro, "wb");
	
	//Se o ficheiro for nulo avisa o utilizador 
	if (ficheiro == NULL) {
		printf("Erro ao abrir o arquivo %s para atualizacao.\n", nomeFicheiro);
		return;
	}

	// Escrever o n�mero de meios n�o recolhidos no arquivo 
	fwrite(&numeroNaoRecolhidos, sizeof(int), 1, ficheiro); 

	// Escrever os dados dos meios n�o recolhidos no arquivo
	for (int i = 0; i < numeroNaoRecolhidos; i++) {
		fwrite(&naoRecolhidosArray[i], sizeof(Transporte), 1, ficheiro);
	}
	//Fecha o ficheiro 
	fclose(ficheiro);
}
