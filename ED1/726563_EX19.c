/* ================================================================== *
	Universidade Federal de Sao Carlos - UFSCar, Sorocaba

	Disciplina: Estruturas de Dados 1
	Prof. Tiago A. Almeida

	Exercício 19 - Batalha de referências

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
#include <ctype.h>

// Frases pre-definidas
#define MSG_ERRO_ALOC 	  "Erro de alocacao!\n"
#define MSG_NAO_EXT  	  "Palavra inexistente na tabela!\n"
#define MSG_TAB_VAZIA	  "Tabela vazia!\n"
#define MSG_EMPATE	  	  "Empate!\n"
#define MSG_OPCAO_INV 	  "Opcao invalida!\n"



// === TAD E DEMAIS REGISTROS ===

typedef struct no{
	char palavra[11];
	int peso, bal;
	struct no *esq, *dir;
}No;

typedef struct heroi{
	char nome[21];
	unsigned long long int pontuacao;
}Heroi;

typedef No *Arvore;



/* ================================================================== */
/* ===================== PREAMBULO DAS FUNCOES ====================== */
/* ================================================================== */

int inserirPalavra(Arvore *t, char *palavra, int peso, int *cresceu);
void RR(Arvore *t);
void RRremocao(Arvore *t);
void LL(Arvore *t);
void LLremocao(Arvore *t);
void RL(Arvore *t);
void LR(Arvore *t);
void SubArvoreEsquerdaCresceu(Arvore *t, int *cresceu);
void SubArvoreEsquerdaDiminuiu(Arvore *t, int *diminuiu);
void SubArvoreDireitaCresceu(Arvore *t, int *cresceu);
void SubArvoreDireitaDiminuiu(Arvore *t, int *diminuiu);
int removerPalavra(Arvore *t, char *palavra, int *diminuiu);
void Sucessor(Arvore *t, Arvore *r, int *diminuiu);
void Batalha(Arvore t, Heroi *h, char *frase);
Arvore Buscar(Arvore t, char *palavra);
void Exibir(Arvore t);
void liberaArvore(Arvore t);




/* ================================================================== */
/* ======================== ROTINA PRINCIPAL ======================== */
/* ================================================================== */

int main(){

	Arvore t=NULL;
	Heroi a, b;
	char palavra[21], frase[1001], c;
	int op, i, x, peso;

	scanf("%d", &op);
	while(op!=5){
		if(op==1){
			scanf("%d", &i);
			while(i){
				getchar();
				scanf("%s %d", palavra, &peso);
				x = strlen(palavra)-1;
				while(x>=0){
					if(!isupper(palavra[x]))
						palavra[x] = toupper(palavra[x]);
					x--;
				}
				if(inserirPalavra(&t, palavra, peso, &x)==-1){
					printf(MSG_ERRO_ALOC);
					return(0);
				}
				i--;
			}
		}

		else if(op==2){
			getchar();
			scanf("%s", palavra);
			x = strlen(palavra)-1;
			while(x>=0){
				if(!isupper(palavra[x]))
					palavra[x] = toupper(palavra[x]);
				x--;
			}
			if(!removerPalavra(&t, palavra, &x))
				printf(MSG_NAO_EXT);
		}

		else if(op==3){
			getchar();
			i = 0;
			while((c=getchar())!='\n'){
				a.nome[i] = c;
				i++;
			}
			a.nome[i] = '\0';
			a.pontuacao = 0;
			i = 0;
			while((c=getchar())!='\n'){
				b.nome[i] = c;
				i++;
			}
			b.nome[i] = '\0';
			b.pontuacao = 0;
			i = 0;
			while((c=getchar())!='\n'){
				frase[i] = c;
				i++;
			}
			frase[i] = '\0';
			x = 0;
			while(frase[0]!='.'){
				if(x==0){
					Batalha(t, &a, frase);
					x = 1;
				}
				else{
					Batalha(t, &b, frase);
					x = 0;
				}
				i = 0;
				while((c=getchar())!='\n'){
					frase[i] = c;
					i++;
				}
				frase[i] = '\0';
			}
			if(a.pontuacao>b.pontuacao)
				printf("%s\n%lld\n", a.nome, a.pontuacao);
			else if(b.pontuacao>a.pontuacao)
				printf("%s\n%lld\n", b.nome, b.pontuacao);
			else{
				printf(MSG_EMPATE);
				printf("%lld\n", a.pontuacao);
			}
		}

		else if(op==4){
			if(t==NULL)
				printf(MSG_TAB_VAZIA);
			else
				Exibir(t);
		}

		else if(op!=5)
			printf(MSG_OPCAO_INV);
		scanf("%d", &op);
	}

	liberaArvore(t);
	return (0);
}



