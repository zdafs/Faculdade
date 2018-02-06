/* ================================================================== *
	Universidade Federal de Sao Carlos - UFSCar, Sorocaba

	Disciplina: Estruturas de Dados 1
	Prof. Tiago A. Almeida

	Exercício 13 - Cavalos Rebeldes

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
#include <string.h>

// Frases pre-definidas
#define MSG_ERRO_ALOC 		"Erro de alocacao!\n"
#define MSG_JA_EXISTE		"Já existe um tabuleiro com este título cadastrado!\n"
#define MSG_NAO_EXISTE		"Não existe nenhum tabuleiro com este título!\n"
#define MSG_OPCAO_INV 		"Opcao invalida!\n"



// === TAD E DEMAIS REGISTROS ===

typedef struct tabuleiro{
	char *nome, **tab;
	int lin, col;
	struct tabuleiro *prox;
}Tabuleiro;

typedef struct{
	Tabuleiro *inicio;
}Lista;

typedef struct celula{
	int lin, col;
	int count;
	struct celula *prox;
}Celula;

typedef struct{
	Celula *inicio, *fim;
}Fila;





/* ================================================================== */
/* ===================== PREAMBULO DAS FUNCOES ====================== */
/* ================================================================== */

void iniciaLista(Lista *lista);
char *getNome();
Tabuleiro *buscaTabuleiro(Lista *lista, char *nome);
int adicionaTabuleiro(Lista *lista, char *nome, int lin, int col);
void preencherTabuleiro(Lista *lista, char c, int lin, int col);
int filaVazia(Fila *fila);
void iniciarFila(Fila *fila);
void enfileirar(Fila *fila, int lin, int col, int count);
void desenfileirar(Fila *fila, Celula *t);
int calcularMovs(int lim_lin, int lim_col, int dst_lin, int dst_col, Celula t, char **tab, Fila *fila);
int resolveTab(Tabuleiro *p, int or_lin, int or_col, int dst_lin, int dst_col);
void resetaTab(Tabuleiro *p);
void liberaLista(Lista *lista);




/* ================================================================== */
/* ======================== ROTINA PRINCIPAL ======================== */
/* ================================================================== */

int main(){
	Lista *lista;
	char *nome;
	int i, j, n, m, op;
	Tabuleiro *p;

	lista = (Lista *) malloc(sizeof(Lista));
	if(lista==NULL){
		printf(MSG_ERRO_ALOC);
		return(0);
	}
	iniciaLista(lista);
	scanf("%d", &op);
	while(op!=3){
		getchar();
		if(op==1){
			nome = getNome();
			p = buscaTabuleiro(lista, nome);
			if(p==NULL){
				scanf("%d %d", &n, &m);
				if(!adicionaTabuleiro(lista, nome, n, m)){
					printf(MSG_ERRO_ALOC);
					return(0);
				}
				for(i=0; i<n; i++){
					getchar();
					for(j=0; j<m; j++)
						preencherTabuleiro(lista, getchar(), i, j);
				}
			}
			else{
				printf(MSG_JA_EXISTE);
				free(nome);
			}
		}
		else if(op==2){
			nome = getNome();
			p = buscaTabuleiro(lista, nome);
			free(nome);
			if(p!=NULL){
				scanf("%d %d", &i, &j);
				scanf("%d %d", &n, &m);
				printf("%d\n", resolveTab(p, i-1, j-1, n-1, m-1));
			}
			else
				printf(MSG_NAO_EXISTE);
		}
		else if(op!=3)
			printf(MSG_OPCAO_INV);
		scanf("%d", &op);
	}

	liberaLista(lista);
	

	return (0);
}



/* ================================================================== */
/* ========== FUNCOES QUE DETERMINAM AS OPERACOES POSSIVEIS ========= */
/* ================================================================== */

void iniciaLista(Lista *lista){
	lista->inicio = NULL;
}

char *getNome(){
	int i = 0;
	char *s, c;

	s = (char *) malloc(1);
	while((c = getchar())!='\n'){
		s[i] = c;
		i++;
		s = (char *) realloc(s, i+1);
	}
	s[i] = '\0';
	return(s);
}

Tabuleiro *buscaTabuleiro(Lista *lista, char *nome){
	Tabuleiro *p;

	for(p = lista->inicio; p!=NULL; p = p->prox){
		if(strcmp(p->nome, nome)==0)
			return(p);
	}
	return(NULL);
}

int adicionaTabuleiro(Lista *lista, char *nome, int lin, int col){
	int i;
	Tabuleiro *aux;

	aux = (Tabuleiro *) malloc(sizeof(Tabuleiro));
	if(aux==NULL)
		return(0);
	aux->nome = nome;
	aux->tab = (char **) malloc(lin*sizeof(char *));
	if(aux->tab==NULL)
		return(0);
	for(i=0; i<lin; i++){
		aux->tab[i] = (char *) malloc(col);
		if(aux->tab[i]==NULL)
			return(0);
	}
	aux->lin = lin;
	aux->col = col;
	aux->prox = lista->inicio;
	lista->inicio = aux;
	return(1);
}

void preencherTabuleiro(Lista *lista, char c, int lin, int col){
	lista->inicio->tab[lin][col] = c;
}

int filaVazia(Fila *fila){
	return(fila->inicio==NULL);
}

void iniciarFila(Fila *fila){
	fila->inicio = NULL;
	fila->fim = fila->inicio;
}

