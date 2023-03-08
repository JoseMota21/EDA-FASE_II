#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include "transporte.h" 
#include "Cliente.h" 
#include <stdlib.h>

int main() {
	Transporte* meioTransporte_1 = NULL; // Lista ligada vazia  
	Transporte novoTransporte = { 0, ' ', 0.0, 0.0 };

	//Transporte* meioTransporte_2 = NULL; 

	Cliente novoCliente = { 0, ' ', 0, 0.0, ' ' };
	Cliente* cliente_1 = NULL; // Lista ligada vazia 

	//int aux_memoria = 0; 

	//Variáveis alocadas ao swicth case 
	int selecao;
	int gestor;
	int consultaDados;
	int TransporteOpcao;

	//Ler o ficheiro Txt
	meioTransporte_1 = lerFicheiroTransporte(meioTransporte_1); // Ficheiro txt dos meios de transporte
	cliente_1 = lerFicheiroCliente(cliente_1); // Ficheiro txt do cliente

	printf("EAD 16522\n");

	printf("1 - GESTOR\n");
	printf("2 - CLIENTE\n");
	scanf("%d", &selecao);

	//Limpar consola 
	system("cls");

	//Selecionar se é gestor ou cliente
	switch (selecao) {
		//Se gestor 
	case 1:
		printf("BEM VINDO GESTOR\n");

		printf("1 - INSERIR TRANSPORTE \n");
		printf("2 - INSERIR CLIENTE \n");
		printf("3 - CONSULTAR DADOS \n");
		printf("4 - REMOVER TRANSPORTE\n");

		scanf("%d", &gestor);

		//Limpar consola 
		system("cls");

		//Selecionar as operações do gestor
		switch (gestor) {
		case 1:
			//adicionarTransporte(meioTransporte_1);

			
			break;

		}
	}



	return;
}
	

	
