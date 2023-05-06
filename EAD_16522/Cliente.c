#define _CRT_SECURE_NO_DEPRECATE 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Cliente.h" 
#include "Transporte.h"


//Inserir Cliente na lista ligada
Cliente* inputCliente(Cliente* cliente_1) {
	
	//Aloca memória para nova instancia da estrutura
	Cliente* novoCliente = (Cliente*)malloc(sizeof(Cliente)); 

	getchar();
	//Pedir informação ao Gestor para o nome do novo cliente
	printf("INSIRA O NOME DO CLIENTE: ");
	fgets(novoCliente->nome_cliente, MAX_NOME_CLIENTE, stdin);
	novoCliente->nome_cliente[strcspn(novoCliente->nome_cliente, "\n")] = '\0';

	//Pedir ao gestor para inserir o numero de contribuinte do cliente
	printf("INSIRA O NUMERO DE CONTRIBUINTE: ");
	scanf("%d", &novoCliente->NIF);

	//Verificar se existe o ID inserido pelo o Gestor já existe na estrutura
	while (ExisteCliente(cliente_1, novoCliente->NIF)) {
		printf("INSIRA O NUMERO DE CONTRIBUINTE: ");
		scanf("%d", &novoCliente->NIF);
	}

	//Quando é criado um novo cliente o saldo dele é 0
	novoCliente->saldo = 0.0; 

	getchar();
	//Inserir a morada do novo cliente
	printf("INSIRA A MORADA DO CLIENTE: ");
	fgets(novoCliente->morada, MAX_MORADA_CLIENTE, stdin);
	novoCliente->morada[strcspn(novoCliente->morada, "\n")] = '\0';

	//Inserir a password do novo cliente
	printf("INSIRA A PASSWORD: ");
	fgets(novoCliente->password, MAX_PASSWORD, stdin);
	novoCliente->password[strcspn(novoCliente->password, "\n")] = '\0'; 

	//No momento da criação o cliente não tem nenhum veiculo alugado (-1 sem veiculo alugado)
	novoCliente->IDveiculoAlugado = -1; 
	
	//Adicionar o novo cliente da lista
	novoCliente->seguinte = cliente_1;
	cliente_1 = novoCliente;

	//Guardar os dados da lista ligada no ficheiro txt 
	saveficheiroCliente(novoCliente);

	system("cls"); // Limpar consola 

	return cliente_1;
}

///Verificar se existe cliente pelo o nif
int ExisteCliente(Cliente* inicio, int nif) {

	//Percorre a lista toda 
	while (inicio != NULL) {

		//Se existir na estrutura o NIF 
		if (inicio->NIF == nif) {
			return 1; //Encontrou na lista
		}
		//Passa para o proximo elemento da lista 
		inicio = inicio->seguinte;
	}
	return 0; //Não encontrou na lista 
}

//Guardar cliente em ficheiro txt 
Cliente* saveficheiroCliente(Cliente* inicio){

	//Abrir ficheiro binario 
	FILE* ficheiroCliente = fopen("Cliente.bin", "wb"); 

	//Se impossivel a abrir o ficheiro avisa o utilizador
	if (ficheiroCliente == NULL) {
		printf("ERRO AO ABRIR O FICHEIRO \n"); 

		return inicio; 
	}

	//Inicio da lista 
	Cliente* atual = inicio;

	//Percorre a estrutura 
	while (atual != NULL) {
		//Escrever os dados no ficheiro bin 
		fwrite(atual, sizeof(Cliente), 1, ficheiroCliente);
		
		atual = atual->seguinte; //Próximo elemento 
	}

	//fechar o ficheiro txt 
	fclose(ficheiroCliente); 

	return inicio; 
}

