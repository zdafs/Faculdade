/* ================================================================== *
	Universidade Federal de Sao Carlos - UFSCar, Sorocaba

	Disciplina: Estruturas de Dados 1
	Prof. Tiago A. Almeida

	Exercício 9 - Editor de texto

	Instrucoes
	----------

	Este arquivo contem o codigo que auxiliara no desenvolvimento do
	exercicio. Voce precisara completar as funcoes requisitadas.

	Voce nao podera criar nenhuma outra funcao. Complete apenas as
	rotinas	fornecidas.
 * ================================================================== */

#include <stdio.h>
#include <stdlib.h>

#define FALSE	0
#define TRUE	1

// Operacoes que podem ser realizadas.
#define INSERIR			'I'
#define MOVER_POSICAO	'M'
#define BACKSPACE		'B'
#define DELETE			'D'
#define IMPRIMIR		'P'
#define FIM				'F'

// Frase exibida quando houver erro nas operacoes
#define FRASE_ERROALOCACAO	"Erro de alocacao!\n"

// === TAD E DEMAIS REGISTROS ===

typedef struct caractere{
	char c;
	struct caractere *ant, *prox;
}Caractere;


typedef struct{
	Caractere *inicio, *fim;
	int tam, cursor;
}Texto;


/* ================================================================== */
/* ===================== PREAMBULO DAS FUNCOES ====================== */
/* ================================================================== */

int iniciaTexto(Texto *texto);
int insere(Texto *texto, char c);
void mover(Texto *texto, int i);
void backspace(Texto *texto);
void delete(Texto *texto);
void imprimir(Texto *texto);
void finaliza(Texto *texto);



/* ================================================================== */
/* ======================== ROTINA PRINCIPAL ======================== */
/* ================================================================== */

int main() {
	Texto *texto;
	int i;
	char c, op;

	texto = (Texto *) malloc(sizeof(Texto));
	if(texto==NULL){
		printf(FRASE_ERROALOCACAO);
		return(0);
	}
	if(iniciaTexto(texto)==FALSE){
		printf(FRASE_ERROALOCACAO);
		return(0);	
	}

	op = getchar();
	while(op!=FIM){
		getchar();
		if(op==INSERIR){
			c = getchar();
			getchar();
			if(insere(texto, c)==FALSE){
				printf(FRASE_ERROALOCACAO);
				return(0);	
			}
		}

		else if(op==MOVER_POSICAO){
			scanf("%d", &i);
			getchar();
			mover(texto, i);
		}

		else if(op==BACKSPACE){
			backspace(texto);
		}

		else if(op==DELETE){
			delete(texto);
		}

		else if(op==IMPRIMIR){
			imprimir(texto);
		}

		op = getchar();
	}

	finaliza(texto);
	
	
	return (0);
}

/* ================================================================== */
/* ========== FUNCOES QUE DETERMINAM AS OPERACOES POSSIVEIS ========= */
/* ================================================================== */


int iniciaTexto(Texto *texto){
	texto->inicio = (Caractere *) malloc(sizeof(Caractere));
	if(texto->inicio==NULL)
		return(0);
	texto->inicio->ant = NULL;
	texto->inicio->prox = NULL;
	texto->fim = texto->inicio;
	texto->tam = 0;
	texto->cursor = 0;
	return(1);
}

int insere(Texto *texto, char c){
	Caractere *aux, *p = texto->inicio;
	int i=1;
	aux = (Caractere *) malloc(sizeof(Caractere));
	if(aux==NULL)
		return(0);
	aux->c = c;
	texto->tam++;
	texto->cursor++;
	while(i<texto->cursor){
		p = p->prox;
		i++;
	}
	aux->prox = p->prox;
	aux->ant = p;
	if(p==texto->fim)
		texto->fim = aux;
	else
		p->prox->ant = aux;
	p->prox = aux;
	return(1);
}

void mover(Texto *texto, int i){
	texto->cursor = texto->cursor + i;
	if(texto->cursor>texto->tam)
		texto->cursor = texto->tam;
	else if(texto->cursor < 0)
		texto->cursor = 0;
}

void backspace(Texto *texto){
	Caractere *aux = texto->inicio->prox;
	int i=1;
	if(texto->cursor!=0){
		while(i<texto->cursor){
			aux = aux->prox;
			i++;
		}
		aux->ant->prox = aux->prox;
		if(aux==texto->fim)
			texto->fim = aux->ant;
		else
			aux->prox->ant = aux->ant;
		texto->cursor--;
		texto->tam--;
		free(aux);
	}
}

void delete(Texto *texto){
	Caractere *aux = texto->inicio->prox;
	int i=0;
	if(texto->cursor<texto->tam){
		while(i<texto->cursor){
			aux = aux->prox;
			i++;
		}
		aux->ant->prox = aux->prox;
		if(aux==texto->fim)
			texto->fim = aux->ant;
		else
			aux->prox->ant = aux->ant;
		texto->tam--;
		free(aux);
	}
}

void imprimir(Texto *texto){
	Caractere *aux;
	if(texto->tam!=0){
		for(aux = texto->inicio->prox; aux!=NULL; aux=aux->prox)
			printf("%c", aux->c);
		printf("\n");
	}
}

void finaliza(Texto *texto){
	Caractere *aux;
	imprimir(texto);
	for(aux=texto->inicio; aux!=NULL; aux=texto->inicio){
		texto->inicio = texto->inicio->prox;
		free(aux);
	}
	free(texto);
}