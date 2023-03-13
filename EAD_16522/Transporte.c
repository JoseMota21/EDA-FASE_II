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
			return 1;
		}
		inicio = inicio->seguinte;
	}
	return 0;
}

//Escrever novo transporte através do teclado
Transporte* inputTransporte(Transporte* meioTransporte_1) {

	Transporte* novoTransporte = (Transporte*)malloc(sizeof(Transporte));
	
	//Pedir informação ao Gestor para adicionar um meio de transporte código
	printf("Insira o codigo do meio de mobilidade: ");
	scanf("%d", &novoTransporte->codigo);

	//Verificar se existe o ID selecionado pelo o Gestor
	while (ExisteTransporte(meioTransporte_1, novoTransporte->codigo)) {
		printf("ID ja existente, por favor inserir outro ID \n");
		scanf("%d", &novoTransporte->codigo);
	}
	//Inserir o meio de transporte
	printf("Insira o tipo de meio de mobilidade (Trotinete ou Bicicleta): ");
	scanf("%s", novoTransporte->tipo);

	//Inserir a carga atual da bateria do meio de transporte
	printf("Insira a carga atual da bateria: ");
	scanf("%f", &novoTransporte->bateria);

	float calcularAutonomia;

	//Capacidade máxima da bateria 100%
	if (novoTransporte->bateria >= 100) {
		novoTransporte->bateria = 100; 
	}
	//Calcular a autonia em função
	calcularAutonomia = novoTransporte->bateria * 80;
	novoTransporte->autonomia = calcularAutonomia / 100;

	//Inserir a localização
	printf("Insira a localizacao: ");
	scanf("%s", novoTransporte->geocodigo);

	//Adicionar o novo meio de transporte ao início da lista
	novoTransporte->seguinte = meioTransporte_1;
	meioTransporte_1 = novoTransporte;

	//Guardar os dados da lista ligada no ficheiro txt 
	saveficheiroTransporte (novoTransporte);

	return meioTransporte_1;
}

//Remover um meio de transporte pelo o ID
Transporte* RemoverTransporte(Transporte* inicio) { 

	Transporte RemoverTransporte = { 0, ' ', 0.0, 0.0, 0.0 };

	int codigo;
	printf("Insira o codigo do meio de mobilidade:\n");
	scanf("%d", &codigo); 

	//Se lista estiver vazia informa o utilizador da aplciação 
	if (inicio == NULL) {
		printf("LISTA VAZIA\n");
		return NULL; //Parar de imediato se a listar tiver vazia
	}
	Transporte* atual = inicio;
	Transporte* anterior = NULL;

	//Procurar na estrutura o ID pedido 
	while (atual != NULL && atual->codigo != codigo) {
		anterior = atual;
		atual = atual->seguinte;
	}

	//Quando a pesquisa chegar ao fim da lista e não for encontrado o id avisa o utilizador
	if (atual == NULL) {
		printf("O MEIO DE TRANSPORTE COM O CODIGO %d NAO FOI ENCONTRADA NA LISTA\n", codigo);
		return NULL;
	}
	//Remove o id da lista
	if (anterior == NULL) { //Se for o primeiro
		inicio = atual->seguinte; 

		system("cls");
		
		//Guardar os novos dados no ficheiro txt 
		saveficheiroTransporte(inicio); 
	}
	else {
		anterior->seguinte = atual->seguinte;
		saveficheiroTransporte(inicio); 
	}
	free(atual); //Libertar a memoria que estava alocada 


	printf("MEIO DE TRANSPORTE COM O ID %d REMOVIDO COM SUCESSO\n", codigo);

	return inicio;
}

Transporte* listarTransporte(Transporte* inicio) {
	
	//Percorre a estrutura até fechar ao fim da lista
	while (inicio != NULL) {

		printf("%d; %s; %.2f; %.2f; %s; %d\n", inicio->codigo, inicio->tipo, inicio->bateria, inicio->autonomia, inicio->geocodigo);

		inicio = inicio->seguinte;
	}
	return 0; 
}

//Guardar em ficheiro TXT a informação das trotinetes 
Transporte* saveficheiroTransporte(Transporte* inicio) {

	//Abrir o ficheiro
	FILE* ficheiroTransporte = fopen("Transporte.txt","w");

	//Se ficheiro Null informação ao utilziador 
	if (ficheiroTransporte == NULL) {
		printf("Erro ao abrir o ficheiro Transporte\n");
		return inicio;
	}

	Transporte* atual = inicio;

	//Equanto que não chega ao fim da estrutura 
	while (atual != NULL) {
	
		//Escrever no ficheiro txt
		fprintf(ficheiroTransporte, "%d;%s;%.2f;%.2f;%s\n", atual->codigo, atual->tipo, atual->bateria, atual->autonomia, atual->geocodigo);

		atual = atual->seguinte;
	}
	//Fechar o txt
	fclose(ficheiroTransporte);
	return inicio; 
}

