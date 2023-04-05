#define _CRT_SECURE_NO_DEPRECATE 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Gestor.h" 

//Inserir um novo gestor à lista 
Gestor* inserirGestor(Gestor* gestor_1) {

	//Aloca memória para nova instancia da estrutura
	Gestor* novoGestor = (Gestor*)malloc(sizeof(Gestor));

	printf("**************************************INSERIR NOVO GESTOR*****************************\n");

	getchar();
	//Pedir informação ao Gestor para adicionar um novo gestor
	printf("INSIRA O NOME DO NOVO GESTOR:\n");
	fgets(novoGestor->nome, 100, stdin);
	novoGestor->nome[strcspn(novoGestor->nome, "\n")] = '\0';

	//Pedir informação ao gestor para colocar seu email 
	printf("INSERIR EMAIL:\n");
	fgets(novoGestor->email, 100, stdin);
	novoGestor->email[strcspn(novoGestor->email, "\n")] = '\0';

	//Pedir informação ao gesotr para colocar a sua password
	printf("INSERIR PASSWORD:\n");
	fgets(novoGestor->password, 100, stdin);
	novoGestor->password[strcspn(novoGestor->password, "\n")] = '\0';

	//Verificar se já existe o gestor criado
	while (existeGestor(gestor_1, novoGestor->email)) {
		fgets(novoGestor->email, 100, stdin);
		novoGestor->email[strcspn(novoGestor->email, "\n")] = '\0';
	}

	//Adicionar gestor ao inicio da lista
	novoGestor->seguinte = gestor_1;
	gestor_1 = novoGestor;

	//Guardar dados em ficheiro txt
	saveficheiroGestor(novoGestor);

	return novoGestor; // retorna o novo apontador para o início da lista

}

//Verificar se já existe gestor criado 
Gestor* existeGestor(Gestor* gestor_1, const char* email) { 

	//Inicio da lista
	Gestor* atual = gestor_1;

	//Percorrer a lista de gestor a verificar se existe o gestor 
	while (atual != NULL) {

		//Se o email introduzido for igual ao email da estrutura, cliente já existe
		if (strcmp(atual->email, email) == 0) {

			//Retorna o valor do apontador 
			return atual;
		}
		// avança para o próximo elemento da lista
		atual = atual->seguinte; 
	}
	//Informa que o gestor ainda não existe na lista
	return NULL;
}

//Guardar em ficheiro txt 
Gestor* saveficheiroGestor(Gestor* inicio) {

	//Abrir ficheiro txt 
	FILE* ficheiroGestor = fopen("Gestor.txt", "w");

	//Se ficheiro impossivel abrir informa o utilizador
	if (ficheiroGestor == NULL) {
		printf("ERRO AO ABRIR O FICHEIRO GESTOR\n");

		return inicio;
	}
	//Inicia o inicio da lista
	Gestor* atual = inicio; 

	//Percorre a lista e escreve os dados no ficheiro txt separados por ; 
	while (atual != NULL) {
		//Escrever os dados no ficheiro txt 
		fprintf(ficheiroGestor, "%s;%s;%s\n", atual->nome, atual->email, atual->password);

		//Passa para o seguinte elemento
		atual = atual->seguinte;
	}

	//fechar o ficheiro txt 
	fclose(ficheiroGestor);

	//Retorna o valor do apontador
	return inicio;
} 

//Verificar se existe Gestor 
Gestor* lerficheiroGestor(Gestor* inicio) {

	//Abrir ficheiro txt 
	FILE* ficheiroGestor = fopen("Gestor.txt", "r");

	//Declaração de variavel com capacidade maxima de 1000 caracteres por linha 
	char linha[1000]; 

	//Se erro ao abrir mensagem para o utilizador
	if (ficheiroGestor == NULL) {
		printf("ERRO AO ABRIR O FICHEIRO GESTOR\n");

		return inicio;
	}

	// Percorre cada linha e armazena a linha lida na variavel linha 
	while (fgets(linha, sizeof(linha), ficheiroGestor) != NULL) {

			
			Gestor* novogestor = (Gestor*)malloc(sizeof(Gestor));

			//Lê os valores da linha (nome, email e password) e armazena da estrutura dos gestor
			sscanf(linha, "%[^;]; %[^;]; %[^\n]", novogestor->nome, novogestor->email, novogestor->password);
			
			//Indica que é o ultimo da lista
			novogestor->seguinte = NULL;

			//Se a lista vazia, o novo gestor é o inici da lista
			if (inicio == NULL) {
				inicio = novogestor;

			}
			//Se lista não estiver vazia 
			else {

				Gestor* atual = inicio;

				//Percorre a lista até chegar ao ultimo elemento e adiciona o novo elemento como proximo
				while (atual->seguinte != NULL) {
					atual = atual->seguinte;

				}
				atual->seguinte = novogestor;
			}
	}

	//Fechar o ficheiro 
	fclose(ficheiroGestor);

	return inicio;
} 

//Login para Gestor 
loginGestor gestorlogin(Gestor* Login) {
	
	//Variáveis 
	char email[100];
	char password[100];  
	loginGestor resultado = { false, NULL }; //Armazene se autenticado e informação do gestor 
	
	getchar();
	//Pedir ao gestor para inserir o email
	printf("+*********************************************** OLA GESTOR **********************************************+\n");
	printf("INSIRA EMAIL:\n");
	fgets(email, 100, stdin);
	email[strcspn(email, "\n")] = '\0';

	//Pedir ao utilizador para inserir password
	printf("INSIRA PASSWORD:\n");
	fgets(password, 100, stdin);
	password[strcspn(password, "\n")] = '\0'; 

	
	Gestor* atual = Login; 


	// Procura por um gestor que tenha o email e password na estrutura
	while (atual != NULL) {
			
			//Se email e password inseridos for igual à password e email da estrutura 
			if (strcmp(atual->email, email) == 0 && strcmp(atual->password, password) == 0) {
				
				resultado.autenticado = true; //Login bem sucedida
				resultado.gestor = atual; //Informa a que gestor corresponde

				system("cls");
				printf("***************************************************** BEM-VINDO, %s!**********************************************\n", atual->nome);
				printf("\n");
				break;
			}
			atual = atual->seguinte;
	}

	//Se login não for bem sucedido informa o utilizador 
	if (!resultado.autenticado) {
		printf("EMAIL OU PASSWORD ERRADO!\n");

		system("pause");
	}
	return resultado; //Devolve as informações sobre a autenticação do gestor 
}
