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
			int resposta=0;
			printf("ID ja existente, por favor inserir outro ID (1 Sair) (0 Inserir ID) \n");
			scanf("%d",&resposta);

			//Se resposta for 1 o programa para 
			if (resposta == 1) {
				return true;
			}
			else if (resposta == 0) {
			
				printf("Insira o codigo do meio de mobilidade: ");
				scanf("%d",&id);

			
			}
		}
		inicio = inicio->seguinte;

	}
	return false;;
}

//Inserir um novo registo na lista ligada transporte 
Transporte* InserirTransporte(Transporte* inicio, int id, char tipo[10], float bateria, float autonomia, char geocodigo[20]) {

	//A verificar o que foi inserido no teclado 
	printf("Inserindo novo registro: id=%d, tipo=%s, bateria=%.2f, autonomia=%.2f, geocodigo=%s\n", id, tipo, bateria, autonomia, geocodigo);


	if (!ExisteTransporte(inicio, id)) {
		Transporte* novo = malloc(sizeof(struct registo));

		if (novo != NULL) {
			novo->codigo = id;
			strcpy(novo->tipo, tipo);
			novo->bateria = bateria;
			novo->autonomia = autonomia;
			strcpy(novo->geocodigo, geocodigo);
			novo->seguinte = inicio;

			//A ter a certeza o que foi inserido 
			printf("Registo Inserido com exito!\n"); 
			printf("Novo registro: id=%d, tipo=%s, bateria=%.2f, autonomia=%.2f, geocodigo=%s\n", novo->codigo, novo->tipo, novo->bateria, novo->autonomia, novo->geocodigo);

			return (novo);
		}
	}
	else {
		printf("Erro ao colocar na memoria"); 
	}

		return (inicio);
}


//Remover um meio de transporte pelo o ID 
Transporte* RemoverTransporte(Transporte* inicio, int id) {

	Transporte* aux = NULL;

	while (inicio != NULL) {
		if (inicio->codigo == id) {
			aux = inicio->seguinte;

			free(inicio);
			return (aux);
		}
		else
		{
			inicio = RemoverTransporte(inicio->seguinte, id);
			return (inicio);
		}

	}
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
		printf("Codigo: %d, Tipo: %s, Bateria: %.2f, Autonomia: %.2f, Geocódigo: %s\n", novoTransporte->codigo, novoTransporte->tipo, novoTransporte->bateria, novoTransporte->autonomia, novoTransporte->geocodigo);
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