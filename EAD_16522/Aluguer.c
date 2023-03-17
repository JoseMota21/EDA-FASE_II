#define _CRT_SECURE_NO_DEPRECATE 
#include "Aluguer.h"
#include <stdio.h>
#include <stdbool.h>

//Alugar Veiculo
void alugarTranporte(Cliente* cliente_1, Transporte* meioTransporte_1, int nif) {

	float distancia = 0.0;
	float preco = 0.0;

	system("cls"); 

	// Encontrar o cliente com o NIF indicado
	Cliente* atualC = cliente_1;
	while (atualC != NULL && atualC->NIF != nif) {
		atualC = atualC->seguinte;
	}

	//Se o cliente já tiver veiculo alugago impossivel alugar transporte
	if (atualC->IDveiculoAlugado != -1) {

		printf("POSSUI VEICULO ALUGADO, IMPOSSIVEL ALUGAR OUTRO. POR FAVOR, ENTREGUE O VEICULO %d PARA SER POSSIVEL ALUGAR OUTRO\n", atualC->IDveiculoAlugado);
		return;
	}

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

	// Procurar o transporte na lista // DISPONIVEL != 0
	Transporte* atual = meioTransporte_1;

	//Calculo da bateria necessária 
	float bateria;
	bateria = (atual->bateria * distancia) / 80;

	while (atual != NULL && atual->codigo != ID) {
		atual = atual->seguinte;
	}
	if (atual == NULL) {
		// Transporte não encontrado
		printf("TRANSPORTE COM O ID %d NAO ENCONTRADO\n", ID);

		system("pause"); 
		system("cls");
	}
	else if (atual->disponivel == 0) {
		//Transporte indisponível
		printf("TRANSPORTE %d INDISPONIVEL\n", ID);
		system("pause");
		system("cls");
	}
	else if (atual->autonomia < distancia) {

		printf("AUTONOMIA INSUFICENTE PARA TERMINAR A VIAGEM\n");
		system("pause");
		system("cls");

	}//Calcular se tem bateria suficiente (embora não faça sentido uma vez que a autonomia está calculada em propoção com a bateria)
	else if (atual->bateria < bateria) {

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
		printf("| %-5d | %-10s | %-8.2f | %-10.2f | %-30s |\n", atual->codigo, atual->tipo, atual->bateria, atual->autonomia, atual->geocodigo);

		//printf("%d; %s; %.2f; %.2f; %s\n", atual->codigo, atual->tipo, atual->bateria, atual->autonomia, atual->geocodigo);
		atual->disponivel = 0;

		//Escrever o ID do veiculo alugado na estrutura cliente no campo IDVEIVULOALUGADO
		atualC->IDveiculoAlugado = atual->codigo;

		//Subtrair o saldo do cliente ao preço (euro) da viagem
		atualC->saldo -= preco;

		//Descontar a autonomia à estrutura do veiculo (km)
		atual->autonomia -= distancia;

		//Descontar a percentagem da bateria
		atual->bateria -= (distancia * 100) / atual->autonomia;

		//Guardar o historico
		historico(atualC, atual);

		system("pause");
		system("cls");
	}

	//Atualizar o ficheiro txt 
	saveAlterarDados(cliente_1);
	//Atualizar o ficheito txt 
	saveAlterarDadosTransportes(meioTransporte_1);

}

//Desalugar veiculo 
void desalugarVeiculo(Cliente* cliente_1, Transporte* meioTransporte_1, int nif) {

	// Encontrar o cliente com o NIF indicado
	Cliente* atualC = cliente_1;
	while (atualC != NULL && atualC->NIF != nif) {
		atualC = atualC->seguinte;
	}

	//Se não tiver veiculo alugado impossivel desalugar
	if (atualC->IDveiculoAlugado == -1) {

		printf("SEM VEICULO ALUGADO\n"); 
		return; 
	}
	
	Transporte* atual = meioTransporte_1; 

	//Percorrer a lista 
	while (atual!= NULL && atual->codigo != atualC->IDveiculoAlugado){ 
		atual = atual->seguinte; 
	}

	if (atual == NULL) {
		printf("TRANSPORTE NÃO ENCONTRADO\n"); 
	}
	else {
		//Transporte está disponivel
		atual->disponivel=1; 

		//Limpar o campo IDVEICULOALUGADO
		atualC->IDveiculoAlugado = -1; 

		printf("VEICULO ENTREGUE\n"); 
	}

	saveAlterarDados(cliente_1); 
	saveAlterarDadosTransportes(meioTransporte_1); 

	system("pause");
	system("cls");
}

//Historico de aluguer 
void historico(Cliente* cliente_1, Transporte* meioTransporte_1) {

	//a para não alterar o historio, irá escrever sempre no fim
	FILE* historico = fopen("Historico.txt", "ab"); 
	if (historico == NULL) {
		printf("Erro ao abrir o arquivo de histórico\n");
		return;
	}

	fprintf(historico,"%s,%d,%d,%s\n", cliente_1->nome_cliente, cliente_1->NIF, meioTransporte_1->codigo, meioTransporte_1->tipo);


	fclose(historico);
}

//Consultar historico 
void* consultarHistorico() {

	//Abrir o ficheiro com os dados de historico
	FILE* ficheiroHistorico = fopen("Historico.txt", "r");

	if (ficheiroHistorico == NULL) {
		printf("ERRO AO ABRIR O HISTORICO\n");
		return;
	}

	char linha[100]; 

	printf("\t++++++++++++++++++++++++++++++++++++++++++ CONSULTAR HISTORICO +++++++++++++++++++++++++++++++++++++++\n");
	printf("\n");
	printf("| %-30s | %-20s | %-10s | %-20s |\n", "NOME", "NIF", "ID", "TIPO");
	printf("|--------------------------------|----------------------|------------|----------------------|\n");

	while (fgets(linha, sizeof(linha), ficheiroHistorico)) {
		char nome_cliente[50], tipo[20];
		int nif, codigo;
		sscanf(linha,"%[^,],%d,%d,%[^,\n]", nome_cliente, &nif, &codigo, tipo);

		printf ("| %-30s | %-20d | %-10d | %-20s |\n", nome_cliente, nif, codigo, tipo);
		

		//printf("%s; %d; %d; %s\n", nome_cliente, nif, codigo, tipo);
	}

	fclose(ficheiroHistorico);
}