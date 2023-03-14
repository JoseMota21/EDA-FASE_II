#include <stdio.h>
#include <stdbool.h> 

//Estrutura Gestor
typedef struct registoGestor {

	char nome[100];
	char email[100]; 
	char password[100]; 

	struct resgistoGestor* seguinte;  //Apontador para o proximo gestor da lista

}Gestor;

//Estrutura boleana a utilizar no login
typedef struct {
	bool autenticado;
	Gestor* gestor;
} loginGestor;

//Guardar gestor em ficheiro txt 
Gestor* saveficheiroGestor(Gestor* inicio);

//Inserir novo gestor
Gestor* inserirGestor(Gestor* gestor_1); 

//Guardar gestor em ficheiro txt 
Gestor* saveficheiroGestor(Gestor* inicio); 

//Ler o ficheiro do gestor
Gestor* lerficheiroGestor(Gestor* inicio); 

//Login de Gestor
loginGestor gestor(Gestor* Login); 