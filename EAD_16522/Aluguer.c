#define _CRT_SECURE_NO_DEPRECATE 
#include "Aluguer.h"
#include <stdio.h>
#include <stdbool.h>

//Alugar Veiculo
void alugarTranporte(Cliente* cliente_1, Transporte* meioTransporte_1) {

	printf("LISTA DE TRANSPORTES LISPONIVEIS PARA ALUGAR\n");
	transportesDisponiveis(meioTransporte_1);

	// Pedir ao cliente o ID do transporte a alugar
	int ID;
	printf("INSIRA O ID DO TRANSPORTE DESEJADO:\n");
	scanf("%d", &ID); 

	printf("DISTANCIA A PERCORRER\n"); 

	// Procurar o transporte na lista // DISPONIVEL != 0
	Transporte* atual = meioTransporte_1;
	while (atual != NULL && atual->codigo != ID) {
		atual = atual->seguinte;
	}
	if (atual == NULL) {
		// Transporte não encontrado
		printf("TRANSPORTE COM O ID %d NAO ENCONTRADO\n", ID);
	}
	else if (atual->disponivel == 0) {
		//Transporte indisponível
		printf("TRANSPORTE INDISPONIVEL\n", ID);
	}
	else {
		// Transporte encontrado e disponível
		printf("TRANSPORTE ESCOLHIDO\n");
		printf("%d; %s; %.2f; %.2f; %s\n", atual->codigo, atual->tipo, atual->bateria, atual->autonomia, atual->geocodigo);
		atual->disponivel = 0;

		//Escrever o ID do veiculo alugado na estrutura cliente no campo IDVEIVULOALUGADO
		cliente_1->IDveiculoAlugado = atual->codigo;

		//Guardar o historico
		historico(cliente_1, atual); 
			
		system("pause"); 
	}

	//Atualizar o ficheiro txt 
	saveAlterarDados(cliente_1); 	
	//Atualizar o ficheito txt 
	saveAlterarDadosTransportes(meioTransporte_1); 

}
//Desalugar veiculo 
void desalugarVeiculo(Cliente* cliente_1, Transporte* meioTransporte_1) {
	
	Transporte* atual = meioTransporte_1; 

	while (atual!= NULL && atual->codigo != cliente_1->IDveiculoAlugado){ 
		atual = atual->seguinte; 
	}

	if (atual == NULL) {
		printf("TRANSPORTE NÃO ENCONTRADO\n"); 
	}
	else {
		//Transporte está disponivel
		atual->disponivel=1; 

		//Limpar o campo IDVEICULOALUGADO
		cliente_1->IDveiculoAlugado = -1; 

		printf("VEICULO ENTREGUE\n"); 
	}

	saveAlterarDados(cliente_1); 
	saveAlterarDadosTransportes(meioTransporte_1); 
}

//Historico de aluguer 
void historico(Cliente* cliente_1, Transporte* meioTransporte_1) {

	//a para não alterar o historio, irá escrever sempre no fim
	FILE* historico = fopen("Historico.txt", "a"); 
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

	if (historico == NULL) {
		printf("Erro ao abrir o arquivo de histórico\n");
		return;
	}

	char linha[100]; 

	while (fgets(linha, sizeof(linha), ficheiroHistorico)) {
		char nome_cliente[50], tipo[20];
		int nif, codigo;
		sscanf(linha,"%[^,],%d,%d,%[^,\n]", nome_cliente, &nif, &codigo, tipo);

		printf("%s; %d; %d; %s\n", nome_cliente, nif, codigo, tipo);
	}

	fclose(ficheiroHistorico);
}
	

