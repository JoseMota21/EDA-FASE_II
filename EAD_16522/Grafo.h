#include <stdio.h>
#include <stdbool.h> 
#define TAM 50 

typedef struct registo3 {
	int ID;
	struct registo3* seguinte;

}*Transporte;  

//Estrutura de um grafo orientado e pesado 
typedef struct registo2 {
	char vertice[TAM];  //Geoc�digo 
	float peso; 

	struct registo2* seguinte; 
}*Adjacente; 

typedef struct registo1 {
	char vertice[TAM]; //Geoc�digo 
	Adjacente adjacente; 
	Transporte transporte; //Lista ligada com os c�digos dos meios de transportes existentes 
	struct registo1* seguinte; 

}*Grafo;