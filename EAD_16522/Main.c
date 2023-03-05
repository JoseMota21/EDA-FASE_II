#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include "transporte.h" 
#include "Cliente.h" 

int main() {
	Transporte* meioTransporte_1 = NULL;
	Transporte novoTransporte = { 0, ' ', 0.0, 0.0 };

	Cliente novoCliente = {0, ' ', 0, 0.0, ' '}; 
	Cliente* cliente_1 = NULL; 

	int selecao;
	int gestor; 

	//Ler o ficheiro Txt
	meioTransporte_1 = lerFicheiroTransporte(meioTransporte_1); 
	cliente_1 = lerFicheiroCliente(cliente_1); 

	printf("Se gestor pressione 1, se cliente pressione 2 ");
	scanf("%d", &selecao); 

	switch (selecao) { 
	case 1: 
		printf("BEM VINDO GESTOR\n"); 

		printf("1 - INSERIR TRANSPORTE \n"); 
		printf("2 - INSERIR CLIENTE \n"); 
		printf("3 - CONSULTAR VEICULOS DE TRANSPORTE \n");
		printf("4 - CONSULTAR LISTA DE CLIENTES \n");

		scanf("%d", &gestor);

		switch (gestor){ 
		case 1: 
			//Pedir informação ao Gestor para adicionar um meio de transporte(Código, tipo, nivel bateria, automonomia estimada)
				printf("Insira o codigo do meio de mobilidade: ");
				scanf("%d", &novoTransporte.codigo);

			//Verificar se existe o ID selecionado pelo o Gestor
			if (ExisteTransporte(meioTransporte_1, novoTransporte.codigo)) {

			}
			else {
				printf("Insira o tipo de meio de mobilidade (Trotinete ou Bicicleta): ");
				scanf(" %s", &novoTransporte.tipo);

				printf("Insira a carga atual da bateria: ");
				scanf("%f", &novoTransporte.bateria);

				//Caso o gestor coloque a bateria supeior a 100 o programa assume por defeito 100%
				if (novoTransporte.bateria > 100) {
					novoTransporte.bateria = 100;
				}
				printf("Insira a autonomia em KM: ");
				scanf("%f", &novoTransporte.autonomia);

				if (novoTransporte.bateria >= 100) {
					novoTransporte.autonomia = 80;
				}
				printf("Insira a localizacao: ");
				scanf("%s", &novoTransporte.geocodigo);

				//printf("%d 7 \n", novoTransporte.codigo); // VERIFICAR O QUE ESTÁ A PASSAR 

				//Inserir meio de transporte na lista ligada/estrutrua
				meioTransporte_1 = InserirTransporte(meioTransporte_1, novoTransporte.codigo, novoTransporte.tipo, novoTransporte.bateria, novoTransporte.autonomia, novoTransporte.geocodigo);

				//Guardar os dados inseridos pelo o utilizador em ficheiro txt
				saveficheiroTransporte(&novoTransporte);
			}
			break;

		case 2: 
			printf("INSERIR CLIENTE\n"); 

			//Pedir informação ao gesotr para introduzir o nome do cliente
			printf ("Insira o nome do cliente: ");
			fgets(novoCliente.nome_cliente, MAX_NOME_CLIENTE, stdin);
			novoCliente.nome_cliente[strcspn(novoCliente.nome_cliente, "\n")] = '\0'; 
			
			//scanf ("%s", &novoCliente.nome_cliente);

			printf("Inserir o Numero de Contribuiunte: "); 
			scanf ("%d", &novoCliente.NIF); 

			printf("Inserir o saldo do cliente: "); 
			scanf("%f", &novoCliente.saldo); 

			printf("Inserir a morada do cliente: "); 
			scanf("%s", &novoCliente.morada); 

			cliente_1 = InserirCliente(cliente_1, novoCliente.nome_cliente, novoCliente.NIF, novoCliente.saldo, novoCliente.morada);
			saveficheiroCliente(&novoCliente); 

			break;

		case 3: 
			//Apresentar dados na consola
			listarTransporte(meioTransporte_1);

			break; 
		case 4: 
			listarCliente(cliente_1);
			break; 
		default:
			printf("OPCAO INVALIDA");
		}
		
		break; 
	case 2: 
		printf("BEM VINDO CLIENTE");
		break;

	default:
		printf("OPCAO INVALIDA");
		break;
	}
}