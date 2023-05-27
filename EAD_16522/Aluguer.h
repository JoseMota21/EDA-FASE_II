#include "Cliente.h"
#include "Transporte.h"
#include "Historico.h"
#include "API.h"

//Fun��o para alugar transporte
void alugarTranporte(Cliente* cliente_1, Transporte* meioTransporte_1, int nif); 

//Entregar o veiculo alugado
void desalugarVeiculo(Cliente* cliente_1, Transporte* meioTransporte_1, int nif); 

//Fun��o para imprimir os meios de transporte na localiza��o pretendida
void imprimirLocalizacaoTransporte(Transporte* transporte); 