//Ler ficheiro txt a informação das trotinetes e colocar na estrutura 
Transporte* lerFicheiroTransporte(Transporte* inicio) {
	//Abrir ficheiro txt 
	FILE* ficheiroTransporte = fopen("Transporte.txt", "r");

	char linha[1000];
	//Se algum problema ao abrir o ficheiro returna uma mensagem de Erro ao abrir o ficheiro
	if (ficheiroTransporte == NULL) {
		printf("Erro ao abrir o ficheiro Transporte\n");
		return inicio; //return inicio 
	}
	//Enquanto que não chega ao fim do ficheiro 
	while (fgets(linha, sizeof(linha), ficheiroTransporte) != NULL) {

		Transporte* novoTransporte = (Transporte*)malloc(sizeof(Transporte));

		//Ler linha a linha do ficheiro e coloca na estrutura 
		sscanf(linha,"%d;%[^;];%f;%f;%s", &novoTransporte->codigo, novoTransporte->tipo, &novoTransporte->bateria, &novoTransporte->autonomia, novoTransporte->geocodigo);

			novoTransporte->seguinte = NULL;
	
		if (inicio == NULL) {
			inicio = novoTransporte;
		}
		else {
			Transporte* atual = inicio;

			while (atual->seguinte != NULL) {
				atual = atual->seguinte;
			}
			atual->seguinte = novoTransporte;
		}
	}
	//Fechar ficheiro txt 
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
	char geocodigo_temp[7];
	strcpy(geocodigo_temp, t1->geocodigo);
	
	
	t1->codigo = t2->codigo;
	strcpy(t1->tipo, t2->tipo);
	t1->bateria = t2->bateria;
	t1->autonomia = t2->autonomia;
	strcpy(t1->geocodigo, t2->geocodigo);
	

	t2->codigo = codigo_temp;
	strcpy(t2->tipo, tipo_temp);
	t2->bateria = bateria_temp;
	t2->autonomia = autonomia_temp;
	strcpy(t2->geocodigo, geocodigo_temp);
	
}

//Ordenar Autonomia ordem decrescente
void OrdenarTransportesPorAutonomiaDecrescente(Transporte* inicio) {
	int troca;
	Transporte* atual, * anterior = NULL;

	//Lista estiver vazia informa o utilizador
	if (inicio == NULL) {
		printf("Lista vazia!\n");
		return;
	}
	do {
		troca = 0;
		atual = inicio;
		//Enquanto que o atual for diferente que o anterior 
		while (atual->seguinte != anterior) {
			//Se autonimoa atual for menor que a autonomia seguinte da lista 
			if (atual->autonomia < atual->seguinte->autonomia) {
				//A autonomia atual é seguinte 
				TrocarTransportes(atual, atual->seguinte);
				troca = 1;
			}
			atual = atual->seguinte;
		}
		anterior = atual;
	} while (troca); //Condição de paragem do ciclo 

	//Mensagem de informação ao utilizador
	printf("TRANSPORTE ORDENADO POR AUTONOMIA\n");

	//Enquanto que não chega ao fim da lista escreve na consola
	while (inicio != NULL) {
		//Escrever na consola 
		printf("%d;%s;%.2f;%.2f;%s\n", inicio->codigo, inicio->tipo, inicio->bateria, inicio->autonomia, inicio->geocodigo);
		inicio = inicio->seguinte;
	}
}

//Alterar dados 
Transporte* AlterarDadosTransporte(Transporte* inicio) {

	//Variaveis
	int ID;
	int campo; 
	char tipo [10]; 
	float bateria; 
	float autonomia; 
	char geocodigo [20]; 

	float calculoAutonomia; 

	system("cls");

	//Mostrar os dados atuais de todos os transportes da lista
	printf("INFORMACOES DOS TRANSPORTES:\n");
	Transporte* atual = inicio;
	while (atual != NULL) {
		printf("%d; %s; %.2f; %.2f; %s\n", atual->codigo, atual->tipo, atual->bateria, atual->autonomia, atual->geocodigo);
		atual = atual->seguinte;
	}

	//Pedir ao utilizador o ID do transporte que quer alterar
	printf("INSIRA O ID DO TRANSPORTE QUE PRETENDE ALTERAR\n");
	scanf("%d", &ID);

	//Procurar o transporte com o ID indicado pelo utilizador
	atual = inicio;
	while (atual != NULL && atual->codigo != ID) {
		atual = atual->seguinte;
	}

	//Se ID não encontrada informa o utilizador
	if (atual == NULL) {
		printf("TRANSPORTE COM O ID %d NAO ENCONTRADO\n", ID);
		return inicio;
	}

	// Mostrar os dados atuais do transporte
	printf("INFORMACOES DO TRANSPORTE SELECIONADO:\n");
	printf("%d; %s; %.2f; %.2f; %s\n", atual->codigo, atual->tipo, atual->bateria, atual->autonomia, atual->geocodigo);


	//Opção de escolha para o cliente
	printf("INSERIR O CAMPO QUE PRETENDE ALTERAR\n");
	printf("1 - ID\n");
	printf("2 - TIPO\n");
	printf("3 - BATERIA\n");
	printf("4 - GEOCODIGO\n");
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
		fgets(geocodigo, 20, stdin);
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
	printf("%d;%s;%.2f;%.2f;%s\n", atual->codigo, atual->tipo, atual->bateria, atual->autonomia, atual->geocodigo); 

	saveAlterarDadosTransportes(inicio); 
}

//Guardar dados em ficheiro temporario (Tranportes)
void saveAlterarDadosTransportes(Transporte* inicio) {
	
	//Abrir ficheiro temporario 
	FILE* ficheirotemporario = fopen("tempt.txt", "w"); 

	if (ficheirotemporario == NULL) {

		printf("ERRO AO ABRIR FICHEIRO");
		return;
	}

	Transporte* atual = inicio; 

	//Enquanto não chega ao fim da lista
	while (atual != NULL) {
		//Escrever no ficheiro temporario
		fprintf(ficheirotemporario, "%d;%s;%.2f;%.2f;%s\n", atual->codigo, atual->tipo, atual->bateria, atual->autonomia, atual->geocodigo);
		atual = atual->seguinte;
	}
	fclose(ficheirotemporario); 

	//Remover ficheiro original
	if (remove("Transporte.txt") != 0) {
		return;
	}
	//Renomear fiheiro temporario
	if (rename("tempt.txt", "Transporte.txt") != 0) {
		return;
	}

}