#include <stdio.h>
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

	struct registoCliente* seguinte; // endereço de memória para uma struct registo Cliente

}Cliente; 

//Função existe cliente 
int ExisteCliente(Cliente* inicio, int nif); 

//Inserir um novo cliente 
Cliente* InserirCliente(Cliente* inicio, char nome[80], int nif, float saldo, char morada[80], char password[20]);

// Listar cliente na consola 
Cliente* listarCliente(Cliente* inicio); 

//Guardar ficheiro em txt 
Cliente* saveficheiroCliente(Cliente* inicio); 

//Ler ficheiro txt 
Cliente* lerFicheiroCliente(Cliente* inicio); 

//Remover cliente da lista ligada 
Cliente* RemoverCliente(Cliente* inicio); 

//Inserir dados através do teclado do computador 
Cliente* inputCliente(Cliente* cliente_1); 

//Login de cliente
Cliente* loginCliente(Cliente* login);  

//dados para o cliente consultar
Cliente* clientedados(Cliente* cliente); 