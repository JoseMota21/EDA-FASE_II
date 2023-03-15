#include "Cliente.h"
#include "Transporte.h"

//Funcão para alugar transporte
void alugarTranporte(Cliente* cliente_1, Transporte* meioTransporte_1, int nif); 

//Guardar historico em ficheiro txt 
void historico(Cliente* cliente_1, Transporte* meioTransporte_1); 

//Consultar historico na consola
void* consultarHistorico(); 

//Entregar o veiculo alugado
void desalugarVeiculo(Cliente* cliente_1, Transporte* meioTransporte_1); 

