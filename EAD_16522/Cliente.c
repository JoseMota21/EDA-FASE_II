#define _CRT_SECURE_NO_DEPRECATE 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Cliente.h" 

#define MAX_LINHA 1000

//Inserir um novo registo na lista ligada transporte 
Cliente* InserirCliente(Cliente* inicio, char nome[80], int nif, float saldo, char morada[80], char password[20]) {
	if (!ExisteCliente(inicio, nif)) {
		Cliente* novo = malloc(sizeof(struct registoCliente));
		if (novo != NULL) {
			strcpy(novo->nome_cliente, nome);
			novo->NIF = nif;
			novo->saldo = saldo;
			strcpy(novo->morada, morada);
			strcpy(novo->password, password);
			novo->seguinte = inicio;
			//Limpar consola 
			system("cls");
			//A ter a certeza o que foi inserido 
			printf("Registo Inserido com exito!\n");
			return (novo);
		}
		else {
			printf("Erro ao colocar na memoria\n");
		}
		return (inicio);
	}
}

Cliente* inputCliente(Cliente* cliente_1) {
	Cliente novoCliente = { 0, ' ', 0, 0.0, ' ' };

	getchar();
	//Pedir informa��o ao Gestor para adicionar um meio de transporte c�digo
	printf("Insira o nome do cliente:\n");
	fgets(novoCliente.nome_cliente, MAX_NOME_CLIENTE, stdin);
	novoCliente.nome_cliente[strcspn(novoCliente.nome_cliente, "\n")] = '\0';

	printf("Inserir o Numero de Contribuiunte:");
	scanf("%d", &novoCliente.NIF);
	//Verificar se existe o ID selecionado pelo o Gestor
	while (ExisteCliente(cliente_1, novoCliente.NIF)) {
		printf("Inserir o Numero de Contribuiunte: ");
		scanf("%d", &novoCliente.NIF);
	}

	printf("Inserir o saldo do cliente: ");
	scanf("%f", &novoCliente.saldo);

	getchar();
	printf("Inserir a morada do cliente: ");
	fgets(novoCliente.morada, MAX_MORADA_CLIENTE, stdin);
	novoCliente.morada[strcspn(novoCliente.morada, "\n")] = '\0';

	printf("Inserir a password: ");
	fgets(novoCliente.password, MAX_PASSWORD, stdin);
	novoCliente.password[strcspn(novoCliente.password, "\n")] = '\0';
	
	//Adicionar o novo meio de transporte ao in�cio da lista
	novoCliente.seguinte = cliente_1;
	cliente_1 = &novoCliente;
	//Inserir os dados na lista ligada
	InserirCliente(cliente_1, novoCliente.nome_cliente, novoCliente.NIF, novoCliente.saldo, novoCliente.morada, novoCliente.password);
	//Guardar os dados da lista ligada no ficheiro txt 

	//listarCliente(cliente_1);

	saveficheiroCliente(cliente_1);// est� a guardar de forma errada 

	return cliente_1;
}

///Verificar se existe o meio de transporte pelo o ID 
int ExisteCliente(Cliente* inicio, int nif) {
	//Enquanto que n�o chegar ao fim da lista analisa 
	while (inicio != NULL) {
		//Se o existir na lista o codigo com o id introduzido pelo o utilizador
		if (inicio->NIF == nif) {
			return 1;
		}
		inicio = inicio->seguinte;
	}
	return 0;
}

//Guardar cliente em ficheiro txt 
Cliente* saveficheiroCliente(Cliente* inicio){

	Cliente* atual = inicio;
	
	//Abrir ficheiro txt 
	FILE* ficheiroCliente = fopen("Cliente.txt", "w"); 

	if (ficheiroCliente == NULL) {
		printf("Erro ao abrir o ficheiro Cliente \n"); 

		return; 
	}

	//Escrever os dados no ficheiro txt 
	fprintf(ficheiroCliente, "%s; %d; %.2f; %s; %s \n", atual->nome_cliente, atual->NIF, atual->saldo, atual->morada, atual->password); 

	//fechar o ficheiro txt 
	fclose(ficheiroCliente); 
}

