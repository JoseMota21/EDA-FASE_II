#define _CRT_SECURE_NO_DEPRECATE 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Transporte.h" 


//Verificar se existe o meio de transporte pelo o ID 
int ExisteTransporte(Transporte* inicio, int id) { 
	
	//Enquanto que n�o chegar ao fim da lista analisa 
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

//Escrever novo transporte atrav�s do teclado
Transporte* inputTransporte(Transporte* meioTransporte_1) {

	//Alocar a capacidade necess�ria de memoria e indica o tamanho de espa�o de memoria a ser alocado 
	Transporte* novoTransporte = (Transporte*)malloc(sizeof(Transporte));

	printf("\t++++++++ INSERIR MEIO DE MOBILIDADE ++++++++++\n"); 
	printf("\n"); 
	
	//Pedir informa��o ao Gestor para adicionar um meio de transporte c�digo
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

	//Vari�vel para calculuar a autonomia
	float calcularAutonomia;

	//Capacidade m�xima da bateria 100%
	if (novoTransporte->bateria >= 100) {
		novoTransporte->bateria = 100; 
	}
	//Calcular a autonomia
	calcularAutonomia = novoTransporte->bateria * 80;
	novoTransporte->autonomia = calcularAutonomia / 100;

	//Inserir a localiza��o
	printf("INSIRA A LOCALIZACAO: ");
	scanf("%s", novoTransporte->geocodigo);

	system("cls");

	//Inserir de forma fixa que o transporte est� disponivel sempre que inser um novo transporte, 1 disponivel, 0 n�o disponivel
	novoTransporte->disponivel = 1; 

	//Adicionar o novo meio de transporte ao in�cio da lista
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

	//Vari�vel auxiliar em forma de apontador que ser� o primeiro elemento da lista
	Transporte* aux = inicio; 

	printf("\t++++++++ REMOVER MEIO DE MOBILIDADE ++++++++++\n"); 
	//Cabe�alho da tabela
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
	//Ap�s remover o elemento permite que a lista permane�a ligada
	Transporte* anterior = NULL;

	//Procurar na estrutura o ID pedido 
	while (atual != NULL && atual->codigo != codigo) {
		anterior = atual;
		atual = atual->seguinte;
	}

	//Quando a pesquisa chegar ao fim da lista e n�o for encontrado o id avisa o utilizador
	if (atual == NULL) {
		printf("O MEIO DE TRANSPORTE COM O ID %d NAO FOI ENCONTRADA NA LISTA\n", codigo);
		system("pause");
		system("cls");
		return NULL;
	}
	//Remove o id da lista
	if (anterior == NULL) { //Se for o primeiro da lista
		inicio = atual->seguinte; 

		system("cls");
		
		//Guardar os novos dados no ficheiro txt 
		saveficheiroTransporte(inicio); 
	}
	else {
		//Se n�o for o primeiro da lista 
		anterior->seguinte = atual->seguinte;
		saveficheiroTransporte(inicio); 
	}
	free(atual); //Libertar a memoria que estava alocada 


	printf("MEIO DE TRANSPORTE COM O ID %d REMOVIDO COM SUCESSO\n", codigo);

	system("pause"); 
	system("cls"); 

	return inicio;
}

Transporte* listarTransporte(Transporte* inicio) {

	printf("\t++++++++ LISTAR MEIO DE MOBILIDADE ++++++++++\n");
	printf("\n"); 

	//Cabe�alho da tabela
	printf("| %-5s | %-10s | %-8s | %-10s | %-30s | %-13s|\n", "ID", "TIPO", "BATERIA", "AUTONOMIA", "LOCALIZACAO", "DISPONIBILIDADE");
	printf("|-------|------------|----------|------------|--------------------------------|----------------|\n");
	
	//Percorre a at� fechar ao fim da lista
	while (inicio != NULL) {

		printf("| %-5d | %-10s | %-8.2f | %-10.2f | %-30s | %-14d |\n", inicio->codigo, inicio->tipo, inicio->bateria, inicio->autonomia, inicio->geocodigo, inicio->disponivel);

		inicio = inicio->seguinte;
	}
	return 0; 
}

//Guardar em ficheiro bin�rio a informa��o das trotinetes 
Transporte* saveficheiroTransporte(Transporte* inicio) {

	//Abrir o ficheiro
	FILE* ficheiroTransporte = fopen("Transporte.bin", "wb");

	//Se impossivel abrir o ficheiro avisa o utilizador
	if (ficheiroTransporte == NULL) {
		printf("ERRO AO ABRIR O FICHEIRO TRANSPORTE\n");
		return inicio;
	}
	
	Transporte* atual = inicio;

	//Enquanto n�o chega ao fim da estrutura 
	while (atual != NULL) {
		//Imprimir a os dados estrutura 
		fwrite(atual, sizeof(Transporte), 1, ficheiroTransporte);
		atual = atual->seguinte;
	}

	//Fechar o arquivo bin�rio
	fclose(ficheiroTransporte);

	return inicio;
}

Transporte* lerFicheiroTransporte(Transporte* inicio) {

	//Abrir o ficheiro transporte em leitura bin�ria
	FILE* ficheiroTransporte;
	ficheiroTransporte = fopen("Transporte.bin", "rb");

	//Se ficheiro n�o foi aberto corretamente
	if (ficheiroTransporte == NULL) {
		printf("ERRO AO ABRIR O FICHEIRO TRANSPORTE\n");
		return inicio;
	}

	while (1) {

		// Alocar a capacidade necess�ria de memoria e indica o tamanho de espa�o de memoria a ser alocado
		Transporte* novoTransporte = (Transporte*)malloc(sizeof(Transporte));

		//L� os dados do ficheiro binario para a estrutura e verifica se a leitura foi bem sucedida 
		if (fread(novoTransporte, sizeof(Transporte), 1, ficheiroTransporte) != 1) {
			
			free(novoTransporte); // Caso a leitura n�o tenha sido sucedida liberta a memoria alocada 
			break;
		}

		//Define o ultimo elemento da lista
		novoTransporte->seguinte = NULL;

		//Se a lista estiver vazia, a vari�vel inicio � definida como a estrutura novo transporte
		if (inicio == NULL) {
			inicio = novoTransporte;
		}
		else {
			//Se n�o percorre a lista ligada para encontrar o ultimo elemento 
			Transporte* atual = inicio;
			//Percorre a lista para encontrar o ultimo elemento 
			while (atual->seguinte != NULL) {
				atual = atual->seguinte;
			}
			atual->seguinte = novoTransporte;
		}
	}

	fclose(ficheiroTransporte);
	return inicio;
}

//Mostrar o meio de mobilidade com maior bateria 
int EncontrarIdTransporteComMaiorBateria(Transporte* inicio) {
	if (inicio == NULL) {
		return -1; // Lista vazia
	}

	Transporte* atual = inicio;
	Transporte* maior = inicio;

	while (atual != NULL) {
		if (atual->bateria > maior->bateria) {
			maior = atual; // Atualiza o ponteiro para o elemento com maior carga de bateria
		}
		atual = atual->seguinte;
	}
	printf("MEIO DE TRANSPORTE COM MAIOR BATERIA\n");
	printf("%d; %.2f\n", maior->codigo, maior->bateria);
	return maior->codigo; // Retorna o ID do meio de transporte com maior bateria
}

//Trocar a ordem dos transportes 
void TrocarTransportes(Transporte* t1, Transporte* t2) {
	int codigo_temp = t1->codigo;
	char tipo_temp[20];

	strcpy(tipo_temp, t1->tipo);
	float bateria_temp = t1->bateria;
	float autonomia_temp = t1->autonomia;
	char geocodigo_temp[20];
	strcpy(geocodigo_temp, t1->geocodigo);
	int disponivel_temp = t1->disponivel;
	
	
	t1->codigo = t2->codigo;
	strcpy(t1->tipo, t2->tipo);
	t1->bateria = t2->bateria;
	t1->autonomia = t2->autonomia;
	strcpy(t1->geocodigo, t2->geocodigo);
	t1->disponivel = t2->disponivel; 
	

	t2->codigo = codigo_temp;
	strcpy(t2->tipo, tipo_temp);
	t2->bateria = bateria_temp;
	t2->autonomia = autonomia_temp;
	strcpy(t2->geocodigo, geocodigo_temp);
	t2->disponivel = disponivel_temp; 
	
}

//Ordenar Autonomia ordem decrescente
void OrdenarTransportesPorAutonomiaDecrescente(Transporte* inicio) {
	int troca;
	Transporte* atual, * anterior = NULL;

	//Lista estiver vazia informa o utilizador
	if (inicio == NULL) {
		printf("LISTA VAZIA!\n");
		return;
	}
	do {
		troca = 0;
		atual = inicio;
		//Enquanto que o atual for diferente que o anterior 
		while (atual->seguinte != anterior) {
			//Se autonimoa atual for menor que a autonomia seguinte da lista 
			if (atual->autonomia < atual->seguinte->autonomia) {
				//A autonomia atual � seguinte 
				TrocarTransportes(atual, atual->seguinte);
				troca = 1;
			}
			atual = atual->seguinte;
		}
		anterior = atual;
	} while (troca); //Condi��o de paragem do ciclo 

	//Mensagem de informa��o ao utilizador
	printf("\t++++++++++ ORDENAR AUTONOMIA ++++++++++\n");

	printf("\n"); 

	//Cabe�alho da tabela
	printf("| %-5s | %-10s | %-8s | %-10s | %-30s | %-13s|\n", "ID", "TIPO", "BATERIA", "AUTONOMIA", "LOCALIZACAO", "DISPONIBILIDADE");
	printf("|-------|------------|----------|------------|--------------------------------|----------------|\n");


	//Enquanto que n�o chega ao fim da lista escreve na consola
	while (inicio != NULL) {
		//Escrever na consola 
		printf("| %-5d | %-10s | %-8.2f | %-10.2f | %-30s | %-14d |\n", inicio->codigo, inicio->tipo, inicio->bateria, inicio->autonomia, inicio->geocodigo, inicio->disponivel);
		inicio = inicio->seguinte;
	}
}

//Alterar dados 
Transporte* AlterarDadosTransporte(Transporte* inicio) {

	system("cls");

	//Variaveis
	int ID;
	int campo; 
	char tipo [10]; 
	float bateria; 
	float autonomia; 
	char geocodigo [20]; 
	float calculoAutonomia; 


	//Mostrar os dados atuais de todos os transportes da lista
	printf("\t++++++++++ INFORMACAO DOS TRANSPORTES ++++++++++\n");
	printf("\n"); 
	//Cabe�alho da tabela
	printf("| %-5s | %-10s | %-8s | %-10s | %-30s | %-13s|\n", "ID", "TIPO", "BATERIA", "AUTONOMIA", "LOCALIZACAO", "DISPONIBILIDADE");
	printf("|-------|------------|----------|------------|--------------------------------|----------------|\n");

	Transporte* atual = inicio;

	while (atual != NULL) {
		printf("| %-5d | %-10s | %-8.2f | %-10.2f | %-30s | %-14d |\n", atual->codigo, atual->tipo, atual->bateria, atual->autonomia, atual->geocodigo, atual->disponivel);
		atual = atual->seguinte;
	}

	printf("\n");

	//Pedir ao utilizador o ID do transporte que quer alterar
	printf("INSIRA O ID DO TRANSPORTE QUE PRETENDE ALTERAR\n");
	scanf("%d", &ID);

	//Procurar o transporte com o ID indicado pelo utilizador
	atual = inicio;
	while (atual != NULL && atual->codigo != ID) {
		atual = atual->seguinte;
	}

	//Se ID n�o encontrada informa o utilizador
	if (atual == NULL) {
		printf("TRANSPORTE COM O ID %d NAO ENCONTRADO\n", ID);
		return inicio;
	}

	system("cls");

	// Mostrar os dados atuais do transporte
	printf("INFORMACOES DO TRANSPORTE SELECIONADO:\n");
	printf("\n");
	//Cabe�alho da tabela
	printf("| %-5s | %-10s | %-8s | %-10s | %-30s | %-13s|\n", "ID", "TIPO", "BATERIA", "AUTONOMIA", "LOCALIZACAO", "DISPONIBILIDADE");
	printf("|-------|------------|----------|------------|--------------------------------|----------------|\n");
	printf("| %-5d | %-10s | %-8.2f | %-10.2f | %-30s | %-14d |\n", atual->codigo, atual->tipo, atual->bateria, atual->autonomia, atual->geocodigo, atual->disponivel);
	
	printf("\n");

	//Op��o de escolha para o cliente
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
		//Atribuir o novo nome � estrutura
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
		fgets(geocodigo, 20, stdin);
		geocodigo[strcspn(geocodigo, "\n")] = '\0';
		//Atribuir o novo nome � estrutura
		strcpy(atual->geocodigo, geocodigo);
		break;
	{
	default:
		break;
		}	
	}
	system("cls"); 

	printf("ALTERACOES EFETUADASD\n");
	printf("\n"); 
	printf("| %-5s | %-10s | %-8s | %-10s | %-30s | %-13s|\n", "ID", "TIPO", "BATERIA", "AUTONOMIA", "LOCALIZACAO", "DISPONIBILIDADE");
	printf("|-------|------------|----------|------------|--------------------------------|----------------|\n");
	printf("| %-5d | %-10s | %-8.2f | %-10.2f | %-30s | %-14d |\n", atual->codigo, atual->tipo, atual->bateria, atual->autonomia, atual->geocodigo, atual->disponivel);

	saveAlterarDadosTransportes(inicio); 

	system ("pause");
	system("cls"); 
}

