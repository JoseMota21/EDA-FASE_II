#define _CRT_SECURE_NO_DEPRECATE 
#include "Aluguer.h"
#include <stdio.h>
#include <stdbool.h>

//Alugar Veiculo
void alugarTranporte(Cliente* cliente_1, Transporte* meioTransporte_1, int nif) {

	//Variáveis 
	char localizacaoIni[100];
	char localizacaoFim[100];

	system("cls"); // Limpar consola

	//Inicio da lista
	Cliente* atualC = cliente_1;

	// Procura na lista o cliente com o NIF logado na aplicação 
	while (atualC != NULL && atualC->NIF != nif) {
		  atualC = atualC->seguinte;
	}

	//Se o cliente já tiver veiculo alugago impossivel alugar transporte
	if (atualC->IDveiculoAlugado != -1) {

		printf("POSSUI VEICULO ALUGADO, IMPOSSIVEL ALUGAR OUTRO. POR FAVOR, ENTREGUE O VEICULO %d PARA SER POSSIVEL ALUGAR OUTRO\n", atualC->IDveiculoAlugado);
		return;
	}

	getchar();

	//Utilizador inser a localização atual 
	printf("INSERIR A LOCALIZACAO ATUAL\n");
	fgets(localizacaoIni, 100, stdin);
	localizacaoIni[strcspn(localizacaoIni, "\n")] = '\0';

	//Utilizador inser a localização final
	printf("INSERIR A LOCALIZACAO DE DESTINO\n");
	fgets(localizacaoFim, 100, stdin);
	localizacaoFim[strcspn(localizacaoFim, "\n")] = '\0';

	//variaveis para as coordenadas convertidas 
	float lat1, lng1, lat2, lng2;
	
	//Função para converters as palavras em coordenadas
	get_coordinates(localizacaoIni, API_KEY, &lat1, &lng1);
	get_coordinates(localizacaoFim, API_KEY, &lat2, &lng2);

	//Calcular a distância percorrida entre a localizaçãoIni e localizaçãoFIM 
	float distancia = haversine_distance (lat1, lng1, lat2, lng2);

	//Informa o utilizar da distancia a percorrer 
	printf("A DISTANCIA A PERCORRER E DE %.2f KM\n ", distancia); 

	printf("\n");

	//Calcular o preço necessario para completar a viagem
	float preco = distancia * 0.4;

	//Caso o saldo do cliente sejá insuficiente avisa o utilizador
	if (atualC->saldo < preco) {
		printf("SALDO INSUFICIENTE\n");
		return;
	}

	//Informar o utilizador do preco final da viagem para completar o trajeto indicado
	printf("O PRECO DA VIAGEM E DE: %.2f \n", preco);

	printf("\n");

	//Mostra quais os veiculos na localidade inserirda, Se houver transporte na localidade inserida executa o resto do codigo 	
	if (TransportePorLocalidade(meioTransporte_1, localizacaoIni) == 1) {

		// Pedir ao cliente o ID do transporte a alugar
		int ID;
			printf("INSIRA O ID DO TRANSPORTE DESEJADO:\n");
			scanf("%d", &ID);

			//Inicio da lista
			Transporte* atual = meioTransporte_1;

			//Calculo da bateria necessária 
		float bateria;
		bateria = (atual->bateria * distancia) / 80;

		//Procura na lista de transportes o ID indicado pelo o cliente 
		while (atual != NULL && atual->codigo != ID) {
			atual = atual->seguinte;
		}
		if (atual == NULL) { // Transporte não encontrado 

			printf("TRANSPORTE COM O ID %d NAO ENCONTRADO\n", ID);

			system("pause");
			system("cls");
		}
		else if (atual->disponivel == 0) { //Transporte indisponível 

			printf("TRANSPORTE %d INDISPONIVEL\n", ID);
			system("pause");
			system("cls");
		}
		else if (atual->autonomia < distancia) { //Autonomia insuficiente

			printf("AUTONOMIA INSUFICENTE PARA TERMINAR A VIAGEM\n");
			system("pause");
			system("cls");

		}
		else if (atual->bateria < bateria) { //Bateria insuficiente

			printf("BATERIA INSUFICENTE PARA TERMINAR A VIAGEM\n");
			system("pause");
			system("cls");
		}
		else {
			system("cls");
			printf("\n");
			//Transporte encontrado e disponível
			printf("*************************************TRANSPORTE ESCOLHIDO***********************\n");
			printf("\n");
			printf("| %-5s | %-10s | %-8s | %-10s | %-30s |\n", "ID", "TIPO", "BATERIA", "AUTONOMIA", "LOCALIZACAO");
			printf("|-------|------------|----------|------------|--------------------------------|\n");

			//Mostra na consola o transporte que foi selecionado e que está disponivel 
			printf("| %-5d | %-10s | %-8.2f | %-10.2f | %-30s |\n", atual->codigo, atual->tipo, atual->bateria, atual->autonomia, atual->geocodigo);

			atual->disponivel = 0; // Veiculo alugado fica indisponivel para alugar

			//Escrever o ID do veiculo alugado na estrutura cliente no campo IDVEIVULOALUGADO
			atualC->IDveiculoAlugado = atual->codigo;

			//Subtrair o saldo do cliente ao preço (euro) da viagem
			atualC->saldo -= preco;

			//Desconta a autonomia à estrutura do veiculo (km)
			atual->autonomia -= distancia;

			//Descontar a percentagem da bateria
			atual->bateria -= (distancia * 100) / atual->autonomia;

			//Guardar o historico
			InserirRegisto(atualC->nome_cliente, atualC->NIF, atual->tipo, atual->codigo, preco, distancia, localizacaoIni, localizacaoFim);

			GuardarHistorico(historico);

			system("pause");
			system("cls");
		}

		//Atualizar o ficheiro cliente 
		saveAlterarDados(cliente_1);
		//Atualizar o ficheito transporte 
		saveAlterarDadosTransportes(meioTransporte_1);

	}
}

//Desalugar veiculo 
void desalugarVeiculo(Cliente* cliente_1, Transporte* meioTransporte_1, int nif) {

	//Inicio da lista
	Cliente* atualC = cliente_1;

	// Procura na lista o cliente com o NIF logado na aplicação 
	while (atualC != NULL && atualC->NIF != nif) {
		atualC = atualC->seguinte;
	}

	//Se não tiver veiculo alugado impossivel desalugar, informa o utilizador 
	if (atualC->IDveiculoAlugado == -1) {

		printf("SEM VEICULO ALUGADO\n"); 
		return; 
	}
	
	//Inicio da lista 
	Transporte* atual = meioTransporte_1; 

	//Percorrer a lista dos transportes até encontrar o nó que contém o veiculo alugado pelo o cliente
	//Verifica se não há mais para percorrer e verifica se o codigo do veiculo na estrutura transporte 
	//não é igual ao código do veiculo alugado
	while (atual!= NULL && atual->codigo != atualC->IDveiculoAlugado){ 
		atual = atual->seguinte; 
	}

	if (atual == NULL) { //Não encontrou o codigo do veiculo alugado 
		printf("TRANSPORTE NÃO ENCONTRADO\n"); 
	}
	else {
		//Transporte fica disponivel
		atual->disponivel=1; 

		//Cliente não tem veiculo alugado
		atualC->IDveiculoAlugado = -1; 

		printf("VEICULO ENTREGUE\n"); 
	}

	//Guardar dos dados no ficheiro cliente
	saveAlterarDados(cliente_1); 
	//Guarda os dados no ficheiro transportes
	saveAlterarDadosTransportes(meioTransporte_1); 

	system("pause");
	system("cls");
}
