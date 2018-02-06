/* ================================================================== *
	Universidade Federal de Sao Carlos - UFSCar, Sorocaba

	Disciplina: Estruturas de Dados 1
	Prof. Tiago A. Almeida

	Exercício 08 - Listas Telefônicas

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
#define MSG_JA_EXISTE_LST	"O título de lista informado já está cadastrado!\n"
#define MSG_JA_EXISTE_REG	"O registro informado já está cadastrado na lista!\n"
#define MSG_NAO_EXISTE_LST	"A lista telefônica requisitada não está cadastrada!\n"
#define MSG_NAO_EXISTE_REG	"O registro buscado não está presente na lista!\n"
#define MSG_IMPRIME_REG 	"Nome: %s\nTel.: %s\n"
#define MSG_LISTA_VAZIA		"Lista vazia!\n"
#define MSG_OPCAO_INV 		"Opcao invalida!\n"

// Constantes
#define NOME_FINAL         	"END"



// === TAD E DEMAIS REGISTROS ===

typedef struct reg{
	char *nome, *telefone;
	struct reg *ant, *prox;
}Reg;

typedef struct l{
	char *nomeLista;
	Reg *ultimoReg;
	struct l *prox;
}ListaTel;

typedef struct{
	ListaTel *inicio;
}Listas;



/* ================================================================== */
/* ===================== PREAMBULO DAS FUNCOES ====================== */
/* ================================================================== */

void iniciaListas(Listas *listas);
ListaTel *confereListaTel(Listas *listas, char *s);
int addListaTel(Listas *listas, char *s);
int iniciaRegs(ListaTel *aux);
int addReg(ListaTel *lista, char *nome, char *tel);
int buscar(ListaTel *lista, char **nome, char **tel, int k);
void imprimirCrescente(ListaTel *lista);
void imprimirDecrescente(ListaTel *lista);
char *pegaString();
void liberaMem(Listas *listas);



/* ================================================================== */
/* ======================== ROTINA PRINCIPAL ======================== */
/* ================================================================== */

int main(){

	Listas *listas;
	int op, k;
	ListaTel *lista;
	char *nome, *tel;

	listas = (Listas *) malloc(sizeof(Listas));
	if(listas==NULL){
		printf(MSG_ERRO_ALOC);
		return(0);
	}
	iniciaListas(listas);
	scanf("%d", &op);
	while(op!=6){
		getchar();
		if(op==1){
			nome = pegaString();
			lista = confereListaTel(listas, nome);
			if(lista==NULL){
				if(!addListaTel(listas, nome)){
					printf(MSG_ERRO_ALOC);
					return(0);
				}
				lista = confereListaTel(listas, nome);
				nome = pegaString();
				while(strcmp(nome, NOME_FINAL)){
					tel = pegaString();
					if((k=addReg(lista, nome, tel))==-1){
						printf(MSG_ERRO_ALOC);
						return(0);
					}
					else if(!k)
						printf(MSG_JA_EXISTE_REG);
					nome = pegaString();
				}
			}
			else
				printf(MSG_JA_EXISTE_LST);
			free(nome);
		}

		else if(op==2){
			nome = pegaString();
			lista = confereListaTel(listas, nome);
			free(nome);
			if(lista!=NULL){
				nome = pegaString();
				tel = pegaString();
				if((k=addReg(lista, nome, tel))==-1){
					printf(MSG_ERRO_ALOC);
					return(0);
				}
				else if(!k)
					printf(MSG_JA_EXISTE_REG);
			}
			else
				printf(MSG_NAO_EXISTE_LST);
		}

		else if(op==3){
			nome = pegaString();
			lista = confereListaTel(listas, nome);
			free(nome);
			if(lista!=NULL){
				nome = pegaString();
				scanf("%d", &k);
				if(buscar(lista, &nome, &tel, k)){
					printf(MSG_IMPRIME_REG, nome, tel);
				}
				else
					printf(MSG_NAO_EXISTE_REG);
			}
			else
				printf(MSG_NAO_EXISTE_LST);
		}

		else if(op==4){
			nome = pegaString();
			lista = confereListaTel(listas, nome);
			free(nome);
			if(lista!=NULL)
				imprimirCrescente(lista);
			else
				printf(MSG_NAO_EXISTE_LST);
		}

		else if(op==5){
			nome = pegaString();
			lista = confereListaTel(listas, nome);
			free(nome);
			if(lista!=NULL)
				imprimirDecrescente(lista);
			else
				printf(MSG_NAO_EXISTE_LST);
		}

		else if(op!=6)
			printf(MSG_OPCAO_INV);

		scanf("%d", &op);
	}

	liberaMem(listas);
	return (0);
}



/* ================================================================== */
/* ========== FUNCOES QUE DETERMINAM AS OPERACOES POSSIVEIS ========= */
/* ================================================================== */

