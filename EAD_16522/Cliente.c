#define _CRT_SECURE_NO_DEPRECATE 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Cliente.h" 

#define MAX_LINHA 1000

//Inserir Cliente na lista ligada
Cliente* inputCliente(Cliente* cliente_1) {
	
	Cliente* novoCliente = (Cliente*)malloc(sizeof(Cliente)); 

	getchar();
	//Pedir informação ao Gestor para adicionar um novo cliente
	printf("INSIRA O NOME DO CLIENTE: ");
	fgets(novoCliente->nome_cliente, MAX_NOME_CLIENTE, stdin);
	novoCliente->nome_cliente[strcspn(novoCliente->nome_cliente, "\n")] = '\0';

	printf("INSIRA O NUMERO DE CONTRIBUINTE: ");
	scanf("%d", &novoCliente->NIF);

	//Verificar se existe o ID selecionado pelo o Gestor
	while (ExisteCliente(cliente_1, novoCliente->NIF)) {
		printf("INSIRA O NUMERO DE CONTRIBUINTE: ");
		scanf("%d", &novoCliente->NIF);
	}

	novoCliente->saldo = 0.0; 

	getchar();
	printf("INSIRA A MORADA DO CLIENTE: ");
	fgets(novoCliente->morada, MAX_MORADA_CLIENTE, stdin);
	novoCliente->morada[strcspn(novoCliente->morada, "\n")] = '\0';

	printf("INSIRA A PASSWORD: ");
	fgets(novoCliente->password, MAX_PASSWORD, stdin);
	novoCliente->password[strcspn(novoCliente->password, "\n")] = '\0'; 

	novoCliente->IDveiculoAlugado = -1; 
	
	//Adicionar o novo cliente da lista
	novoCliente->seguinte = cliente_1;
	cliente_1 = novoCliente;

	//Guardar os dados da lista ligada no ficheiro txt 
	saveficheiroCliente(novoCliente);

	system("cls"); 

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

	//Abrir ficheiro txt 
	FILE* ficheiroCliente = fopen("Cliente.txt", "w"); 

	if (ficheiroCliente == NULL) {
		printf("ERRO AO ABRIR O FICHEIRO \n"); 

		return inicio; 
	}

	Cliente* atual = inicio;

	while (atual != NULL) {
		//Escrever os dados no ficheiro txt 
		fprintf(ficheiroCliente, "%s;%d;%.2f;%s;%d;%s\n", atual->nome_cliente, atual->NIF, atual->saldo, atual->morada,atual->IDveiculoAlugado, atual->password);

		atual = atual->seguinte;
	}

	//fechar o ficheiro txt 
	fclose(ficheiroCliente); 

	return inicio; 
}

