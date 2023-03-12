#define _CRT_SECURE_NO_DEPRECATE 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Transporte.h" 

//Verificar se existe o meio de transporte pelo o ID 
int ExisteTransporte(Transporte* inicio, int id) { 
	
	//Enquanto que não chegar ao fim da lista analisa 
	while (inicio != NULL) {
		//Se o existir na lista o codigo com o id introduzido pelo o utilizador
		if (inicio->codigo == id) {
			return 1;
		}
		inicio = inicio->seguinte;
	}
	return 0;
}

//Escrever novo transporte através do teclado
Transporte* inputTransporte(Transporte* meioTransporte_1) {

	Transporte* novoTransporte = (Transporte*)malloc(sizeof(Transporte));
	
	//Pedir informação ao Gestor para adicionar um meio de transporte código
	printf("Insira o codigo do meio de mobilidade: ");
	scanf("%d", &novoTransporte->codigo);

	//Verificar se existe o ID selecionado pelo o Gestor
	while (ExisteTransporte(meioTransporte_1, novoTransporte->codigo)) {
		printf("ID ja existente, por favor inserir outro ID \n");
		scanf("%d", &novoTransporte->codigo);
	}
	//Inserir o meio de transporte
	printf("Insira o tipo de meio de mobilidade (Trotinete ou Bicicleta): ");
	scanf("%s", novoTransporte->tipo);

	//Inserir a carga atual da bateria do meio de transporte
	printf("Insira a carga atual da bateria: ");
	scanf("%f", &novoTransporte->bateria);

	printf("Insira a autonomia: ");
	scanf("%f", &novoTransporte->autonomia);

	printf("Insira a localizacao: ");
	scanf("%s", novoTransporte->geocodigo);

	printf("Disponivel: ");
	scanf("%d", &novoTransporte->disponivel);

	//Adicionar o novo meio de transporte ao início da lista
	novoTransporte->seguinte = meioTransporte_1;
	meioTransporte_1 = novoTransporte;

	//Inserir os dados na lista ligada
	InserirTransporte(meioTransporte_1, novoTransporte->codigo, novoTransporte->tipo, novoTransporte->bateria, novoTransporte->autonomia, novoTransporte->geocodigo, novoTransporte->disponivel);

	//Guardar os dados da lista ligada no ficheiro txt 
	saveficheiroTransporte (meioTransporte_1);

	return meioTransporte_1;
}

//Inserir um novo registo na lista ligada transporte 
Transporte* InserirTransporte(Transporte* inicio, int id, char tipo[10], float bateria, float autonomia, char geocodigo[20], int disponivel) {

	if (!ExisteTransporte(inicio, id)) {
		Transporte* novo = malloc(sizeof(Transporte));
		if (novo != NULL) {
			novo->codigo = id;
			strcpy(novo->tipo, tipo);
			novo->bateria = bateria;
			novo->autonomia = autonomia;
			strcpy(novo->geocodigo, geocodigo);
			novo->disponivel = disponivel;
			novo->seguinte = inicio;
		
			//A ter a certeza o que foi inserido 
			printf("Registo Inserido com exito!\n");
			return (novo);
		}
		else {
			printf("Erro ao colocar na memoria\n");
		}
	}
	return (inicio);
}

//Remover um meio de transporte pelo o ID
Transporte* RemoverTransporte(Transporte* inicio) { 

	Transporte RemoverTransporte = { 0, ' ', 0.0, 0.0, 0.0 };

	int codigo;
	printf("Insira o codigo do meio de mobilidade:\n");
	scanf("%d", &codigo); 

	//Se lista estiver vazia informa o utilizador da aplciação 
	if (inicio == NULL) {
		printf("LISTA VAZIA\n");
		return NULL; //Parar de imediato se a listar tiver vazia
	}
	Transporte* atual = inicio;
	Transporte* anterior = NULL;

	//Procurar na estrutura o ID pedido 
	while (atual != NULL && atual->codigo != codigo) {
		anterior = atual;
		atual = atual->seguinte;
	}

	//Quando a pesquisa chegar ao fim da lista e não for encontrado o id avisa o utilizador
	if (atual == NULL) {
		printf("O MEIO DE TRANSPORTE COM O CODIGO %d NAO FOI ENCONTRADA NA LISTA\n", codigo);
		return NULL;
	}
	//Remove o id da lista
	if (anterior == NULL) { //Se for o primeiro
		inicio = atual->seguinte; 

		system("cls");
		
		//Guardar os novos dados no ficheiro txt 
		saveficheiroTransporte(inicio); 
	}
	else {
		anterior->seguinte = atual->seguinte;
		saveficheiroTransporte(inicio); 
	}
	free(atual); //Libertar a memoria que estava alocada 


	printf("MEIO DE TRANSPORTE COM O ID %d REMOVIDO COM SUCESSO\n", codigo);

	return inicio;
}

Transporte* listarTransporte(Transporte* inicio) {
	
	//Percorre a estrutura até fechar ao fim da lista
	while (inicio != NULL) {

		printf("%d; %s; %.2f; %.2f; %s; %d\n", inicio->codigo, inicio->tipo, inicio->bateria, inicio->autonomia, inicio->geocodigo, inicio->disponivel);

		inicio = inicio->seguinte;
	}
	return 0; 
}

