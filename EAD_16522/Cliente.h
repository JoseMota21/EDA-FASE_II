#include <stdio.h>
#define MAX_NOME_CLIENTE 80 
#define MAX_MORADA_CLIENTE 80

//Estrutura para o registo do cliente
typedef struct registoCliente {
	//int ID_cliente; // ID do cliente 
	char nome_cliente[MAX_NOME_CLIENTE]; // Nome do cliente
	int NIF; // Numero de identificação fiscal do cliente
	float saldo; //saldo do cliente
	char morada[MAX_MORADA_CLIENTE]; //morada do cliente

	struct registoCliente* seguinte; // endereço de memória para uma struct registo Cliente

}Cliente; 

//Função existe cliente 
int ExisteCliente(Cliente* inicio, int nif); 

//Inserir um novo cliente 
Cliente* InserirCliente(Cliente* inicio, char nome[80], int nif, float saldo, char morada[80]); 

// Listar cliente na consola 
Cliente* listarCliente(Cliente* inicio); 

//Guardar ficheiro em txt 
Cliente* saveficheiroCliente(Cliente* inicio); 

//Ler ficheiro txt 
Cliente* lerFicheiroCliente(Cliente* inicio); 

//Remover cliente
Cliente* RemoverCliente(Cliente* inicio, int nif); 