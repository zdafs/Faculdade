/* ================================================================== *
	Universidade Federal de Sao Carlos - UFSCar, Sorocaba

	Disciplina: Estruturas de Dados 1
	Prof. Tiago A. Almeida

	Exercício 17 - Treinador de corvos

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

// Frases e constantes pre-definidas
#define MSG_ERRO_ALOC 	  "Erro de alocacao!\n"
#define MSG_JA_EXT_CASA	  "Casa ja memorizada!\n"
#define MSG_JA_EXT_TRT	  "Territorio ja memorizado!\n"
#define MSG_NAO_EXT_CASA  "A casa referenciada nao esta memorizada!\n"
#define MSG_NAO_EXT_TRT   "O territorio referenciado nao esta memorizado!\n"
#define MSG_CASA_REMOVIDA "A casa referenciada foi removida pois se tornou nao unica!\n"
#define MSG_POS_OCUPADA   "A posicao referenciada ja esta ocupada!\n"
#define MSG_NAO_RMV_UNICO "Nao e possivel remover todos os territorios de uma casa!\n"
#define MSG_ARV_VAZIA	  "Arvore de Casas vazia!\n"
#define MSG_OPCAO_INV 	  "Opcao invalida!\n"



// === TAD E DEMAIS REGISTROS ===

typedef struct arvTerritorios{
	int valorTerritorio;
	struct arvTerritorios *esq, *dir;
}arvTerritorios;

typedef struct arvCasas{
	char nomeCasa[21], ABB;
	int valorCasa;
	arvTerritorios *territorios;
	struct arvCasas *esq, *dir;
}arvCasas;





/* ================================================================== */
/* ===================== PREAMBULO DAS FUNCOES ====================== */
/* ================================================================== */

arvCasas *criaNovaCasa(char *nomeCasa, int valor);
void insereNovaCasa(arvCasas **casa, arvCasas *p);
int memorizarCasa(char c, arvTerritorios *pai, int valor, arvCasas *p);
arvTerritorios *buscarTerritorio(arvTerritorios *pai, int valor, arvCasas *casa);
arvCasas *buscarCasa(arvCasas *casa, int valor);
arvCasas *removerCasa(arvCasas **casa, int valor);
arvCasas **menorElemArvCasas(arvCasas **casa);
//arvCasas **maiorElemArvCasas(arvCasas **casa);
//int confereABBArvCasas(arvCasas *casa);
arvTerritorios **menorElemArvTerritorios(arvTerritorios **pai);
arvTerritorios **maiorElemArvTerritorios(arvTerritorios **pai);
int confereABBArvTerritorios(arvTerritorios *pai);
int ajustaArvCasas(arvCasas **casa, arvCasas *p);
void liberaTerritorios(arvTerritorios *pai);
int removerTerritorio(arvTerritorios **pai, arvCasas *casa, int valor);
void exibirArvCasas(arvCasas *casa);
void exibirArvTerritorios(arvTerritorios *pai);
void liberaCasas(arvCasas *casa);
void getNome(char *nome);




/* ================================================================== */
/* ======================== ROTINA PRINCIPAL ======================== */
/* ================================================================== */