void enfileirar(Fila *fila, int lin, int col, int count){
	Celula *aux;
	aux = (Celula *) malloc(sizeof(Celula));
	aux->lin = lin;
	aux->col = col;
	aux->count = count;
	aux->prox = NULL;
	if(filaVazia(fila))
		fila->inicio = aux;
	else
		fila->fim->prox = aux;
	fila->fim = aux;
}

void desenfileirar(Fila *fila, Celula *t){
	Celula *aux;
	aux = fila->inicio;
	fila->inicio = aux->prox;
	t->lin = aux->lin;
	t->col = aux->col;
	t->count = aux->count;
	free(aux);
}

int calcularMovs(int lim_lin, int lim_col, int dst_lin, int dst_col, Celula t, char **tab, Fila *fila){
	if((t.lin+2==dst_lin && t.col+1==dst_col) || (t.lin+2==dst_lin && t.col-1==dst_col) || (t.lin-2==dst_lin && t.col+1==dst_col) ||
	   (t.lin-2==dst_lin && t.col-1==dst_col) || (t.lin+1==dst_lin && t.col+2==dst_col) || (t.lin-1==dst_lin && t.col+2==dst_col) ||
	   (t.lin+1==dst_lin && t.col-2==dst_col) || (t.lin-1==dst_lin && t.col-2==dst_col))
		return(t.count + 1);
	if(t.lin+2<lim_lin && t.lin+2>=0 && t.col+1<lim_col && t.col+1>=0 && tab[t.lin+2][t.col+1]=='.'){
		tab[t.lin+2][t.col+1] = 'C';
		enfileirar(fila, t.lin+2, t.col+1, t.count+1);
	}
	if(t.lin+2<lim_lin && t.lin+2>=0 && t.col-1<lim_col && t.col-1>=0 && tab[t.lin+2][t.col-1]=='.'){
		tab[t.lin+2][t.col-1] = 'C';
		enfileirar(fila, t.lin+2, t.col-1, t.count+1);
	}
	if(t.lin-2<lim_lin && t.lin-2>=0 && t.col+1<lim_col && t.col+1>=0 && tab[t.lin-2][t.col+1]=='.'){
		tab[t.lin-2][t.col+1] = 'C';
		enfileirar(fila, t.lin-2, t.col+1, t.count+1);
	}
	if(t.lin-2<lim_lin && t.lin-2>=0 && t.col-1<lim_col && t.col-1>=0 && tab[t.lin-2][t.col-1]=='.'){
		tab[t.lin-2][t.col-1] = 'C';
		enfileirar(fila, t.lin-2, t.col-1, t.count+1);
	}
	if(t.lin+1<lim_lin && t.lin+1>=0 && t.col+2<lim_col && t.col+2>=0 && tab[t.lin+1][t.col+2]=='.'){
		tab[t.lin+1][t.col+2] = 'C';
		enfileirar(fila, t.lin+1, t.col+2, t.count+1);
	}
	if(t.lin-1<lim_lin && t.lin-1>=0 && t.col+2<lim_col && t.col+2>=0 && tab[t.lin-1][t.col+2]=='.'){
		tab[t.lin-1][t.col+2] = 'C';
		enfileirar(fila, t.lin-1, t.col+2, t.count+1);
	}
	if(t.lin+1<lim_lin && t.lin+1>=0 && t.col-2<lim_col && t.col-2>=0 && tab[t.lin+1][t.col-2]=='.'){
		tab[t.lin+1][t.col-2] = 'C';
		enfileirar(fila, t.lin+1, t.col-2, t.count+1);
	}
	if(t.lin-1<lim_lin && t.lin-1>=0 && t.col-2<lim_col && t.col-2>=0 && tab[t.lin-1][t.col-2]=='.'){
		tab[t.lin-1][t.col-2] = 'C';
		enfileirar(fila, t.lin-1, t.col-2, t.count+1);
	}

	return(0);
}

int resolveTab(Tabuleiro *p, int or_lin, int or_col, int dst_lin, int dst_col){
	Fila *fila;
	int q=0;
	Celula t;

	if(p->tab[or_lin][or_col]=='#' || p->tab[dst_lin][dst_col]=='#')
		return(-1);
	if(or_lin==dst_lin && or_col==dst_col)
		return(0);
	fila = (Fila *) malloc(sizeof(Fila));
	iniciarFila(fila);
	enfileirar(fila, or_lin, or_col, 0);
	while(!filaVazia(fila) && q==0){
		desenfileirar(fila, &t);
		q = calcularMovs(p->lin, p->col, dst_lin, dst_col, t, p->tab, fila);
	}
	if(q!=0){
		while(!filaVazia(fila))
			desenfileirar(fila, &t);
		free(fila);
		resetaTab(p);
		return(q);
	}
	free(fila);
	resetaTab(p);
	return(-1);
}

void resetaTab(Tabuleiro *p){
	int i, j;
	for(i=0; i<p->lin; i++){
		for(j=0; j<p->col; j++){
			if(p->tab[i][j]!='#')
				p->tab[i][j] = '.';
		}
	}
}

void liberaLista(Lista *lista){
	int i;
	Tabuleiro *aux;

	for(aux=lista->inicio; aux!=NULL; aux=lista->inicio){
		lista->inicio = aux->prox;
		for(i=0; i<aux->lin; i++)
			free(aux->tab[i]);
		free(aux->nome);
		free(aux->tab);
		free(aux);
	}
	free(lista);
}