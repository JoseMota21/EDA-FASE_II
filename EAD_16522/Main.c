#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include "transporte.h" 
#include "Cliente.h" 
#include <stdlib.h>

int main() {
	//Inicializar as listas 
	Transporte* meioTransporte_1 = NULL; // Lista ligada vazia  
	Cliente* cliente_1 = NULL; // Lista ligada vazia 
	
	//Variáveis alocadas ao swicth case 
	int user;
	int gestor;
	int eliminar; 
	int consultar; 
	int MenuCliente; 
	
	//Ler o ficheiro Txt
	//Ficheiro Transportes
	meioTransporte_1 = lerFicheiroTransporte(meioTransporte_1);
	// Ficheiro txt do cliente
	cliente_1 = lerFicheiroCliente(cliente_1); 
	
	printf("EAD 16522\n");

	printf("1 - GESTOR\n");
	printf("2 - CLIENTE\n");
	scanf("%d", &user);

	//Limpar consola 
	system("cls");

	//Selecionar se é gestor ou cliente
	switch (user) {
		//Se gestor 
	case 1:
		printf("BEM VINDO GESTOR\n");

		printf("1 - INSERIR TRANSPORTE \n");
		printf("2 - INSERIR CLIENTE \n");
		printf("3 - REMOVER DADOS \n");
		printf("4 - CONSULTAR DADOS \n");

		scanf("%d", &gestor);

		//Limpar consola 
		system("cls");

		//Selecionar as operações do gestor
		switch (gestor) {
		case 1:
			//Adicionar meios de transporte através da escrita no teclado
			inputTransporte(meioTransporte_1); 
		break;

		case 2: 
			//Adicionar cliente através da escrita no teclado 
			inputCliente(cliente_1); 
			break;
		case 3: 
			printf("1 - REMOVER TRANSPORTE\n"); 
			printf("2 - REMOVER CLIENTE\n");

			scanf("%d", &eliminar); 
			
			switch (eliminar) {

			case 1: 
				//Remover transporte
				RemoverTransporte(meioTransporte_1); 
				break; 

			case 2: 
				//Remover cliente
				RemoverCliente(cliente_1); 
				break; 
	
			default:
				printf("OPCAO INVALIDA"); 
				break;
			}
			break;
		case 4: 
			printf("1 - CONSULTAR TRANSPORTE\n");
			printf("2 - CONSULTAR CLIENTE\n");
			scanf("%d", &consultar);
			switch (consultar) {
			case 1: 
				//Ordenar Transporte por autonomia (decrescente)
				OrdenarTransportesPorAutonomiaDecrescente(meioTransporte_1);
				break; 

			default:
				printf("opcao invalida"); 
				break;
			}
			break; 
			break; 
		}
		break;
	case 2: 
		//Login com o user cliente (Acesso com o login e passwrod) 
		cliente_1 = loginCliente(cliente_1); 

		if (cliente_1 != NULL) {
			printf("MENU CLIENTE\n");

			printf("1 - CONSULTAR DADOS\n");
			printf("2 - ALTERAR DADOS\n");
			scanf("%d", &MenuCliente);

			switch (MenuCliente) {

			case 1:
				//Cliente a consultar dados
				clientedados(cliente_1);
				break;
			case 2: 
				//Alterar dados de cliente 
				AlterarDados(cliente_1); 

			default:
				break;
			}
		}
		//system("cls");


	}

	return;
}
	

	