//Guardar em ficheiro TXT a informação das trotinetes 
Transporte* saveficheiroTransporte(Transporte* inicio) {

	//Abrir o ficheiro
	FILE* ficheiroTransporte = fopen("Transporte.txt","w");

	//Se ficheiro Null informação ao utilziador 
	if (ficheiroTransporte == NULL) {
		printf("Erro ao abrir o ficheiro Transporte\n");
		return inicio;
	}

	Transporte* atual = inicio;

	//Equanto que não chega ao fim da estrutura 
	while (atual != NULL) {
	
		//Escrever no ficheiro txt
		fprintf(ficheiroTransporte, "%d; %s; %.2f; %.2f; %s; %d\n", atual->codigo, atual->tipo, atual->bateria, atual->autonomia, atual->geocodigo, atual->disponivel);

		atual = atual->seguinte;
	}
	//Fechar o txt
	fclose(ficheiroTransporte);
	return inicio; 
}

//Ler ficheiro txt a informação das trotinetes e colocar na estrutura 
Transporte* lerFicheiroTransporte(Transporte* inicio) {
	//Abrir ficheiro txt 
	FILE* ficheiroTransporte = fopen("Transporte.txt", "r");

	char linha[1000];
	//Se algum problema ao abrir o ficheiro returna uma mensagem de Erro ao abrir o ficheiro
	if (ficheiroTransporte == NULL) {
		printf("Erro ao abrir o ficheiro Transporte\n");
		return inicio; //return inicio 
	}
	//Enquanto que não chega ao fim do ficheiro 
	while (fgets(linha, sizeof(linha), ficheiroTransporte) != NULL) {

		Transporte* novoTransporte = (Transporte*)malloc(sizeof(Transporte));

		//Ler linha a linha do ficheiro e coloca na estrutura 
		sscanf(linha, "%d;%[^;];%f;%f;%s;%d", &novoTransporte->codigo, novoTransporte->tipo, &novoTransporte->bateria, &novoTransporte->autonomia, novoTransporte->geocodigo, novoTransporte->disponivel);

			novoTransporte->seguinte = NULL;
	
		if (inicio == NULL) {
			inicio = novoTransporte;
		}
		else {
			Transporte* atual = inicio;

			while (atual->seguinte != NULL) {
				atual = atual->seguinte;
			}
			atual->seguinte = novoTransporte;
		}
	}
	//Fechar ficheiro txt 
	fclose(ficheiroTransporte);
	return inicio;

} 

//Mostrar o meio de mobilidade com maior bateria 
int EncontrarIdTransporteComMaiorBateria(Transporte* inicio) {
	if (inicio == NULL) {
		return -1; // Lista vazia
	}

	Transporte* atual = inicio;
	Transporte* maior = inicio;

	while (atual != NULL) {
		if (atual->bateria > maior->bateria) {
			maior = atual; // Atualiza o ponteiro para o elemento com maior carga de bateria
		}
		atual = atual->seguinte;
	}
	printf("MEIO DE TRANSPORTE COM MAIOR BATERIA\n");
	printf("%d; %.2f\n", maior->codigo, maior->bateria);
	return maior->codigo; // Retorna o ID do meio de transporte com maior bateria
}

//Trocar a ordem dos transportes 
void TrocarTransportes(Transporte* t1, Transporte* t2) {
	int codigo_temp = t1->codigo;
	char tipo_temp[20];

	strcpy(tipo_temp, t1->tipo);
	float bateria_temp = t1->bateria;
	float autonomia_temp = t1->autonomia;
	char geocodigo_temp[7];
	strcpy(geocodigo_temp, t1->geocodigo);
	int disponivel_temp = t1->disponivel;
	
	t1->codigo = t2->codigo;
	strcpy(t1->tipo, t2->tipo);
	t1->bateria = t2->bateria;
	t1->autonomia = t2->autonomia;
	strcpy(t1->geocodigo, t2->geocodigo);
	t2->disponivel = t2->disponivel;

	t2->codigo = codigo_temp;
	strcpy(t2->tipo, tipo_temp);
	t2->bateria = bateria_temp;
	t2->autonomia = autonomia_temp;
	strcpy(t2->geocodigo, geocodigo_temp);
	t2->disponivel = disponivel_temp;
}

//Ordenar Autonomia ordem decrescente
void OrdenarTransportesPorAutonomiaDecrescente(Transporte* inicio) {
	int troca;
	Transporte* atual, * anterior = NULL;

	//Lista estiver vazia informa o utilizador
	if (inicio == NULL) {
		printf("Lista vazia!\n");
		return;
	}

	do {
		troca = 0;
		atual = inicio;
		//Enquanto que o atual for diferente que o anterior 
		while (atual->seguinte != anterior) {
			//Se autonimoa atual for menor que a autonomia seguinte da lista 
			if (atual->autonomia < atual->seguinte->autonomia) {
				//A autonomia atual é seguinte 
				TrocarTransportes(atual, atual->seguinte);
				troca = 1;
			}
			atual = atual->seguinte;
		}
		anterior = atual;
	} while (troca); //Condição de paragem do ciclo 

	//Mensagem de informação ao utilizador
	printf("TRANSPORTE ORDENADO POR AUTONOMIA\n");

	//Enquanto que não chega ao fim da lista escreve na consola
	while (inicio != NULL) {
		//Escrever na consola 
		printf("%d; %s;%.2f;%.2f;%s;%d\n", inicio->codigo, inicio->tipo, inicio->bateria, inicio->autonomia, inicio->geocodigo, inicio->disponivel);
		inicio = inicio->seguinte;
	}
}
