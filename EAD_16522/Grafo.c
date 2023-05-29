#define _CRT_SECURE_NO_DEPRECATE 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "Grafo.h"  

//Criar vértices apartir da lista dos meios de transporte 
Vertice* criarVertices(Grafo** g, Transporte* meios) {
	
	// Identificação do vértice 
	int VerticeID = 1;

	// Lista ligada dos meios de transporte
	Transporte* atual = meios;

	// Alocar a memória para criar o vertice 0 
	Vertice* vertice0 = malloc(sizeof(Vertice)); 

	//Vertice 0 definido como fixo (Localização, Tipo, ID e bateria)
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
		//Liberta o espaço alocado ao vertice 0 
		free(vertice0);
		return NULL;
	}

	//Definir o vertice 0 como o primeiro da lista de vértices 
	(*g)->vertices = vertice0;  
	//Aponta para a lista de meios de transporte 
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
	
		//Ultimo vértice da lista de vértices (Inicialmente o último vértice é o primeiro)
		Vertice* ultimo = (*g)->vertices; 

		//Percorre a lista de vértice até encontrar o último vértice 
		while (ultimo->seguinte != NULL) { 
			//Aponta para o próximo vértice da lista 
			ultimo = ultimo->seguinte;
		}
		
		//Após encontrar o ultimo vértice aponta para o novo vértice 
		ultimo->seguinte = novo;

		// Incrementar a identificação dos vértices 
		VerticeID++;

		// Apontar para o próximo meio de transporte da lista dos meios de transporte
		atual = atual->seguinte; 
	} 

	//Total de vértices na lista 
	(*g)->numeroVertices = VerticeID; 
	
	//Guardar os vértices no ficheiro txt  
	guardarVertices(*g); 

	//Retorna o apontador para o primeiro vértice 
	return (*g)->vertices;
}

//Função para encontrar os vertices no grafo através do ID 
Vertice* encontrarVertice(Grafo* g, int id) {

	//Variável que recebe o apontador para o primeiro vertice 
	Vertice* atual = g->vertices;

	//Percorre a lista de vértices até ao fim 
	while (atual != NULL) {
			
			//Se o vertice ID for igual ao desejado retorna o vertice atual 
			if (atual->VerticeID == id) {
				return atual;
			}
		//Avança para o próximo vertice da lista 
		atual = atual->seguinte;
	}
	return NULL;
} 

