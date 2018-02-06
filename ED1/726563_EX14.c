/* ================================================================== *
	Universidade Federal de Sao Carlos - UFSCar, Sorocaba

	Disciplina: Estruturas de Dados 1
	Prof. Tiago A. Almeida

	Exercício 14 - Recuperacao da Arvore Binaria

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

typedef struct no{
	int item;
	struct no *esq, *dir;
}No;

No *constroiRecursivo(int *pre, int *em, int *pos, int esq, int dir);
int buscar(int *em, int esq, int dir, int item);
No *criaNo(int item, No *esq, No *dir);
void imprimePosOrdem(No *arv);

int main(){
	No *arv;
	int *em, *pre, t, i;

	scanf("%d", &t);
	em = (int *) malloc(t*sizeof(int));
	pre = (int *) malloc(t*sizeof(int));
	for(i=0; i<t; i++)
		scanf("%d", &pre[i]);
	for(i=0; i<t; i++)
		scanf("%d", &em[i]);
	i = 0;
	arv = constroiRecursivo(pre, em, &i, 0, t-1);
	imprimePosOrdem(arv);
	return(0);

}

No *constroiRecursivo(int *pre, int *em, int *pos, int esq, int dir){
	No *pEsq, *pDir;
	int item, raiz;

	if(esq<=dir){
		item = pre[(*pos)];
		(*pos)++;
		raiz = buscar(em, esq, dir, item);
		pEsq = constroiRecursivo(pre, em, pos, esq, raiz-1);
		pDir = constroiRecursivo(pre, em, pos, raiz+1, dir);
		return(criaNo(item, pEsq, pDir));
	}
	return(NULL);
}

int buscar(int *em, int esq, int dir, int item){
	int i;

	for(i=esq; i<=dir; i++){
		if(em[i]==item)
			return(i);
	}
}

No *criaNo(int item, No *esq, No *dir){
	No *p;

	p = (No *) malloc(sizeof(No));
	p->item = item;
	p->esq = esq;
	p->dir = dir;
	return(p);
}

void imprimePosOrdem(No *arv){
	if(arv!=NULL){
		imprimePosOrdem(arv->esq);
		imprimePosOrdem(arv->dir);
		printf("%d\n", arv->item);
		free(arv);
	}
}