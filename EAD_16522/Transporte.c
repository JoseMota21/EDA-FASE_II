#define _CRT_SECURE_NO_DEPRECATE 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Transporte.h" 

//Verificar se existe o meio de transporte pelo o ID 
int ExisteTransporte(Transporte* inicio, int id) {

	while (inicio != NULL) {

		if (inicio->codigo == id) {
			int resposta = 0;
			printf("%d", id);
			printf("ID ja existente, por favor inserir outro ID (1 Sair) (0 Inserir ID) \n");
			scanf("%d", &resposta);

			printf("%d", resposta);

			//Se resposta for 1 o programa stop 
			if (resposta == 1) {
				return true;
			}
			else if (resposta == 0) {

				printf("Insira o codigo do meio de mobilidade: ");
				scanf("%d", &id);
			}
		}

		inicio = inicio->seguinte;

	}
	return false;
}
//Inserir um novo registo na lista ligada transporte 

Transporte* InserirTransporte(Transporte* inicio, int id, char tipo[10], float bateria, float autonomia, char geocodigo[20]) {

	//A verificar o que foi inserido no teclado 
	//printf("Inserindo novo registro: id=%d, tipo=%s, bateria=%.2f, autonomia=%.2f, geocodigo=%s\n", id, tipo, bateria, autonomia, geocodigo)	
	Transporte* novo = malloc(sizeof(struct registo));

	if (novo != NULL) {
		novo->codigo = id;
		strcpy(novo->tipo, tipo);
		novo->bateria = bateria;
		novo->autonomia = autonomia;
		strcpy(novo->geocodigo, geocodigo);
		novo->seguinte = inicio;

		//Limpar consola 
		system("cls");
		//A ter a certeza o que foi inserido 
		printf("Registo Inserido com exito!\n");
		//printf("Novo registro: id=%d, tipo=%s, bateria=%.2f, autonomia=%.2f, geocodigo=%s\n", novo->codigo, novo->tipo, novo->bateria, novo->autonomia, novo->geocodigo);

		return (novo);
	}
	else {
		printf("Erro ao colocar na memoria\n");
	}

	return (inicio);

} 

//Remover um meio de transporte pelo o ID 
Transporte* RemoverTransporte(Transporte* inicio, int id) {

	//Se lista estiver vazia informa o utilizador da aplciação 
	if (inicio == NULL) {
		printf("LISTA VAZIA\n");
		return;
	}
	Transporte* atual = inicio;
	Transporte* anterior = NULL;

	//Procurar na estrutura o ID pedido 
	while (atual != NULL && atual->codigo != id) {
		anterior = atual;
		atual = atual->seguinte;
	}

	//Quando a pesquisar chegar ao fim da lista e não for encontrado o id avisa o utilizador
	if (atual == NULL) {
		printf("O MEIO DE TRANSPORTE COM O CODIGO %d NAO FOI ENCONTRADA NA LISTA\n", id);
		return;
	}
	//Remove o id da lista
	if (anterior == NULL) { //Se for o primeiro
		inicio = atual->seguinte;
	}
	else {
		anterior->seguinte = atual->seguinte;
	}
	free(atual); //Libertar a memoria que estava alocada 

	printf("MEIO DE TRANSPORTE COM O ID %d REMOVIDO COM SUCESSO\n", id);
}

//Apresentar na consola o conteudo da lista ligada 
Transporte* listarTransporte(Transporte* inicio) {

	while (inicio != NULL) {

		printf("%d; %s; %.2f; %.2f; %s\n", inicio->codigo, inicio->tipo, inicio->bateria, inicio->autonomia, inicio->geocodigo);

		inicio = inicio->seguinte;
	}
}

//Guardar em ficheiro TXT a informação das trotinetes 
Transporte* saveficheiroTransporte(Transporte* inicio) {

	//Abrir o ficheiro
	FILE* ficheiroTransporte = fopen("Transporte.txt", "a+");

	//Se ficheiro Null informação ao utilziador 
	if (ficheiroTransporte == NULL) {
		printf("Erro ao abrir o ficheiro Transporte\n");
		return;
	}

	Transporte* atual = inicio;

	while (atual != NULL) {

		fprintf(ficheiroTransporte, "%d; %s; %.2f; %.2f; %s \n", atual->codigo, atual->tipo, atual->bateria, atual->autonomia, atual->geocodigo);

		atual = atual->seguinte;
	}
	//Fechar o txt
	fclose(ficheiroTransporte);

}

//Ler ficheiro txt a informação das trotinetes e colocar na estrutura 
Transporte* lerFicheiroTransporte(Transporte* inicio) {
	FILE* ficheiroTransporte = fopen("Transporte.txt", "r");

	char linha[1000];

	if (ficheiroTransporte == NULL) {
		printf("Erro ao abrir o ficheiro Transporte\n");
		return inicio; //return inicio 
	}

	while (fgets(linha, sizeof(linha), ficheiroTransporte) != NULL) {

		Transporte* novoTransporte = (Transporte*)malloc(sizeof(Transporte));

		sscanf(linha, "%d;%[^;];%f;%f;%s", &novoTransporte->codigo, novoTransporte->tipo, &novoTransporte->bateria, &novoTransporte->autonomia, novoTransporte->geocodigo);

		//Verificar o que está a ser lido 
		//sscanf(linha, "%d; %s; %.2f; %.2f; %s", &novoTransporte->codigo, novoTransporte->tipo, &novoTransporte->bateria, &novoTransporte->autonomia, novoTransporte->geocodigo);
		
		//Verificar o que está a ser lido 
		//printf("Codigo: %d, Tipo: %s, Bateria: %.2f, Autonomia: %.2f, Geocódigo: %s\n", novoTransporte->codigo, novoTransporte->tipo, novoTransporte->bateria, novoTransporte->autonomia, novoTransporte->geocodigo);
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

	fclose(ficheiroTransporte);
	return inicio;

} 

//Mostrar a trotinete com maior bateria (Possivelmente vou adptar isto para ordenar) 
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
	printf("MEIO DE TRANSPORTE COM MAIOR AUTONOMIA\n");
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

	t1->codigo = t2->codigo;
	strcpy(t1->tipo, t2->tipo);
	t1->bateria = t2->bateria;
	t1->autonomia = t2->autonomia;
	strcpy(t1->geocodigo, t2->geocodigo);

	t2->codigo = codigo_temp;
	strcpy(t2->tipo, tipo_temp);
	t2->bateria = bateria_temp;
	t2->autonomia = autonomia_temp;
	strcpy(t2->geocodigo, geocodigo_temp);
}

//Ordenar Autonomia ordem decrescente
void OrdenarTransportesPorAutonomiaDecrescente(Transporte* inicio) {
	int trocado;
	Transporte* atual, * anterior = NULL;

	//Lista estiver vazia informa o utilizador
	if (inicio == NULL) {
		printf("Lista vazia!\n");
		return;
	}

	do {
		trocado = 0;
		atual = inicio;

		while (atual->seguinte != anterior) {
			if (atual->autonomia < atual->seguinte->autonomia) {
				TrocarTransportes(atual, atual->seguinte);
				trocado = 1;
			}
			atual = atual->seguinte;
		}
		anterior = atual;
	} while (trocado);

	
	printf("TRANSPORTE ORDENADO POR AUTONOMIA\n");

	//Enquanto que não chega ao fim da lista escreve na consola
	while (inicio != NULL) {
		printf("%d; %s;%.2f;%.2f;%s\n", inicio->codigo, inicio->tipo, inicio->bateria, inicio->autonomia, inicio->geocodigo);
		inicio = inicio->seguinte;
	}
}