//Criar a estrutura Grafo 
Grafo* criarGrafo(int numeroVertices) {

	// Aloca memória para a estrutura do grafo
	Grafo* g = malloc(sizeof(Grafo));
	//Se grafo for NULL retorna NULL 
	if (g == NULL) {
		
		printf("GRAFO NULO\n"); 
		return NULL;
	}

	// Inicializa o número de vértices
	g->numeroVertices = numeroVertices;

	// Aloca um bloco de memória para armazenar a matriz de visitados 
	g->visitados = malloc(numeroVertices * sizeof(bool*)); 

	//Se visitados for NULL (Erro na alocação de memória)
	if (g->visitados == NULL) {
		//Liberta a memória do grafo 
		free(g);
		return NULL;
	}

	// Aloca memória para a matriz de adjacência
	g->matrizadj = malloc(numeroVertices * sizeof(Aresta*));

	//Se a matriz de adjancencia for NULL (Erro na alocação de memória)
	if (g->matrizadj == NULL) {
		
		//Liberta a memoria dos visitados 
		free(g->visitados);
		free(g);
		return NULL;
	}

	// Percorre a matriz de visitados e a matriz de adjacência (Inicialziar as matrizes)
	for (int i = 0; i < numeroVertices; i++) {

		//Inicializa todos os valores com o valor de zero  
		g->visitados[i] = calloc(numeroVertices, sizeof(bool)); 
		g->matrizadj[i] = calloc(numeroVertices, sizeof(Aresta*));

		//Verificar se alocação de memoria foi feito corretamente 
		if (g->visitados[i] == NULL || g->matrizadj[i] == NULL) {
			
			// Liberta a memória alocada anteriormente (visitados e matriz de adjacencia)
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

	//Retorna o grafo 
	return g;
}

//Cria as arestas entre dois pontos (orige e destino)
Aresta* criarAresta(Grafo* g, int origem, int destino, float peso) {

	//Procura os vértices de origem e destino (Garantir que os vértices existem) 
	Vertice* verticeOrigem = encontrarVertice(g, origem);
	Vertice* verticeDestino = encontrarVertice(g, destino);


	// Verificar se a origem e o destino são válidos
	if (origem < 0 || origem >= g->numeroVertices || destino < 0 || destino >= g->numeroVertices) {
		printf("VERTICES INVALIDOS.\n"); 

		return NULL;
	}
	
	//Verifica se encontrou o vértice de origem
	if (verticeOrigem == NULL) {
		printf("VERTICE ORIGEM NAO ENCONTRADO.\n");
		return NULL;
	}
	//Verifica se encontrou o vértice de destino 
	if (verticeDestino == NULL) {
		printf("VERTICE DE DESTINO NAO ENCONTRADO\n");
		return NULL;
	}

	//Verifica se já existe uma aresta entre a origem e o destino 
	if (g->matrizadj[origem][destino] != NULL) { 
		//Se existir avisa o utilizador 
		printf("ARESTA JA EXISTE ENTRE OS VERTICES %d e %d\n", origem, destino);
		return NULL;
	}

	// Criar a nova aresta (Origem -> Destino)
	Aresta* novaArestaOrigem = malloc(sizeof(Aresta));

	//Se houver erro na alocação de memória avisa o utilzador 
	if (novaArestaOrigem == NULL) {
		printf("ERRO: Falha ao alocar memoria para a nova aresta.\n");
		return NULL;
	}
	 
	//Vertice adjacente recebe o valor de destino (Vértice a ser conectado apartir da origem) 
	novaArestaOrigem->vertice_adjacente = destino; 
	//Peso = distancia entre a origem e o destino 
	novaArestaOrigem->peso = peso; 
	//Não possui uma aresta adjacente seguinte
	novaArestaOrigem->proximo = NULL;  

	// Atualizar a matriz de adjacência
	g->matrizadj[origem][destino] = novaArestaOrigem;


	// Criar a aresta (Destino -> origem) 
	Aresta* novaArestaDestino = malloc(sizeof(Aresta));  

	//Se falha na alocação de memória avisa o utilizador 
	if (novaArestaDestino == NULL) { 
		printf("ERRO: Falha ao alocar memoria para a nova aresta.\n");
		return NULL;
	}

	//Vertice adjacente recebe o valor de origem (Vértice a ser conectado apartir do destino) 
	novaArestaDestino->vertice_adjacente = origem; 
	// Peso = distancia entre o destino e a origem
	novaArestaDestino->peso = peso; 
	//Não possui uma aresta adjacente seguinte 
	novaArestaDestino->proximo = NULL; 

	// Atualizar a matriz de adjacência
	g->matrizadj[destino][origem] = novaArestaDestino;  

	//Guardar o grafo em txt 
	guardarGrafo(g); 

	//Retorna a nova aresta criada 
	return novaArestaOrigem;  
}
 
//Imprimir na consola o grafo
void imprimirGrafo(Grafo* g) {

	//Apontador para a lista dos vértices 
	Vertice* atualVertice = g->vertices;
	Aresta* atualAresta;  // declarar para percorrer as arestas 

	//Cabeçalho da tabela 
	printf("------------------------- GRAFO-------------------\n"); 
	printf("\n");
	printf("|%-5s | %-5s | %-10s|\n", "ORIGEM", "DESTINO", "DISTANCIA"); 

	//Percorre os vértices de origem do grafo 
	for (int origem = 0; origem < g->numeroVertices; origem++) {

		//Percorre os vértices de destino do grafo  
		for (int destino = 0; destino < g->numeroVertices; destino++) {

			//Se aresta entre a origem e o destino existir 
			if (g->matrizadj[origem][destino] != NULL) {

				//Apontador para aresta atual 
				Aresta* aresta = g->matrizadj[origem][destino];

				//Enquanto que aresta for != NULL 
				while (aresta != NULL) {
					//Immprime na consola os vertice origem e destino (vizinho) e peso 
					printf("|%-6d | %-7d | %-10.2f|\n", origem, aresta->vertice_adjacente, aresta->peso);

					//Passa para a próxima aresta 
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

	//Cabeçalho da tabela
	printf("|%-12s | %-5s | %-10s | %-10s | %-30s|\n", "ID VERTICE", "ID", "TIPO", "BATERIA", "LOCALIZACAO");

	//Percorre a lista dos vértices até ao fim 
	while (vertice != NULL) {

		//Imprime na consola a informação do ID do vértice, ID do meio de transporte, o tipo de transporte, bateria e localização 
		printf("|%-12d | %-5d | %-10s | %-10.2f | %-30s|\n", vertice->VerticeID, vertice->ID, vertice->Tipo, vertice->bateria, vertice->geocodigo);

		//Passa para o próximo vértice
		vertice = vertice->seguinte;
	}

	printf("\n");

	//Retorna o apontador para o primeiro vértice 
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

			// Verificar se há uma aresta entre os vértices de origem e destino
			if (g->matrizadj[origem][destino] != NULL) {  

				//Recebe a aresta entre os vértices de origem e destino
				Aresta* aresta = g->matrizadj[origem][destino]; 

				//Percorre as arestaas até ao fim
				while (aresta != NULL) {

					// Escreve no ficheiro as informações do grafo: origem, destino e peso da aresta
					fprintf(ficheiroGrafo, "%d;%d;%.2f\n", origem, destino, aresta->peso);  
					//Passa para a próxima aresta 
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

	//Percorre a lista dos vértice até ao fim
	while (verticeAtual != NULL) {  

		//Atribuir o endereço do proximo vértice 
		Vertice* proximoVertice = verticeAtual->seguinte; 

		//Executa enquanto houver um proximo vértice  
		while (proximoVertice != NULL) {
			
			//Declarar variáveis para o apoio da conversão das coordenadas 
			float lat1, lng1, lat2, lng2;  

			//Obtem as coordenadas do vértice atual (origem)
			get_coordinates(verticeAtual->geocodigo, API_KEY, &lat1, &lng1);  
			//Obtem as coordenadas do proximo vértice (destino)
			get_coordinates(proximoVertice->geocodigo, API_KEY, &lat2, &lng2); 

			// Calcular a distância entre os vértices  (origem e destino)
			float distancia = haversine_distance(lat1, lng1, lat2, lng2); 

			// Criar as arestas entre os vértices 
			criarAresta(g, verticeAtual->VerticeID, proximoVertice->VerticeID, distancia); 

			//Passa para o proximo vertice seguinte
			proximoVertice = proximoVertice->seguinte; 
		}

		//Passa para o próximo vértice 
		verticeAtual = verticeAtual->seguinte; 
	}
}

//Guardar vertices em ficheiro txt 
Grafo* guardarVertices (Grafo* g) {

	// Abrir o ficheiro dos vértices em escrita
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

	//Inicia no primeiro vértice
	Vertice* atual = g->vertices;
	 
	//Percorre a lista dos vertices até ao fim 
	while (atual != NULL) {

		//Escreve no ficheiro o ID do vértice, o ID do meio de transporte, o tipo de meio de transporte, a bateria e a sua localização  
		fprintf(ficheiroVertice, "%d;%d;%s;%.2f;%s\n",atual->VerticeID, atual->ID, atual->Tipo, atual->bateria, atual->geocodigo);
		
		//Passa para o seguinte vertice 
		atual = atual->seguinte;
	}

	// fechar o ficheiro
	fclose(ficheiroVertice);
}   

//Percuros minimo de recolha dos meios de transporte 
void percursoMinimo(Grafo* g, int origem) { 

	//Variavel do número de vértices existentes no grafo
	int numeroVertices = g->numeroVertices; 

	// Vetor de visitados para registar quais os vértices foram visitados 
	bool* visitados = malloc(numeroVertices * sizeof(bool)); 

	//Percorre todos os elementos do vetor e inicializa como false (Como não visitados)
	for (int i = 0; i < numeroVertices; i++) { 
		visitados[i] = false;
	} 

	//Declarar variáveis
	int caminho[100 + 1]; //Array para armazenar o caminho que minimo. (+1 armazena o vértice origem (armazém)) (Armazena os vértices do caminho minimo)
	int posicao = 0; //Posição atual  

	caminho[posicao] = origem; //Garantir que o vértice origem é o ponto de partida 
	visitados[origem] = true; // Marcar o vertice 0 como visitado (true)


	//Construir o percurso minimo recorrendo ao vizinho mais próximo 
	for (int i = 0; i < numeroVertices - 1; i++) {

		//Atribui o vertice atual ao caminho 
		int verticeAtual = caminho[posicao];
		//Guardar na variável vizinhoMaisProximo o vizinho mais proximo da variável atual 
		int vizinhoMaisProximo = EncontrarMaisProximo50(g, verticeAtual, visitados);

		if (vizinhoMaisProximo == -1) {
			// Todos os vértices com bateria inferior a 50% já foram visitados 
			//Interromper o loop, todos os vértices visitados 
			break;
		}

		//Adicionar o vizinhoMaisProximo no array
		//++posição incrementa (Avançar para a próxima posição para não escrever em cima do que foi escrito) 
		//Cada vértice encontrado é adicionado para para a próxima posição do array
		caminho[++posicao] = vizinhoMaisProximo;
		visitados[vizinhoMaisProximo] = true; // Marcar o vértice como visitado 
	}

	//Voltar para a origem (armazém) Adiciona a origem ao final do array 
	caminho[++posicao] = origem;

	//Limpar a consola 
	system("cls");

	//Imprimir o caminho a ser percorrido
	//Imprime os valores contidos no array que será o percurso minimo 
	imprimirCaminho(caminho, posicao);

	system("pause"); //Pausa no sistema 
	system("cls"); //Limpar a consola 

	//Declharar variáveis
	int capacidadeCamiao = 20; // Capacidade maxima do camião (m3) - volume 
	int capacidadeDisponivel = capacidadeCamiao; //Capacidade disponivel do camião 

	Transporte* Recolhidos[100]; //Armazena o número de transporte recolhidos 
	int numeroRecolhidos = 0; // Número de transportes recolhidos 

	//Função para a recolha dos meios  
	recolherMeios(g, origem, Recolhidos, &numeroRecolhidos, capacidadeCamiao, caminho, posicao);

	printf("\n \n");

	//Imprimir na consola os meios de transporte recolhidos 
	imprimirRecolhidos(Recolhidos, numeroRecolhidos);

	//Libertar a memoria dos visitados (apoio na construção do percurso a ser recolhido)
	free(visitados);
}

//Recolher os meios de transporte ao longo do percurso definido pelo o caminho 
void recolherMeios(Grafo* g, int origem, Transporte* recolhidos[], int* numeroRecolhidos, int capacidadeCamiao, int caminho[], int posicao) {  
	
	//Declarar variáveis 
	int capacidadeDisponivel = capacidadeCamiao; // Capacidade máxima do camião 
	int naoRecolhidos = 0; //Número de recolhidos 
	Transporte* naoRecolhidosArray[100]; //Armazeno os trasportes que não foram recolhidos 

	//Percorre até à posição final enquanto houver espaço no camião 
	for (int i = 0; i <= posicao && capacidadeDisponivel > 0; i++) {
		
		int vertice = caminho[i]; // Valor do vértice do caminho 

		//Encontrar o meio de transporte associado a esse vértice 
		Transporte* transporte = encontrarTransportePorVertice(g, vertice);

		//Se os meios de transporte for diferente de NULL 
		if (transporte != NULL) { 

			//Se o tipo de transporte for trotinete o volume ocupado é de 2 m3, caso o volume de trotinete seja != de trotinete (BIKE)
			//o volume ocupado no camiao será de 5 m3 
			int volumeCamiao = (strcmp(transporte->tipo, "TROTINETE") == 0) ? 2 : 5;  

			//Se o volume do camião o volume do camião necessário para transportar o meio de transporte é menor ou igual 
			//à capacidade disponviel do camião, o meio de transporte pode ser recolhido 
			if (volumeCamiao <= capacidadeDisponivel) {
				
				transporte->bateria = 100.0;  //Transporte recolhido bateria 100%  
				transporte->autonomia = 80.0;  //Transporte recolhido autonomia 80km 
				strcpy(transporte->geocodigo, "///cantarola.sondado.nevoeiro"); //Meio de transporte com a localização do armazém
				
				//Capacidde disponivel é reduzida 
				capacidadeDisponivel -= volumeCamiao; 

				//O meio de transporte é adicionado no array de recolhidos 
				recolhidos[*numeroRecolhidos] = transporte; 
				(*numeroRecolhidos)++; //Incrementa (número de transportes recolhidos ) 

			}
			else {
				//Se o volume do camião necessário para transportar o meio de transporte for maior do que a capacidade disponivel no camião, 
				//o meio de transporte não pode ser recolhido 

				naoRecolhidosArray[naoRecolhidos] = transporte;  // O meio de transporte é adicionado ao array dos não recolhidos 
				naoRecolhidos++; //Número de transporte não recolhidos 
			}
		}
		else {
			//Exclui o vértice zero caso o meio de transporte não for encontrado 
			if (vertice != 0) {
				printf("TRANSPORTE NAO ENCONTRADO PARA O VERTICE %d\n", vertice);  
			}
		}
		
		//Guardar a lista de meios de transporte no ficheiro .bin 
		saveAlterarDadosTransportes(g->meios);

		//Atualizar o ficheiro dos não recolhidos 
		atualizarFicheiroNaoRecolhidos ("NRecolhidos.bin", naoRecolhidosArray, naoRecolhidos);
	} 

	//Se existir meios de transporte não recolhidos 
	if (naoRecolhidos > 0) { 

		//Imprimir os transportes nao recolhidos 
		imprimirNaoRecolhidos(naoRecolhidosArray, naoRecolhidos); 
		//Guardar os dados nao recolhidos em formato .bin 
		saveNaoRecolhidos(naoRecolhidosArray, naoRecolhidos, "NRecolhidos.bin"); 
	}
}

//Imprimir na consola o caminho minimo (imprime os valores contidos no array caminho)
void imprimirCaminho(int caminho[], int posicao) { 

	//Cabeçalho
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

	//Cabeçalho da tabela
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

	//Cabeçalho da tabela 
	printf("\t++++++++ MEIOS DE TRANSPORTE NAO RECOLHIDOS ++++++++++\n");
	printf("\n| %-5s | %-10s |\n", "ID", "TIPO");
	printf("|--------------------|\n"); 

	//Percorre os meios de transporte que não foram recolhidos e impre na consola 
	for (int i = 0; i < numeroNaoRecolhidos; i++) {
		//Imprimir na consola com o ID do meio de transporte e o tipo de transporte (BIKE) (TROTINETE)
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

	//Declarar variáveis 
	int numeroVertices = g->numeroVertices; // Número de vértices no grafo 
	float menorPeso = FLT_MAX; //Maior valor para o tipo flaot 
	int vizinhoProximo = -1;  //Inicializar como -1 (Nenhum vértice encotrado)

	//Percorre todos os vértices 
	for (int i = 0; i < numeroVertices; i++) {

		//Verifica se não é o vértie em que estamos e se ainda não foi visitado 
		if (i != verticeAtual && !visitados[i]) {  
			
			//Atribui à aresta a referencia que liga o vértice atual ao vértice i 
			Aresta* aresta = g->matrizadj[verticeAtual][i]; 

			//Encontrar o vértice correspondente ao vértice i 
			Vertice* vertice = encontrarVertice(g, i); 

			//Se aresta não for nula e a bateria do transporte for inferior a 50% 
			if (aresta != NULL && vertice->bateria < 50.0) {
				
				//Comparar o peso da aresta atual com o peso encontrado até ao momento 
				if (aresta->peso < menorPeso) {
					menorPeso = aresta->peso;
					vizinhoProximo = i;
				}
			}
		}
	}
	
	//Retorna o vértice mais próximo 
	return vizinhoProximo;
} 

//Guardados os meios de transporte não recolhidos em ficheiro bin
void saveNaoRecolhidos(Transporte* naoRecolhidos[], int numeroNaoRecolhidos, const char* TransportesNaoRecolhidos) {

	//Abre o ficheiro em modo escrita bináaria 
	FILE* ficheiro = fopen(TransportesNaoRecolhidos, "wb"); 

	//Se o ficheiro for NULL avisa o utilizador 
	if (ficheiro == NULL) {
		printf("ERRO AO ABRIR O FICHEIRO %s \n", TransportesNaoRecolhidos); 
	}

	//Escreve no ficheiro em bin os não recolhidos 
	fwrite(&numeroNaoRecolhidos, sizeof(int), 1, ficheiro);

	//Percorre o arrau dos não recolhidos e escreve no ficheiro 
	for (int i = 0; i < numeroNaoRecolhidos; i++) {
		//Escreve no ficheiro 
		fwrite(naoRecolhidos[i], sizeof(Transporte), 1, ficheiro);  
	}

	//Fechar o ficheiro 
	fclose(ficheiro); 
 
	printf("\n");
}

//Função para ler os dados do ficheiro 
void lerDadosDeArquivo(const char* TransportesNaoRecolhidos) {

	//Abir o ficheiro em modo de leitura em .bin
	FILE* ficheiro = fopen(TransportesNaoRecolhidos, "rb");
	
	//Se o ficheiro null avisa o utilizador  
	if (ficheiro == NULL) { 
		printf("Erro ao abrir o arquivo %s.\n", TransportesNaoRecolhidos);
		return; 
	}

	//Declarar variávies 
	int numeroNaoRecolhidos;  // Numero de não recolhidos 
	fread(&numeroNaoRecolhidos, sizeof(int), 1, ficheiro); //Lê o número de meios não recolhidos 

	// Criar um array temporário para armazenar os meios não recolhidos 
	Transporte* naoRecolhidosArray = malloc(numeroNaoRecolhidos * sizeof(Transporte));

	// Ler os dados dos meios não recolhidos do ficheiro  
	for (int i = 0; i < numeroNaoRecolhidos; i++) {
		fread(&naoRecolhidosArray[i], sizeof(Transporte), 1, ficheiro); // Os dados do ficheiro e guardar no array temporário 
	}
	//Fechar o ficheiro 
	fclose(ficheiro); 

	//Imprimir na consola os meios de transporte não recolhidos 
	imprimirMeiosNaoRecolhidos(naoRecolhidosArray, numeroNaoRecolhidos); 

	//Libertar a memória do array temporario 
	free(naoRecolhidosArray);
}
 
//Função para imprimir os meis de transporte não recolhidos 
void imprimirMeiosNaoRecolhidos(Transporte* naoRecolhidosArray, int numeroNaoRecolhidos) { 
	
	//Cabeçalho da tabela 
	printf("\t+++++++++++ MEIOS DE TRANSPORTE NAO RECOLHIDOS +++++++++++++\n"); 
	printf("\n| %-5s | %-10s |\n", "ID", "TIPO"); 
	printf("|--------------------|\n"); 

	//Percorre o array e imprime cada meio de transporte não recolhido na consola 
	for (int i = 0; i < numeroNaoRecolhidos; i++) { 
		printf("| %-5d | %-10s |\n", naoRecolhidosArray[i].codigo, naoRecolhidosArray[i].tipo); //Imprime o transporte não recolhido 
	}
	
	//Alera o utilizador dos meios de transporte não recolhidos 
	printf("\n%d meio(s) de transporte nao foram possiveis de recolher \n\n", numeroNaoRecolhidos);  
}

//Atualziar o ficheiro de não recolhidos 
void atualizarFicheiroNaoRecolhidos (const char* nomeFicheiro, Transporte* naoRecolhidosArray, int numeroNaoRecolhidos) {
	
	//Abrir o ficheiro em modo de escrito em .bin 
	FILE* ficheiro = fopen(nomeFicheiro, "wb");
	
	//Se o ficheiro for nulo avisa o utilizador 
	if (ficheiro == NULL) {
		printf("Erro ao abrir o arquivo %s para atualizacao.\n", nomeFicheiro);
		return;
	}

	// Escrever o número de meios não recolhidos no arquivo 
	fwrite(&numeroNaoRecolhidos, sizeof(int), 1, ficheiro); 

	// Escrever os dados dos meios não recolhidos no arquivo
	for (int i = 0; i < numeroNaoRecolhidos; i++) {
		fwrite(&naoRecolhidosArray[i], sizeof(Transporte), 1, ficheiro);
	}
	//Fecha o ficheiro 
	fclose(ficheiro);
}
