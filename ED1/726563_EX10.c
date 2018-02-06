/* ================================================================== *
	Universidade Federal de Sao Carlos - UFSCar, Sorocaba

	Disciplina: Estruturas de Dados 1
	Prof. Tiago A. Almeida

	Exercício 10 - Polinomios

	Instrucoes
	----------

	Este arquivo contem o codigo que auxiliara no desenvolvimento do
	exercicio. Voce precisara completar as funcoes requisitadas.

	Voce nao podera criar nenhuma outra funcao. Complete apenas as
	rotinas	fornecidas.
 * ================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define FALSE 0
#define TRUE 1

// Operacoes que podem ser realizadas.
#define LER_POLINOMIO		1
#define APAGAR_POLINOMIO	2
#define REMOVER_TERMO		3
#define RESOLVER_POLINOMIO	4
#define IMPRIMIR_POLINOMIOS	5
#define SOMAR_POLINOMIOS	6
#define SUB_POLINOMIOS		7
#define MULT_POLINOM_CONST	8
#define SAIR				9

// Frase exibida quando houver erro nas operacoes
#define FRASE_ERROALOCACAO	"Erro de alocacao!\n"
#define FRASE_OP_INVALIDA 	"Operacao invalida!\n"
#define FRASE_EXP_INVALIDO 	"Expoente invalido!\n"
#define FRASE_P_VAZIO		" Polinomio vazio!"
#define FRASE_T_N_ENCONTRADO "Termo nao encontrado!\n"

// Definicao do elemento da lista
typedef struct {
	float coef;
	int expo;
} Termo;

// Definicao do nó
typedef struct no	{
	Termo t;
	struct no *prox;
} Node;

// Definicao do Polinomio
typedef Node *Polinomio;

/* ================================================================== */
/* ===================== PREAMBULO DAS FUNCOES ====================== */
/* ================================================================== */

/* Insere termo a termo na lista encadeada, formando um novo polinomio.
 * Caso o polinomio já exista, o mesmo é mantido e os termos são anexados. */
/* NÃO ALTERAR!!! */
int lerPolinomio(Polinomio p);

/* Imprime o termo apontado por p. */
/* NÃO ALTERAR!!! */
void imprimirTermo(Polinomio p);

/* Inicializa o polinomio. Cria o nó cabeca com expoente igual a -1.
 * Retorna (1) em caso de sucesso e (0) em caso de erro de alocação. */
int inicPolinomio(Polinomio *p);

/* Retorna (1) caso o polinomio esteja vazio (só existe o nó cabeça) e
 * (0) caso contrário. */
int polinomioVazio(Polinomio p);

/* Exibe o polinomio. Os termos sao impressos em ordem DECRESCENTE dos
 * expoentes. Retorna (1) em caso de sucesso e (0) caso o polinomio
 * esteja vazio. */
int imprimirPolinomio(Polinomio p);

/* Insere um novo termo no polinômio. Os termos são inseridos em ordem
 * CRESCENTE dos expoentes. Caso o polinômio já tenha um termo com o
 * mesmo expoente, os coeficientes devem ser somados. Retorna (1) em
 * caso de sucesso e (0) em caso de erro de alocação */
int inserirTermo(Polinomio p, Termo t);

/* Libera a memória alocada em todo o polinômio, inclusive no nó cabeça. */
void apagarPolinomio(Polinomio *p);

/* Remove do polinômio o termo enviado como argumento. Deve-se liberar a
 * memória alocada do termo removido. Retorna (1) caso o elemento seja
 * encontrado e (0) caso contrário. */
int removerTermo(Polinomio p, Termo t);

/* Dado o valor de x, retorna a solução do polinomio. Retorna (0) caso o
 * polinômio esteja vazio. */
float resolverPolinomio(Polinomio p, float x);

/* Retorna em C o resultado de A + B. */
void somarPolinomios(Polinomio a, Polinomio b, Polinomio c);

/* Retorna em C o resultado de A - B. */
void subPolinomios(Polinomio a, Polinomio b, Polinomio c);

/* Multiplica o polinômio pela constante enviada como argumento. */
void multPolinomioConst(Polinomio p, int constante);

/* ================================================================== */
/* ======================== ROTINA PRINCIPAL ======================== */
/* ================================================================== */

