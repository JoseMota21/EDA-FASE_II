#include "Cliente.h"
#include "Transporte.h"
#include "Historico.h"
#include "API.h"

/**
 * @brief Realiza o aluger de um meio de transporte para um cliente. 
 * A função `alugarTranporte` solicita ao cliente que insira a localização atual e a localização de destino. Em seguida,
 * calcula a distância entre as duas localizações utilizando as coordenadas. Com base na distância, calcula o
 * preço da viagem e verifica se o saldo do cliente é suficiente. Se o saldo for suficiente, a função verifica se há
 * transporte disponível na localização inicial. Se houver, solicita ao cliente o ID do transporte desejado e verifica se
 * o transporte existe, está disponível, possui autonomia suficiente e bateria suficiente para a viagem. Se todas as
 * condições forem atendidas, o veículo é alugado torna-se indisponível para alugar, o ID do veículo alugado é registado
 * no campo `IDveiculoAlugado` da estrutura `Cliente`, o saldo do cliente é atualizado, a autonomia e a bateria do
 * transporte são ajustadas, a localização de destino é registada no campo `geocodigo` do transporte e o registo da
 * viagem é inserido no histórico. Em seguida, os dados são salvos nos ficheiros. Caso contrário, são
 * exibidas mensagens de erro adequadas. No final, os arquivos de cliente e transporte são atualizados com as
 * alterações realizadas.
 *
 * @param cliente_1 Apontador para o início da lista de clientes.
 * @param meioTransporte_1 Apontador para o início da lista de meios de transporte.
 * @param nif NIF do cliente que está realizando o aluguel.
 */
void alugarTranporte(Cliente* cliente_1, Transporte* meioTransporte_1, int nif); 

/**
 * @brief Desaluga o veículo alugado pelo um cliente.
 *
 * A função `desalugarVeiculo` procura o cliente na lista com o NIF fornecido e verifica se possui um veículo alugado.
 * Se o cliente não tiver um veículo alugado, exibida uma mensagem informativa ao utilizador. Caso contrário, a função percorre a
 * lista de transportes à procura do veículo alugado pelo cliente, com base no ID do veículo. Se o veículo
 * for encontrado, ele fica disponível, o campo `IDveiculoAlugado` do cliente é ajustado para indicar que ele
 * não possui mais um veículo alugado e uma mensagem de confirmação é exibida. Os dados são salvos nos ficheiros
 * correspondentes. Caso o veículo não seja encontrado, é exibida uma mensagem de erro. No final, os ficheiros de cliente e
 * transporte são atualizados com as alterações realizadas.
 *
 * @param cliente_1 Apontador para o início da lista de clientes.
 * @param meioTransporte_1 Apontador para o início da lista de meios de transporte.
 * @param nif NIF do cliente que está realizando a devolução do veículo.
 */
void desalugarVeiculo(Cliente* cliente_1, Transporte* meioTransporte_1, int nif); 