int main(){

	int op, valor, x;
	char nome[21], c;
	arvCasas *casa, *aux;
	arvTerritorios *pai;

	casa = NULL;
	scanf("%d", &op);
	while(op!=7){
		if(op==1){
			getchar();
			getNome(nome);
			scanf("%d", &valor);
			aux = criaNovaCasa(nome, valor);
			if(aux==NULL){
				printf(MSG_ERRO_ALOC);
				return(0);
			}
			scanf("%d", &valor);
			while(valor!=-1){
				pai = buscarTerritorio(aux->territorios, valor, aux);
				scanf(" %c", &c);
				scanf("%d", &valor);
				if(pai!=NULL){
					//getchar();
					x = memorizarCasa(c, pai, valor, aux);
					if(x==-2){
						printf(MSG_ERRO_ALOC);
						return(0);
					}
					else if(x==-1)
						printf(MSG_JA_EXT_TRT);
					else if(x==0)
						printf(MSG_POS_OCUPADA);
				}
				else
					printf(MSG_NAO_EXT_TRT);
				scanf("%d", &valor);
			}
			if(ajustaArvCasas(&casa, aux)==0)
				printf(MSG_JA_EXT_CASA);
		}

		else if(op==2){
			scanf("%d", &valor);
			aux = removerCasa(&casa, valor);
			scanf("%d", &valor);
			scanf(" %c", &c);
			if(aux!=NULL){
				pai = buscarTerritorio(aux->territorios, valor, aux);
				scanf("%d", &valor);
				if(pai!=NULL){
					//getchar();
					x = memorizarCasa(c, pai, valor, aux);
					if(x==-2){
						printf(MSG_ERRO_ALOC);
						return(0);
					}
					else if(x==-1)
						printf(MSG_JA_EXT_TRT);
					else if(x==0)
						printf(MSG_POS_OCUPADA);
				}
				else
					printf(MSG_NAO_EXT_TRT);
				if(ajustaArvCasas(&casa, aux)==0)
					printf(MSG_CASA_REMOVIDA);
			}
			else{
				scanf("%d", &valor);
				printf(MSG_NAO_EXT_CASA);
			}
		}

		else if(op==3){
			scanf("%d", &valor);
			aux = removerCasa(&casa, valor);
			if(aux!=NULL){
				liberaTerritorios(aux->territorios);
				free(aux);
			}
			else
				printf(MSG_NAO_EXT_CASA);
		}

		else if(op==4){
			scanf("%d", &valor);
			aux = removerCasa(&casa, valor);
			scanf("%d", &valor);
			if(aux!=NULL){
				x = removerTerritorio(&(aux->territorios), aux, valor);
				if(x==0)
					printf(MSG_NAO_EXT_TRT);
				else if(x==-1)
					printf(MSG_NAO_RMV_UNICO);
				if(ajustaArvCasas(&casa, aux)==0)
					printf(MSG_CASA_REMOVIDA);
			}
			else
				printf(MSG_NAO_EXT_CASA);
		}

		else if(op==5){
			if(casa==NULL)
				printf(MSG_ARV_VAZIA);
			else
				exibirArvCasas(casa);
		}

		else if(op==6){
			scanf("%d", &valor);
			aux = buscarCasa(casa, valor);
			if(aux!=NULL)
				exibirArvTerritorios(aux->territorios);
			else
				printf(MSG_NAO_EXT_CASA);
		}

		else if(op!=7)
			printf(MSG_OPCAO_INV);
		scanf("%d", &op);
	}

	liberaCasas(casa);

	return (0);
}



/* ================================================================== */
/* ========== FUNCOES QUE DETERMINAM AS OPERACOES POSSIVEIS ========= */
/* ================================================================== */

arvCasas *criaNovaCasa(char *nomeCasa, int valor){
	arvCasas *p;
	p = (arvCasas *)malloc(sizeof(arvCasas));
	if(p==NULL)
		return(NULL);
	strcpy(p->nomeCasa, nomeCasa);
	p->valorCasa = -valor;
	p->esq = NULL;
	p->dir = NULL;
	p->ABB = 0;
	p->territorios = (arvTerritorios *)malloc(sizeof(arvTerritorios));
	if(p->territorios==NULL){
		free(p);
		return(NULL);
	}
	p->territorios->valorTerritorio = valor;
	p->territorios->esq = NULL;
	p->territorios->dir = NULL;
	return(p);
}

void insereNovaCasa(arvCasas **casa, arvCasas *p){
	if(*casa==NULL)
		(*casa) = p;
	else if((*casa)->valorCasa>p->valorCasa)
		insereNovaCasa(&((*casa)->esq), p);
	else if((*casa)->valorCasa<p->valorCasa)
		insereNovaCasa(&((*casa)->dir), p);
}
	
int memorizarCasa(char c, arvTerritorios *pai, int valor, arvCasas *p){
	if(c=='E'){
		if(pai->esq==NULL){
			if(buscarTerritorio(p->territorios, valor, p)!=NULL)
				return(-1);
			pai->esq = (arvTerritorios *)malloc(sizeof(arvTerritorios));
			if(pai->esq==NULL)
				return(-2);
			pai->esq->valorTerritorio = valor;
			pai->esq->esq = NULL;
			pai->esq->dir = NULL;
			if(p->ABB==0)
				p->valorCasa = p->valorCasa - valor;
			else
				p->valorCasa = p->valorCasa + valor;
			return(1);
		}
	}
	else{
		if(pai->dir==NULL){
			if(buscarTerritorio(p->territorios, valor, p)!=NULL)
				return(-1);
			pai->dir = (arvTerritorios *)malloc(sizeof(arvTerritorios));
			if(pai->dir==NULL)
				return(-2);
			pai->dir->valorTerritorio = valor;
			pai->dir->esq = NULL;
			pai->dir->dir = NULL;
			if(p->ABB==0)
				p->valorCasa = p->valorCasa - valor;
			else
				p->valorCasa = p->valorCasa + valor;
			return(1);
		}
	}
	return(0);
}

