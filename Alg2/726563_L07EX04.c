/* ================================================================== *
    Universidade Federal de Sao Carlos - UFSCar, Sorocaba
 
    Disciplina: Algoritmos e Programação 2
    Prof. Tiago A. Almeida
 
    Lista 07 - Exercício 04 - Fila do banco
 
    Instrucoes
    ----------
 
    Este arquivo contem o codigo que auxiliara no desenvolvimento do
    exercicio. Voce precisara completar as partes requisitadas.
 
* ================================================================== *
    Dados do aluno:
 
    RA: 726563
    Nome: Lucca La Fonte Albuquerque Carvalho
 
* ================================================================== */

/* Bilbiotecas */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* Mensagens predefinidas */
#define ATENDENTE_TRABALHANDO 	"Atendente ja trabalhando\n"
#define GUICHE_OCUPADO 			"Guiche ocupado\n"


/* Opcoes do menu */
enum opcoes {FECHAR_BANCO = 0, INSERIR_ATENDENTE, INSERIR_CLIENTE, TOTAL_ATENDENTE, TOTAL_CLIENTE, EXIBE_ATENDENTE, EXIBE_CLIENTE, DESOCUPA_ATENDENTE, REMOVE_ATENDENTE, ATENDE_CLIENTE };

/* ======================================================= */

// declaracoes de registros

/* No da lista de atendentes */
typedef struct _atendente {
	char *nome_atendente;	
	char *nome_cliente;
	int guiche;
	int ocupado;
	struct _atendente *prox;
} NoAtendente;

/* No da fila de clientes */
typedef struct _cliente {
	char *nome_cliente;	
	struct _cliente *prox;
} NoCliente;

/* Estrutura que aponta para o primeiro nó da lista de atendentes */
typedef struct _lista_atendente {
	NoAtendente *inicio;
} ListaAtendente;

/* Estrutura que aponta para o primeiro nó da fila de clientes */
typedef struct _fila_cliente {
	NoCliente *inicio;
} FilaCliente;

/* ======================================================= */

/* Funcoes ja implementadas */

/* Exibe os atendentes os guiches e os clientes sendo atendidos */
void exibe_atendentes(ListaAtendente *lista_atendente);

/* Exibe os clientes que estao sendo atendidos e estao na fila */
void exibe_clientes(ListaAtendente *lista_atendente, FilaCliente *fila_cliente);



// declaracoes das demais funcoes
void inicializa(ListaAtendente *lista_atendente, FilaCliente *fila_cliente);
int total_clientes(FilaCliente *fila_cliente);
int total_atendentes(ListaAtendente *lista_atendente);
int lista_vazia(ListaAtendente *lista_atendente);
int fila_vazia(FilaCliente *fila_cliente);
int fechar_banco(ListaAtendente *lista_atendente, FilaCliente *fila_cliente);
void insere_atendente(ListaAtendente *lista_atendente);
void insere_cliente(FilaCliente *fila_cliente);
char *desocupa_atendente(ListaAtendente *lista_atendente, int num_guiche);
char *remove_atendente(ListaAtendente *lista_atendente, int num_guiche);
int atende_cliente(ListaAtendente *lista_atendente, FilaCliente *fila_cliente);



/* ======================================================= */

/* ------------------------------ */
/* ROTINA PRINCIPAL - NAO ALTERAR */
/* ------------------------------ */