//Ler ficheiro txt e colocar os dados na estrutura do cliente 
Cliente* lerFicheiroCliente(Cliente* inicio) {

	//Abrir ficheiro bin 
	FILE* ficheiroCliente = fopen("Cliente.bin", "rb");

	//Se impossivel a abrir o ficheiro informa o utilizador 
	if (ficheiroCliente == NULL) {
		printf("ERRO AO ABRIR O FICHEIRO \n");

		return inicio;
	}

	//Lê todos os dados até que não haja mais nenhum para ler no ficheiro 
	while (1) {

		// Alocar a capacidade necessária de memoria e indica o tamanho de espaço de memoria a ser alocado
		Cliente* novoCliente = (Cliente*)malloc(sizeof(Cliente));
		
			//Lê os dados do ficheiro binario para a estrutura e verifica se a leitura foi bem sucedida 
			if (fread(novoCliente, sizeof(Cliente), 1, ficheiroCliente) != 1) {

				free(novoCliente); //Caso a leitura não tenha sido sucedida liberta a memória alocada
				break;
			}
			//Define o ultimo elemento da lista 
			novoCliente->seguinte = NULL;  

			//Se a lista estiver vazia, a variável inicio é definida como a estrutura novo transporte
			if (inicio == NULL) {
				inicio = novoCliente; 
			}
			else { //Se não percorre a lista ligada para encontrar o ultimo elemento 
				Cliente* atual = inicio; 

				//Percorre a lista até encontrar o último elemento 
				while (atual->seguinte != NULL) {
					atual = atual->seguinte; 
				}
				//Proximo elemento
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
	//Cabeçalho da tabela 
	printf("| %-20s | %-11s | %-10s | %-30s | %-10s | %-20s |\n", "NOME", "NIF", "SALDO", "MORADA", "VEICULO", "PASSWORD");
	printf("|----------------------|-------------|------------|--------------------------------|------------|----------------------|\n");

	//Percorre a lista até chegar ao fim 
	while (inicio != NULL) { 

			//Escreve na consola os elementos da estrutura 
			printf("| %-20s | %-11d | %-10.2f | %-30s | %-10d | %-20s |\n", inicio->nome_cliente, inicio->NIF, inicio->saldo, inicio->morada, inicio->IDveiculoAlugado, inicio->password);
			inicio = inicio->seguinte;

	}
} 

//Remover cliente, remover um cliente pelo o NIF 
Cliente* RemoverCliente(Cliente* inicio) {

	//Inicializa todos os campos com valores de zero
	Cliente novoCliente = { 0, ' ', 0, 0.0, 0, ' ' }; 
	
	//Variaveis 
	int nif; 
	Cliente* aux = inicio; //Variável auxiliar em forma de apontador que será o primeiro elemento da lista 

	printf("\t++++++++++++++++++++++++++++++++++++++++++ REMOVER CLIENTE +++++++++++++++++++++++++++++++++++++++\n");
	printf("\n");
	//Cabeçalho da tabela 
	printf("| %-20s | %-11s | %-5s | %-30s | %-10s | %-20s |\n", "NOME", "NIF", "SALDO", "MORADA", "VEICULO", "PASSWORD");
	printf("|----------------------|-------------|-------|--------------------------------|------------|----------------------|\n");

	//Percorre todos os clientes existentes na lista
	while (aux != NULL) {

		//Imprime na consola todos os clientes 
		printf("| %-20s | %-11d | %-5.2f | %-30s | %-10d | %-20s |\n", aux->nome_cliente, aux->NIF, aux->saldo, aux->morada, aux->IDveiculoAlugado, aux->password);
		aux = aux->seguinte;
	}

	printf("\n");

	//Gestor insere o NIF do clientes que pretende eliminar 
	printf("INSERIR O NIF DO CLIENTE A ELIMINAR: "); 
	scanf("%d", &nif); 

	system("cls"); //Limpar consola 

	//Se lista estiver vazia informa o utilizador
	if (inicio == NULL) {
		printf("LISTA VAZIA\n");
		return NULL;
	}
	//Aponta para o inicio da lista
	Cliente* atual = inicio;
	//Após remover o elemento permite que a lista permaneça ligada
	Cliente* anterior = NULL;

	//Procurar na estrutura o ID pedido 
	while (atual != NULL && atual->NIF != nif) {
		anterior = atual;
		atual = atual->seguinte;
	}

	//Quando a pesquisar chegar ao fim da lista e não for encontrado o NIF avisa o utilizador
	if (atual == NULL) {
		printf("O CLIENTE COM O NIF %d NAO FOI ENCONTRADA NA LISTA\n", nif);
		return;
	}
	//Remove o NIF (Remove o cliente) da lista
	if (anterior == NULL) { //Se for o primeiro
		inicio = atual->seguinte;

		system("cls"); 
		listarCliente(inicio); //Mostra a lista de clientes na consola
		saveficheiroCliente(inicio); //guarda no ficheiro as alterações efetuadas 
	}
	else {
		//Se não for o primeiro da lista 
		anterior->seguinte = atual->seguinte;

		listarCliente(inicio); //Mostra a lista de clientes na consola
		saveficheiroCliente(inicio); //Guarda as alterações 
	}
	free(atual); //Libertar a memoria que estava alocada 
	printf("\n");

	printf("CLIENTE COM O NIF %d REMOVIDO COM SUCESSO\n", nif); //Infoma que cliente foi removido com sucesso
	system("pause"); 
	system("cls");

	return inicio; 
}

//Login para cliente 
LoginResult loginCliente(Cliente* login){

	//Variáveis 
	LoginResult resultado = { false, NULL }; //Armazena se autenticado e informação do cliente
	int nif; 
	char password[MAX_PASSWORD]; 

	printf("****************************************** L O G I N **************************************\n");
	printf("\n"); 

	//Cliente introduz o seu NIF 
	printf("INSIRA O NIF: "); 
	scanf("%d", &nif); 

	getchar(); 
	//Cliente introduz a sua password
	printf("INSIRA PASSWORD: ");
	fgets(password, MAX_PASSWORD, stdin);
	password[strcspn(password,"\n")] = '\0';

	//Inicio da lista
	Cliente* atual = login; 
		
		//Procura por um cliente que tenha NIF e password na estrutura
		while (atual != NULL) {
			
			//Se NIF e password inseridos for igual à password e NIF da estrutua
			if (atual->NIF == nif && strcmp(atual->password, password) == 0) {
				resultado.autenticado = true; //Login com sucesso
				resultado.cliente = atual; //Informa que cliente corresponde
				system("cls"); 
				printf("BEM-VINDO, %s!\n", atual->nome_cliente); 
			}
			atual = atual->seguinte; 
		}
		//Se login não for bem sucedido informa o utilizador
		if (!resultado.autenticado) {
			printf("NIF OU PASSWORD INCORRETOS\n");

			system("pause");
		}
	return resultado; //Devolve as informações sobre a autenticação 
}

//Dados de cliente (cliente logado consulta os seus dados) 
Cliente* clientedados(Cliente* cliente) {

	system("cls"); 

	//Mostrar os dados atuais de todos os transportes da lista
	printf("+++++++++++++++++++++++++++++++++++++++ MEUS DADOS +++++++++++++++++++++++++++++++++++++++\n");
	printf("\n");

	//Cabeçalho da tabela
	printf("| %-20s | %-11s | %-10s | %-30s | %-10s | %-20s |\n", "NOME", "NIF", "SALDO", "MORADA", "VEICULO", "PASSWORD");
	printf("|----------------------|-------------|------------|--------------------------------|------------|----------------------|\n");
	
	//Imprime os seus dados na consola
	printf("| %-20s | %-11d | %-10.2f | %-30s | %-10d | %-20s |\n", cliente->nome_cliente, cliente->NIF, cliente->saldo, cliente->morada, cliente->IDveiculoAlugado, cliente->password);
	
	printf("\n");
	system("pause"); 
	system("cls"); 
} 

//Alterar dados de uma estrutura cliente
Cliente* AlterarDadosCliente(Cliente* inicio, int nif) {

	//Variaveis
	int campo;
	char nome[MAX_NOME_CLIENTE];
	char morada[MAX_MORADA_CLIENTE];
	char password[MAX_PASSWORD];
	Cliente* atual = inicio; //Inicio da lista 

	//Percorre a lista até o atual == Null e nif da lista = nif introduzido
	while (atual != NULL && atual->NIF != nif) {
		atual = atual->seguinte;
	}

	system("cls");
	// Mostrar os dados atuais do cliente
	printf("\t++++++++++++++++++++++++++++++++++++++++ MEUS DADOS +++++++++++++++++++++++++++++++++++++++\n");
	printf("\n");
	printf("| %-20s | %-11s | %-10s | %-30s | %-10s | %-20s |\n", "NOME", "NIF", "SALDO", "MORADA", "VEICULO", "PASSWORD");
	printf("|----------------------|-------------|------------|--------------------------------|------------|----------------------|\n");
	//Imprime na consola os dados 
	printf("| %-20s | %-11d | %-10.2f | %-30s | %-10d | %-20s |\n", atual->nome_cliente, atual->NIF, atual->saldo, atual->morada, atual->IDveiculoAlugado, atual->password);

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
	//Imprime os dados na consola
	printf("| %-20s | %-11d | %-5.2f | %-30s | %-10d | %-20s |\n", atual->nome_cliente, atual->NIF, atual->saldo, atual->morada, atual->IDveiculoAlugado, atual->password);

	saveAlterarDados(inicio); //Guardar os dados atualizados 

	system("pause"); 
	system("cls"); //Limpa a consola 
} 

//Guardar as alterações efetuadas
void saveAlterarDados(Cliente* inicio) {

	 //Abrir ficheiro txt
	FILE * ficheiroCliente = fopen("Cliente.bin", "wb");

	//Se impossivel abrir informa o utilizador 
	if (ficheiroCliente == NULL) {
		printf("ERRO AO ABRIR O FICHEIRO \n");

		return inicio;
	}

	//Inicio
	Cliente* atual = inicio;

	//Percorre a lista
	while (atual != NULL) {
		//Escrever os dados no ficheiro txt 
		fwrite(atual, sizeof(Cliente), 1, ficheiroCliente);

		atual = atual->seguinte; //Proximo
	}

	//fechar o ficheiro txt 
	fclose(ficheiroCliente);
	
	//Remover ficheiro original
	if (remove("Cliente.txt") != 0) {
		return;
	}

	//Renomear fiheiro temporario
	if (rename("temp.txt", "Cliente.txt")!= 0) {
		return;
	}
}

//Carregar Saldo cliente 
Cliente* carregarSaldo(Cliente* cliente, int nif) {

	//Variavel
	Cliente* atual = cliente; //Inicio da lista
	float saldoinserido;

	//Percorre a lista até encontrar o cliente com o nif do cliente logado 
	while (atual != NULL && atual->NIF != nif) {
		atual = atual->seguinte; //Proximo
	}
		
	system("cls"); 

	printf("+++++++++++++++++++++++++++++++++++++++ CARREGAR SALDO +++++++++++++++++++++++++++++++++++++++\n");
	printf("\n");

	//Inserir o saldo 
	printf("\tINSIRA O SALDO\n"); 
	scanf("%f", &saldoinserido); 

	//Atulizar o saldo do cliente
	atual->saldo += saldoinserido; 

	//Informação do saldo total 
	printf("O SEU SALDO E DE %.2f\n", atual->saldo); 

	saveAlterarDados(cliente); //Grava as alterações no ficheiro 

	system("pause"); 
	system("cls"); 

	return cliente; 
}  

//Localizar meios de Transporte por Raio 
int veiculosRaio (char localizacaoAtual[], char tipoMeio[], int raio, Transporte* meio ) {

	//Variávies auxiliares 
	float lat, lng; 
	float lat2, lng2;
	

	Transporte* meios = meio;

	//Função para converters as palavras em coordenadas 
	get_coordinates(localizacaoAtual, API_KEY, &lat, &lng); 
	get_coordinates(meio->geocodigo, API_KEY, &lat2, &lng2);

	
		while (meios != NULL) {
		
		if (meios->disponivel && strcmp(meios->tipo, tipoMeio) == 0) { 


			// Converte as coordenadas de graus para radianos
			const double PI = acos(-1.0);
			lat *= PI / 180.0;
			lng *= PI / 180.0;
			lat2 *= PI / 180.0;
			lng2 *= PI / 180.0;

			// Calcula a distância entre as coordenadas utilizando a fórmula de Haversine
			const double R = 6371.0; // Raio médio da Terra em km
			const double dLat = lat2 - lat;
			const double dLon = lng2 - lng;
			const double a = sin(dLat / 2.0) * sin(dLat / 2.0) + cos(lat) * cos(lat) * sin(dLon / 2.0) * sin(dLon / 2.0);
			const double c = 2.0 * atan2(sqrt(a), sqrt(1.0 - a));
			const double distancia = R * c;

			// Verifica se a distância está dentro do raio
			if (distancia <= raio) {
				printf("Meio de transporte disponivel: %d\n", meios->codigo);
			}
		}

		meios = meios->seguinte;
	}

	return 0;
}







 

