#include <stdio.h>
#include <stdbool.h> 
#define TAM 50 

typedef struct registo3 {
	int ID;
	struct registo3* seguinte;

}*Transporte;  

//Estrutura de um grafo orientado e pesado 
typedef struct registo2 {
	char vertice[TAM];  //Geocódigo 
	float peso; 

	struct registo2* seguinte; 
}*Adjacente; 

typedef struct registo1 {
	char vertice[TAM]; //Geocódigo 
	Adjacente adjacente; 
	Transporte transporte; //Lista ligada com os códigos dos meios de transportes existentes 
	struct registo1* seguinte; 

}*Grafo;