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

	return novoGestor; // retorna o novo ponteiro para o início da lista
}

Gestor* existeGestor(Gestor* gestor_1, const char* email) {

	Gestor* atual = gestor_1;

	//Percorrer a lista de gestor a verificar se existe o gestor 
	while (atual != NULL) {
		if (strcmp(atual->email, email) == 0) {

			return atual;
		}
		atual = atual->seguinte; // avança para o próximo nó da lista
	}
	return NULL;
}

//Guardar em ficheiro txt 
Gestor* saveficheiroGestor(Gestor* inicio) {

	//Abrir ficheiro txt 
	FILE* ficheiroGestor = fopen("Gestor.txt", "w");

	if (ficheiroGestor == NULL) {
		printf("ERRO AO ABRIR O FICHEIRO GESTOR\n");

		return inicio;
	}

	Gestor* atual = inicio; 

	while (atual != NULL) {
		//Escrever os dados no ficheiro txt 
		fprintf(ficheiroGestor, "%s;%s;%s\n", atual->nome, atual->email, atual->password);

		atual = atual->seguinte;
	}

	//fechar o ficheiro txt 
	fclose(ficheiroGestor);

	return inicio;
} 

//Verificar se existe Gestor 
Gestor* lerficheiroGestor(Gestor* inicio) {

	//Abrir ficheiro txt 
	FILE* ficheiroGestor = fopen("Gestor.txt", "r");

	//Declaração de varial ha com capacidade maxima de 100 
	char linha[1000]; 

	//Se erro ao abrir mensagem para o utilizador
	if (ficheiroGestor == NULL) {
		printf("ERRO AO ABRIR O FICHEIRO GESTOR\n");

		return inicio;
	}

	// Enquanto que não chega ao fim da ultima linha
		while (fgets(linha, sizeof(linha), ficheiroGestor) != NULL) {

			Gestor* novogestor = (Gestor*)malloc(sizeof(Gestor));

			//A ler o ficheiro (possivel problema) 
			sscanf(linha, "%[^;]; %[^;]; %[^\n]", novogestor->nome, novogestor->email, novogestor->password);

			novogestor->seguinte = NULL;
			//Quando chegar ao fim 
			if (inicio == NULL) {
				inicio = novogestor;

			}
			else {
				Gestor* atual = inicio;

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

	loginGestor resultado = { false, NULL }; 
	
	char email[100];
	char password[100]; 
	
	getchar();
	//Pedir ao gestor para inserir o email
	printf("INSIRA EMAIL:\n");
	fgets(email, 100, stdin);
	email[strcspn(email, "\n")] = '\0';

	//Pedir ao utilizador para inserir password
	printf("INSIRA PASSWORD:\n");
	fgets(password, 100, stdin);
	password[strcspn(password, "\n")] = '\0'; 

	Gestor* atual = Login; 


	// Percorre a estrutura até chegar ao final
	while (atual != NULL) {
			//se password inseria for igual à password da estrutura
			//e se a password inserida for igual à password da estrutura 

			if (strcmp(atual->email, email) == 0 && strcmp(atual->password, password) == 0) {
				resultado.autenticado = true;
				resultado.gestor = atual;

				printf("Bem-vindo, %s!\n", atual->nome);
				break;
			}
			atual = atual->seguinte;
	}

	if (!resultado.autenticado) {
		printf("NIF ou password incorretos!\n");

		system("pause");
	}
	return resultado;
}