//Ler ficheiro txt e colocar os dados na estrutura do cliente 
Cliente* lerFicheiroCliente(Cliente* inicio) {

	//Abrir ficheiro txt 
	FILE* ficheiroCliente = fopen("Cliente.txt", "r");

	//Declaração de varial ha com capacidade maxima de 100 
	char linha[MAX_LINHA];

	//Se erro ao abrir mensagem para o utilizador
	if (ficheiroCliente == NULL) {
		printf("ERRO AO ABRIR O FICHEIRO \n");

		return inicio;
	}

	//Enquanto que não chega ao fim da ultima linha 
	while (fgets(linha, sizeof(linha), ficheiroCliente) != NULL) {

		Cliente* novoCliente = (Cliente*)malloc(sizeof(Cliente));

		//A ler o ficheiro (possivel problema) 
		sscanf(linha, "%[^;]; %d; %f; %[^;]; %d; %[^\n]", novoCliente->nome_cliente, &novoCliente->NIF, &novoCliente->saldo, novoCliente->morada, &novoCliente->IDveiculoAlugado, novoCliente->password);

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

	printf("\t++++++++++++++++++++++++++++++++++++++++++ LISTA DE CLIENTES +++++++++++++++++++++++++++++++++++++++\n");
	printf("\n");
	printf("| %-20s | %-11s | %-5s | %-30s | %-10s | %-20s |\n", "NOME", "NIF", "SALDO", "MORADA", "VEICULO", "PASSWORD");
	printf("|----------------------|-------------|-------|--------------------------------|------------|----------------------|\n");

	//Enquanto que não terminar de listar 
	while (inicio != NULL) { 

		printf("| %-20s | %-11d | %-5.2f | %-30s | %-10d | %-20s |\n", inicio->nome_cliente, inicio->NIF, inicio->saldo, inicio->morada, inicio->IDveiculoAlugado, inicio->password);
		inicio = inicio->seguinte;
	}
} 

//Remover cliente, remover um cliente pelo o NIF 
Cliente* RemoverCliente(Cliente* inicio) {

	Cliente novoCliente = { 0, ' ', 0, 0.0, 0, ' ' }; 

	int nif; 
	Cliente* aux = inicio;

	printf("\t++++++++++++++++++++++++++++++++++++++++++ REMOVER CLIENTE +++++++++++++++++++++++++++++++++++++++\n");
	printf("\n");
	printf("| %-20s | %-11s | %-5s | %-30s | %-10s | %-20s |\n", "NOME", "NIF", "SALDO", "MORADA", "VEICULO", "PASSWORD");
	printf("|----------------------|-------------|-------|--------------------------------|------------|----------------------|\n");

	while (aux != NULL) {

		printf("| %-20s | %-11d | %-5.2f | %-30s | %-10d | %-20s |\n", aux->nome_cliente, aux->NIF, aux->saldo, aux->morada, aux->IDveiculoAlugado, aux->password);
		aux = aux->seguinte;
	}

	printf("\n");

	printf("INSERIR O NIF DO CLIENTE A ELIMINAR: "); 
	scanf("%d", &nif); 

	system("cls"); 

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
	printf("\n");
	printf("CLIENTE COM O NIF %d REMOVIDO COM SUCESSO\n", nif);
	system("pause"); 
	system("cls");

	return inicio; 
}

//Login para cliente 
LoginResult loginCliente(Cliente* login){

	LoginResult resultado = { false, NULL }; 
	
	//Variáveis 
	int nif; 
	char password[MAX_PASSWORD]; 

	printf("****************************************** L O G I N **************************************\n");
	printf("\n"); 

	printf("INSIRA O NIF: "); 
	scanf("%d", &nif); 

	getchar(); 
	printf("INSIRA PASSWORD: ");
	fgets(password, MAX_PASSWORD, stdin);
	password[strcspn(password,"\n")] = '\0';

	Cliente* atual = login; 
		
		//Percorre a estrutura até chegar ao final
		while (atual != NULL) {
			//se password inseria for igual à passeword da estrutura
			//e se a password inserida for igual à password da estrutura 
			if (atual->NIF == nif && strcmp(atual->password, password) == 0) {
				resultado.autenticado = true; 
				resultado.cliente = atual;
				system("cls"); 
				printf("BEM-VINDO, %s!\n", atual->nome_cliente); 
			}
			atual = atual->seguinte;
		}
		if (!resultado.autenticado) {
			printf("NIF OU PASSWORD INCORRETOS\n");

			system("pause");
		}
	return resultado;
}

//Dados de cliente (cliente consulta os seus dados) 
Cliente* clientedados(Cliente* cliente) {

	system("cls"); 

	//Mostrar os dados atuais de todos os transportes da lista
	printf("+++++++++++++++++++++++++++++++++++++++ MEUS DADOS +++++++++++++++++++++++++++++++++++++++\n");
	printf("\n");

	//Cabeçalho da tabela
	printf("| %-20s | %-11s | %-5s | %-30s | %-10s | %-20s |\n", "NOME", "NIF", "SALDO", "MORADA", "VEICULO", "PASSWORD");
	printf("|----------------------|-------------|-------|--------------------------------|------------|----------------------|\n");
	printf("| %-20s | %-11d | %-5.2f | %-30s | %-10d | %-20s |\n", cliente->nome_cliente, cliente->NIF, cliente->saldo, cliente->morada, cliente->IDveiculoAlugado, cliente->password);
	
	printf("\n");
	system("pause"); 
	system("cls"); 
} 

//Alterar dados de uma estrutura 
Cliente* AlterarDadosCliente(Cliente* inicio, int nif) {

	//Variaveis
	int campo;
	char nome[MAX_NOME_CLIENTE];
	char morada[MAX_MORADA_CLIENTE];
	char password[MAX_PASSWORD];

	 
	// Encontrar o cliente com o NIF indicado
	Cliente* atual = inicio;
	while (atual != NULL && atual->NIF != nif) {
		atual = atual->seguinte;
	}

	system("cls");
	// Mostrar os dados atuais do cliente
	printf("\t++++++++++++++++++++++++++++++++++++++++ MEUS DADOS +++++++++++++++++++++++++++++++++++++++\n");
	printf("\n");
	printf("| %-20s | %-11s | %-5s | %-30s | %-10s | %-20s |\n", "NOME", "NIF", "SALDO", "MORADA", "VEICULO", "PASSWORD");
	printf("|----------------------|-------------|-------|--------------------------------|------------|----------------------|\n");
	printf("| %-20s | %-11d | %-5.2f | %-30s | %-10d | %-20s |\n", atual->nome_cliente, atual->NIF, atual->saldo, atual->morada, atual->IDveiculoAlugado, atual->password);

	printf("\n"); 

	//Opção de escolha para o cliente
	printf("INSERIR O CAMPO QUE PRETENDE ALTERAR\n");
	printf("\n");
	printf("1 - NOME\n");
	printf("2 - NIF\n");
	printf("3 - MORADA\n");
	printf("4 - PASSWORD\n");
	scanf("%d", &campo);

	

	//Escolha do utilizador o campo que pretende alterar
	switch (campo) {
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
		fgets(password, MAX_PASSWORD, stdin);
		password[strcspn(password, "\n")] = '\0';
		//Atribuir a nova password à estrutura
		strcpy(atual->password, password);
		break;
	default:
		printf("OPCAO INVALIDA\n");
		break;
	}
	system("cls");
	//Mostrar ao utilizador os novos dados
	printf("\n");
	printf("| %-20s | %-11s | %-5s | %-30s | %-10s | %-20s |\n", "NOME", "NIF", "SALDO", "MORADA", "VEICULO", "PASSWORD");
	printf("|----------------------|-------------|-------|--------------------------------|------------|----------------------|\n");
	printf("| %-20s | %-11d | %-5.2f | %-30s | %-10d | %-20s |\n", atual->nome_cliente, atual->NIF, atual->saldo, atual->morada, atual->IDveiculoAlugado, atual->password);

	saveAlterarDados(inicio);

	system("pause"); 
	system("cls");
} 

//Guardar as alterações efetuadas
void saveAlterarDados(Cliente* inicio) {

	//Abrir ficheiro temporario
	FILE* ficheirotemporario = fopen("temp.txt", "w");

	//
	if (ficheirotemporario == NULL) {

		printf("ERRO AO ABRIR FICHEIRO");
		return;
	}
	Cliente* atual = inicio;

	//Enquanto não chega ao fim da lista
	while (atual != NULL) {
		//Escrever no ficheiro temporario
		fprintf(ficheirotemporario, "%s; %d; %.2f; %s; %d; %s\n", atual->nome_cliente, atual->NIF, atual->saldo, atual->morada, atual->IDveiculoAlugado, atual->password);
		atual = atual->seguinte;
	}
	
	fclose(ficheirotemporario);
	
	//Remover ficheiro original
	if (remove("Cliente.txt") != 0) {
		return;
	}
	//Renomear fiheiro temporario
	if (rename("temp.txt", "Cliente.txt" )!= 0) {
		return;
	}
}

//Carregar Saldo cliente 
Cliente* carregarSaldo(Cliente* cliente, int nif) {

	// Encontrar o cliente com o NIF indicado
	Cliente* atual = cliente;
	while (atual != NULL && atual->NIF != nif) {
		atual = atual->seguinte;
	}

	float saldoinserido; 
	system("cls"); 

	printf("+++++++++++++++++++++++++++++++++++++++ CARREGAR SALDO +++++++++++++++++++++++++++++++++++++++\n");
	printf("\n");

	printf("\tINSIRA O SALDO\n"); 
	scanf("%f", &saldoinserido); 

	//Atulizar o salfo do cliente
	atual->saldo += saldoinserido; 

	printf("O SEU SALDO E DE %.2f\n", atual->saldo); 

	saveAlterarDados(cliente);

	system("pause"); 
	system("cls"); 

	return cliente; 
}
