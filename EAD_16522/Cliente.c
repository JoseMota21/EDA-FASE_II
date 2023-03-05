#define _CRT_SECURE_NO_DEPRECATE 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Cliente.h" 

#define MAX_LINHA 100 

//Inserir novo cliente na estrutura 
Cliente* InserirCliente(Cliente* inicio, int id, char nome[], int nif, float saldo, char morada[]) {

	Cliente* novo = malloc(sizeof(struct registoCliente)); 
	
	if (novo != NULL) {
		novo->ID_cliente = id; 
		strcpy(novo->nome_cliente, nome); 
		novo->NIF = nif; 
		novo->saldo = saldo; 
		strcpy(novo->morada, morada); 
		novo->seguinte = inicio; 

		inicio = novo; 
	}
	return (novo);
}

//Verificar se o cliente existe pelo o NIF 
int ExisteCliente (Cliente* inicio, int nif){

	Cliente* atual = inicio; 

	while (atual != NULL) 
	{
		//Se cliente existir na lista returna 1; 
		if (atual->NIF == nif) {
			printf("Cliente já existe na lista\n"); 

				return 1; 
		}

		atual = atual->seguinte; 
	}

	return 0;
}

//Guardar cliente em ficheiro txt 
Cliente* saveficheiroCliente(Cliente* inicio){

	int ultimo_id = 0; 
	char linha[MAX_LINHA]; 

	//Abrir ficheiro txt 
	FILE* ficheiroCliente = fopen("Cliente.txt", "a+"); 

	if (ficheiroCliente == NULL) {
		printf("Erro ao abrir o ficheiro Cliente \n"); 

		return; 
	}

	//Verificar qual o ultimo ID 
	while (fgets(linha, MAX_LINHA, ficheiroCliente)){
		int ID = 0; 
		sscanf(linha, "ID: %d", &ID); 
		
		//Se o ID for maior que o ultimo ID
		if (ID > ultimo_id) {
			ultimo_id = ID; 
		}
	}

	//fechar o ficheiro txt 
	fclose(ficheiroCliente); 

	//Incrementar o ID
	int ID_Atual = ultimo_id + 1; 

	//Abrir o ficheiro 
	ficheiroCliente = fopen ("Cliente.txt", "a+");

	//Se erro ao abrir mensagem para o utilizador
	if (ficheiroCliente == NULL) {
		printf("Erro ao abrir o ficheiro Cliente \n");

		return;
	}

	Cliente* atual = inicio; 

	//Escrever os dados no ficheiro txt 
	fprintf(ficheiroCliente, "%d; %s; %d; %.2f; %s \n", atual->ID_cliente, atual->nome_cliente, atual->NIF, atual->saldo, atual->morada); 

	//fechar o ficheiro txt 
	fclose(ficheiroCliente); 
}

//Ler ficheiro txt e colocar os dados na estrutura do cliente 
Cliente* lerFicheiroCliente(Cliente* inicio) {

	//Abrir ficheiro txt 
	FILE* ficheiroCliente = fopen("Cliente.txt", "r");

	//Declaração de varial ha com capacidade maxima de 100 
	char linha[MAX_LINHA]; 

	//Se erro ao abrir mensagem para o utilizador
	if (ficheiroCliente == NULL) {
		printf("Erro ao abrir o ficheiro Cliente \n");

		return;
	}

	//Enquanto que não chega ao fim da ultima linha 
	while (fgets(linha, sizeof (linha), ficheiroCliente) != NULL) {

		Cliente* novoCliente = (Cliente*)malloc(sizeof(Cliente)); 

		//A ler o ficheiro 
		//"%d;%[^;];%d;%f;%s", ) // se não estiver a ler corretamente 
		sscanf(linha, "%d; %s; %d; %.2f; %s", &novoCliente->ID_cliente, &novoCliente->nome_cliente, &novoCliente->NIF, &novoCliente->saldo, &novoCliente->morada); 

		//Quando chegar ao fim 
		if (inicio == NULL) {
			inicio = novoCliente; 

		}
		else {
			Cliente* atual = inicio; 

			while (atual->seguinte != NULL){ 
				atual = atual->seguinte; 

			}
			atual->seguinte = novoCliente; 
		}
	}

	//Fechar o ficheiro 
	fclose(ficheiroCliente); 

	return inicio; 
	
} 

// Listar cliente na consola 
Cliente* listarCliente(Cliente* inicio) {

	//Enquanto que não terminar de listar 
	while (inicio != NULL) { 

		//A escrever na consola
		printf("%d; %s; %d; %.2f; %s \n", inicio->ID_cliente, inicio->nome_cliente, inicio->NIF, inicio->saldo, inicio->morada); 
		inicio = inicio->seguinte;
	}
} 