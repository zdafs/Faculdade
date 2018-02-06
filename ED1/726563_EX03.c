/* Universidade Federal de Sao Carlos - UFSCar, Sorocaba

  Disciplina: Estruturas de Dados 1
  Prof. Tiago A. Almeida

  Exercício 3 - (TAD Pilha) Calculadora Pós-Fixada

  Instrucoes
  ----------

  Este arquivo contem o codigo que auxiliara no desenvolvimento do
  exercicio. Voce precisara completar as funcoes requisitadas.

  Voce nao podera criar nenhuma outra funcao. Complete apenas as rotinas
  fornecidas.                             */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/************************************************/

typedef struct no{
	float item;
	struct no *prox;
}no;

typedef struct{
	no *topo;
}Tpilha;


/************************************************/

void criaPilha(Tpilha *pilha);
void empilha(Tpilha *pilha, float n);
float desempilha(Tpilha *pilha);


/************************************************/

int main()
{
	Tpilha *pilha;
 	char *exp, c;
 	int i=0;
 	float n, v, s;
 	pilha = (Tpilha *) malloc(sizeof(Tpilha));
 	criaPilha(pilha);
 	exp = (char *) malloc(sizeof(char));
 	while((c=getchar())!='\n'){
 		exp[i]=c;
 		i++;
 		exp = (char *) realloc(exp, (i+1)*sizeof(char));
 	}
 	exp[i]='\0';

 	while(*exp!='\0'){
 		if(*exp!='+'&&*exp!='-'&&*exp!='*'&&*exp!='/'){
 			scanf("%f", &n);
 			empilha(pilha, n);
 		}
 		else{
 			if(*exp=='+'){
 				n = desempilha(pilha) + desempilha(pilha);
 				empilha(pilha, n);
 			}
 			else if(*exp=='-'){
 				v = desempilha(pilha);
 				s = desempilha(pilha);
 				n = s - v;
 				empilha(pilha, n);
 			}
 			else if(*exp=='*'){
 				n = desempilha(pilha) * desempilha(pilha);
 				empilha(pilha, n);
 			}
 			else if(*exp=='/'){
 				v = desempilha(pilha);
 				s = desempilha(pilha);
 				n = s / v;
 				empilha(pilha, n);
 			}
 		}
 		exp++;
 	}
 	printf("%f\n", desempilha(pilha));
 	free(pilha->topo);
 	free(pilha);

  return (0);
}

void criaPilha(Tpilha *pilha){
	pilha->topo=NULL;
}

void empilha(Tpilha *pilha, float n){
	no *aux;
	aux = (no *) malloc(sizeof(no));
	aux->item = n;
	aux->prox = pilha->topo;
	pilha->topo = aux;
}

float desempilha(Tpilha *pilha){
	no *aux;
	float i;
	aux = pilha->topo;
	pilha->topo = pilha->topo->prox;
	i = aux->item;
	free(aux);
	return(i);
}