//Ler ficheiro txt e colocar os dados na estrutura do cliente 
Cliente* lerFicheiroCliente(Cliente* inicio) {

	//Abrir ficheiro txt 
	FILE* ficheiroCliente = fopen("Cliente.txt", "r");

	//Declara��o de varial ha com capacidade maxima de 100 
	char linha[MAX_LINHA];

	//Se erro ao abrir mensagem para o utilizador
	if (ficheiroCliente == NULL) {
		printf("Erro ao abrir o ficheiro Cliente \n");

		return inicio;
	}

	//Enquanto que n�o chega ao fim da ultima linha 
	while (fgets(linha, sizeof(linha), ficheiroCliente) != NULL) {

		Cliente* novoCliente = (Cliente*)malloc(sizeof(Cliente));

		//A ler o ficheiro (possivel problema) 
		sscanf(linha, "%[^;]; %d; %f; %[^;]; %[^\n]", novoCliente->nome_cliente, &novoCliente->NIF, &novoCliente->saldo, novoCliente->morada, novoCliente->password);

		novoCliente->seguinte = NULL; 
		//Quando chegar ao fim 
		if (inicio == NULL) {
			inicio = novoCliente;

		}
		else {
			Cliente* atual = inicio;

			while (atual->seguinte != NULL) {
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

	//Enquanto que n�o terminar de listar 
	while (inicio != NULL) { 

		//A escrever na consola
		printf("%s; %d; %.2f; %s; %s \n",inicio->nome_cliente, inicio->NIF, inicio->saldo, inicio->morada, inicio->password); 
		inicio = inicio->seguinte;
	}
} 

//Remover cliente, remover um cliente pelo o NIF 
Cliente* RemoverCliente(Cliente* inicio) {

	Cliente novoCliente = { 0, ' ', 0, 0.0, ' ' }; 

	int nif; 

	printf("Inserir o nif do cliente a eliminar:\n"); 
	scanf("%d", &nif); 

	//Se lista estiver vazia informa o utilizador da aplcia��o 
	if (inicio == NULL) {
		printf("LISTA VAZIA\n");
		return NULL;
	}
	Cliente* atual = inicio;
	Cliente* anterior = NULL;

	//Procurar na estrutura o ID pedido 
	while (atual != NULL && atual->NIF != nif) {
		anterior = atual;
		atual = atual->seguinte;
	}

	//Quando a pesquisar chegar ao fim da lista e n�o for encontrado o id avisa o utilizador
	if (atual == NULL) {
		printf("O CLIENTE COM O NIF %d NAO FOI ENCONTRADA NA LISTA\n", nif);
		return;
	}
	//Remove o id da lista
	if (anterior == NULL) { //Se for o primeiro
		inicio = atual->seguinte;

		system("cls"); 
		listarCliente(inicio); 
		saveficheiroCliente(inicio); 
	}
	else {
		anterior->seguinte = atual->seguinte;

		listarCliente(inicio);
		saveficheiroCliente(inicio); 
	}
	free(atual); //Libertar a memoria que estava alocada 

	printf("CLIENTE COM O NIF %d REMOVIDO COM SUCESSO\n", nif);

	return inicio; 
}

//Login para cliente 
Cliente* loginCliente(Cliente* login) {
	
	int nif; 
	char password[MAX_PASSWORD]; 

	printf("Insira o NIF:"); 
	scanf("%d", &nif); 

	getchar(); 
	printf("Insira a password: ");
	fgets(password, MAX_PASSWORD, stdin);
	password[strcspn(password, "\n")] = '\0';

	Cliente* atual = login; 

	while (atual != NULL) { 

		//Se o NIF agurdado na estrutura = ao nif inserido pelo user e password da estrutura = � password inserida 
		if (atual->NIF == nif && strcmp(atual->password, password)) {
			printf("Bem-vindo, %s!\n,", atual->nome_cliente);
			return atual;
		} 

		atual = atual->seguinte; 

		
	}
	printf("NIF ou password incorretos!\n");
	
	return NULL;

}