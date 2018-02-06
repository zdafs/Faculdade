/* ================================================================== *
    Universidade Federal de Sao Carlos - UFSCar, Sorocaba
 
    Disciplina: Algoritmos e Programação 2
    Prof. Tiago A. Almeida
 
    Lista 07 - Exercício 03 - Pilhas
 
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
#include <stdlib.h>

#define MSG_PILHA_VAZIA "Pilha vazia.\n"

#define OPCAO_INSERIR 		1
#define OPCAO_REMOVER 		2
#define OPCAO_TRANSFERIR 	3
#define OPCAO_IMPRIMIR 		4
#define OPCAO_FINALIZAR 	5

// Registro com cada nó da pila
typedef struct No {
    struct No *prox;
    int item;
} No;

// Registro que aponta para o topo da pilha
typedef struct {
    No *topo;
} Pilha;


// declaracoes das funcoes
void iniciar_pilha(Pilha *pilha);
void inserir_pilha(Pilha *pilha, int item);
int remover_pilha(Pilha *pilha);
void imprimir_pilha(Pilha pilha);
void liberar_pilha(Pilha *pilha);
int p=0;//variavel para manter controle da quebra de linha em imprimir_pilha


/* ------------------------------ */
/* ROTINA PRINCIPAL - NAO ALTERAR */
/* ------------------------------ */
int main() {
     
	int num_pilhas;
	Pilha *pilhas;
	int i;
    int opcao, posicao;
	int num_itens, item;
	int a, b;

	scanf("%d", &num_pilhas);

	pilhas = (Pilha *)malloc(num_pilhas * sizeof(Pilha));
	for (i = 0; i < num_pilhas; ++i)
		iniciar_pilha(pilhas + i); /* Inicializa a pilha */

	while (scanf("%d", &opcao) > 0 && opcao != OPCAO_FINALIZAR) {
		switch (opcao) {
		case OPCAO_INSERIR:
			scanf("%d %d", &posicao, &num_itens);
			--posicao;
			for (i = 0; i < num_itens; ++i) {
				scanf("%d", &item);
				inserir_pilha(pilhas + posicao, item); /* Aloca um nó e insere na pilha com o item */
			}
			break;
		case OPCAO_REMOVER:
			scanf("%d %d", &posicao, &num_itens);
			--posicao;
			for (i = 0; i < num_itens; ++i)
				remover_pilha(pilhas + posicao); /* Remove o nó do topo, libera a memória usada pelo nó e retorna o item */
			break;
		case OPCAO_TRANSFERIR:
			scanf("%d %d %d", &a, &b, &num_itens);
			--a, --b;
			for (i = 0; i < num_itens; ++i)
				inserir_pilha(pilhas + b, remover_pilha(pilhas + a));
			break;
		case OPCAO_IMPRIMIR:
			scanf("%d", &posicao);
			imprimir_pilha(pilhas[--posicao]); /* Imprime os itens da pilha da base para o topo */
			break;
		}
	}
    
	for (i = 0; i < num_pilhas; ++i)
		liberar_pilha(pilhas + i); /* Libera os nós da pilha */
    free(pilhas);
    
    return 0;
}


/* ------------------------- */
/* IMPLEMENTACAO DAS FUNCOES */
/* ------------------------- */

void iniciar_pilha(Pilha *pilha)
{
	//inicializa o vetor pilhas na posicao i com topo NULL
	pilha->topo=NULL;
}
void inserir_pilha(Pilha *pilha, int item)
{
	if(pilha->topo==NULL)
	{
		pilha->topo=(No *)malloc(sizeof(No));
		pilha->topo->item=item;
		pilha->topo->prox=NULL;
	}
	else
	{
		//guarda o valor do No
		No *aux=(No *)malloc(sizeof(No));
		aux->item=item;
		//aponta o novo No para o antigo topo
		aux->prox=pilha->topo;
		//aponta o topo para o ultimo(novo) No inserido
		pilha->topo=aux;
	}
}
int remover_pilha(Pilha *pilha)
{
	if(pilha->topo!=NULL)
	{
		int item=pilha->topo->item;
		if(pilha->topo->prox==NULL)//tem apenas um No
		{
			free(pilha->topo);//libera o topo da pilha atual
			pilha->topo=NULL;//deixa a pilha vazia
			return(item);
		}
		No *aux=pilha->topo;//guarda o atual topo da pilha
		pilha->topo=pilha->topo->prox;//transfere o topo para baixo da pilha
		free(aux);//libera o antigo topo
		return(item);
	}
	else
		printf(MSG_PILHA_VAZIA);
	return(-1);
}
void imprimir_pilha(Pilha pilha)
{
	p++;//na primeira fez que executa a função p=1 e, durante o processo de recursão, contabiliza o numero de vezes que passa na função
	if(pilha.topo==NULL)//caso a lista esteja vazia
	{
		printf(MSG_PILHA_VAZIA);
		p=0;//reseta a variavel de controle caso tenha que ser utilizada mais uma vez
		return;
	}
	Pilha aux;
	aux.topo=pilha.topo->prox;//pilha auxiliar(topo igual ao elemento abaixo do topo da pilha original)
	if(aux.topo==NULL)//caso base(variavel auxiliar esta na base da pilha original)
	{
		printf("%d ", pilha.topo->item);
		if(p==1)//caso seja a pilha tenha apenas 1 elemento
		{
			printf("\n");
			p=0;//reset da variavel de controle
		}
		return;
	}
	imprimir_pilha(aux);//recursao utlizando a pilha auxiliar
	p--;//diminui em 1 o valor da variavel de controle. Significa que saiu de uma das etapas da recursão
	printf("%d ", pilha.topo->item);
	if(p==1)//quando p=1 quer dizer que não ha mais funções empilhadas
	{
		p=0;//reset da variavel de controle
		printf("\n");
	}
	return;
}
void liberar_pilha(Pilha *pilha)
{
	No *aux;
	for(aux=pilha->topo; aux!=NULL; aux=pilha->topo)
	{
		pilha->topo=pilha->topo->prox;
		free(aux);
	}
}

