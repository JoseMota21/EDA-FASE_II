#define _CRT_SECURE_NO_DEPRECATE 
#include <stdio.h>
#include "transporte.h" 

int main() {
	Transporte* meioTransporte_1 = NULL; 
	Transporte meioTransporte = { 0, ' ', 0.0, 0.0}; 

	//Ler o ficheiro Txt
	meioTransporte_1 = lerFicheiroTransporte(meioTransporte_1);
	
	//Pedir informação ao Gestor para adicionar um meio de transporte (Código, tipo, nivel bateria, automonomia estimada)  		
	printf("Insira o codigo do meio de mobilidade: ");
	scanf("%d", &meioTransporte.codigo); 

	//Verificar se existe o ID selecionado pelo o Gestor
	if (ExisteTransporte(meioTransporte_1, meioTransporte.codigo)) {
		
	}
	else {
		printf("Insira o tipo de meio de mobilidade (T ou B): ");
		scanf(" %c", &meioTransporte.tipo);

		printf("Insira a carga atual da bateria: ");
		scanf("%f", &meioTransporte.bateria); 

		//Caso o gestor coloque a bateria supeior a 100 o programa assume por defeito 100%
		if (meioTransporte.bateria > 100) {
			meioTransporte.bateria = 100; 
		}
		printf("Insira a autonomia em KM: ");
		scanf("%f", &meioTransporte.autonomia);

		printf("Insira a localização: ");
		scanf("%s", &meioTransporte.geocodigo);

		saveficheiroTransporte(&meioTransporte);
	}
	return 0;
} 