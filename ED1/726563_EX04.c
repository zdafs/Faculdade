/* ================================================================== *
	Universidade Federal de Sao Carlos - UFSCar, Sorocaba

	Disciplina: Estruturas de Dados 1
	Prof. Tiago A. Almeida

	Exercício 04 - Ultima Carta

	Instrucoes
	----------

	Este arquivo contem o codigo que auxiliara no desenvolvimento do
	exercicio. Voce precisara completar as funcoes requisitadas.

	Voce nao podera criar nenhuma outra funcao. Complete apenas as
	rotinas	fornecidas.
 * ==================================================================
    Dados do aluno:

   RA: 726563
   Nome: Lucca La Fonte Albuquerque Carvalho

* ================================================================== */

#include <stdio.h>
#include <stdlib.h>

// Frase exibida quando houver erro nas operacoes
#define FRASE_ERRO_ALOC "Erro de alocacao!\n"


// === TAD E DEMAIS REGISTROS ===

typedef struct carta{
	int num;
	struct carta *prox;
}Carta;

typedef struct{
	Carta *frente, *tras;
}Fila;



/* ================================================================== */
/* ===================== PREAMBULO DAS FUNCOES ====================== */
/* ================================================================== */

void iniciaFila(Fila *fila);
void enfileira(Fila *fila, int n);
void desenfileira(Fila *fila, int *n);
void colocaFinal(Fila *fila);
int filaVazia(Fila *fila);






/* ================================================================== */
/* ======================== ROTINA PRINCIPAL ======================== */
/* ================================================================== */

int main(){

	Fila *fila;
	int n, i=0;

	fila = (Fila *) malloc(sizeof(Fila));
	if(fila==NULL){
		printf(FRASE_ERRO_ALOC);
		return(0);
	}
	iniciaFila(fila);
	scanf("%d", &n);
	while(n!=0){
		enfileira(fila, n);
		scanf("%d", &n);
	}


	while(i==0){
		desenfileira(fila, &n);
		if((i=filaVazia(fila))==0){
			printf("%d ", n);
			colocaFinal(fila);
		}
		else
			printf("\n%d\n", n);
	}

	return (0);
}



/* ================================================================== */
/* ========== FUNCOES QUE DETERMINAM AS OPERACOES POSSIVEIS ========= */
/* ================================================================== */

void iniciaFila(Fila *fila){
	fila->frente = NULL;
	fila->tras = fila->frente;
}

void enfileira(Fila *fila, int n){
	Carta *aux;
	aux = (Carta *) malloc(sizeof(Carta));
	aux->num = n;
	aux->prox = NULL;
	if(fila->frente==NULL)
		fila->frente = aux;
	else
		fila->tras->prox = aux;
	fila->tras = aux;
}

void desenfileira(Fila *fila, int *n){
	Carta *aux;
	aux = fila->frente;
	fila->frente = aux->prox;
	*n = aux->num;
	free(aux);
}

void colocaFinal(Fila *fila){
	fila->tras->prox = fila->frente;
	fila->frente = fila->frente->prox;
	fila->tras = fila->tras->prox;
	fila->tras->prox = NULL;
}

int filaVazia(Fila *fila){
	return(fila->frente==NULL);
}