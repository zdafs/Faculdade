/* ================================================================== *
	Universidade Federal de Sao Carlos - UFSCar, Sorocaba

	Disciplina: Estruturas de Dados 1
	Prof. Tiago A. Almeida

	Exercício 06 - Batata Quente

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


// === TAD E DEMAIS REGISTROS ===

typedef struct Celula{
	char *nome;
	struct Celula *prox;
}Celula;

typedef struct{
	Celula *inicio, *fim;
	int tam;
}Lista;



/* ================================================================== */
/* ===================== PREAMBULO DAS FUNCOES ====================== */
/* ================================================================== */

void iniciaLista(Lista *lista);
void inserir(Lista *lista, char *nome);
void remover(Lista *lista, Celula *aux);
void jogo(Lista *lista, int k);






/* ================================================================== */
/* ======================== ROTINA PRINCIPAL ======================== */
/* ================================================================== */

int main(){

	Lista *lista;
	int n, k, i;
	char *nome, c;

	lista = (Lista *) malloc(sizeof(Lista));
	iniciaLista(lista);
	scanf("%d %d", &n, &k);
	getchar();
	while(n>0){
		i=0;
		nome = (char *) malloc(1);
		while((c = getchar())!='\n' /*&& nome[i]!=' '*/){
			if(c!=' '){
				nome[i] = c;
				i++;
				nome = (char *) realloc(nome, (i+1));
			}
		}
		nome[i]='\0';
		inserir(lista, nome);
		n--;
	}

	jogo(lista, k);

	free(lista);

	return (0);
}



/* ================================================================== */
/* ========== FUNCOES QUE DETERMINAM AS OPERACOES POSSIVEIS ========= */
/* ================================================================== */

void iniciaLista(Lista *lista){
	lista->inicio = NULL;
	lista->fim = lista->inicio;
	lista->tam = 0;
}

void inserir(Lista *lista, char *nome){
	Celula *aux;
	aux = (Celula *) malloc(sizeof(Celula));
	aux->nome = nome;
	aux->prox = NULL;
	if(lista->inicio==NULL)
		lista->inicio = aux;
	else
		lista->fim->prox = aux;
	lista->fim = aux;
	lista->tam++;
}

void remover(Lista *lista, Celula *aux){
	puts(aux->prox->nome);
	free(aux->prox->nome);
	lista->inicio = aux->prox->prox;
	free(aux->prox);
	aux->prox = lista->inicio;
	lista->tam--;
}

void jogo(Lista *lista, int k){
	int i;
	Celula *aux;
	lista->fim->prox = lista->inicio;
	for(i=1, aux=lista->inicio; lista->tam!=1; i++){
		if(i%k==0){
			remover(lista, aux);
			aux = lista->inicio;
		}
		else
			aux = aux->prox;
	}
	puts(lista->inicio->nome);
	free(lista->inicio->nome);
	free(lista->inicio);
}