int main() {
	int Opcao; 	    // operacao escolhida pelo usuario
	Polinomio A,B,C;
	char labelPolinom; // rotulo do polinomio empregado nas operacoes
	Termo t;
	int constante;
	float x;
	
	// polinomio A
	if (!inicPolinomio(&A)){
		printf(FRASE_ERROALOCACAO);
		exit(1);
	}
	
	// polinomio B
	if (!inicPolinomio(&B)){
		printf(FRASE_ERROALOCACAO);
		exit(1);
	}

	// polinomio C que armazenara as operacoes de soma e subtracao
	if (!inicPolinomio(&C)){
		printf(FRASE_ERROALOCACAO);
		exit(1);
	}
	
	//Enquanto Opcao for diferente de SAIR.
	do {

		//Pergunta a Opcao que o usuario deseja realizar.
		scanf("%d", &Opcao);

		//Verifica qual Opcao foi escolhida.
		switch (Opcao) {
			
			// Opcao 1
			case LER_POLINOMIO:
				scanf("\n%c", &labelPolinom);
				if (labelPolinom == 'A') {
					if (!lerPolinomio(A)) {
						printf(FRASE_ERROALOCACAO);
						exit(1);
					}
					printf("A =");
					if (!imprimirPolinomio(A))
						printf(FRASE_P_VAZIO);
					printf("\n");
					
				} else if (labelPolinom == 'B') {
					if (!lerPolinomio(B)) {
						printf(FRASE_ERROALOCACAO);
						exit(1);
					}
					printf("B =");
					if (!imprimirPolinomio(B))
						printf(FRASE_P_VAZIO);
					printf("\n");
					
				} else
					printf(FRASE_OP_INVALIDA);
					
				break;			

			// Opcao 2
			case APAGAR_POLINOMIO:
				scanf("\n%c", &labelPolinom);
				if (labelPolinom == 'A') {
					apagarPolinomio(&A);
					if (!inicPolinomio(&A)){
						printf(FRASE_ERROALOCACAO);
						exit(1);
					}
					
				} else if (labelPolinom == 'B') {
					apagarPolinomio(&B);
					if (!inicPolinomio(&B)){
						printf(FRASE_ERROALOCACAO);
						exit(1);
					}
					
				} else
					printf(FRASE_OP_INVALIDA);
			
				break;

			// Opcao 3
			case REMOVER_TERMO:
				scanf("\n%c %d %f", &labelPolinom, &t.expo, &t.coef);
				if (labelPolinom == 'A') {
					if (t.coef < 0)
						printf(FRASE_EXP_INVALIDO);
					else
						if (!removerTermo(A, t))
							printf(FRASE_T_N_ENCONTRADO);
						else {
							printf("A =");
							if (!imprimirPolinomio(A))
								printf(FRASE_P_VAZIO);
							printf("\n");
						}
					
				} else if (labelPolinom == 'B') {
					if (t.coef < 0)
						printf(FRASE_EXP_INVALIDO);
					else
						if (!removerTermo(B, t))
							printf(FRASE_T_N_ENCONTRADO);		
						else {
							printf("B =");
							if (!imprimirPolinomio(B))
								printf(FRASE_P_VAZIO);
							printf("\n");
						}			
					
				} else
					printf(FRASE_OP_INVALIDA);
					
				break;
				
			// Opcao 4
			case RESOLVER_POLINOMIO:
				scanf("\n%c %f", &labelPolinom, &x);
				if (labelPolinom == 'A') {
					printf("A =");
					if (!imprimirPolinomio(A))
						printf(FRASE_P_VAZIO);
					printf(" = %.1f\n", resolverPolinomio(A, x));
					
				} else if (labelPolinom == 'B') {
					printf("B =");
					if (!imprimirPolinomio(B))
						printf(FRASE_P_VAZIO);
					printf(" = %.1f\n", resolverPolinomio(B, x));
					
				} else
					printf(FRASE_OP_INVALIDA);

				break;
				
			// Opcao 5
			case IMPRIMIR_POLINOMIOS:
				printf("A =");
				if (!imprimirPolinomio(A))
					printf(FRASE_P_VAZIO);
				printf("\n");
					
				printf("B =");
				if (!imprimirPolinomio(B))
					printf(FRASE_P_VAZIO);
				printf("\n");
				
				break;

			// Opcao 6
			case SOMAR_POLINOMIOS:
				// limpando polinomio C, que armazenara o resultado
				apagarPolinomio(&C);
				if (!inicPolinomio(&C)) {
					printf(FRASE_ERROALOCACAO);
					exit(1);
				}
				
				somarPolinomios(A, B, C);
				printf("A + B =");
				if (!imprimirPolinomio(C))
					printf(FRASE_P_VAZIO);
				printf("\n");
				
				break;

			// Opcao 7
			case SUB_POLINOMIOS:
				// limpando polinomio C, que armazenara o resultado
				apagarPolinomio(&C);
				if (!inicPolinomio(&C)) {
					printf(FRASE_ERROALOCACAO);
					exit(1);
				}
				
				subPolinomios(A, B, C);
				printf("A - B =");
				if (!imprimirPolinomio(C))
					printf(FRASE_P_VAZIO);
				printf("\n");
				
				break;
			
			// Opcao 8
			case MULT_POLINOM_CONST:
				scanf("\n%c %d", &labelPolinom, &constante);
				if (labelPolinom == 'A') {
					multPolinomioConst(A, constante);
					printf("A =");
					if (!imprimirPolinomio(A))
						printf(FRASE_P_VAZIO);
					printf("\n");
					
				} else if (labelPolinom == 'B') {
					multPolinomioConst(B, constante);
					printf("B =");
					if (!imprimirPolinomio(B))
						printf(FRASE_P_VAZIO);
					printf("\n");
					
				} else
					printf(FRASE_OP_INVALIDA);
			
				break;

			// Opcao 9
			case SAIR:
				apagarPolinomio(&A);
				apagarPolinomio(&B);
				apagarPolinomio(&C);
				break;
		}

	} while (Opcao != SAIR);
	
	return 0;
}

