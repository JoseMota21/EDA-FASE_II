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
	int NIF; // Numero de identificação fiscal do cliente
	float saldo; //saldo do cliente
	char morada[MAX_MORADA_CLIENTE]; //morada do cliente
	char password[MAX_PASSWORD]; 
	int IDveiculoAlugado; //ID do veiculo alugado 
	
	struct registoCliente* seguinte; // endereço de memória para uma struct registo Cliente

}Cliente; 

//Estrutura boleana de login (Informa se sucesso/insucesso de login e o cliente) 
typedef struct {
	bool autenticado;
	Cliente* cliente;
} LoginResult;

//Verifica se existe cliente
int ExisteCliente(Cliente* inicio, int nif); 

// Lista cliente na consola 
Cliente* listarCliente(Cliente* inicio); 

//Guardar ficheiro em txt 
Cliente* saveficheiroCliente(Cliente* inicio); 

//Ler ficheiro txt 
Cliente* lerFicheiroCliente(Cliente* inicio); 

//Remover cliente da lista ligada 
Cliente* RemoverCliente(Cliente* inicio); 

//Inserir dados 
Cliente* inputCliente(Cliente* cliente_1); 

//Login de cliente
LoginResult loginCliente(Cliente* login); 

//Dados de cliente
Cliente* clientedados(Cliente* cliente); 

//Alterar determinados dados da estrutura cliente
Cliente* AlterarDadosCliente(Cliente* inicio, int nif); 

//Guardar dados alterador (ficheiro temporario criado)
void saveAlterarDados(Cliente* inicio); 

//Carregar saldo ao cliente
Cliente* carregarSaldo(Cliente* cliente_1, int nif); 

//Elimina os dados da estrutura cliente
void EliminarClientes_all(Cliente* inicio);

#endif /* CLIENTE_H */ 