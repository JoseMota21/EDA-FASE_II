#include "Cliente.h"
#include "Transporte.h"
#include "Historico.h"
#include "API.h"

/**
 * @brief Realiza o aluger de um meio de transporte para um cliente. 
 * A fun��o `alugarTranporte` solicita ao cliente que insira a localiza��o atual e a localiza��o de destino. Em seguida,
 * calcula a dist�ncia entre as duas localiza��es utilizando as coordenadas. Com base na dist�ncia, calcula o
 * pre�o da viagem e verifica se o saldo do cliente � suficiente. Se o saldo for suficiente, a fun��o verifica se h�
 * transporte dispon�vel na localiza��o inicial. Se houver, solicita ao cliente o ID do transporte desejado e verifica se
 * o transporte existe, est� dispon�vel, possui autonomia suficiente e bateria suficiente para a viagem. Se todas as
 * condi��es forem atendidas, o ve�culo � alugado torna-se indispon�vel para alugar, o ID do ve�culo alugado � registado
 * no campo `IDveiculoAlugado` da estrutura `Cliente`, o saldo do cliente � atualizado, a autonomia e a bateria do
 * transporte s�o ajustadas, a localiza��o de destino � registada no campo `geocodigo` do transporte e o registo da
 * viagem � inserido no hist�rico. Em seguida, os dados s�o salvos nos ficheiros. Caso contr�rio, s�o
 * exibidas mensagens de erro adequadas. No final, os arquivos de cliente e transporte s�o atualizados com as
 * altera��es realizadas.
 *
 * @param cliente_1 Apontador para o in�cio da lista de clientes.
 * @param meioTransporte_1 Apontador para o in�cio da lista de meios de transporte.
 * @param nif NIF do cliente que est� realizando o aluguel.
 */
void alugarTranporte(Cliente* cliente_1, Transporte* meioTransporte_1, int nif); 

/**
 * @brief Desaluga o ve�culo alugado pelo um cliente.
 *
 * A fun��o `desalugarVeiculo` procura o cliente na lista com o NIF fornecido e verifica se possui um ve�culo alugado.
 * Se o cliente n�o tiver um ve�culo alugado, exibida uma mensagem informativa ao utilizador. Caso contr�rio, a fun��o percorre a
 * lista de transportes � procura do ve�culo alugado pelo cliente, com base no ID do ve�culo. Se o ve�culo
 * for encontrado, ele fica dispon�vel, o campo `IDveiculoAlugado` do cliente � ajustado para indicar que ele
 * n�o possui mais um ve�culo alugado e uma mensagem de confirma��o � exibida. Os dados s�o salvos nos ficheiros
 * correspondentes. Caso o ve�culo n�o seja encontrado, � exibida uma mensagem de erro. No final, os ficheiros de cliente e
 * transporte s�o atualizados com as altera��es realizadas.
 *
 * @param cliente_1 Apontador para o in�cio da lista de clientes.
 * @param meioTransporte_1 Apontador para o in�cio da lista de meios de transporte.
 * @param nif NIF do cliente que est� realizando a devolu��o do ve�culo.
 */
void desalugarVeiculo(Cliente* cliente_1, Transporte* meioTransporte_1, int nif); 
