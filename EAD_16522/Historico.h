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

	int ID; 
	float preco; //Preço da viagem
	float distancia; //distancia percorrida
	char moradaIni[80]; //Morada inicial da viagem
	char moradaFim[80]; //Morada final da viagem
	struct  historico* seguinte; // endereço de memória para uma struct registo historico 

}HistoricoRegisto; 

extern HistoricoRegisto* historico; 

//Inserir novo registo à estrutura do historico 
void InserirRegisto(Cliente* cliente, Transporte* meioTransporte, float preco, float distanciaPer, char* localidadeIni, char* localidadeFim); 

//Guardar a estrutura historico em ficheiro txt
void GuardarHistorico(HistoricoRegisto* historico); 

//Consultar o historico 
HistoricoRegisto* consultarhistorico (HistoricoRegisto* historico); 

//Ler ficheiro TXT 
HistoricoRegisto* lerficheirohistorico(HistoricoRegisto* historico, Cliente* cliente, Transporte* meioTransporte);

//Cliente consulta historico 
void consultarHistoricoCliente(HistoricoRegisto* historico, int nif); 

#endif /* HISTORICO_H */ 