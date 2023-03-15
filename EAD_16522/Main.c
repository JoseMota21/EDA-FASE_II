#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include "Transporte.h" 
#include "Cliente.h" 
#include "Aluguer.h"
#include "Gestor.h"
#include <stdlib.h>
#include<stdbool.h>

int main() {
	//Inicializar as listas 
	Transporte* meioTransporte_1 = NULL; // Lista ligada transportes vazia  
	Cliente* cliente_1 = NULL; // Lista ligada clientes vazia 
	Gestor* gestor_1 = NULL; // Lista ligada clientes vazia 

	//Qual o cliente que está logado no sistema 
	Cliente* logado = NULL;

	//Ler ficheiro txt meio de transporte
	meioTransporte_1 = lerFicheiroTransporte(meioTransporte_1);

	//Ler ficheiro txt cliente
	cliente_1 = lerFicheiroCliente(cliente_1);

	//Ler ficheiro txt gestor 
	gestor_1 = lerficheiroGestor(gestor_1); 

	int opcao;
	int gestor;
	int cliente;

	do {
		system("cls");
		printf("M E N U\n");
		printf("1 - GESTOR\n");
		printf("2 - CLIENTE\n");
		printf("0 - SAIR\n");

		scanf("%d", &opcao);

		system("cls");

		switch (opcao) {

		case 1:
			do {
				printf("1 - INSERIR TRANSPORTE NOVO\n");
				printf("2 - INSERIR CLIENTE NOVO\n");
				printf("3 - REMOVER TRANSPORTE\n");
				printf("4 - REMOVER CLIENTE\n");
				printf("5 - ORDENAR TRANSPORTE AUTONOMIA\n");
				printf("6 - CONSULTAR LISTA DE TRANSPORTE\n");
				printf("7 - CONSULTAR LISTA DE CLIENTES\n");
				printf("8 - ALTERAR DADOS DE MEIOS DE TRANSPORTES\n");
				printf("9 - CONSULTAR TRANSPORTES DISPONIVEIS\n"); 
				printf("10 - CONSULTAR HISTORICO DE ALUGUER\n");
				printf("11 - INSERIR GESTOR\n");
				printf("12 - SAIR\n");
				scanf("%d", &gestor);

				system("cls");

				switch (gestor) {
				case 1:
					
					meioTransporte_1 = inputTransporte(meioTransporte_1);
					break;
				case 2:

					cliente_1 = inputCliente(cliente_1);
					break;
				case 3:

					RemoverTransporte(meioTransporte_1);
					break;
				case 4:

					RemoverCliente(cliente_1);
					break;
				case 5:

					OrdenarTransportesPorAutonomiaDecrescente(meioTransporte_1);
					system("pause"); // Pausa no sistema, pressionar alguma tecla para proseguir
					system("cls");
					break;
				case 6:

					listarTransporte(meioTransporte_1);
					system("pause"); // Pausa no sistema, pressionar alguma tecla para proseguir
					system("cls");
					break;
				case 7:

					listarCliente(cliente_1);
					system("pause"); // Pausa no sistema, pressionar alguma tecla para proseguir
					system("cls");
					break;
				case 8:

					AlterarDadosTransporte(meioTransporte_1);
					break;
				case 9:

					transportesDisponiveis(meioTransporte_1); 
					system("pause"); // Pausa no sistema, pressionar alguma tecla para proseguir
					system("cls");
					break; 
				case 10: 

					consultarHistorico(); 
					system("pause"); // Pausa no sistema, pressionar alguma tecla para proseguir
					system("cls");
					break; 
				case 11: 

					gestor_1 = inserirGestor(gestor_1); 
					break; 

				default:
					printf("OPCAO INVALIDA\n");
					break;
				}

			} while (gestor != 12);
			break;

		case 2:
		{
			LoginResult resultadologin = loginCliente(cliente_1);

			if (resultadologin.autenticado) {

				Cliente* logado = resultadologin.cliente;

				do {
					printf("1 - CONSULTAR DADOS MEUS DADOS\n");
					printf("2 - ALTERAR MEUS DADOS\n");
					printf("3 - ALUGAR TRANSPORTE\n");
					printf("4 - DESALUGAR TRANSPORTE\n");
					printf("5 - CARREGAR SALDO\n");
					printf("6 - SAIR\n");
					scanf("%d", &cliente);

					switch (cliente) {
					case 1:
						clientedados(logado);	
						break;
					case 2:

						AlterarDadosCliente(cliente_1, logado->NIF);
						break;
					case 3:

						alugarTranporte(logado, meioTransporte_1); 
						break;
					case 4: 

						desalugarVeiculo(logado, meioTransporte_1);
						break; 
					case 5: 

						carregarSaldo(cliente_1, logado->NIF); 
						break; 
					default:
						printf("OPCAO INVALIDA\n");
						break;
					}
				} while (cliente != 6);
			}
		}
	}
		
	} while (opcao != 0); 
		
	return;
}
	

	
