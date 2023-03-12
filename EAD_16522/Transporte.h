#include <stdio.h>
#include <stdbool.h>


//Estrutura para o registo do meio de mobilidade eletrica 
typedef struct registo {
	int codigo; // ID do meio de mobilidade  
	char tipo [10]; // (Trotinete ou Bicicleta) 
	float bateria;
	float autonomia; //Autonomia em KM  
	char geocodigo[20];	//localização 
	int disponivel;

	struct registo* seguinte; // endereço de memória para uma struct registo

}Transporte;

//Verificar a existencia do ID na lista ligada Inicio
int ExisteTransporte(Transporte* Inicio, int ID);

//Inserir um novo registo para Transporte 
Transporte* InserirTransporte(Transporte* Inicio, int ID, char Tipo[], float Bateria, float Autonmia, char Geocodigo[], int disponivel);

//Remover um meio de transporte atraves do ID
Transporte* RemoverTransporte(Transporte* inicio); 

//Listar Transporte na Consola 
Transporte* listarTransporte(Transporte* Inicio);

//Guardar em ficheiro txt Transposrte
Transporte* saveficheiroTransporte(Transporte* inicio);

//Ler ficheiro txt Tranporte 
Transporte* lerFicheiroTransporte(Transporte* inicio);

//Encontrar na estrutura o meio de transporte com maior bateria
int EncontrarIdTransporteComMaiorBateria(Transporte* inicio); 

//Ordenar o meio de transporte de forma decrescente a autonomia 
void OrdenarTransportesPorAutonomiaDecrescente(Transporte* inicio);  

//Adicionar transporte pelo o teclado 
Transporte* inputTransporte(Transporte* meioTransporte_1); 



