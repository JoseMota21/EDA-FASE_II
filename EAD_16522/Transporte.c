#define _CRT_SECURE_NO_DEPRECATE 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Transporte.h" 

//Verificar se existe o meio de transporte pelo o ID 
int ExisteTransporte(Transporte* inicio, int id) { 
	
	//Enquanto que não chegar ao fim da lista analisa 
	while (inicio != NULL) {

		//Se o existir na lista o codigo com o id introduzido pelo o utilizador
		if (inicio->codigo == id) {
			//Se existir na lista returna 1
			return 1;
		}
		inicio = inicio->seguinte;
	}
	return 0;
}

//Escrever novo transporte através do teclado
Transporte* inputTransporte(Transporte* meioTransporte_1) {

	//Alocar a capacidade necessária de memoria e indica o tamanho de espaço de memoria a ser alocado 
	Transporte* novoTransporte = (Transporte*)malloc(sizeof(Transporte));

	printf("\t++++++++ INSERIR MEIO DE MOBILIDADE ++++++++++\n"); 
	printf("\n"); 
	
	//Pedir informação ao Gestor para adicionar um meio de transporte código
	printf("INSIRA O ID DO NOVO MEIO DE MOBILIDADE: ");
	scanf("%d", &novoTransporte->codigo);

	//Verificar se existe o ID selecionado pelo o Gestor
	while (ExisteTransporte(meioTransporte_1, novoTransporte->codigo)) {
		printf("O ID INTRODUZIDO JA EXISTE, POR FAVOR INSIRA OUTRO DIFERENTE\n");
		scanf("%d", &novoTransporte->codigo);
	}
	//Inserir o meio de transporte
	printf("INSIRA O MEIO DE MOBILIDADE (TROTINETE, BICICLETA, MOTA): ");
	scanf("%s", novoTransporte->tipo);

	//Inserir a carga atual da bateria do meio de transporte
	printf("INSIRA A BATERIA ATUAL DO MEIO: ");
	scanf("%f", &novoTransporte->bateria);

	//Variável para calculuar a autonomia
	float calcularAutonomia;

	//Capacidade máxima da bateria 100%
	if (novoTransporte->bateria >= 100) {
		novoTransporte->bateria = 100; 
	}
	//Calcular a autonomia
	calcularAutonomia = novoTransporte->bateria * 80;
	novoTransporte->autonomia = calcularAutonomia / 100;

	//Inserir a localização
	printf("INSIRA A LOCALIZACAO: ");
	scanf("%s", novoTransporte->geocodigo);

	system("cls");

	//Inserir de forma fixa que o transporte está disponivel sempre que inser um novo transporte, 1 disponivel, 0 não disponivel
	novoTransporte->disponivel = 1; 

	//Adicionar o novo meio de transporte ao início da lista
	novoTransporte->seguinte = meioTransporte_1; 
	meioTransporte_1 = novoTransporte;

	//Guardar os dados da lista ligada no ficheiro txt 
	saveficheiroTransporte (novoTransporte);

	//Returna a lista de transporte 
	return meioTransporte_1; 
}

