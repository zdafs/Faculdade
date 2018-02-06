/* ================================================================== *
	Universidade Federal de Sao Carlos - UFSCar, Sorocaba

	Disciplina: Estruturas de Dados 1
	Prof. Tiago A. Almeida

	Exercício 05 - Dobraduras Inteligentes

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
#include <math.h>

// Frases exibidas quando houver erro nas operacoes
#define MSG_ERRO_ALOC 	"Erro de alocacao!\n"
#define MSG_VAZIO 		"Não há nenhum quebra-cabeça para ser resolvido!\n"
#define MSG_OPCAO_INV 	"Opcao invalida!\n"


// === TAD E DEMAIS REGISTROS ===

typedef struct Pilha{
	char *pPilha;
	int topo;
}Pilha;

typedef struct celula{
	int dobras;
	char tipo;
	struct celula *prox;
}Celula;

typedef struct{
	Celula *frente, *tras;
}Fila;



/* ================================================================== */
/* ===================== PREAMBULO DAS FUNCOES ====================== */
/* ================================================================== */

void iniciaFila(Fila *fila);
void enfileirar(Fila *fila);
void inserir(Fila *fila, Pilha *pilha, char tp, int tam);
void qtDobrasBio(Fila *fila, Pilha *pilha, char c);
int ehPrimo(int n);
void qtDobrasMat(Fila *fila, Pilha *pilha, int n);
void liberaPilhaAtual(Pilha *pilha);
int filaVazia(Fila *fila);
void colocaFinalFila(Fila *fila);
void resolucao(Fila *fila, char *c, int *n);
void desenfileira(Fila *fila);





/* ================================================================== */
/* ======================== ROTINA PRINCIPAL ======================== */
/* ================================================================== */

int main(){

	Fila *fila;
	Pilha *pilha;
	int op, tam, i, n;
	char tp, c;
	fila = (Fila *) malloc(sizeof(Fila));
	if(fila==NULL){
		printf(MSG_ERRO_ALOC);
		return(0);
	}
	iniciaFila(fila);
	scanf("%d", &op);
	while(op!=4){
		if(op==1){
			pilha = (Pilha *) malloc(sizeof(Pilha));
			i=0;
			getchar();
			scanf("%c %d", &tp, &tam);
			inserir(fila, pilha, tp, tam);
			if(tp=='B'){
				if((c=getchar())=='\n')
					c=getchar();
				while(i<tam){
					qtDobrasBio(fila, pilha, c);
					i++;
					c=getchar();
				}
			}
			else{
				while(i<tam){
					scanf("%d", &n);
					qtDobrasMat(fila, pilha, n);
					i++;
				}
			}
			liberaPilhaAtual(pilha);
		}

		else if(op==2){
			if(filaVazia(fila))
				printf(MSG_VAZIO);
			else
				colocaFinalFila(fila);
		}

		else if(op==3){
			if(filaVazia(fila))
				printf(MSG_VAZIO);
			else{
				resolucao(fila, &c, &n);
				printf("%d (%c)\n", n, c);
				desenfileira(fila);
			}
		}

		else if(op!=4)
			printf(MSG_OPCAO_INV);

		scanf("%d", &op);
	}

	while(!filaVazia(fila))
		desenfileira(fila);
	free(fila);

	return (0);
}



/* ================================================================== */
/* ========== FUNCOES QUE DETERMINAM AS OPERACOES POSSIVEIS ========= */
/* ================================================================== */

void iniciaFila(Fila *fila){
	fila->frente = NULL;
	fila->tras = NULL;
}

void enfileirar(Fila *fila){
	Celula *aux;
	aux = (Celula *) malloc(sizeof(Celula));
	if(aux==NULL){
		printf(MSG_ERRO_ALOC);
		return;
	}
	aux->dobras = 0;
	aux->prox = NULL;
	if(fila->frente==NULL)
		fila->frente = aux;
	else
		fila->tras->prox = aux;
	fila->tras = aux;
}

void inserir(Fila *fila, Pilha *pilha, char tp, int tam){
	enfileirar(fila);
	fila->tras->tipo = tp;
	pilha->topo = -1;
	pilha->pPilha = (char *) malloc(tam*sizeof(char));
}

void qtDobrasBio(Fila *fila, Pilha *pilha, char c){
	if(pilha->topo>=0 && ((pilha->pPilha[pilha->topo]=='A'&&c=='T')||(pilha->pPilha[pilha->topo]=='T'&&c=='A')
	   ||(pilha->pPilha[pilha->topo]=='C'&&c=='G')||(pilha->pPilha[pilha->topo]=='G'&&c=='C')))
	{
		pilha->topo--;
		fila->tras->dobras++;
	}
	else{	
		pilha->topo++;
		pilha->pPilha[pilha->topo] = c;
	}
}

int ehPrimo(int n){
	int i;
	if(n!=2&&n%2==0||n==1)
		return(0);
	for(i=3; i<=sqrt(n); i+=2){
		if(n%i==0)
			return(0);
	}
	return(1);
}

void qtDobrasMat(Fila *fila, Pilha *pilha, int n){
	char p;
	p = ehPrimo(n);
	if(pilha->topo>=0 && pilha->pPilha[pilha->topo]==1 && p==1){
		pilha->topo--;
		fila->tras->dobras++;
	}
	else{
		pilha->topo++;
		pilha->pPilha[pilha->topo] = p;
	}
}

void liberaPilhaAtual(Pilha *pilha){
	free(pilha->pPilha);
	free(pilha);
}

int filaVazia(Fila *fila){
	return(fila->frente==NULL);
}

void colocaFinalFila(Fila *fila){
	fila->tras->prox = fila->frente;
	fila->frente = fila->frente->prox;
	fila->tras = fila->tras->prox;
	fila->tras->prox = NULL;
}

void resolucao(Fila *fila, char *c, int *n){
	*c = fila->frente->tipo;
	*n = fila->frente->dobras;
}

void desenfileira(Fila *fila){
	Celula *aux;
	aux = fila->frente;
	fila->frente=fila->frente->prox;
	free(aux);
}