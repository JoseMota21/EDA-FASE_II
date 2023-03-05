#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include "transporte.h" 
#include "Cliente.h" 
#include <stdlib.h>

int main() {
	Transporte* meioTransporte_1 = NULL;
	Transporte novoTransporte = { 0, ' ', 0.0, 0.0 };

	Cliente novoCliente = { 0, ' ', 0, 0.0, ' ' };
	Cliente* cliente_1 = NULL;

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
			
			//Pedir informação ao Gestor para adicionar um meio de transporte código
			printf("Insira o codigo do meio de mobilidade: ");
			scanf("%d", &novoTransporte.codigo);

			//Verificar se existe o ID selecionado pelo o Gestor
			if (ExisteTransporte(meioTransporte_1, novoTransporte.codigo)) {

			}
			else {
				//Inserir o meio de transporte
				printf("Insira o tipo de meio de mobilidade (Trotinete ou Bicicleta): ");
				scanf(" %s", &novoTransporte.tipo);

				//Inserir a carga atual da bateria do meio de transporte 
				printf("Insira a carga atual da bateria: ");
				scanf("%f", &novoTransporte.bateria);

				//Caso o gestor coloque a bateria supeior a 100 o programa assume por defeito 100%
				if (novoTransporte.bateria > 100) {
					novoTransporte.bateria = 100;
				}
				//Pedir para inserir a autonomia 
				printf("Insira a autonomia em KM: ");
				scanf("%f", &novoTransporte.autonomia);

				//A autonomia máxima do meio de transporte é de 80 km, se a capacidade da bateria for de 100 a o veiculo tem autonomia para 80 km 
				if (novoTransporte.bateria >= 100) {
					novoTransporte.autonomia = 80;
				}
				//Inserir a localização do meio de transporte
				printf("Insira a localizacao: ");
				scanf("%s", &novoTransporte.geocodigo);

				//Inserir meio de transporte na lista ligada/estrutrua
				meioTransporte_1 = InserirTransporte(meioTransporte_1, novoTransporte.codigo, novoTransporte.tipo, novoTransporte.bateria, novoTransporte.autonomia, novoTransporte.geocodigo);

				//Guardar os dados inseridos pelo o utilizador em ficheiro txt
				saveficheiroTransporte(&novoTransporte);
			}
			break;

		case 2:
			//Ignorar o \n para a proxima linha 
			getchar();

			//Pedir informação ao gesotr para introduzir o nome do cliente
			printf("Insira o nome do cliente: ");
			fgets(novoCliente.nome_cliente, MAX_NOME_CLIENTE, stdin);
			novoCliente.nome_cliente[strcspn(novoCliente.nome_cliente, "\n")] = '\0';

			//Pedir informação ao utilizador para inserir o numero de contribuinte do cliente
			printf("Inserir o Numero de Contribuiunte: ");
			scanf("%d", &novoCliente.NIF);
			
			//Pedir informação ao utilziador para inserir o saldo do cliente
			printf("Inserir o saldo do cliente: ");
			scanf("%f", &novoCliente.saldo);

			//Ignorar o ENTER anterior
			getchar();
			//Pedir informação ao utilizador para inserir a morada do cliente
			printf("Inserir a morada do cliente: ");
			fgets(novoCliente.morada, MAX_MORADA_CLIENTE, stdin);
			novoCliente.morada[strcspn(novoCliente.morada, "\n")] = '\0';

			//Inserir cliente na estrutura
			cliente_1 = InserirCliente(cliente_1, novoCliente.nome_cliente, novoCliente.NIF, novoCliente.saldo, novoCliente.morada);

			//Guardar o último dado inserido no ficheiro txt
			saveficheiroCliente(&novoCliente);
			
			//Questionar o utilzidor da aplicação de pretende inserir outro utilizador ou sair
			printf("PRETENDE ADICIONAR NOVO CLIENTE? 1 - SIM; 2- NAO\n");
			scanf("%d", &selecao);

			break;

		case 3:

			printf("PARA TRANSPORTES PRESSIONAR 1 \n");
			printf("PARA CLIENTES PRESSIONAR 2 \n");
			scanf("%d", &consultaDados);

			//Limpar consola 
			system("cls");

			switch (consultaDados) {

			case 1:
			
				printf("1 - VISUALIZAR LISTA\n"); 
				printf("2 - VISUALIZAR AUTONOMIA ORDEM DECRESCETE\n");
				printf("3 - VISUALIZAR MEIO DE TRANSPORTE COM MAIOR AUTONOMIA\n");
				scanf ("%d", &TransporteOpcao);

				switch (TransporteOpcao){
				
				case 1: 
					//Apresentar dados na consola
					printf("LISTA DE TRANSPORTES\n");
					listarTransporte(meioTransporte_1); // Listar os Transporte na consola
					break; 
				case 2: 
					system("cls");
					OrdenarTransportesPorAutonomiaDecrescente(meioTransporte_1); //Listar por ordem decrescente na consola
					break; 
				case 3: 
					system("cls"); 
					EncontrarIdTransporteComMaiorBateria(meioTransporte_1); //Transporte com maior carga de bateria 
					break; 

				default:
					printf("Opcao Inválida\n"); 
					break;
				}
				break;
			case 2:
				printf("LISTA DE CLIENTES\n");
				//Apresentar dados na consola
				listarCliente(cliente_1);
				break;
			default:
				printf("OPCAO NEGADA");
				break;
			}
			break; 

		case 4: 
			//Pedir ao utilizador para inserir o ID que pretende eliminar
			printf("INSIRA O ID QUE PRETENDE ELIMINAR: \n"); 
			scanf("%d",&novoTransporte.codigo); 

	
			RemoverTransporte(meioTransporte_1, novoTransporte.codigo); //Função de remover o meio de transporte	

			//listarTransporte(meioTransporte_1);
			break; 

		}
		break;

	//Se cliente
	case 2:
		printf("BEM VINDO CLIENTE\n");
		printf("INSIRA O ID QUE PRETENDE ELIMINAR: \n");
		scanf("%d", &novoCliente.NIF);


		RemoverCliente(cliente_1,novoCliente.NIF); 
		listarCliente(cliente_1);

			printf("INSERIR O USER\n");

			break;

		default:
			printf("OPCAO INVALIDA");
			break;
		}

	return;
}

	
