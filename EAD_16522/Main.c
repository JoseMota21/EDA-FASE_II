#define _CRT_SECURE_NO_DEPRECATE 
#include <stdio.h>
#include "transporte.h" 

int main() {
	Transporte* meioTransporte = NULL; 
	//Transporte meioTransporte = { 0, ' ', 0.0, 0.0, NULL }; 

	meioTransporte = lerFicheiroTransporte(meioTransporte); 
	
	/*

	//Pedir Informações para inserir meio de transporte 	
	printf("Insira o codigo do meio de mobilidade: ");
	scanf("%d", &meioTransporte.codigo);

	printf("Insira o tipo de meio de mobilidade (T ou B): ");
	scanf(" %c", &meioTransporte.tipo); 

	printf("Insira a carga atual da bateria: ");
	scanf("%f", &meioTransporte.bateria); 

	printf("Insira a autonomia em KM: ");
	scanf("%f", &meioTransporte.autonomia); 
	*/

	*/


	listarTransporte(meioTransporte);
	//saveficheiroTransporte(&meioTransporte); 

	

	return 0;

} 