//Remover um meio de transporte pelo o ID
Transporte* RemoverTransporte(Transporte* inicio) { 

	//Inicializa todos os campos com valores de zero
	Transporte RemoverTransporte = { 0, ' ', 0.0, 0.0, 0.0,0};

	//Variável auxiliar primeiro elemento da lista
	Transporte* aux = inicio; 

	printf("\t++++++++ REMOVER MEIO DE MOBILIDADE ++++++++++\n"); 
	//Cabeçalho da tabela
	printf("| %-5s | %-10s | %-8s | %-10s | %-30s | %-13s|\n", "ID", "TIPO", "BATERIA", "AUTONOMIA", "LOCALIZACAO", "DISPONIBILIDADE");
	printf("|-------|------------|----------|------------|--------------------------------|----------------|\n");

	//Percorrer todos os transportes existentes na lista
	while (aux != NULL){
		printf("| %-5d | %-10s | %-8.2f | %-10.2f | %-30s | %-14d |\n", aux->codigo, aux->tipo, aux->bateria, aux->autonomia, aux->geocodigo, aux->disponivel);
		aux = aux->seguinte; 
	}

	//Variavel para ler o ID do transporte a eliminar
	int codigo;
	printf("INSIRA O ID DO MEIO DE MOBILIDDE: ");
	scanf("%d", &codigo); 

	printf("\n"); 

	//Se lista estiver vazia informa o utilizador
	if (inicio == NULL) {
		printf("LISTA VAZIA\n");
		return NULL; //Parar de imediato se a listar estiver vazia 
	}
	//Apontador para o inicio da lista de transportes
	Transporte* atual = inicio;
	//Após remover o elemento permite que a lista permaneça ligada
	Transporte* anterior = NULL;

	//Procurar na estrutura o ID pedido 
	while (atual != NULL && atual->codigo != codigo) {
		anterior = atual;
		atual = atual->seguinte;
	}

	//Quando a pesquisa chegar ao fim da lista e não for encontrado o ID avisa o utilizador
	if (atual == NULL) {
		printf("O MEIO DE TRANSPORTE COM O ID %d NAO FOI ENCONTRADA NA LISTA\n", codigo);
		system("pause");
		system("cls");
		return NULL;
	}
	//Remove o id da lista
	if (anterior == NULL) { //Se for o primeiro da lista
		inicio = atual->seguinte; 

		system("cls"); //Limpar consola
		
		//Guardar os novos dados no ficheiro txt 
		saveficheiroTransporte(inicio); 
	}
	else {
		//Se não for o primeiro da lista 
		anterior->seguinte = atual->seguinte;
		saveficheiroTransporte(inicio); 
	}
	free(atual); //Libertar a memoria que estava alocada 

	//Informação para o utilizador 
	printf("MEIO DE TRANSPORTE COM O ID %d REMOVIDO COM SUCESSO\n", codigo);

	system("pause"); // Sistema em pause 
	system("cls"); // Limpa consola

	return inicio;
}

Transporte* listarTransporte(Transporte* inicio) {

	printf("\t++++++++ LISTAR MEIO DE MOBILIDADE ++++++++++\n");
	printf("\n"); 

	//Cabeçalho da tabela
	printf("| %-5s | %-10s | %-8s | %-10s | %-30s | %-13s|\n", "ID", "TIPO", "BATERIA", "AUTONOMIA", "LOCALIZACAO", "DISPONIBILIDADE");
	printf("|-------|------------|----------|------------|--------------------------------|----------------|\n");
	
	//Percorre a até fechar ao fim da lista 
	while (inicio != NULL) {
		//Escreve na consola os dados da estrutura em questão
		printf("| %-5d | %-10s | %-8.2f | %-10.2f | %-30s | %-14d |\n", inicio->codigo, inicio->tipo, inicio->bateria, inicio->autonomia, inicio->geocodigo, inicio->disponivel);

		inicio = inicio->seguinte;
	}
	return 0; 
}

//Guardar em ficheiro binário a informação das trotinetes 
Transporte* saveficheiroTransporte(Transporte* inicio) {

	//Abrir o ficheiro
	FILE* ficheiroTransporte = fopen("Transporte.bin", "wb");

	//Se impossivel a abrir o ficheiro avisa o utilizador
	if (ficheiroTransporte == NULL) {
		printf("ERRO AO ABRIR O FICHEIRO TRANSPORTE\n");
		return inicio;
	}
	
	Transporte* atual = inicio;

	//Enquanto não chega ao fim da estrutura 
	while (atual != NULL) {
		//Imprimir a os dados estrutura 
		fwrite(atual, sizeof(Transporte), 1, ficheiroTransporte);
		atual = atual->seguinte;
	}

	//Fechar o arquivo binário
	fclose(ficheiroTransporte);

	return inicio;
}

Transporte* lerFicheiroTransporte(Transporte* inicio) {

	//Abrir o ficheiro transporte em leitura binária
	FILE* ficheiroTransporte = fopen("Transporte.bin", "rb"); 
	
	//Se ficheiro não foi aberto corretamente
	if (ficheiroTransporte == NULL) {
		printf("ERRO AO ABRIR O FICHEIRO TRANSPORTE\n");
		return inicio;
	}

	//Lê todos os dados até que não haja mais nenhum para ler no ficheiro 
	while (1) {

		// Alocar a capacidade necessária de memoria e indica o tamanho de espaço de memoria a ser alocado
		Transporte* novoTransporte = (Transporte*)malloc(sizeof(Transporte));

		//Lê os dados do ficheiro binario para a estrutura e verifica se a leitura foi bem sucedida 
		if (fread(novoTransporte, sizeof(Transporte), 1, ficheiroTransporte) != 1) {
			
			free(novoTransporte); // Caso a leitura não tenha sido sucedida liberta a memoria alocada 
			break;
		}

		//Define o ultimo elemento da lista
		novoTransporte->seguinte = NULL;

		//Se a lista estiver vazia, a variável inicio é definida como a estrutura novo transporte
		if (inicio == NULL) {
			inicio = novoTransporte;
		}
		else {
			//Se não percorre a lista ligada para encontrar o ultimo elemento 
			Transporte* atual = inicio;
			//Percorre a lista para encontrar o ultimo elemento 
			while (atual->seguinte != NULL) {
				atual = atual->seguinte;
			}
			atual->seguinte = novoTransporte;
		}
	}
	//Fechar o ficheiro
	fclose(ficheiroTransporte);
	return inicio;
}

