#include <stdio.h>
#include <stdbool.h> 

//Estrutura Gestor
typedef struct registoGestor {

	char nome[100];
	char email[100]; 
	char password[100]; 

	struct resgistoGestor* seguinte;  //Apontador para o proximo gestor da lista

}Gestor;

//Estrutura boleana de login (Informa se sucesso/insucesso de login e o gestor) 
typedef struct {
	bool autenticado;
	Gestor* gestor;
} loginGestor;

//Guardar gestor em ficheiro txt 
Gestor* saveficheiroGestor(Gestor* inicio);

//Inserir novo gestor no inicio da lista
Gestor* inserirGestor(Gestor* gestor_1); 

//Guardar gestor em ficheiro txt 
Gestor* saveficheiroGestor(Gestor* inicio); 

//Ler o ficheiro do gestor txt 
Gestor* lerficheiroGestor(Gestor* inicio); 

//Login de Gestor
loginGestor gestorlogin(Gestor* Login); 

//Verificar se já existe o gestor por email 
Gestor* existeGestor(Gestor* gestor_1, const char* email);

