#include <stdio.h>
#include <stdbool.h> 
#include "Cliente.h"
#include "Transporte.h"

#ifndef HISTORICO_H
#define HISTORICO_H 

//Estrutura para historico
typedef struct historico {

	Cliente* cliente; 
	Transporte* meioTransporte; 

	float preco; //Pre�o da viagem
	float distancia; //distancia percorrida
	char moradaIni[80]; //Morada inicial da viagem
	char moradaFim[80]; //Morada final da viagem
	struct  historico* seguinte; // endere�o de mem�ria para uma struct registo historico 

}HistoricoRegisto; 

extern HistoricoRegisto* historico; 

//Inserir novo registo � estrutura do historico 
void InserirRegisto(Cliente* cliente, Transporte* meioTransporte, float preco, float distanciaPer, char* localidadeIni, char* localidadeFim); 

void GuardarHistorico(HistoricoRegisto* historico); 

#endif /* HISTORICO_H */ 