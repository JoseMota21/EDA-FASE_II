#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include "Transporte.h" 
#include "Cliente.h" 
#include "Aluguer.h"
#include "Gestor.h"
#include "Historico.h"
#include "Grafo.h"
#include "API.h"
#include <stdlib.h>
#include<stdbool.h>

int main() {

	//Inicializar as listas 
	Transporte* meioTransporte_1 = NULL; // Lista ligada transportes vazia  
	Cliente* cliente_1 = NULL; // Lista ligada clientes vazia 
	Gestor* gestor_1 = NULL; // Lista ligada clientes vazia 
	Grafo* grafo_1 = NULL; // Lista ligada vazia 
	Vertice* vertices = NULL; // Lista ligada vazia 
	HistoricoRegisto* historico_1 = NULL; //Lista ligada historico vazia 
	Cliente* logado = NULL; //Informa qual o cliente que está logado no sistema 
	

	//Ler ficheiro bin meio de transporte
	meioTransporte_1 = lerFicheiroTransporte (meioTransporte_1);

	//Ler ficheiro bin cliente
	cliente_1 = lerFicheiroCliente (cliente_1);

	//Ler ficheiro gestor 
	gestor_1 = lerficheiroGestor (gestor_1);  

	//Ler ficheiro Historico 
	historico_1 = lerficheirohistorico(historico_1); 

	//Representar os meios de transporte em vertices 
	vertices = criarVertices(&grafo_1, meioTransporte_1);


	//Variáveis de switch case
	int opcao;
	int gestor;
	int cliente;
	int gestorech; 
	char localizacao[100];
	char localizacaoAtu[100];
	char tipoMeio[80];
	int raio; 

	//variaveis para as coordenadas convertidas 
	float lat1, lng1, lat2, lng2; 

	do {
		system("cls");

		//Mostra na consola as opçoes possiveis 
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
			//Mostra na consola as opçoes possiveis 
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

						//Opções possiveis de escolha
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
						printf("12 - LOCALIZAR TRANSPORTE POR LOCALIDADE\n");
						printf("13 - MEIOS DE TRANSPORTE COM BATERIA INFERIOR A 50\n");
						printf("14 - LISTAR VERTICES\n");
						printf("15 - IMPRIMIR GRAFO\n");

						printf("--------------------------------------------------\n");
						printf("\n");
						printf("16 - SAIR\n");
						scanf("%d", &gestor); 

						system("cls");

						switch (gestor) {
						case 1:
							//Inserir meio de transporte no inicio da lista
							meioTransporte_1 = inputTransporte(vertices,meioTransporte_1); 

							break;
						case 2:
							//Inserir cliente no inicio da lista
							cliente_1 = inputCliente(cliente_1);
							break;
						case 3:
							//Remover transporte da lista
							meioTransporte_1 = RemoverTransporte(meioTransporte_1);
							break;
						case 4:
							//Remover cliente da lista
							cliente_1 = RemoverCliente(cliente_1);
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
							//Consultar o historico de que cliente
							consultarhistorico(historico_1);
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
							fgets(localizacao, 100, stdin);
							localizacao[strcspn(localizacao, "\n")] = '\0';
							
							//Mostra quais os veiculos na localidade inserirda 
							TransportePorLocalidade(meioTransporte_1, localizacao);
							break; 
						case 13: 
							//Listar os meios de transporte com bateria inferior a 50% 
							inferior50(meioTransporte_1); 
							break; 
						case 14: 
							//Listar os vértices na consola 
							listarVertices(grafo_1); 

							system("pause"); 
							system("cls");
							break;
						case 15:  
							// Inserir arestas para cada par de meios de transporte
							for (Transporte* t1 = meioTransporte_1; t1 != NULL; t1 = t1->seguinte) {
								for (Transporte* t2 = t1->seguinte; t2 != NULL; t2 = t2->seguinte) {
									
									//Converter 3 palavras do what3words em coordenadas (latitude e longitude)
									get_coordinates(t1->geocodigo, API_KEY, &lat1, &lng1);
									get_coordinates(t2->geocodigo, API_KEY, &lat2, &lng2);
									
									//Calcular a distancia entre os vertices
									float distancia = haversine_distance(lat1, lng1, lat2, lng2); 
									
									//Criar as arestas entre os vertices (Transporte 1 e Transporte 2)
									criarAresta(grafo_1, t1->codigo, t2->codigo, distancia);
									//criarAresta(g, t2->codigo, t1->codigo, 2); // adicionar também a aresta inversa
								}
							}

							//Imprimir Grafo completo (Arestas, Vértice, peso)
							imprimirGrafo(grafo_1);

							system("pause"); 
							system("cls"); 
							break; 
						default:
							//Caso nenhuma opcao for inserida corretamente informa o utilizar 
							printf("OPCAO INVALIDA\n");
							break;
						}
					} while (gestor != 16); // Voltar para o menu anterior 

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
					//Opçoes disponvies 
					printf("SELECIONE AS OPERACOES PRETENDIDAS\n");
					printf("\n");
					printf("--------------------------------------------------\n");
					printf("1 - CONSULTAR DADOS MEUS DADOS\n");
					printf("2 - ALTERAR MEUS DADOS\n");
					printf("3 - ALUGAR TRANSPORTE\n");
					printf("4 - DESALUGAR TRANSPORTE\n");
					printf("5 - CARREGAR SALDO\n");
					printf("6 - CONSULTAR HISTORICO\n");
					printf("7 - PROCURAR PELO O RAIO\n");
					printf("--------------------------------------------------\n");
					printf("8 - SAIR\n");
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
					case 6: 
						//Cliente consulta o seu historico 
						consultarHistoricoCliente(historico_1, logado->NIF); 
						break;
					case 7: 
						//Procurar pelo o raio 
						getchar(); 
						//Inserir a localização Atual 
						printf("INSERIR A LOCALIZACAO ATUAL\n");
						fgets(localizacaoAtu, 100, stdin);
						localizacaoAtu[strcspn(localizacaoAtu, "\n")] = '\0';

						//Inseir tipo de meio de transporte desejado 
						printf("INSERIR O MEIO PRETENDIDO\n");
						fgets(tipoMeio, 100, stdin);
						tipoMeio[strcspn(tipoMeio, "\n")] = '\0'; 

						printf("INSERIR O RAIO DE PESQUISA\n");
						scanf("%d", &raio); 
						
						//Diz quais os meios de transporte disponiveis no raio a pesquisar 
						veiculosRaio(localizacaoAtu, tipoMeio, raio, meioTransporte_1);  

						system("pause"); 
						system("cls"); 
						break; 
					default:
						//Caso nenhuma opcao for inserida corretamente informa o utilizar 
						printf("OPCAO INVALIDA\n");
						break;
					}
				} while (cliente != 8); // Volta para o menu anterior
			}
		}
	}
		
	} while (opcao != 0); // Sai do programa 
		
	return;
}
	

	
