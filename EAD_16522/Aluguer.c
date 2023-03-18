#define _CRT_SECURE_NO_DEPRECATE 
#include "Aluguer.h"
#include <stdio.h>
#include <stdbool.h>

//Alugar Veiculo
void alugarTranporte(Cliente* cliente_1, Transporte* meioTransporte_1, int nif) {

	//Variáveis 
	float distancia = 0.0;
	float preco = 0.0;

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

	//Pedir ao utilizador para inserir a distancia que vai percorrer
	printf("DISTANCIA A PERCORRER\n");
	scanf("%f", &distancia);

	printf("\n");

	//Calcular o preço necessario para completar a viagem
	preco = distancia * 0.4;

	//Caso o saldo do cliente sejá insuficiente avisa o utilizador
	if (atualC->saldo < preco) {
		printf("SALDO INSUFICIENTE\n");
		return;
	}

	//Informar o utilizador do preco final da viagem para completar o trajeto indicado
	printf("O PRECO DA VIAGEM E DE: %.2f \n", preco);

	printf("\n");

	//Lista de transportes disponiveis para alugar veiculo
	transportesDisponiveis(meioTransporte_1);

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
		// Transporte encontrado e disponível
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
		historico(atualC, atual);

		system("pause");
		system("cls");
	}

	//Atualizar o ficheiro cliente 
	saveAlterarDados(cliente_1);
	//Atualizar o ficheito transporte 
	saveAlterarDadosTransportes(meioTransporte_1);

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

//Historico de aluguer 
void historico(Cliente* cliente_1, Transporte* meioTransporte_1) {

	//Abre o ficheiro 
	FILE* historico = fopen("Historico.txt", "a"); 

	//Se ficheiro não aberto corretamente informa o utilizador
	if (historico == NULL) {
		printf("ERRO AO ABRIR O HISTORICO\n");
		return;
	}

	//Escreve no ficheiro txt 
	fprintf(historico,"%s,%d,%d,%s\n", cliente_1->nome_cliente, cliente_1->NIF, meioTransporte_1->codigo, meioTransporte_1->tipo);

	fclose(historico);
}

//Consultar historico 
void* consultarHistorico() {

	//Abrir o ficheiro com os dados de historico
	FILE* ficheiroHistorico = fopen("Historico.txt", "r");

	//Se ficheiro não aberto corretamente informa o utilizador
	if (ficheiroHistorico == NULL) {
		printf("ERRO AO ABRIR O HISTORICO\n");
		return;
	}

	//Variavel
	char linha[1000]; 
	char nome_cliente[50]; 
	char tipo[20];
	int nif, codigo;

	printf("\t++++++++++++++++++++++++++++++++++++++++++ CONSULTAR HISTORICO +++++++++++++++++++++++++++++++++++++++\n");
	printf("\n");
	printf("| %-30s | %-20s | %-10s | %-20s |\n", "NOME", "NIF", "ID", "TIPO");
	printf("|--------------------------------|----------------------|------------|----------------------|\n");

	//Lê as informações contidas no ficheiro
	while (fgets(linha, sizeof(linha), ficheiroHistorico)) { //Lê cada linha do ficheiro e armazena na variável linha
		
		sscanf(linha,"%[^,],%d,%d,%[^,\n]", nome_cliente, &nif, &codigo, tipo);

		//Imprime na consola 
		printf ("| %-30s | %-20d | %-10d | %-20s |\n", nome_cliente, nif, codigo, tipo);
		
	}
	//Fecha o ficheiro 
	fclose(ficheiroHistorico);
}