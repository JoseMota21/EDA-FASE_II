#include <stdio.h>
#include <stdbool.h> 

#ifndef TRANSPORTE_H 
#define TRANSPORTE_H  

//Estrutura para o registo do meio de mobilidade eletrica 
typedef struct registo {
	int codigo; // ID do meio de mobilidade  
	char tipo[10]; // (Trotinete ou Bicicleta) 
	float bateria;
	float autonomia; //Autonomia em KM  
	char geocodigo[100];	//localização 
	int disponivel;
	struct registo* seguinte; // endereço de memória para uma struct registo

}Transporte;

#endif 

#ifndef GRAFO_H
#define GRAFO_H 

//Estrutura para vertices
typedef struct vertice {
    char geocodigo[100]; // What3Words
    int ID;              // ID do meio de transporte 
    int VerticeID;
    float bateria;       // Bateria do meio de transporte
    char Tipo[20];

    //Cliente* clientes; 
    Transporte* meios;

    struct aresta* adjacencias; // Lista de adjacências
    struct vertice* seguinte;
} Vertice;

//Estrutura para as arestas
typedef struct Aresta {
    int vertice_adjacente;
    float peso;
    struct Aresta* proximo;
} Aresta;

//Estrutura para grafo 
typedef struct grafo {

    int numeroVertices;

    Aresta* arestas;
    Vertice* vertices;
} Grafo;

#endif  

//Verificar a existencia do ID na lista ligada Inicio 
int ExisteTransporte(Transporte* Inicio, int ID); 

//Remover um meio de transporte atraves do ID
Transporte* RemoverTransporte(Transporte* inicio); 

//Lista Transporte na Consola 
Transporte* listarTransporte(Transporte* Inicio);

//Guardar em ficheiro bin Transposrte
Transporte* saveficheiroTransporte(Transporte* inicio);

//Ler ficheiro bin Tranporte 
Transporte* lerFicheiroTransporte(Transporte* inicio);

//Ordenar o meio de transporte de forma decrescente a autonomia 
void OrdenarTransportesPorAutonomiaDecrescente(Transporte* inicio);  

//Adicionar transporte pelo o teclado 
Transporte* inputTransporte(Vertice* v, Transporte* meioTransporte_1); 

//Alterar dados da lista ligada transporte
Transporte* AlterarDadosTransporte(Transporte* inicio); 

//Guardar as alterações realizadas em ficheiro temporario que posteriormente irá substituir o original
void saveAlterarDadosTransportes(Transporte* inicio);  
 
//Mostrar meios de transportes disponiveis 
Transporte* transportesDisponiveis(Transporte* meioTransporte_1);  

//Vizualizar transportes por localidade
int TransportePorLocalidade(Transporte* inicio, char* localidade); 

//Veiculos elétricos com bateria inferior a 50% 
Transporte* inferior50(Transporte* inicio); 

void adicionarVertice(Grafo* g, int id, char tipo[], float bateria, char geocodigo[]); 