arvTerritorios *buscarTerritorio(arvTerritorios *pai, int valor, arvCasas *casa){
	arvTerritorios *p;
	
	if(casa->ABB==1){
		if(pai==NULL)
			return(NULL);
		if(pai->valorTerritorio>valor)
			return(buscarTerritorio(pai->esq, valor, casa));
		if(pai->valorTerritorio<valor)
			return(buscarTerritorio(pai->dir, valor, casa));
		return(pai);
	}

	if(pai==NULL)
		return(NULL);
	if(pai->valorTerritorio==valor)	
		return(pai);
	if((p = buscarTerritorio(pai->esq, valor, casa))==NULL)
		return(buscarTerritorio(pai->dir, valor, casa));
	return(p);
}

arvCasas *buscarCasa(arvCasas *casa, int valor){
	if(casa==NULL)
		return(NULL);
	if(casa->valorCasa>valor)
		return(buscarCasa(casa->esq, valor));
	if(casa->valorCasa<valor)
		return(buscarCasa(casa->dir, valor));
	return(casa);
}

arvCasas *removerCasa(arvCasas **casa, int valor){
	arvCasas *p;
	arvCasas **aux;
	int x;
	char nome[21], ABB;
	arvTerritorios *territorios;

	if((*casa)==NULL)
		return(NULL);
	if((*casa)->valorCasa>valor)
		return(removerCasa(&((*casa)->esq), valor));
	if((*casa)->valorCasa<valor)
		return(removerCasa(&((*casa)->dir), valor));
	if((*casa)->esq==NULL){
		p = *casa;
		(*casa) = (*casa)->dir;
	}
	else if((*casa)->dir==NULL){
		p = *casa;
		(*casa) = (*casa)->esq;
	}
	else{
		aux = menorElemArvCasas(&((*casa)->dir));
		x = (*casa)->valorCasa;
		strcpy(nome, (*casa)->nomeCasa);
		territorios = (*casa)->territorios;
		ABB = (*casa)->ABB;
		(*casa)->valorCasa = (*aux)->valorCasa;
		strcpy((*casa)->nomeCasa, (*aux)->nomeCasa);
		(*casa)->territorios = (*aux)->territorios;
		(*casa)->ABB = (*aux)->ABB;
		(*aux)->valorCasa = x;
		strcpy((*aux)->nomeCasa, nome);
		(*aux)->territorios = territorios;
		(*aux)->ABB = ABB;
		p = *aux;
		(*aux) = (*aux)->dir;
	}
	p->esq = NULL;
	p->dir = NULL;
	return(p);
}

arvCasas **menorElemArvCasas(arvCasas **casa){
	if((*casa)->esq==NULL)
		return(casa);
	return(menorElemArvCasas(&((*casa)->esq)));
}

/*arvCasas **maiorElemArvCasas(arvCasas **casa){
	if((*casa)->dir==NULL)
		return(casa);
	return(menorElemArvCasas(&((*casa)->dir)));	
}

int confereABBArvCasas(arvCasas *casa){
	arvCasas **p, **q;
	int esq, dir;

	if(pai==NULL)
		return(1);
	esq = confereABBArvCasas(pai->esq);
	if(esq)
		dir = confereABBArvCasas(pai->dir);
	else
		return(0);
	if(esq && dir){
		if(casa->dir==NULL && casa->esq==NULL)
			return(1);
		if(casa->dir==NULL){
			p = maiorElemArvCasas(&(casa->esq));
			if(casa->valorCasa>(*p)->valorCasa)
				return(1);
		}
		else if(casa->esq==NULL){
			p = menorElemArvCasas(&(casa->dir));
			if(casa->valorCasa<(*p)->valorCasa)
				return(1);	
		}
		else{
			p = menorElemArvCasas(&(casa->dir));
			q = maiorElemArvCasas(&(casa->esq));
			if(casa->valorCasa<(*p)->valorCasa && casa->valorCasa>(*q)->valorCasa)
				return(1);
		}
	}
	return(0);
}*/

arvTerritorios **menorElemArvTerritorios(arvTerritorios **pai){
	if((*pai)->esq==NULL)
		return(pai);
	return(menorElemArvTerritorios(&((*pai)->esq)));
}

