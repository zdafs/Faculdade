#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct aluno{
	int ra, ingresso, creditos;
	char nome[101];
	struct aluno *esq, *dir;
}Aluno;

Aluno *inicializar();
int insere(Aluno *aux, Aluno **v);
Aluno **busca(int ra, Aluno **v);
void alterar(char *nome, int ingresso, int creditos, Aluno *v);
void remover(Aluno **v);
void promove(Aluno *v, Aluno **r, Aluno *aux);
void imprime(Aluno v);
void lista(Aluno *v);

int main(){


	return(0);
}

Aluno *inicializar(){
	FILE *f;
	Aluno *v=NULL, *aux=NULL;

	f = fopen("Alunos.dat", "r");
	if(f!=NULL){
		v = (Aluno *)malloc(sizeof(Aluno));
		fscanf(f,"%d@%s@%d@%d\n", &(v->ra),v->nome,&(v->ingresso),&(v->creditos));
		v->esq = NULL;
		v->dir = NULL;
		aux = (Aluno *)malloc(sizeof(Aluno));
		while(fscanf(f,"%d@%s@%d@%d\n", &(aux->ra),aux->nome,&(aux->ingresso),&(aux->creditos))!=EOF){
			insere(aux, &v);
			aux = (Aluno *)malloc(sizeof(Aluno));
		}
		free(aux);
		fclose(f);
	}
	return(v);
}

int insere(Aluno *aux, Aluno **v){
	if((*v)==NULL){
		*v = aux;
		aux->esq = NULL;
		aux->dir = NULL;
		return(1);
	}
	else if((*v)->ra>aux->ra)
		return(insere(aux, &((*v)->esq)));
	else if((*v)->ra<aux->ra)
		return(insere(aux, &((*v)->dir)));
	return(0);
}

Aluno **busca(int ra, Aluno **v){
	if((*v)==NULL)
		return(NULL);
	if(ra<(*v)->ra)
		return(busca(ra, &((*v)->esq)));
	if(ra>(*v)->ra)
		return(busca(ra, &((*v)->dir)));
	return(v);
}

void alterar(char *nome, int ingresso, int creditos, Aluno *v){
	strcpy(v->nome, nome);
	v->ingresso = ingresso;
	v->creditos = creditos;
}

void remover(Aluno **v){
	Aluno *aux;

	if((*v)->esq==NULL){
		aux = *v;
		*v = (*v)->dir;
		free(aux);
	}
	else if((*v)->dir==NULL){
		aux = *v;
		*v = (*v)->esq;
		free(aux);
	}
	else{
		promove(*v, &((*v)->dir), aux);
	}
}

void promove(Aluno *v, Aluno **r, Aluno *aux){
	if((*r)->esq==NULL){
		v->ra = (*r)->ra;
		strcpy(v->nome, (*r)->nome);
		v->ingresso = (*r)->ingresso;
		v->creditos = (*r)->creditos;
		aux = *r;
		*r = (*r)->dir;
		free(aux);
	}
	else
		promove(v, &((*r)->esq), aux);
}

void imprime(Aluno v){
	printf("%s\n%d\n%d\n%d\n", v.nome, v.ra, v.ingresso, v.creditos);
}

void lista(Aluno *v){
	if(v!=NULL){
		lista(v->esq);
		imprime(*v);
		lista(v->dir);
	}
}