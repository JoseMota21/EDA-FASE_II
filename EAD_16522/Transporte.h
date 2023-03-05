#include <stdio.h>


//Estrutura para o registo do meio de mobilidade eletrica 
typedef struct registo {
	int codigo; // ID do meio de mobilidade  
	char tipo [10]; // (Trotinete ou Bicicleta) 
	float bateria;
	float autonomia; //Autonomia em KM  
	char geocodigo[20];	//localização 

	struct registo* seguinte; // endereço de memória para uma struct registo

}Transporte;

//Verificar a existencia do ID na lista ligada Inicio
int ExisteTransporte(Transporte* Inicio, int ID);

//Inserir um novo registo para Transporte 
Transporte* InserirTransporte(Transporte* Inicio, int ID, char Tipo[], float Bateria, float Autonmia, char Geocodigo[]);

//Remover um meio de transporte atraves do ID
Transporte* RemoverTransporte(Transporte* Inicio, int ID);

//Listar Transporte na Consola 
Transporte* listarTransporte(Transporte* Inicio);

//Guardar em ficheiro txt Transposrte
Transporte* saveficheiroTransporte(Transporte* inicio);

//Ler ficheiro txt Tranporte 
Transporte* lerFicheiroTransporte(Transporte* inicio);

//ORDENAR TESTE 
void ordenarPorAutonomia(Transporte* inicio); 