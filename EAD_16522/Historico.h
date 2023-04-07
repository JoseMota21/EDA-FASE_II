#include <stdio.h>
#include <stdbool.h> 
#include "Cliente.h"
#include "Transporte.h"

#ifndef HISTORICO_H
#define HISTORICO_H 

//Estrutura para historico
typedef struct historico {

	//Cliente* cliente; 
	//Transporte* meioTransporte; 
	 
	char nome_cliente[80]; 
	int nif; 
	int ID;
	char tipo[20];
	float preco; //Preço da viagem
	float distancia; //distancia percorrida
	char moradaIni[80]; //Morada inicial da viagem
	char moradaFim[80]; //Morada final da viagem
	struct  historico* seguinte; // endereço de memória para uma struct registo historico 

}HistoricoRegisto; 

extern HistoricoRegisto* historico; 

//Inserir novo registo à estrutura do historico 
void InserirRegisto(char* nome, int NIF, char* tipo, int id, float preco, float distanciaPer, char* localidadeIni, char* localidadeFim);

//Guardar a estrutura historico em ficheiro txt
void GuardarHistorico(HistoricoRegisto* historico); 

//Consultar o historico 
HistoricoRegisto* consultarhistorico (HistoricoRegisto* historico); 

//Ler ficheiro TXT 
HistoricoRegisto* lerficheirohistorico(HistoricoRegisto* historico);

//Cliente consulta historico 
void consultarHistoricoCliente(HistoricoRegisto* historico, int nif); 

#endif /* HISTORICO_H */ 