//Trocar a ordem dos transportes 
void TrocarTransportes(Transporte* t1, Transporte* t2) {

	//Declarar variaveis
	int codigo_temp;
	char tipo_temp[20];
	char geocodigo_temp[100]; 
	float bateria_temp; 
	float autonomia_temp; 
	int disponivel_temp; 

	//Armazena temporariamente os valores dos apontadores 
	codigo_temp = t1->codigo;
	strcpy(tipo_temp, t1->tipo); //copia da string do campo tipo de t1 para a variavel tipo_temp
	bateria_temp = t1->bateria; 
	autonomia_temp = t1->autonomia;
	strcpy(geocodigo_temp, t1->geocodigo);
	disponivel_temp = t1->disponivel;
	
	//Troca os valroes da estrutura de t2 para t1
	t1->codigo = t2->codigo; //copia o valor do campo codigo da estrutura t2 para a campo codigo da estrutura t1 
	strcpy(t1->tipo, t2->tipo);
	t1->bateria = t2->bateria;
	t1->autonomia = t2->autonomia;
	strcpy(t1->geocodigo, t2->geocodigo);
	t1->disponivel = t2->disponivel; 
	
	//Atribui os valores temporarios armazenados em t2 e assim trocar os valores entre t1 e t2
	t2->codigo = codigo_temp; 
	strcpy(t2->tipo, tipo_temp);
	t2->bateria = bateria_temp; //atribui o valor do campo bateria de t2 para a variavel temporaria 
	t2->autonomia = autonomia_temp;
	strcpy(t2->geocodigo, geocodigo_temp);
	t2->disponivel = disponivel_temp; 
	
}

//Ordenar Autonomia ordem decrescente
void OrdenarTransportesPorAutonomiaDecrescente(Transporte* inicio) {
	
	//Variavel 
	int troca;
	//Atual aponta para o elemento atual da lista e anterior para o elemento anterior
	Transporte* atual, * anterior = NULL;

	//Lista estiver vazia informa o utilizador
	if (inicio == NULL) {
		printf("LISTA VAZIA!\n");
		return;
	}
	//Percorre a lista e compara e troca os elementos até que a lista esteja completamente ordenada
	do {
		troca = 0;
		atual = inicio;

		//Quando atual for igual a anterior lista está ordenada
 		while (atual->seguinte != anterior) {

			//Se autonimoa atual for menor que a autonomia seguinte da lista 
			if (atual->autonomia < atual->seguinte->autonomia) {

				//Chamar função para trocar as posições dos elementos da lista
				TrocarTransportes(atual, atual->seguinte);
				
				//Informa que houve troca
				troca = 1;
			}
			//Aponta para o proximo elemento da lista
			atual = atual->seguinte;
		}
		anterior = atual;
		//Condição de paragem do ciclo, se troca = 0 o loop é interrompido e a lista está ordenada
	} while (troca); 

	//Mensagem de informação ao utilizador
	printf("\t++++++++++ ORDENAR AUTONOMIA ++++++++++\n");

	printf("\n"); 

	//Cabeçalho da tabela
	printf("| %-5s | %-10s | %-8s | %-10s | %-30s | %-13s|\n", "ID", "TIPO", "BATERIA", "AUTONOMIA", "LOCALIZACAO", "DISPONIBILIDADE");
	printf("|-------|------------|----------|------------|--------------------------------|----------------|\n");


	//Enquanto que não chega ao fim da lista escreve na consola
	while (inicio != NULL) {
		//Escrever na consola 
		printf("| %-5d | %-10s | %-8.2f | %-10.2f | %-30s | %-14d |\n", inicio->codigo, inicio->tipo, inicio->bateria, inicio->autonomia, inicio->geocodigo, inicio->disponivel);
		inicio = inicio->seguinte;
	}
}

