#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include "transporte.h" 

int main() {
	Transporte* meioTransporte_1 = NULL;
	Transporte novoTransporte = { 0, ' ', 0.0, 0.0 }; 


	//Ler o ficheiro Txt
	meioTransporte_1 = lerFicheiroTransporte(meioTransporte_1); 

	//Pedir informação ao Gestor para adicionar um meio de transporte (Código, tipo, nivel bateria, automonomia estimada)  		
	printf("Insira o codigo do meio de mobilidade: ");
	scanf("%d", &novoTransporte.codigo);

	
	//Verificar se existe o ID selecionado pelo o Gestor
	if (ExisteTransporte(meioTransporte_1, novoTransporte.codigo)) {

	}
	else {
		printf("Insira o tipo de meio de mobilidade (T ou B): ");
		scanf(" %s", &novoTransporte.tipo);

		printf("Insira a carga atual da bateria: ");
		scanf("%f", &novoTransporte.bateria);

		//Caso o gestor coloque a bateria supeior a 100 o programa assume por defeito 100%
		if (novoTransporte.bateria > 100) {
			novoTransporte.bateria = 100;
		}
		printf("Insira a autonomia em KM: ");
		scanf("%f", &novoTransporte.autonomia);

		printf("Insira a localização: ");
		scanf("%s", &novoTransporte.geocodigo);


		meioTransporte_1 = InserirTransporte (meioTransporte_1, novoTransporte.codigo, novoTransporte.tipo, novoTransporte.bateria, novoTransporte.autonomia, novoTransporte.geocodigo);
		//listarTransporte(meioTransporte_1);
		meioTransporte_1 = saveficheiroTransporte(meioTransporte_1);

	} 
	
	

	return 0;
}