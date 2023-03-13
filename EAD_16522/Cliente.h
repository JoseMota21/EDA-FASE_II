#include <stdio.h>
#include <stdbool.h>

#ifndef CLIENTE_H
#define CLIENTE_H


#define MAX_NOME_CLIENTE 80 
#define MAX_MORADA_CLIENTE 80
#define MAX_PASSWORD 20

//Estrutura para o registo do cliente
typedef struct registoCliente {
	//int ID_cliente; // ID do cliente 
	char nome_cliente[MAX_NOME_CLIENTE]; // Nome do cliente
	int NIF; // Numero de identifica��o fiscal do cliente
	float saldo; //saldo do cliente
	char morada[MAX_MORADA_CLIENTE]; //morada do cliente
	char password[MAX_PASSWORD]; 
	
	struct registoCliente* seguinte; // endere�o de mem�ria para uma struct registo Cliente

}Cliente; 

//Estrutura boleana
typedef struct {
	bool autenticado;
	Cliente* cliente;
} LoginResult;

//Fun��o existe cliente 
int ExisteCliente(Cliente* inicio, int nif); 

// Listar cliente na consola 
Cliente* listarCliente(Cliente* inicio); 

//Guardar ficheiro em txt 
Cliente* saveficheiroCliente(Cliente* inicio); 

//Ler ficheiro txt 
Cliente* lerFicheiroCliente(Cliente* inicio); 

//Remover cliente da lista ligada 
Cliente* RemoverCliente(Cliente* inicio); 

//Inserir dados atrav�s do teclado do computador 
Cliente* inputCliente(Cliente* cliente_1); 

//Login de cliente
LoginResult loginCliente(Cliente* login); 

//dados para o cliente consultar
Cliente* clientedados(Cliente* cliente); 

//Alterar determinados dados da estrutura cliente
Cliente* AlterarDadosCliente(Cliente* inicio); 

//Guardar dados alterador (ficheiro temporario criado)
void saveAlterarDados(Cliente* inicio); 

#endif /* CLIENTE_H */ 