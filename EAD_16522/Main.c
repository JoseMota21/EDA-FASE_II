#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include "transporte.h" 
#include "Cliente.h" 
#include <stdlib.h>

int main() {
	//Inicializar as listas 
	Transporte* meioTransporte_1 = NULL; // Lista ligada vazia  
	Cliente* cliente_1 = NULL; // Lista ligada vazia 
	
	//Vari�veis alocadas ao swicth case 
	int selecao;
	int gestor;
	
	//Ler o ficheiro Txt
	meioTransporte_1 = lerFicheiroTransporte(meioTransporte_1); // Ficheiro txt dos meios de transporte
	cliente_1 = lerFicheiroCliente(cliente_1); // Ficheiro txt do cliente

	printf("EAD 16522\n");

	printf("1 - GESTOR\n");
	printf("2 - CLIENTE\n");
	scanf("%d", &selecao);

	//Limpar consola 
	system("cls");

	//Selecionar se � gestor ou cliente
	switch (selecao) {
		//Se gestor 
	case 1:
		printf("BEM VINDO GESTOR\n");

		printf("1 - INSERIR TRANSPORTE \n");
		printf("2 - INSERIR CLIENTE \n");
		printf("3 - REMOVER DADOS \n");

		scanf("%d", &gestor);

		//Limpar consola 
		system("cls");

		//Selecionar as opera��es do gestor
		switch (gestor) {
		case 1:
			adicionarTransporte(meioTransporte_1); 
		break;

		case 2: 
			inputCliente(cliente_1); 
			break;
		case 3: 
			RemoverTransporte(meioTransporte_1); 
			//listarTransporte(meioTransporte_1); 

		}
	}



	return;
}
	

	
