/* ================================================================== *
	Universidade Federal de Sao Carlos - UFSCar, Sorocaba

	Disciplina: Algoritmos e Programação 2
	Prof. Tiago A. Almeida

	Lista 01 - Exercício 04 - Lista Estática

	Instrucoes
	----------

	Este arquivo contem o codigo que auxiliara no desenvolvimento do
	exercicio. Voce precisara completar as partes requisitadas.

* ================================================================== *
	Dados do aluno:

	RA: 726563
	Nome: Lucca La Fonte Albuquerque Carvalho

* ================================================================== */

#include <stdio.h>

#define MAX 100 // tamanho maximo da lista

// menu de opcoes
#define INICIALIZAR 		1
#define ADICIONAR 			2
#define ADICIONAR_POSICAO 	3
#define REMOVER 			4
#define REMOVER_OCORRENCIAS 5
#define BUSCAR 				6
#define IMPRIMIR			7
#define IMPRIMIR_POSICAO	8	
#define SAIR 				0

// frases pre-definidas para saida
#define FRASE_LISTA_CHEIA "Lista cheia!\n"
#define FRASE_LISTA_VAZIA "Lista vazia!\n"
#define FRASE_ELEM_NAO_ENCONTRADO "Elemento nao encontrado!\n"
#define FRASE_POSICAO_NAO_EXISTENTE "Posicao nao existente!\n"
#define FRASE_POSICAO_VAZIA "Posicao vazia!\n"


//Declaracoes das funcoes
void inicializarLista(int Lista[], int qt_elementos);
void adicionarElemento(int Lista[], int qt_elementos, int valor);
void adicionarPosicao(int Lista[], int qt_elementos, int valor, int posicao);
void removerPosicao(int Lista[], int qt_elementos, int posicao);
int removerOcorrencias(int Lista[], int qt_elementos, int valor);
int buscarValor(int Lista[], int qt_elementos, int valor);
void imprimirLista(int Lista[], int qt_elementos);
void imprimirPosicao(int Lista[], int posicao);
/* ------------------------------ */
/* ROTINA PRINCIPAL - NAO ALTERAR */
/* ------------------------------ */
int main()
{
	int Lista[MAX],		// lista
	    qt_elementos=0,	// quantidade de elementos na lista
	    opcao,			// opcao selecionada pelo usuario
	    valor,			// valor informado pelo usuario
	    posicao,		// posicao informada pelo usuario
	    qt_removidos;	// armazena a quantidade de elementos removidos na opcao 5
	   

	scanf("%d", &opcao);

	while (opcao != SAIR)
	{
		switch(opcao)
		{
			case INICIALIZAR:
				if (qt_elementos == 0) {
					scanf("%d", &qt_elementos);
					inicializarLista(Lista, qt_elementos);
				}
				else
					printf("A lista contem elementos!\n");
				
			break;

			case ADICIONAR:
				if (qt_elementos == MAX) printf(FRASE_LISTA_CHEIA);
				else {
					scanf("%d", &valor);
					adicionarElemento(Lista, qt_elementos, valor);
					qt_elementos++;
				}

			break;		

			case ADICIONAR_POSICAO:
				if (qt_elementos == MAX) printf(FRASE_LISTA_CHEIA);
				else {
					scanf("%d", &posicao);
				
					if (posicao > qt_elementos) printf(FRASE_POSICAO_NAO_EXISTENTE);
					else {
						scanf("%d", &valor);
						adicionarPosicao(Lista, qt_elementos, valor, posicao);
						qt_elementos++;
					}
				}

			break;

			case REMOVER:

				if (qt_elementos == 0) printf(FRASE_LISTA_VAZIA);
				else {
					scanf("%d", &posicao);

					if ((posicao > qt_elementos) || (posicao < 1)) printf(FRASE_POSICAO_NAO_EXISTENTE);
					else {
						removerPosicao(Lista, qt_elementos, posicao);
						qt_elementos--;
					}
				}

			break;


			case REMOVER_OCORRENCIAS:

				if (qt_elementos == 0) printf(FRASE_LISTA_VAZIA);
				else {
					scanf("%d", &valor);
					qt_removidos = removerOcorrencias(Lista, qt_elementos, valor);
					if (qt_removidos == 0) printf(FRASE_ELEM_NAO_ENCONTRADO);
					else qt_elementos = qt_elementos - qt_removidos;

				}
			break;


			case BUSCAR:
				if (qt_elementos == 0) printf(FRASE_LISTA_VAZIA);
				else {
					scanf("%d", &valor);
					if (buscarValor(Lista, qt_elementos, valor) == 0) printf(FRASE_ELEM_NAO_ENCONTRADO);
				}

			break;

			case IMPRIMIR:
				if (qt_elementos == 0) printf(FRASE_LISTA_VAZIA);
				else {
					imprimirLista(Lista, qt_elementos);
				}

			break;

			case IMPRIMIR_POSICAO:
				if (qt_elementos == 0) printf(FRASE_LISTA_VAZIA);
				else {
					scanf("%d", &posicao);

					if (posicao > MAX) printf(FRASE_POSICAO_NAO_EXISTENTE);
					else if (posicao > qt_elementos) printf(FRASE_POSICAO_VAZIA);
					else imprimirPosicao(Lista, posicao);
				}

			break;			
		}

		scanf("%d", &opcao);
	}

	return 0;
}


/* ------------------------- */
/* IMPLEMENTACAO DAS FUNCOES */
/* ------------------------- */

void imprimirLista(int Lista[], int qt_elementos){
	int i;

	for (i = 0; i < qt_elementos; i++){
		printf("%d ", Lista[i]);
	}

	printf("\n");
}


void imprimirPosicao(int Lista[], int posicao){
	printf("%d\n", Lista[posicao-1]);
}


void inicializarLista(int Lista[], int qt_elementos)
{
	int i;
	for(i=0; i<qt_elementos; i++)
	{
		scanf("%d", &Lista[i]);
	}
}

void adicionarElemento(int Lista[], int qt_elementos, int valor)
{
	Lista[qt_elementos]=valor;
}

void adicionarPosicao(int Lista[], int qt_elementos, int valor, int posicao)
{
	int i;
	for(i=qt_elementos; i>posicao-1; i--)
	{
		Lista[i]=Lista[i-1];
	}
	Lista[posicao-1]=valor;
}

void removerPosicao(int Lista[], int qt_elementos, int posicao)
{
	int i;
	for(i=posicao-1; i<qt_elementos-1; i++)
	{
		Lista[i]=Lista[i+1];
	}
}

int removerOcorrencias(int Lista[], int qt_elementos, int valor)
{
	int i, n=0;
	for(i=0; i<qt_elementos; i++)
	{
		if(Lista[i]==valor)
		{
			n++;
			removerPosicao(Lista, qt_elementos, i+1);
			qt_elementos--;
			i=0;
		}
	}
	return(n);
}

int buscarValor(int Lista[], int qt_elementos, int valor)
{
	int i, n=0;
	for(i=0; i<qt_elementos; i++)
	{
		if(Lista[i]==valor)
		{
			printf("%d ", i+1);
			n++;
		}
	}
	if(n>0)
	{
		printf("\n");
	}
	return(n);
}