int main() {
	ListaAtendente lista_atendente;
	FilaCliente fila_cliente;
	int opcao, num_guiche;
	char *nome;

	/* Define o inicio das listas como NULL */
	inicializa(&lista_atendente, &fila_cliente);

	while (1) {
		scanf("%d", &opcao);
		
		switch (opcao) {
			case FECHAR_BANCO:
				/* Libera da memoria as estruturas de dados e conta quanto clientes estao na fila */
				printf("Banco fechado: %d cliente(s) nao atendido(s)\n", fechar_banco(&lista_atendente, &fila_cliente));
				return 0;
				break;

			case INSERIR_ATENDENTE:
				/* 	Recebe o nome e o guiche do atendente
					Verifica se o atendente ja esta inserido
					Verifica se o guiche ja esta ocupado
					Insere o atendente na lista ordenando pelo numero do guiche */
				insere_atendente(&lista_atendente);
				break;

			case INSERIR_CLIENTE:
				/* 	Recebe o nome do cliente
					Insere o cliente no fim da fila */
				insere_cliente(&fila_cliente);
				break;

			case TOTAL_ATENDENTE:
				if (lista_vazia(&lista_atendente)) /* 	Retorna 1 se a lista esta vazia e 0 caso contrario */
					printf("Sem atendentes\n");
				else
					/* 	Retorna o numero de atendentes na lista */
					printf("Total atendentes: %d\n", total_atendentes(&lista_atendente));
				break;

			case TOTAL_CLIENTE:
				if (fila_vazia(&fila_cliente)) /* 	Retorna 1 se a fila esta vazia e 0 caso contrario */
					printf("Sem clientes\n");
				else
					/* 	Retorna o numero de cliente na fila */
					printf("Total clientes: %d\n", total_clientes(&fila_cliente));
				break;

			case EXIBE_ATENDENTE:
				exibe_atendentes(&lista_atendente);
				break;

			case EXIBE_CLIENTE:
				exibe_clientes(&lista_atendente, &fila_cliente);
				break;

			case DESOCUPA_ATENDENTE:
				scanf("%d", &num_guiche);
				/* 	Verifica se o guiche informado eh valido
					Desocupa o atendente (marca ocupado como 0) 
					Retorna o nome do atendente desocupado e NULL caso nao encontre */
				nome = desocupa_atendente(&lista_atendente, num_guiche);
				if (nome == NULL)
					printf("Atendente nao encontrado\n");
				else
					printf("Atendente %s desocupado\n", nome);
				break;

			case REMOVE_ATENDENTE:
				scanf("%d", &num_guiche);
				/*	Verifica se o guiche informado eh valido
					Remove o atendente da lista e libera a memoria do struct referente 
					Retorna o nome do atendente removido e NULL caso nao encontre */
				nome = remove_atendente(&lista_atendente, num_guiche);
				if (nome == NULL)
					printf("Atendente nao encontrado\n");
				else
					printf("Atendente %s removido\n", nome);
				break;

			case ATENDE_CLIENTE:
				if (lista_vazia(&lista_atendente))
					printf("Sem atendentes para atender\n");
				else {
					if (fila_vazia(&fila_cliente))
						printf("Sem clientes para serem atendidos\n");
					else {
						/* 	Verifica se algum atendente esta desocupado
							Remove o cliente do inicio da fila
							Copia o nome do cliente para nome_cliente do struct do atedente desocupado 
							Libera a memoria da struct referente ao cliente
							Retorna 1 se encontrou atendente desocupado e 0 caso contrario */
						if (atende_cliente(&lista_atendente, &fila_cliente))
							printf("Cliente atendido\n");
						else
							printf("Todos os atendentes estao ocupados\n");
					}
				}
				break;

			default:
				printf("Opcao invalida. Digite novamente\n");
				break;
		}
	}
}

/* ======================================================= */

/* ------------------------- */
/* IMPLEMENTACAO DAS FUNCOES */
/* ------------------------- */

/* Funcoes ja implementadas */

void exibe_atendentes(ListaAtendente *lista_atendente) {
	NoAtendente *aux = lista_atendente->inicio;

	while (aux != NULL) {
		if (aux->ocupado)
			printf("Atendente: %s || Guiche: %d || Cliente: %s\n", aux->nome_atendente, aux->guiche, aux->nome_cliente);
		else
			printf("Atendente: %s || Guiche: %d || Sem cliente\n", aux->nome_atendente, aux->guiche);
		aux = aux->prox;
	}	
}

void exibe_clientes(ListaAtendente *lista_atendente, FilaCliente *fila_cliente) {
	NoAtendente *auxA = lista_atendente->inicio;
	NoCliente *auxC = fila_cliente->inicio;

	printf("Clientes sendo atendidos:\n");
	while(auxA != NULL) {
		if (auxA->ocupado)
			printf("%s\n", auxA->nome_cliente);
		auxA = auxA->prox;
	}

	printf("Clientes na Fila:\n");
	while (auxC != NULL) {
		printf("%s\n", auxC->nome_cliente);
		auxC = auxC->prox;
	}	
}