//Alterar dados 
Transporte* AlterarDadosTransporte(Transporte* inicio) {

	//Limpar consola 
	system("cls");

	//Variaveis
	int ID;
	int campo; 
	char tipo [10]; 
	float bateria; 
	float autonomia; 
	char geocodigo [100]; 
	float calculoAutonomia; 

	Transporte* atual = inicio;

	//Mostrar os dados atuais de todos os transportes da lista
	printf("\t++++++++++ INFORMACAO DOS TRANSPORTES ++++++++++\n");
	printf("\n"); 
	//Cabeçalho da tabela
	printf("| %-5s | %-10s | %-8s | %-10s | %-30s | %-13s|\n", "ID", "TIPO", "BATERIA", "AUTONOMIA", "LOCALIZACAO", "DISPONIBILIDADE");
	printf("|-------|------------|----------|------------|--------------------------------|----------------|\n");

	//Escreve todos os dados da lista na consola
	while (atual != NULL) {
		printf("| %-5d | %-10s | %-8.2f | %-10.2f | %-30s | %-14d |\n", atual->codigo, atual->tipo, atual->bateria, atual->autonomia, atual->geocodigo, atual->disponivel);
		atual = atual->seguinte;
	}

	printf("\n");

	//Pedir ao utilizador o ID do transporte que quer alterar
	printf("INSIRA O ID DO TRANSPORTE QUE PRETENDE ALTERAR\n");
	scanf("%d", &ID);


	atual = inicio;

	//Percorre a lista até o atual == Null e codigo da lista = ID introduzido
	while (atual != NULL && atual->codigo != ID) {
		atual = atual->seguinte;
	}

	//Se ID não encontrada informa o utilizador
	if (atual == NULL) {
		printf("TRANSPORTE COM O ID %d NAO ENCONTRADO\n", ID);
		return inicio;
	}

	system("cls");

	// Mostrar os dados atuais do transporte com o ID escolhido 
	printf("INFORMACOES DO TRANSPORTE SELECIONADO:\n");
	printf("\n");
	//Cabeçalho da tabela
	printf("| %-5s | %-10s | %-8s | %-10s | %-30s | %-13s|\n", "ID", "TIPO", "BATERIA", "AUTONOMIA", "LOCALIZACAO", "DISPONIBILIDADE");
	printf("|-------|------------|----------|------------|--------------------------------|----------------|\n");
	printf("| %-5d | %-10s | %-8.2f | %-10.2f | %-30s | %-14d |\n", atual->codigo, atual->tipo, atual->bateria, atual->autonomia, atual->geocodigo, atual->disponivel);
	
	printf("\n");

	//Opção de escolha para o cliente
	printf("INSERIR O CAMPO QUE PRETENDE ALTERAR\n");
	printf("\n");
	printf("1 - ID\n");
	printf("2 - TIPO\n");
	printf("3 - BATERIA\n");
	printf("4 - LOCALIZACAO\n");
	scanf("%d", &campo);

	switch (campo) {
	case 1:
		//Alterar o ID do meio
		printf("INSIRA O NOVO ID\n");
		scanf("%d", &atual->codigo);
		break;
	case 2:
		getchar();
		//Alterar o tipo de meio 
		printf("INSIRA O NOVO TIPO\n");
		fgets(tipo, 20, stdin);
		tipo[strcspn(tipo, "\n")] = '\0';
		//Atribuir o novo nome à estrutura
		strcpy(atual->tipo, tipo);
		break;
	case 3:
		//Alterar o nivel de bateria
		printf("INSERIA O NIVEL DE BATERIA\n");
		scanf("%f", &atual->bateria);

		//Calcular a autonomia
		calculoAutonomia = atual->bateria * 80;
		atual->autonomia = calculoAutonomia / 100;
		break;
	case 4:
		getchar();
		printf("INSIRA A LOCALIZACAO\n");
		fgets(geocodigo, 100, stdin);
		geocodigo[strcspn(geocodigo, "\n")] = '\0';
		//Atribuir o novo nome à estrutura
		strcpy(atual->geocodigo, geocodigo);
		break;
	{
	default:
		break;
		}	
	}
	system("cls"); 

	//Mostra na consola os dados alterados do transporte escolhido
	printf("ALTERACOES EFETUADASD\n");
	printf("\n"); 
	printf("| %-5s | %-10s | %-8s | %-10s | %-30s | %-13s|\n", "ID", "TIPO", "BATERIA", "AUTONOMIA", "LOCALIZACAO", "DISPONIBILIDADE");
	printf("|-------|------------|----------|------------|--------------------------------|----------------|\n");
	printf("| %-5d | %-10s | %-8.2f | %-10.2f | %-30s | %-14d |\n", atual->codigo, atual->tipo, atual->bateria, atual->autonomia, atual->geocodigo, atual->disponivel);

	//Guarda as alterações no ficheiro bin
	saveAlterarDadosTransportes(inicio); 

	system ("pause");
	system("cls"); 
}

