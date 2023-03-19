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

	//Informa qual o cliente que est� logado no sistema 
	Cliente* logado = NULL;

	//Ler ficheiro bin meio de transporte
	meioTransporte_1 = lerFicheiroTransporte(meioTransporte_1);

	//Ler ficheiro bin cliente
	cliente_1 = lerFicheiroCliente(cliente_1);

	//Ler ficheiro bin gestor 
	gestor_1 = lerficheiroGestor(gestor_1); 


	//Vari�veis de switch case
	int opcao;
	int gestor;
	int cliente;
	int gestorech; 

	char localiza��o[100];

	do {
		system("cls");

		//Mostra na consola as op�oes possiveis 
		printf("+********************************************************* M E N U ********************************************+\n");
		printf("\n");
		printf("1 - GESTOR\n");
		printf("2 - CLIENTE\n");
		printf("0 - SAIR\n");

		scanf("%d", &opcao);

		system("cls");

	switch (opcao) {

		case 1:
		{	
			//Mostra na consola as op�oes possiveis 
			printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++ G E S T O R +++++++++++++++++++++++++++++++++++++++++++++++\n"); 
			printf("\n");
			printf("1 - CRIAR GESTOR\n");
			printf("2 - LOGIN\n");
			printf("0 - SAIR\n");
			scanf("%d", &gestorech);

			switch (gestorech) {
			case 1:
				system("cls");
				printf("CRIAR NOVO RESGISTO\n");
				gestor_1 = inserirGestor(gestor_1); //Inserir um novo registo de gestor
				break;

			case 2:
			{
				system("cls");
				//Gestor efetua o login
				loginGestor logingestor = gestorlogin(gestor_1);

				//Se gestor estiver autenticado
				if (logingestor.autenticado) {
					Gestor* logado = logingestor.gestor;

					do {

						//Op��es possiveis de escolha
						printf("SELECIONE AS OPERACOES PRETENDIDAS\n");
						printf("\n");
						printf("--------------------------------------------------\n");
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
						printf("12 - LOCALIZAR TRANSPORTE POR LOCALIDADE");
						printf("--------------------------------------------------\n");
						printf("\n");
						printf("13 - SAIR\n");
						scanf("%d", &gestor);

						system("cls");

						switch (gestor) {
						case 1:
							//Inserir meio de transporte no inicio da lista
							meioTransporte_1 = inputTransporte(meioTransporte_1);
							break;
						case 2:
							//Inserir cliente no inicio da lista
							cliente_1 = inputCliente(cliente_1);
							break;
						case 3:
							//Remover transporte da lista
							RemoverTransporte(meioTransporte_1);
							break;
						case 4:
							//Remover cliente da lista
							RemoverCliente(cliente_1);
							break;
						case 5:
							//Ordenar transporte por ordem decrescente
							OrdenarTransportesPorAutonomiaDecrescente(meioTransporte_1);
							system("pause"); // Pausa no sistema, pressionar alguma tecla para proseguir
							system("cls");
							break;
						case 6:
							//Listar transportes na consola
							listarTransporte(meioTransporte_1);
							system("pause"); // Pausa no sistema, pressionar alguma tecla para proseguir
							system("cls");
							break;
						case 7:
							//Listar cliente na consola
							listarCliente(cliente_1);
							system("pause"); // Pausa no sistema, pressionar alguma tecla para proseguir
							system("cls");
							break;
						case 8:
							//Alterar dados de transportes
							AlterarDadosTransporte(meioTransporte_1);
							break;
						case 9:
							//Mostrar na consola os transportes disponiveis 
							transportesDisponiveis(meioTransporte_1);
							system("pause"); // Pausa no sistema, pressionar alguma tecla para proseguir
							system("cls");
							break;
						case 10:
							//Consultar o historico de que cliente alugou qual veiculo (ID e NIF)
							consultarHistorico();
							system("pause"); // Pausa no sistema, pressionar alguma tecla para proseguir
							system("cls");
							break;
						case 11:
							//Inserir novo gestor na lista
							gestor_1 = inserirGestor(gestor_1);
							break;
						case 12: 
							getchar(); 
							//Pede ao utilizador para inserir a localidade 
							printf("LOCALIDADE DE PESQUEISA:\n"); 							
							fgets(localiza��o, 100, stdin);
							localiza��o[strcspn(localiza��o, "\n")] = '\0';


							//Mostra quais os veiculos na localidade inserirda 
							TransportePorLocalidade(meioTransporte_1, localiza��o);
							break; 

						default:
							//Caso nenhuma opcao for inserida corretamente informa o utilizar 
							printf("OPCAO INVALIDA\n");
							break;
						}
					} while (gestor != 13); // Voltar para o menu anterior
				}	break;
			}while (gestorech != 0); //voltar para o menu anterior
			}
		}break;

		case 2:
		{
			//Cliente efetua o login
			LoginResult resultadologin = loginCliente(cliente_1);

			//Se cliente autenticado
			if (resultadologin.autenticado) {

				Cliente* logado = resultadologin.cliente;

				do {
					//Op�oes disponvies 
					printf("SELECIONE AS OPERACOES PRETENDIDAS\n");
					printf("\n");
					printf("--------------------------------------------------\n");
					printf("1 - CONSULTAR DADOS MEUS DADOS\n");
					printf("2 - ALTERAR MEUS DADOS\n");
					printf("3 - ALUGAR TRANSPORTE\n");
					printf("4 - DESALUGAR TRANSPORTE\n");
					printf("5 - CARREGAR SALDO\n");
					printf("--------------------------------------------------\n");
					printf("6 - SAIR\n");
					scanf("%d", &cliente);

					switch (cliente) {
					case 1:
						//Cliente consulta os seus dados
						clientedados(logado);	
						break;
					case 2:
						//Cliente altera dos seus dados
						AlterarDadosCliente(cliente_1, logado->NIF);
						break;
					case 3:
						//Cliente aluga o transportes
						alugarTranporte(cliente_1, meioTransporte_1, logado->NIF); 
						break;
					case 4: 
						//Cliente desaluga o transporte
						desalugarVeiculo(cliente_1, meioTransporte_1, logado->NIF);
						break; 
					case 5: 
						//Cliente carrega saldo
						carregarSaldo(cliente_1, logado->NIF); 
						break; 
					default:
						//Caso nenhuma opcao for inserida corretamente informa o utilizar 
						printf("OPCAO INVALIDA\n");
						break;
					}
				} while (cliente != 6); // Volta para o menu anterior
			}
		}
	}
		
	} while (opcao != 0); // Sai do programa 
		
	return;
}
	

	