/* ================================================================== */
/* ========== FUNCOES QUE DETERMINAM AS OPERACOES POSSIVEIS ========= */
/* ================================================================== */

/* Insere termo a termo na lista encadeada, formando um novo polinomio.
 * Caso o polinomio já exista, o mesmo é mantido e os termos são anexados. */
/* NÃO ALTERAR!!! */
int lerPolinomio(Polinomio p) {
	Termo t;

	scanf("%d", &t.expo);
	while (t.expo >= 0) {
		scanf("%f", &t.coef);
		if (!inserirTermo(p, t))
			return FALSE;
		scanf("%d", &t.expo);
	}

	return TRUE;
}

/* Imprime o termo apontado por p. */
/* NÃO ALTERAR!!! */
void imprimirTermo(Polinomio p) {
	if ((p->prox->t.expo != -1) && (p->t.coef > 0))
		printf(" +");
	else
		printf(" ");
		
	if (p->t.expo == 1) {
		printf("%.1fx", p->t.coef);	
	} else if (p->t.expo == 0) {
		printf("%.1f", p->t.coef);
	} else {
		printf("%.1fx^%d", p->t.coef, p->t.expo);	
	}
}

/* Inicializa o polinomio. Cria o nó cabeca com expoente igual a -1.
 * Retorna (1) em caso de sucesso e (0) em caso de erro de alocação. */
int inicPolinomio(Polinomio *p) {
	*p = (Polinomio) malloc(sizeof(Node));
	if(*p==NULL)
		return(0);
	(*p)->t.expo = -1;
	(*p)->prox = *p;
	return(1);
}

/* Retorna (1) caso o polinomio esteja vazio (só existe o nó cabeça) e
 * (0) caso contrário. */
int polinomioVazio(Polinomio p) {
	return(p->prox==p);
}

/* Exibe o polinômio. Os termos sao impressos em ordem DECRESCENTE dos
 * expoentes. Retorna (1) em caso de sucesso e (0) caso o polinomio
 * esteja vazio. */
int imprimirPolinomio(Polinomio p) {
	if(polinomioVazio(p))
		return(0);
	if(p->prox->prox->t.expo==-1)
		imprimirTermo(p->prox);
	else{
		imprimirPolinomio(p->prox);
		imprimirTermo(p->prox);
	}
	return(1);
}