//Guardar dados em ficheiro temporario (Tranportes)
void saveAlterarDadosTransportes(Transporte* inicio) {
	
	//Abrir o ficheiro
	FILE * ficheiroTransporte = fopen("Transporte.bin", "wb");

	//Se ficheiro Null informação ao utilizador 
	if (ficheiroTransporte == NULL) {
		printf("ERRO AO ABRIR O FICHEIRO TRANSPORTE\n");
		return inicio;
	}

	//Inicio 
	Transporte* atual = inicio;

	//Enquanto não chega ao fim da estrutura 
	while (atual != NULL) {

		fwrite(atual, sizeof(Transporte), 1, ficheiroTransporte);

		atual = atual->seguinte;
	}

	//Fechar o arquivo binário
	fclose(ficheiroTransporte);

	//Remover ficheiro original
	if (remove("Transporte.txt") != 0) {
		return;
	}
	//Renomear fiheiro temporario
	if (rename("tempt.txt", "Transporte.txt") != 0) {
		return;
	}
}

//Mostrar meios de transportes disponiveis 
Transporte* transportesDisponiveis(Transporte* meioTransporte_1) { 

		//Primeiro elemento da lista 
		Transporte* atual = meioTransporte_1; 

		//Mostra os transportes disponiveis
		printf("******************************************TRANSPORTES DISPONIVEIS*********************************\n"); 
		printf("\n"); 
		printf("| %-5s | %-10s | %-8s | %-10s | %-30s | %-13s|\n", "ID", "TIPO", "BATERIA", "AUTONOMIA", "LOCALIZACAO", "DISPONIBILIDADE");
		printf("|-------|------------|----------|------------|--------------------------------|----------------|\n"); 
		
		//Percorre a lista dos transportes até ao fim
		while (atual!= NULL){

		//Se tiver a 1 o campo disponivel significa que o veiculo está disponivel
		if (atual->disponivel == 1) {
			//Imprime os transportes disponiveis na consola
			printf("| %-5d | %-10s | %-8.2f | %-10.2f | %-30s | %-14d |\n", atual->codigo, atual->tipo, atual->bateria, atual->autonomia, atual->geocodigo, atual->disponivel);
		}

		//Aponta para o proximo elemento da lista
		atual = atual->seguinte; 

	}
	return 0; 
} 

//Mostrar os transportes na localidade mencionada
int	TransportePorLocalidade(Transporte* inicio, char* localidade) {

	printf("\t++++++++ LISTAR MEIO DE MOBILIDADE ++++++++++\n");
	printf("\n");

	//Cabeçalho da tabela
	printf("| %-5s | %-10s | %-8s | %-10s | %-30s | %-13s|\n", "ID", "TIPO", "BATERIA", "AUTONOMIA", "LOCALIZACAO", "DISPONIBILIDADE");
	printf("|-------|------------|----------|------------|--------------------------------|----------------|\n");

	bool encontrado = false; 
	//Percorre a lista
	while (inicio != NULL) {
		// Verifica se o transporte está na localidade desejada
		if (strcmp(inicio->geocodigo, localidade) == 0) {
			//Escreve na consola os dados da estrutura em questão
			printf("| %-5d | %-10s | %-8.2f | %-10.2f | %-30s | %-14d |\n", inicio->codigo, inicio->tipo, inicio->bateria, inicio->autonomia, inicio->geocodigo, inicio->disponivel); 

			//Caso encontre a localidade
			encontrado = true; 
		}
		inicio = inicio->seguinte;
	} 

	printf("\n"); 
	
	//Se a localidade não corresponder informa o utilizador 
	if (!encontrado) {
		printf("NAO EXISTE O VEICULO NA LOCALIDADE PRETENDIDA\n"); 
		system("pause"); 
		system("cls"); 

		return 0; 
	}

	return 1;
}

//Veiculos elétricos com bateria inferior a 50% 
Transporte* inferior50(Transporte* inicio) {

	//Percorrer a lista ligada 
	while (inicio!= NULL) { 

		//Verifica qual o meio de transporte com bateria inferior a 50% 
		if (inicio->bateria < 50.0) {
			printf("%d;%s\n", inicio->codigo, inicio->tipo); 
		}

		inicio = inicio->seguinte; 
	}

} 

