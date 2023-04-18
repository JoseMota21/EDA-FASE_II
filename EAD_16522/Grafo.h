#include <stdio.h>
#include <stdbool.h> 

typedef struct vertice {
	int ID;
	char localizacao[80]; 
	char Tipo[80]; 
	
	struct verticie* seguinte; 
}Vertice;
