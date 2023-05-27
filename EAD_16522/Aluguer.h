#include "Cliente.h"
#include "Transporte.h"
#include "Historico.h"
#include "API.h"

//Função para alugar transporte
void alugarTranporte(Cliente* cliente_1, Transporte* meioTransporte_1, int nif); 

//Entregar o veiculo alugado
void desalugarVeiculo(Cliente* cliente_1, Transporte* meioTransporte_1, int nif); 

//Função para imprimir os meios de transporte na localização pretendida
void imprimirLocalizacaoTransporte(Transporte* transporte); 