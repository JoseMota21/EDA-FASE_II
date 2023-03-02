#include <stdio.h>
#define MAX_TIPO 50 

typedef struct registo {
	int codigo; //Identificação do meio de mobilidade 
	char tipo; // Tipo de meio de mobilidade (Trotinete ou Bicicleta) 
	float bateria; 
	float autonomia; //Autonomia em KM  

	struct registo* seguinte; // endereço de memória para uma struct registo
	
}Transporte;

//Inserir um novo registo para Transporte 
Transporte* InserirTransporte(Transporte* Inicio, int ID, char Tipo[], float Bateria, float Autonmia);

//Verificar a existencia do ID na lista ligada Inicio
int ExisteTransporte(Transporte* Inicio, int ID); 

//Remover um meio de transporte atraves do ID
Transporte* RemoverTransporte (Transporte* Inicio, int ID); 

//Listar Transporte na Consola 
Transporte* listarTransporte (Transporte* Inicio); 

//Guardar em ficheiro txt 
Transporte* saveficheiroTransporte(Transporte* inicio);  

Transporte* lerFicheiroTransporte(Transporte* inicio); 


