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
	//Pedir informação ao Gestor para adicionar um meio de transporte código
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
	
	//Adicionar o novo meio de transporte ao início da lista
	novoCliente.seguinte = cliente_1;
	cliente_1 = &novoCliente;
	//Inserir os dados na lista ligada
	InserirCliente(cliente_1, novoCliente.nome_cliente, novoCliente.NIF, novoCliente.saldo, novoCliente.morada, novoCliente.password);
	//Guardar os dados da lista ligada no ficheiro txt 

	
	saveficheiroCliente(cliente_1);// está a guardar de forma errada 

	return cliente_1;
}

///Verificar se existe o meio de transporte pelo o ID 
int ExisteCliente(Cliente* inicio, int nif) {
	//Enquanto que não chegar ao fim da lista analisa 
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

	//Declaração de varial ha com capacidade maxima de 100 
	char linha[MAX_LINHA];

	//Se erro ao abrir mensagem para o utilizador
	if (ficheiroCliente == NULL) {
		printf("Erro ao abrir o ficheiro Cliente \n");

		return inicio;
	}

	//Enquanto que não chega ao fim da ultima linha 
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

	//Enquanto que não terminar de listar 
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

	//Se lista estiver vazia informa o utilizador da aplciação 
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

	//Quando a pesquisar chegar ao fim da lista e não for encontrado o id avisa o utilizador
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
Cliente* loginCliente(Cliente* login){
	
	//Variáveis 
	int nif; 
	char password[MAX_PASSWORD]; 

	printf("Insira o NIF:"); 
	scanf("%d", &nif); 

	getchar(); 
	printf("Insira a password: ");
	fgets(password, MAX_PASSWORD, stdin);
	password[strcspn(password, "\n")] = '\0';

	Cliente* atual = login; 
		
		//Percorre a estrutura até chegar ao final
		while (atual != NULL) {
			//se password inseria for igual à passeword da estrutura
			//e se a password inserida for igual à password da estrutura 
			if (atual->NIF == nif && strcmp(atual->password, password) == 0) {
				system("cls"); 
				printf("Bem-vindo, %s!\n", atual->nome_cliente);
				return atual;
			}

			atual = atual->seguinte;

		}
		printf("NIF ou password incorretos!\n");

		return NULL;
}

//Dados de cliente (cliente consulta os seus dados) 
Cliente* clientedados(Cliente* cliente) {
	
	printf("%s; %d; %.2f; %s; %s\n" , cliente->nome_cliente, cliente->NIF, cliente->saldo, cliente->morada, cliente->password);
} 

//Alterar dados de uma estrutura 
Cliente* AlterarDados(Cliente* inicio){

	//Variaveis
	int campo; 
	char nome[MAX_NOME_CLIENTE]; 
	char morada[MAX_MORADA_CLIENTE]; 
	char password[MAX_PASSWORD]; 

	Cliente* atual = inicio; 

	//Se o cliente estiver logado informação a apresentar
	if (loginCliente) {

		system("cls");
		// Mostrar os dados atuais do cliente
		printf("DADOS:\n");
		printf("%s; %d; %.2f; %s; %s\n", atual->nome_cliente, atual->NIF, atual->saldo, atual->morada, atual->password);

		//Opção de escolha para o cliente
		printf("INSERIR O CAMPO QUE PRETENDE ALTERAR\n"); 
		printf("1 - NOME\n"); 
		printf("2 - NIF\n");
		printf("3 - MORADA\n");
		printf("4 - PASSWORD\n");
		scanf("%d", &campo);

		//Escolha do utilizador o campo que pretende alterar
		switch (campo){
		case 1: 
			getchar();
			//Alterar o nome
			printf("INSIRA O NOVO NOME\n"); 
			fgets(nome, MAX_NOME_CLIENTE, stdin);
			nome[strcspn(nome, "\n")] = '\0';
			//Atribuir o novo nome à estrutura
			strcpy(atual->nome_cliente, nome); 
			break; 
			
		case 2: 		
			//Alterar o número de contribuinte
			printf("INSIRA O NIF\n");
			scanf("%d", &atual->NIF); 
			break; 

		case 3: 
			getchar();
			//Alterar a sua morada
			printf("INSIRA MORADA\n");
			fgets(morada, MAX_MORADA_CLIENTE, stdin);
			morada[strcspn(morada, "\n")] = '\0';
			//Atribuir a nova morada à estrutura
			strcpy(atual->morada, morada);
			break; 
		
		case 4: 
			getchar();
			//Alterar a sua password
			printf("INSIRA PASSWORD\n");
			fgets(password,MAX_PASSWORD, stdin);
			password[strcspn(password, "\n")] = '\0';
			//Atribuir a nova password à estrutura
			strcpy(atual->password, password);
			break; 
		default:
			printf("OPCAO INVALIDA\n");
			break;
		}
		//Mostrar ao utilizador os novos dados
	printf("%s; %d; %.2f; %s; %s", atual->nome_cliente, atual->NIF, atual->saldo, atual->morada, atual->password);
	}
}