/* ================================================================== */
/* ========== FUNCOES QUE DETERMINAM AS OPERACOES POSSIVEIS ========= */
/* ================================================================== */


void RR(Arvore *t) {
	Arvore aux;

	aux = (*t)->dir;
	(*t)->dir = aux->esq;
	aux->esq = (*t);
	aux->bal = 0;
	(*t)->bal = 0;
	(*t) = aux;
}

void RRremocao(Arvore *t){
	Arvore aux;

	aux = (*t)->dir;
	(*t)->dir = aux->esq;
	aux->esq = (*t);
	if(aux->bal==0){
		(*t)->bal = -1;
		aux->bal = 1;
	}
	else{
		(*t)->bal = 0;
		aux->bal = 0;
	}
	(*t) = aux;	
}

void LL(Arvore *t) {
	Arvore aux;

	aux = (*t)->esq;
	(*t)->esq = aux->dir;
	aux->dir = (*t);
	aux->bal = 0;
	(*t)->bal = 0;
	(*t) = aux;
}

void LLremocao(Arvore *t){
	Arvore aux;

	aux = (*t)->esq;
	(*t)->esq = aux->dir;
	aux->dir = (*t);
	if(aux->bal==0){
		(*t)->bal = 1;
		aux->bal = -1;	
	}
	else{
		aux->bal = 0;
		(*t)->bal = 0;
	}
	(*t) = aux;	
}

void RL(Arvore *t) {
	Arvore aux, aux2;

	aux = (*t)->dir;
	aux2 = aux->esq;
	aux->esq = aux2->dir;
	aux2->dir = aux;
	(*t)->dir = aux2->esq;
	aux2->esq = (*t);
	if(aux2->bal==-1)
		(*t)->bal = 1;
	else
		(*t)->bal = 0;
	if(aux2->bal==1)
		aux->bal = -1;
	else
		aux->bal = 0;
	aux2->bal = 0;
	(*t) = aux2;
}

void LR(Arvore *t) {
	Arvore aux, aux2;

	aux = (*t)->esq;
	aux2 = aux->dir;
	aux->dir = aux2->esq;
	aux2->esq = aux;
	(*t)->esq = aux2->dir;
	aux2->dir = (*t);
	if(aux2->bal==1)
		(*t)->bal = -1;
	else
		(*t)->bal = 0;
	if(aux2->bal==-1)
		aux->bal = 1;
	else
		aux->bal = 0;
	aux2->bal = 0;
	(*t) = aux2;
}

void SubArvoreEsquerdaCresceu(Arvore *t, int *cresceu) {
	if((*cresceu)){
		if((*t)->bal==-1){
			(*t)->bal = 0;
			(*cresceu) = 0;
		}
		else if((*t)->bal==0){
			(*t)->bal = 1;
			(*cresceu) = 1;
		}
		else{
			if((*t)->esq->bal>0){
				LL(t);
				(*cresceu) = 0;
			}
			else if((*t)->esq->bal<0){
				LR(t);
				(*cresceu) = 0;
			}
		}
	}
}

void SubArvoreEsquerdaDiminuiu(Arvore *t, int *diminuiu){
	if((*diminuiu)){
		if((*t)->bal==1){
			(*t)->bal = 0;
			(*diminuiu) = 1;
		}
		else if((*t)->bal==0){
			(*t)->bal = -1;
			(*diminuiu) = 0;
		}
		else{
			if((*t)->dir->bal<0){
				RRremocao(t);
				(*diminuiu) = 1;
			}
			else if((*t)->dir->bal>0){
				RL(t);
				(*diminuiu) = 1;
			}
			else{
				RRremocao(t);
				(*diminuiu) = 0;
			}
		}
	}	
}

void SubArvoreDireitaCresceu(Arvore *t, int *cresceu) {
	if((*cresceu)){
		if((*t)->bal==1){
			(*t)->bal = 0;
			(*cresceu) = 0;
		}
		else if((*t)->bal==0){
			(*t)->bal = -1;
			(*cresceu) = 1;
		}
		else{
			if((*t)->dir->bal<0){
				RR(t);
				(*cresceu) = 0;
			}
			else if((*t)->dir->bal>0){
				RL(t);
				(*cresceu) = 0;
			}
		}
	}
}

