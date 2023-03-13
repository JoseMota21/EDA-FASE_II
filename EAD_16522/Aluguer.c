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
	printf("Insira o ID do transporte a alugar:\n");
	scanf("%d", &ID);

	// Procurar o transporte na lista // DISPONIVEL != 0
	Transporte* atual = meioTransporte_1;
	while (atual != NULL && atual->codigo != ID) {
		atual = atual->seguinte;
	}
	if (atual == NULL) {
		// Transporte não encontrado
		printf("Erro: Transporte com o ID %d não encontrado\n", ID);
	}
	else if (atual->disponivel == 0) {
		//Transporte indisponível
		printf("Erro: transporte com o ID %d já se encontra alugado\n", ID);
	}
	else {
		// Transporte encontrado e disponível
		printf("Transporte escolhido:\n");
		printf("%d; %s; %.2f; %.2f; %s\n", atual->codigo, atual->tipo, atual->bateria, atual->autonomia, atual->geocodigo);
		atual->disponivel = 0;
		
		system("pause"); 
	}
	
	//Atualizar o ficheito txt 
	saveAlterarDadosTransportes(meioTransporte_1); 
	historico(cliente_1, atual);
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

