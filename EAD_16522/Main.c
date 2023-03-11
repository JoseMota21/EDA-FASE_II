#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include "transporte.h" 
#include "Cliente.h" 
#include <stdlib.h>
#define true 1; 
#define false 2; 

typedef int bool;

int main() {
	//Inicializar as listas 
	Transporte* meioTransporte_1 = NULL; // Lista ligada transportes vazia  
	Cliente* cliente_1 = NULL; // Lista ligada clientes vazia 
	
	int opcao; 
	int gestor;
	int cliente;
	
	bool logado = true; 

	//Ler o ficheiro Txt
	//Ficheiro Transportes
	meioTransporte_1 = lerFicheiroTransporte(meioTransporte_1);
	// Ficheiro txt do cliente
	cliente_1 = lerFicheiroCliente(cliente_1); 

	do {
		//system("cls");
		printf("M E N U\n");
		printf("1 - GESTOR\n");
		printf("2 - CLIENTE\n");
		printf("0 - SAIR\n");

		scanf("%d", &opcao);

		switch (opcao){

		case 1: 
			do {
				printf("1 - INSERIR TRANSPORTE NOVO\n");
				printf("2 - INSERIR CLIENTE NOVO\n");
				printf("3 - REMOVER TRANSPORTE\n");
				printf("4 - REMOVER CLIENTE\n");
				printf("5 - ORDENAR TRANSPORTE AUTONOMIA\n");
				printf("6 - CONSULTAR LISTAR DE TRANSPORTE\n"); 
				printf("7 - CONSULTAR LISTA DE CLIENTES\n");
				scanf("%d", &gestor);
				system("cls");
				switch (gestor){ 
				case 1: 
					inputTransporte(meioTransporte_1);
					break;
				case 2: 
					inputCliente(cliente_1);
					break; 
				case 3: 
					RemoverTransporte(meioTransporte_1);
					break; 
				case 4: 
					RemoverCliente(cliente_1); 
					break;
				case 5: 
					OrdenarTransportesPorAutonomiaDecrescente(meioTransporte_1);
					break;
				case 6: 
					listarTransporte(meioTransporte_1);
					break;
				case 7: 
					listarCliente(cliente_1); 
					break;
				default:
					printf("OPCAO\n");
					break;
				}
				
			} while (gestor !=0);
			break;
		case 2:
			do {
				logado = loginCliente(cliente_1);
				if (logado){

					printf("1 - CONSULTAR DADOS MEUS DADOS\n");
					printf("2 - ALTERAR MEUS DADOS\n");
					scanf("%d", &cliente);

					switch (cliente) {
					case 1:
						clientedados(cliente_1);
						break;
					case 2:
						AlterarDados(cliente);
						break;
					default:
						printf("OPCAO \n");
						break;
					}
					break;
				}
				
			} while (logado !=0);
			break;
		default:
			printf("OPCAO INVALIDA\n");
			break;
		}
		break;

	} while (opcao != 0);
	
	return;
}
	

	