//Guardar dados em ficheiro temporario (Tranportes)
void saveAlterarDadosTransportes(Transporte* inicio) {
	
	//Abrir o ficheiro
		FILE * ficheiroTransporte = fopen("Transporte.txt", "wb");

	//Se ficheiro Null informa��o ao utilizador 
	if (ficheiroTransporte == NULL) {
		printf("ERRO AO ABRIR O FICHEIRO TRANSPORTE\n");
		return inicio;
	}

	Transporte* atual = inicio;

	//Enquanto n�o chega ao fim da estrutura 
	while (atual != NULL) {

		fwrite(atual, sizeof(Transporte), 1, ficheiroTransporte);

		atual = atual->seguinte;
	}

	//Fechar o arquivo bin�rio
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

	Transporte* atual = meioTransporte_1; 

	printf("******************************************TRANSPORTES DISPONIVEIS*********************************\n"); 
	printf("\n"); 
	printf("| %-5s | %-10s | %-8s | %-10s | %-30s | %-13s|\n", "ID", "TIPO", "BATERIA", "AUTONOMIA", "LOCALIZACAO", "DISPONIBILIDADE");
	printf("|-------|------------|----------|------------|--------------------------------|----------------|\n"); 
		while (atual!= NULL){
		//Se tiver a 1 veiculo disponivel 
		if (atual->disponivel == 1) {
			printf("| %-5d | %-10s | %-8.2f | %-10.2f | %-30s | %-14d |\n", atual->codigo, atual->tipo, atual->bateria, atual->autonomia, atual->geocodigo, atual->disponivel);
		}
		atual = atual->seguinte; 

	}
	return 0; 
} 