/* Insere um novo termo no polinômio. Os termos são inseridos em ordem
 * CRESCENTE dos expoentes. Caso o polinômio já tenha um termo com o
 * mesmo expoente, os coeficientes devem ser somados. Retorna (1) em
 * caso de sucesso e (0) em caso de erro de alocação */
int inserirTermo(Polinomio p, Termo t) {
	Node *aux, *q;

	q = p;
	while(q->prox->t.expo!=-1 && q->prox->t.expo<t.expo)
		q = q->prox;
	if(q->prox->t.expo==t.expo){
		q->prox->t.coef = q->prox->t.coef + t.coef;
		return(1);
	}
	aux = (Node *) malloc(sizeof(Node));
	if(aux==NULL)
		return(0);
	aux->t = t;
	aux->prox = q->prox;
	q->prox = aux;
	return(1);
}

/* Apaga toda a lista encadeada, inclusive o nó cabeça. */
void apagarPolinomio(Polinomio *p) {
	Node *aux;

	for(aux=(*p)->prox; aux->t.expo!=-1; aux=*p){
		*p = aux->prox;
		free(aux);
	}
	free(*p);
}

/* Remove do polinômio o termo enviado como argumento. Deve-se liberar a
 * memória alocada do termo removido. Retorna (1) caso o elemento seja
 * encontrado e (0) caso contrário. */
int removerTermo(Polinomio p, Termo t) {
	Node *aux, *q;

	if(polinomioVazio(p))
		return(0);
	aux = p;
	while(aux->prox->t.expo!=-1 && aux->prox->t.expo<t.expo)
		aux = aux->prox;
	if(aux->prox->t.expo==t.expo){
		if(aux->prox->t.coef==t.coef){
			q = aux->prox;
			aux->prox = aux->prox->prox;
			free(q);
			return(1);
		}
	}
	return(0);
}

/* Dado o valor de x, retorna a solução do polinomio. Retorna (0) caso o
 * polinômio esteja vazio. */
float resolverPolinomio(Polinomio p, float x) {
	Node *aux;
	float r;

	if(polinomioVazio(p))
		return(0);
	for(aux=p->prox, r=0; aux->t.expo!=-1; aux=aux->prox)
		r = r + aux->t.coef*pow(x,aux->t.expo);
	return(r);
}

/* Retorna em C o resultado de A + B. */
void somarPolinomios(Polinomio a, Polinomio b, Polinomio c) {
	Node *p, *q;
	Termo aux;

	for(p=a->prox, q=b->prox; p->t.expo!=-1 || q->t.expo!=-1;){
		if(q->t.expo==-1 || (p->t.expo!=-1 && p->t.expo<q->t.expo)){
			inserirTermo(c, p->t);
			p = p->prox;
		}
		else if(p->t.expo==-1 || q->t.expo<p->t.expo){
			inserirTermo(c, q->t);
			q = q->prox;
		}
		else{
			aux.coef = p->t.coef + q->t.coef;
			aux.expo = p->t.expo;
			if(aux.coef!=0)
				inserirTermo(c, aux);
			p = p->prox;
			q = q->prox;
		}
	}
}

/* Retorna em C o resultado de A - B. */
void subPolinomios(Polinomio a, Polinomio b, Polinomio c) {
	Node *p, *q;
	Termo aux;

	for(p=a->prox, q=b->prox; p->t.expo!=-1 || q->t.expo!=-1;){
		if(q->t.expo==-1 || (p->t.expo!=-1 && p->t.expo<q->t.expo)){
			inserirTermo(c, p->t);
			p = p->prox;
		}
		else if(p->t.expo==-1 || q->t.expo<p->t.expo){
			aux.coef = -(q->t.coef);
			aux.expo = q->t.expo;
			inserirTermo(c, aux);
			q = q->prox;
		}
		else{
			aux.coef = p->t.coef - q->t.coef;
			aux.expo = p->t.expo;
			if(aux.coef!=0)
				inserirTermo(c, aux);
			p = p->prox;
			q = q->prox;
		}
	}
}

/* Multiplica o polinomio pela constante enviada como argumento. */
void multPolinomioConst(Polinomio p, int constante) {
	Node *aux;

	for(aux=p->prox; aux->t.expo!=-1; aux=aux->prox)
		aux->t.coef = constante*aux->t.coef;
}
