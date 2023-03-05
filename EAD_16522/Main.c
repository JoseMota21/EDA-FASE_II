#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include "transporte.h" 
#include "Cliente.h" 

int main() {
	Transporte* meioTransporte_1 = NULL;
	Transporte novoTransporte = { 0, ' ', 0.0, 0.0 };

	int selecao;
	int gestor; 

	//Ler o ficheiro Txt
	meioTransporte_1 = lerFicheiroTransporte(meioTransporte_1); 

	printf("Se gestor pressione 1, se cliente pressione 2\n");
	scanf("%d", &selecao); 

	switch (selecao) { 
	case 1: 
		printf("BEM VINDO GESTOR\n"); 

		printf("1 - INSERIR TRANSPORTE \n"); 
		printf("2 - INSERIR CLIENTE \n"); 
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

				printf("%d 7 \n", novoTransporte.codigo);

				//Inserir meio de transporte na lista ligada/estrutrua
				meioTransporte_1 = InserirTransporte(meioTransporte_1, novoTransporte.codigo, novoTransporte.tipo, novoTransporte.bateria, novoTransporte.autonomia, novoTransporte.geocodigo);

				//Guardar os dados inseridos pelo o utilizador em ficheiro txt
				saveficheiroTransporte(&novoTransporte);

			}
			//Apresentar dados na consola
			listarTransporte(meioTransporte_1);
			break;

		case 2: 

			printf("INSERIR CLIENTE");  
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