arvTerritorios **maiorElemArvTerritorios(arvTerritorios **pai){
	if((*pai)->dir==NULL)
		return(pai);
	return(maiorElemArvTerritorios(&((*pai)->dir)));
}

int confereABBArvTerritorios(arvTerritorios *pai){
	int esq, dir;
	arvTerritorios **p, **q;

	if(pai==NULL)
		return(1);
	esq = confereABBArvTerritorios(pai->esq);
	if(esq)
		dir = confereABBArvTerritorios(pai->dir);
	else
		return(0);
	if(esq && dir){
		if(pai->dir==NULL && pai->esq==NULL)
			return(1);
		if(pai->dir==NULL){
			p = maiorElemArvTerritorios(&(pai->esq));
			if(pai->valorTerritorio>(*p)->valorTerritorio)
				return(1);
		}
		else if(pai->esq==NULL){
			p = menorElemArvTerritorios(&(pai->dir));
			if(pai->valorTerritorio<(*p)->valorTerritorio)
				return(1);	
		}
		else{
			p = menorElemArvTerritorios(&(pai->dir));
			q = maiorElemArvTerritorios(&(pai->esq));
			if(pai->valorTerritorio<(*p)->valorTerritorio && pai->valorTerritorio>(*q)->valorTerritorio)
				return(1);
		}
	}
	return(0);
}

int ajustaArvCasas(arvCasas **casa, arvCasas *p){
	int aux;

	aux = confereABBArvTerritorios(p->territorios);
	if((aux && p->ABB==0) || (!aux && p->ABB==1)){
		p->valorCasa = -(p->valorCasa);
		p->ABB = (char) aux;
	}
	if(buscarCasa((*casa), p->valorCasa)!=NULL){
		liberaTerritorios(p->territorios);
		free(p);
		return(0);
	}
	insereNovaCasa(casa, p);
	return(1);
}

void liberaTerritorios(arvTerritorios *pai){
	if(pai!=NULL){
		liberaTerritorios(pai->esq);
		liberaTerritorios(pai->dir);
		free(pai);
	}
}

int removerTerritorio(arvTerritorios **pai, arvCasas *casa, int valor){
	arvTerritorios *p, **aux;

	if(casa->ABB==1){
		if((*pai)==NULL)
			return(0);
		if((*pai)->valorTerritorio>valor)
			return(removerTerritorio(&((*pai)->esq), casa, valor));
		if((*pai)->valorTerritorio<valor)
			return(removerTerritorio(&((*pai)->dir), casa, valor));
		if((casa->territorios==(*pai)) && (*pai)->esq==NULL && (*pai)->dir==NULL)
			return(-1);
		casa->valorCasa = casa->valorCasa - valor;
	}
	else{
		if((*pai)==NULL)
			return(0);
		if((*pai)->valorTerritorio!=valor){
			if(removerTerritorio(&((*pai)->esq), casa, valor)==0)
				return(removerTerritorio(&((*pai)->dir), casa, valor));
			return(1);
		}
		if((casa->territorios==(*pai)) && (*pai)->esq==NULL && (*pai)->dir==NULL)
			return(-1);
		casa->valorCasa = casa->valorCasa + valor;
	}
	if((*pai)->esq==NULL){
		p = (*pai);
		(*pai) = (*pai)->dir;
		free(p);
	}
	else if((*pai)->dir==NULL){
		p = (*pai);
		(*pai) = (*pai)->esq;
		free(p);
	}
	else{
		aux = menorElemArvTerritorios(&((*pai)->dir));
		p = (*aux);
		(*pai)->valorTerritorio = (*aux)->valorTerritorio;
		(*aux) = (*aux)->dir;
		free(p);
	}
	return(1);
}

void exibirArvCasas(arvCasas *casa){
	if(casa!=NULL){
		exibirArvCasas(casa->esq);
		printf("%d\n", casa->valorCasa);
		exibirArvCasas(casa->dir);
	}
}

void exibirArvTerritorios(arvTerritorios *pai){
	if(pai!=NULL){
		exibirArvTerritorios(pai->esq);
		printf("%d\n", pai->valorTerritorio);
		exibirArvTerritorios(pai->dir);
	}
}

void liberaCasas(arvCasas *casa){
	if(casa!=NULL){
		liberaCasas(casa->esq);
		liberaCasas(casa->dir);
		free(casa->territorios);
		free(casa);
	}
}

void getNome(char *nome){
	char c;
	int i=0;

	while((c=getchar())!=' '){
		nome[i] = c;
		i++;
	}
	nome[i] = '\0';
}