void inicializa(ListaAtendente *lista_atendente, FilaCliente *fila_cliente)
{
	lista_atendente->inicio=NULL;
	fila_cliente->inicio=NULL;
}
int total_clientes(FilaCliente *fila_cliente)
{
	NoCliente *i=fila_cliente->inicio;
	int cont=0;
	while(i!=NULL)
	{
		cont++;
		i=i->prox;
	}
	return(cont);
}
int total_atendentes(ListaAtendente *lista_atendente)
{
	NoAtendente *i=lista_atendente->inicio;
	int cont=0;
	while(i!=NULL)
	{
		cont++;
		i=i->prox;
	}
	return(cont);	
}
int lista_vazia(ListaAtendente *lista_atendente)
{
	if(lista_atendente->inicio==NULL)
		return(1);
	return(0);
}
int fila_vazia(FilaCliente *fila_cliente)
{
	if(fila_cliente->inicio==NULL)
		return(1);
	return(0);
}
int fechar_banco(ListaAtendente *lista_atendente, FilaCliente *fila_cliente)
{
	int cont=total_clientes(fila_cliente);
	NoCliente *j, *aux2;
	for(j=fila_cliente->inicio, aux2=fila_cliente->inicio; j!=NULL; aux2=j)
	{
		j=j->prox;
		//free(aux2->nome_cliente);
		free(aux2);
	}
	fila_cliente->inicio=NULL;
	NoAtendente *i, *aux;
	for(i=lista_atendente->inicio, aux=lista_atendente->inicio; i!=NULL; aux=i)
	{
		i=i->prox;
		//free(aux->nome_atendente);
		//free(aux->nome_cliente);
		free(aux);
	}
	lista_atendente->inicio=NULL;
	return(cont);
}
void insere_atendente(ListaAtendente *lista_atendente)
{
	char c;
	int num_letras, cont=0;
	NoAtendente *aux=(NoAtendente *)malloc(sizeof(NoAtendente)), *i, **j;
	scanf("%d", &num_letras);
	aux->nome_atendente=(char *)malloc(num_letras+1);
	aux->ocupado=0;
	aux->prox=NULL;
	if((c=getchar())=='\n')
		c=getchar();
	while(c!='\n')
	{
		aux->nome_atendente[cont]=c;
		cont++;
		c=getchar();
	}
	aux->nome_atendente[cont]='\0';
	for(i=lista_atendente->inicio; i!=NULL; i=i->prox)
	{
		if(strcmp(aux->nome_atendente,i->nome_atendente)==0)
		{
			free(aux->nome_atendente);
			free(aux);
			printf(ATENDENTE_TRABALHANDO);
			return;
		}
	}
	scanf("%d", &aux->guiche);
	for(i=lista_atendente->inicio, j=&(lista_atendente->inicio); i!=NULL; i=i->prox, j=&((*j)->prox))
	{
		if(aux->guiche==i->guiche)
		{
			free(aux->nome_atendente);
			free(aux);
			printf(GUICHE_OCUPADO);
			return;
		}
		else if((aux->guiche)<(i->guiche))
		{
			aux->prox=*j;
			*j=aux;
			return;
		}
	}
	*j=aux;
}
void insere_cliente(FilaCliente *fila_cliente)
{
	int num_letras, cont=0;
	NoCliente *i=fila_cliente->inicio;
	char c;
	scanf("%d", &num_letras);
	if(fila_vazia(fila_cliente))
	{
		fila_cliente->inicio=(NoCliente *)malloc(sizeof(NoCliente));
		fila_cliente->inicio->nome_cliente=(char *)malloc(num_letras+1);
		if((c=getchar())=='\n')
			c=getchar();
		while(c!='\n')
		{
			fila_cliente->inicio->nome_cliente[cont]=c;
			cont++;
			c=getchar();
		}
		fila_cliente->inicio->nome_cliente[cont]='\0';
		fila_cliente->inicio->prox=NULL;
		return;
	}
	while(i->prox!=NULL)
		i=i->prox;
	i->prox=(NoCliente *)malloc(sizeof(NoCliente));
	i->prox->nome_cliente=(char *)malloc(num_letras+1);
	if((c=getchar())=='\n')
		c=getchar();
	while(c!='\n')
	{
		i->prox->nome_cliente[cont]=c;
		cont++;
		c=getchar();
	}
	i->prox->nome_cliente[cont]='\0';
	i->prox->prox=NULL;
}
char *desocupa_atendente(ListaAtendente *lista_atendente, int num_guiche)
{
	NoAtendente *i;
	for(i=lista_atendente->inicio; i!=NULL; i=i->prox)
	{
		if(i->guiche==num_guiche)
		{
			i->ocupado=0;
			return(i->nome_atendente);
		}
	}
	return(NULL);
}
char *remove_atendente(ListaAtendente *lista_atendente, int num_guiche)
{
	char *nome;
	NoAtendente *i, **j;
	for(i=lista_atendente->inicio, j=&(lista_atendente->inicio); i!=NULL; i=i->prox, j=&((*j)->prox))
	{
		if(i->guiche==num_guiche)
		{
			nome=(char *)malloc(sizeof(i->nome_atendente+1));
			strcpy(nome, i->nome_atendente);
			*j=i->prox;
			free(i->nome_atendente);
			free(i->nome_cliente);
			free(i);
			return(nome);
		}
	}
	return(NULL);
}
int atende_cliente(ListaAtendente *lista_atendente, FilaCliente *fila_cliente)
{
	NoCliente *aux=fila_cliente->inicio;
	NoAtendente *i;
	fila_cliente->inicio=fila_cliente->inicio->prox;
	for(i=lista_atendente->inicio; i!=NULL; i=i->prox)
	{
		if(i->ocupado==0)
		{
			i->ocupado=1;
			i->nome_cliente=(char *)malloc(sizeof(strlen(aux->nome_cliente+1)));
			strcpy(i->nome_cliente,aux->nome_cliente);
			free(aux->nome_cliente);
			free(aux);
			return(1);
		}
	}
	fila_cliente->inicio=aux;
	return(0);
}