void SubArvoreDireitaDiminuiu(Arvore *t, int *diminuiu){
	if((*diminuiu)){
		if((*t)->bal==-1){
			(*t)->bal = 0;
			(*diminuiu) = 1;
		}
		else if((*t)->bal==0){
			(*t)->bal = 1;
			(*diminuiu) = 0;
		}
		else{
			if((*t)->esq->bal>0){
				LLremocao(t);
				(*diminuiu) = 1;
			}
			else if((*t)->esq->bal<0){
				LR(t);
				(*diminuiu) = 1;
			}
			else{
				LLremocao(t);
				(*diminuiu) = 0;
			}
		}
	}	
}

int inserirPalavra(Arvore *t, char *palavra, int peso, int *cresceu){
	int ret;

	if(*t==NULL){
		*t = (Arvore) malloc(sizeof(No));
		if((*t)==NULL)
			return(-1);
		strcpy((*t)->palavra, palavra);
		(*t)->peso = peso;
		(*t)->bal = 0;
		(*t)->esq = NULL;
		(*t)->dir = NULL;
		*cresceu = 1;
		return(1);
	}
	if(strcmp(palavra, (*t)->palavra)<0){
		if((ret = inserirPalavra(&((*t)->esq), palavra, peso, cresceu))==1){
			SubArvoreEsquerdaCresceu(t, cresceu);
			return(1);
		}
		return(ret);
	}
	if(strcmp(palavra, (*t)->palavra)>0){
		if((ret = inserirPalavra(&((*t)->dir), palavra, peso, cresceu))==1){
			SubArvoreDireitaCresceu(t, cresceu);
			return(1);
		}
		return(ret);
	}
	(*t)->peso = peso;
	*cresceu = 0;
	return(0);
}

int removerPalavra(Arvore *t, char *palavra, int *diminuiu){
	Arvore aux;

	if(*t==NULL)
		return(0);
	if(strcmp(palavra, (*t)->palavra)<0){
		if(removerPalavra(&((*t)->esq), palavra, diminuiu)){
			SubArvoreEsquerdaDiminuiu(t, diminuiu);
			return(1);
		}
		return(0);
	}
	if(strcmp(palavra, (*t)->palavra)>0){
		if(removerPalavra(&((*t)->dir), palavra, diminuiu)){
			SubArvoreDireitaDiminuiu(t, diminuiu);
			return(1);
		}
		return(0);
	}
	aux = *t;
	if(aux->esq==NULL){
		(*t) = aux->dir;
		(*diminuiu) = 1;
	}
	else if(aux->dir==NULL){
		(*t) = aux->esq;
		(*diminuiu) = 1;
	}
	else{
		Sucessor(&aux, &(aux->dir), diminuiu);
		if((*diminuiu)){
			SubArvoreDireitaDiminuiu(t, diminuiu);
		}
	}
	free(aux);
	return(1);
}

void Sucessor(Arvore *t, Arvore *r, int *diminuiu){
	if((*r)->esq!=NULL){
		Sucessor(t, &((*r)->esq), diminuiu);
		if((*diminuiu))
			SubArvoreEsquerdaDiminuiu(r, diminuiu);
	}
	else{
		strcpy((*t)->palavra, (*r)->palavra);
		(*t)->peso = (*r)->peso;
		(*t) = (*r);
		(*r) = (*r)->dir;
		(*diminuiu) = 1;
	}
}

void Batalha(Arvore t, Heroi *h, char *frase){
	int mult=1, i=0, j=0;
	char palavra[11];
	Arvore aux;

	while(i<strlen(frase)){
		if(isalpha(frase[i]))
			frase[i] = toupper(frase[i]);
		i++;
	}
	i = 0;	
	while(i<strlen(frase)){
		while(i<strlen(frase) && frase[i]!=' '){
			palavra[j] = frase[i];
			j++;
			i++;
		}
		palavra[j] = '\0';
		aux = Buscar(t, palavra);
		if(aux!=NULL){
			h->pontuacao = h->pontuacao + ((unsigned long long int)mult*aux->peso);
			if(mult<1024)
				mult = mult*2;
		}
		else
			mult = 1;
		j = 0;
		i++;
	}
}

Arvore Buscar(Arvore t, char *palavra){
	if(t==NULL)
		return(NULL);
	if(strcmp(palavra, t->palavra)<0)
		return(Buscar(t->esq, palavra));
	if(strcmp(palavra, t->palavra)>0)
		return(Buscar(t->dir, palavra));
	return(t);
}

void Exibir(Arvore t){
	if(t!=NULL){
		printf("%s %d\n", t->palavra, t->peso);
		Exibir(t->esq);
		Exibir(t->dir);
	}
}

void liberaArvore(Arvore t){
	if(t!=NULL){
		liberaArvore(t->esq);
		liberaArvore(t->dir);
		free(t);
	}
}