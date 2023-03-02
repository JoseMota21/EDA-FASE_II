#define _CRT_SECURE_NO_DEPRECATE 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Transporte.h"  


//Inserir um novo registo na lista ligada transporte 
Transporte* InserirTransporte(Transporte* inicio, int id, char tipo[], float bateria, float autonomia) {

	if (!ExisteTransporte(inicio, id)) {
		Transporte* novo = malloc(sizeof(struct registo)); 
		
			if (novo != NULL) {
				novo->codigo = id;
				strcpy(novo->tipo, tipo); 
				novo->bateria = bateria;
				novo->autonomia = autonomia; 
				novo->seguinte = inicio; 

				return (novo); 
			}
	} else return (inicio);
}

//Verificar se existe o meio de transporte pelo o ID 
int ExisteTransporte(Transporte* inicio, int id) {
	while (inicio != NULL) {
		
		if (inicio->codigo == id) {
			return (1);
		
			inicio = inicio->seguinte; 
		}
	}
	return(0); 
}

//Remover um meio de transporte pelo o ID 
Transporte* RemoverTransporte(Transporte* inicio, int id) {

	Transporte* antigo = inicio, * atual = inicio, * aux;

	if (atual == NULL) {
		return (NULL);
	}
	else if (atual->codigo == id){
		aux = atual->seguinte;
		free(atual);

		return(aux);
	}
}

//Apresentar na consola o conteudo da lista ligada 
Transporte* listarTransporte (Transporte* inicio) {
	while (inicio != NULL) {
	
		printf("%d; %c; %.2f; %.2f \n", inicio->codigo, inicio->tipo, inicio->bateria, inicio->autonomia); 

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

	//Escrever no txt
	fprintf(ficheiroTransporte, "%d; %c; %.2f; %.2f \n", inicio->codigo, inicio->tipo, inicio->bateria, inicio->autonomia);
	inicio = inicio->seguinte;

	//Fechar o txt
	fclose(ficheiroTransporte);

}

//Ler ficheiro TXT a informação das trotinetes 
Transporte* lerFicheiroTransporte(Transporte* inicio) {
	FILE* ficheiroTransporte = fopen("Transporte.txt", "r");

	char linha[100];

	if (ficheiroTransporte == NULL) {
		printf("Erro ao abrir o ficheiro Transporte\n");
		return inicio; //return inicio 
	}

	while (fgets(linha, sizeof(linha), ficheiroTransporte) != NULL) {

		Transporte* novoTransporte = (Transporte*)malloc(sizeof(Transporte)); 

		sscanf (linha, "%d; %c; %.2f; %.2f", &novoTransporte->codigo, &novoTransporte->tipo, &novoTransporte->bateria, &novoTransporte->autonomia); 
		novoTransporte->seguinte = NULL; 

		if (inicio == NULL) {
			inicio = novoTransporte; 
		} else {
			Transporte* atual = inicio; 

			while (atual->seguinte != NULL){
				atual = atual->seguinte; 
			}
			atual->seguinte = novoTransporte; 
		}
	}

	fclose(ficheiroTransporte); 
	return inicio; 

}
