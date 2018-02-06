/* ================================================================== *
   Universidade Federal de Sao Carlos - UFSCar, Sorocaba

   Disciplina: Algoritmos e Programação 2
   Prof. Tiago A. Almeida

   Lista 05 - Exercício 05 - Lista estática encadeada ordenada

   Instrucoes
   ----------

   Este arquivo contem o codigo que auxiliara no desenvolvimento do
   exercicio. Voce precisara completar as partes requisitadas.

* ================================================================== *
   Dados do aluno:

   RA: 726563
   Nome: Lucca La Fonte Albuquerque Carvalho

* ================================================================== */

#include <stdio.h>


#define MAX 100 // Quantidade máxima de elementos da lista

// Estrutura de um nó da lista
typedef struct No {
    struct No *prox;  // campo que aponta para o seu próximo nó
    int valor;        // valor do nó
} No;


// Variáveis globais
No vetor[MAX];    // lista estática de nós com MAX posições
No *lista;        // nó que aponta para o início da lista ordenada
No *disponiveis;  // nó que aponta para a primeira posição vazia da lista


// Protótipos das funções
int inserir(int valor);
int remover(int valor);
int buscar(int valor);
void imprimir();


/* ------------------------------ */
/* ROTINA PRINCIPAL - NAO ALTERAR */
/* ------------------------------ */
int main() {
    int i, opcao, valor;

	// A lista inicia-se vazia
	lista = NULL;
    
    // Cada nó do vetor aponta para o próximo nó
    for (i = 0; i < MAX - 1; ++i)
        vetor[i].prox = &vetor[i + 1];
    vetor[MAX - 1].prox = NULL;
    
    // A lista de nós disponíveis inicialmente abrange todo o vetor
    disponiveis = &vetor[0];

	// Tratar entradas
	while (scanf("%d", &opcao) > 0) {
		switch (opcao) {
		case 1:
			scanf("%d", &valor);
			if (!inserir(valor))
                printf("Nao foi possivel inserir.\n");
			break;
		case 2:
			scanf("%d", &valor);
			if (!remover(valor))
                printf("Nao foi possivel remover.\n");
			break;
		case 3:
			scanf("%d", &valor);
			printf("%d\n", buscar(valor));
			break;
		case 4:
			imprimir();
			break;
		case 5:
			return 0;
		}
	}
    
    return 0;
}


/* ------------------------- */
/* IMPLEMENTACAO DAS FUNCOES */
/* ------------------------- */

int inserir(int valor) {
	No *i, *aux, **j;
	int flag=0;
    
	if(disponiveis==NULL)
		return(0);
	else
	{
		aux=disponiveis;
		disponiveis=disponiveis->prox;
		aux->valor=valor;
		aux->prox=NULL;
		if(lista==NULL)
			lista=aux;
		else
		{
			for(i=lista, j=&lista; i!=NULL&&flag==0; i=i->prox)
			{
				if((aux->valor)<(i->valor))
				{
					*j=aux;
					aux->prox=i;
					flag=1;
				}
				else if(((aux->valor)>=(i->valor))&&(i->prox==NULL))
				{
					i->prox=aux;
					flag=1;
				}
				j=&i->prox;
			}
		}
	}
	return(1);
    
}

int remover(int valor) {
	int flag=0, diff;
	No *i, **j;
	if(lista==NULL)
		return(0);
	else
	{
		for(i=lista, j=&lista; i!=NULL; i=i->prox)
		{
			if(i->valor==valor)
			{
				*j=i->prox;
				i->prox=NULL;
				flag=1;
				diff=i-vetor;
			}
			j=&i->prox;
		}
		if(flag==0)
			return(0);
		else
		{
			if(disponiveis==NULL)
				disponiveis=&vetor[diff];
			else if(diff<(disponiveis-vetor))
			{
				vetor[diff].prox=disponiveis;
				disponiveis=&vetor[diff];
			}
			else
			{
				vetor[diff].prox=disponiveis->prox;
				disponiveis->prox=&vetor[diff];
			}
		}
	}
    	return(1);
}

int buscar(int valor) {

	No *i;
	int cont=-1;
	for(i=lista; i!=NULL; i=i->prox)
	{
		cont++;
		if(i->valor==valor)
		{
			return(cont);
		}
	}
	return(-1);
    
}

void imprimir() {
    
	No *i;
	for(i=lista; i!=NULL; i=i->prox)
	{
		printf("%d ", i->valor);
	}
	printf("\n");

  
    
}