void iniciaListas(Listas *listas){
	listas->inicio = NULL;
}

ListaTel *confereListaTel(Listas *listas, char *s){
	ListaTel *aux;
	for(aux=listas->inicio; aux!=NULL; aux=aux->prox){
		if(strcmp(aux->nomeLista, s)==0){
			return(aux);
		}
	}
	return(NULL);
}

int addListaTel(Listas *listas, char *s){
	ListaTel *aux;
	aux = (ListaTel *) malloc(sizeof(ListaTel));
	if(aux==NULL)
		return(0);
	aux->nomeLista = s;
	if(!iniciaRegs(aux))
		return(0);
	aux->prox = listas->inicio;
	listas->inicio = aux;
	return(1);
}

int iniciaRegs(ListaTel *aux){
	aux->ultimoReg = (Reg *) malloc(sizeof(Reg));
	if(aux->ultimoReg==NULL)
		return(0);
	aux->ultimoReg->prox = aux->ultimoReg;
	aux->ultimoReg->ant = aux->ultimoReg;
	return(1);
}

int addReg(ListaTel *lista, char *nome, char *tel){
	Reg *aux, *p;
	p = lista->ultimoReg->prox->prox;
	while(p!=lista->ultimoReg->prox && (strcmp(p->nome, nome)<0 || (strcmp(p->nome, nome)==0 && strcmp(p->telefone, tel)<=0))){
		if(strcmp(p->nome, nome)==0 && strcmp(p->telefone, tel)==0){
			free(nome);
			free(tel);
			return(0);
		}
		p = p->prox;
	}
	aux = (Reg *) malloc(sizeof(Reg));
	if(aux==NULL)
		return(-1);
	aux->nome = nome;
	aux->telefone = tel;
	aux->prox = p;
	aux->ant = p->ant;
	if(p==lista->ultimoReg->prox)
		lista->ultimoReg = aux;
	p->ant->prox = aux;
	p->ant = aux;
	return(1);
}

int buscar(ListaTel *lista, char **nome, char **tel, int k){
	Reg *p;
	int flag;
	if(nome[0][0]=='(' && nome[0][3]==')' && nome[0][4]==' ' && nome[0][9]=='-'){
		for(p=lista->ultimoReg->prox->prox, flag=1; p!=lista->ultimoReg->prox && flag; p=p->prox){
			if(strcmp(p->telefone, *nome)==0)
				flag = 0;
		}
	}
	else{
		for(p=lista->ultimoReg->prox->prox, flag=1; p!=lista->ultimoReg->prox && flag; p=p->prox){
			if(strcmp(p->nome, *nome)==0)
				flag = 0;
		}	
	}
	free(*nome);
	if(flag)
		return(0);
	p = p->ant;
	if(k>0){
		while(k){
			p = p->prox;
			if(p==lista->ultimoReg->prox)
				return(0);
			k--;
		}
	}
	else if(k<0){
		while(k){
			p = p->ant;
			if(p==lista->ultimoReg->prox)
				return(0);
			k++;
		}
	}
	*nome = p->nome;
	*tel = p->telefone;
	return(1);
}

void imprimirCrescente(ListaTel *lista){
	Reg *p;
	if(lista->ultimoReg->prox==lista->ultimoReg){
		printf(MSG_LISTA_VAZIA);
		return;
	}
	for(p=lista->ultimoReg->prox->prox; p!=lista->ultimoReg->prox; p=p->prox)
		printf(MSG_IMPRIME_REG, p->nome, p->telefone);
}

void imprimirDecrescente(ListaTel *lista){
	Reg *p;
	if(lista->ultimoReg->prox==lista->ultimoReg){
		printf(MSG_LISTA_VAZIA);
		return;
	}
	for(p=lista->ultimoReg; p!=lista->ultimoReg->prox; p=p->ant)
		printf(MSG_IMPRIME_REG, p->nome, p->telefone);	
}

char *pegaString(){
	int i=0;
	char c, *s;
	s = (char *) malloc(1);
	while((c = getchar())!='\n'){
		s[i] = c;
		i++;
		s = (char *) realloc(s, i+1);
	}
	s[i] = '\0';
	return(s);
}

void liberaMem(Listas *listas){
	Reg *aux;
	ListaTel *aux2;
	for(aux2=listas->inicio; aux2!=NULL; aux2=listas->inicio){
		listas->inicio = aux2->prox;
		aux2->ultimoReg->prox->ant = aux2->ultimoReg->prox;
		for(aux=aux2->ultimoReg; aux->ant!=aux; aux=aux2->ultimoReg){
			aux2->ultimoReg = aux->ant;
			free(aux->nome);
			free(aux->telefone);
			free(aux);
		}
		free(aux2->ultimoReg);
		free(aux2->nomeLista);
		free(aux2);
	}
	free(listas);
}