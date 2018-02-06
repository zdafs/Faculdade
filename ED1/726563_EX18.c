/* ================================================================== *
	Universidade Federal de Sao Carlos - UFSCar, Sorocaba

	Disciplina: Estruturas de Dados 1
	Prof. Tiago A. Almeida

	Exercício 18 - Árvore AVL (Adelson-Velskii e Landis)

	Instrucoes
	----------

	Este arquivo contem o codigo que auxiliara no desenvolvimento do
	exercicio. Voce precisara completar as funcoes requisitadas.

	Voce nao podera criar nenhuma outra funcao. Complete apenas as
	rotinas	fornecidas.
 * ================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 70
#define TRUE 1
#define FALSE 0

// Frase exibida quando houver erro nas operacoes
#define FRASE_ERROALOCACAO	"Erro de alocacao!\n"
#define FRASE_OPCAO_INVAL	"Opcao invalida!\n"
#define FRASE_ERRO_AVL		"Erro: a arvore nao possui estrutura de AVL!!!\n"

// Definicao do elemento da árvore
typedef struct {
	int ra;
	char nome[MAX];
} Aluno;

// Definicao do nó
typedef struct no {
	Aluno info;
	struct no *esq, *dir;
	short int bal;
} No;

// Definicao da Arvore
typedef No *Arvore;

/* ================================================================== */
/* ===================== PREAMBULO DAS FUNCOES ====================== */
/* ================================================================== */

/* Verifica se a árvore informada tem a estrutura de uma árvore AVL.
 * NÃO ALTERAR!!! */
int verificaAVL(Arvore t, int *alt);

/* Inicializa a arvore. */
void inicArvore(Arvore *t);

/* Caso exista um aluno com o RA informado, returne TRUE e atribua
 * em 'a' os dados do aluno. Caso contrário retorne FALSE. */
int consultaAluno(Arvore t, int ra, Aluno *a);

/* Imprime a arvore sob a forma de uma árvore 'deitada'. */
void imprimeArvore(Arvore t, int nivel);

/* Devolve o número de nós da arvore 't'. */
int numeroNosArvore(Arvore t);

/* Devolve a altura da arvore 't'. */
int alturaArvore(Arvore t); 

/* Executa um percurso inordem na arvore, imprimindo todos os elementos. */
void percorreArvore(Arvore t);

/* Libera todos os nós da arvore apontada por 't', bem 
como todas as cadeias que guardam os nomes. */
void liberaArvore(Arvore *t);

/** Rotinas para rotação na árvore **/

/* Rotação simples RR - Rotação Direira */
void RR(Arvore *t);

/* Rotação simples LL - Rotação Esquerda */
void LL(Arvore *t);

/* Rotação dupla RL - Rotação Direita-Esquerda*/
void RL(Arvore *t);

/* Rotação dupla LR - Rotação Esquerda-Direita */
void LR(Arvore *t);

/** Rotinas auxiliares para inserção. */

/* Faz os ajustes quando a sub-árvore esquerda cresceu. */
void SubArvoreEsquerdaCresceu(Arvore *t, int *cresceu);

/* Faz os ajustes quando a sub-árvore direita cresceu. */
void SubArvoreDireitaCresceu(Arvore *t, int *cresceu);

/* Insere o aluno informado como parâmetro caso não exista aluno
 * com o mesmo RA e devolve TRUE. Caso contrário devolve FALSE.
 * A variável 'cresceu' recebe TRUE se a há aumento da altura da
 * árvore e FALSE, caso contrário. */
int insereAlunoAVL(Arvore *t, Aluno a, int *cresceu);

/* Cria um novo nó, com registro do aluno 'a'. */
Arvore novoNo(Aluno a);


/* ================================================================== */
/* ======================== ROTINA PRINCIPAL ======================== */
/* ================================================================== */

int main() {
	int info, ra, nivel;
	Aluno aluno;
	Arvore t;
	char acao;
	int cresceu;
	int altura;

	inicArvore(&t);

	//Enquanto opcao for diferente de SAIR
	do { 

		//Pergunta a opcao que o usuario deseja realizar
		scanf("\n%c", &acao);

		//Verifica qual opcao foi escolhida.
		switch (acao) {

			case 'i':
				scanf("%d %[^\n]",&aluno.ra, aluno.nome);

				info = insereAlunoAVL(&t, aluno, &cresceu);
				if (info == FALSE)
					printf("RA %d ja estava presente na arvore de dados.\n", aluno.ra);
				
				else if(info == -1){
					printf(FRASE_ERROALOCACAO);
					exit(0);
				}
				break;
			
			case 'c':
				scanf("%d",&ra);
				if (consultaAluno(t, ra, &aluno))
					printf("%d, %s\n", aluno.ra, aluno.nome);
				else
					printf("RA %d nao encontrado na arvore de dados.\n", ra);
				break;

			case 'd':
				nivel = 0;
				imprimeArvore(t, nivel);
				break;

			case 'n':
				printf("Numero de nos na arvore de dados: %d.\n", numeroNosArvore(t));
				break;

			case 'a':
				printf("Altura da arvore de dados: %d.\n", alturaArvore(t));
				break;

			case 'p':
				percorreArvore(t);
				break;

			case 'x':
				if (!verificaAVL(t, &altura))
					printf(FRASE_ERRO_AVL);

				liberaArvore(&t);
				break;

			default:
				printf(FRASE_OPCAO_INVAL);
				break;
		}

	} while (acao != 'x');

	printf("Processamento finalizado\n");
	return 0;
}

/* ================================================================== */
/* ========== FUNCOES QUE DETERMINAM AS OPERACOES POSSIVEIS ========= */
/* ================================================================== */

/* Verifica se a árvore informada tem a estrutura de uma árvore AVL.
 * NÃO ALTERAR!!! */
int verificaAVL(Arvore t, int *alt) {
	int altEsq, altDir, bal, resEsq, resDir;
	
	if (t == NULL) {
		*alt = 0;
		return TRUE;
	}

	resEsq = verificaAVL(t->esq, &altEsq);
	resDir = verificaAVL(t->dir, &altDir);
	bal = t->bal;

	*alt = ((altEsq<altDir) ? altDir : altEsq) + 1;

	return ((bal >= -1) && (bal <= +1)
		&& (bal == (altDir-altEsq))
		&& resEsq && resDir);
}

/* Inicializa a arvore. */
void inicArvore(Arvore *t) {
	*t = NULL;
}

/* Caso exista um aluno com o RA informado, returne TRUE e atribua
 * em 'a' os dados do aluno. Caso contrário retorne FALSE. */
int consultaAluno(Arvore t, int ra, Aluno *a) {
	if(t==NULL)
		return(FALSE);
	if(t->info.ra>ra)
		return(consultaAluno(t->esq, ra, a));
	if(t->info.ra<ra)
		return(consultaAluno(t->dir, ra, a));
	*a = t->info;
	return(TRUE);
}

/* Imprime a arvore sob a forma de uma árvore 'deitada'. */
void imprimeArvore(Arvore t, int nivel){
	int i = 0;

	if(t!=NULL){
		while(i<nivel){
			printf("\t");
			i++;
		}
		printf("%d, %s\n", t->info.ra, t->info.nome);
		imprimeArvore(t->esq, nivel+1);
		imprimeArvore(t->dir, nivel+1);
	}
}

/* Devolve o número de nós da arvore 't'. */
int numeroNosArvore(Arvore t){
	if(t==NULL)
		return(0);
	return(numeroNosArvore(t->esq) + numeroNosArvore(t->dir) + 1);
}

/* Devolve a altura da arvore 't'. */
int alturaArvore(Arvore t){
	int hEsq, hDir;

	if(t==NULL)
		return(0);
	hEsq = alturaArvore(t->esq);
	hDir = alturaArvore(t->dir);
	if(hEsq>hDir)
		return(hEsq + 1);
	return(hDir + 1);
}

/* Executa um percurso inordem na arvore, imprimindo todos os elementos. */
void percorreArvore(Arvore t){
	if(t!=NULL){
		percorreArvore(t->esq);
		printf("%d, %s\n", t->info.ra, t->info.nome);
		percorreArvore(t->dir);
	}
}

/* Libera todos os nós da arvore apontada por 't', bem 
como todas as cadeias que guardam os nomes. */
void liberaArvore(Arvore *t){
	if((*t)!=NULL){
		liberaArvore(&((*t)->esq));
		liberaArvore(&((*t)->dir));
		free(*t);
	}
}

/** Rotinas para rotação na árvore **/

/* Rotação simples RR - Rotação Direira */
void RR(Arvore *t) {
	Arvore aux;

	aux = (*t)->dir;
	(*t)->dir = aux->esq;
	aux->esq = (*t);
	aux->bal = 0;
	(*t)->bal = 0;
	(*t) = aux;
}

/* Rotação simples LL - Rotação Esquerda */
void LL(Arvore *t) {
	Arvore aux;

	aux = (*t)->esq;
	(*t)->esq = aux->dir;
	aux->dir = (*t);
	aux->bal = 0;
	(*t)->bal = 0;
	(*t) = aux;
}

/* Rotação dupla RL - Rotação Direita-Esquerda*/
void RL(Arvore *t) {
	Arvore aux, aux2;

	aux = (*t)->dir;
	aux2 = aux->esq;
	aux->esq = aux2->dir;
	aux2->dir = aux;
	(*t)->dir = aux2->esq;
	aux2->esq = (*t);
	if(aux2->bal==1)
		(*t)->bal = -1;
	else
		(*t)->bal = 0;
	if(aux2->bal==-1)
		aux->bal = 1;
	else
		aux->bal = 0;
	aux2->bal = 0;
	(*t) = aux2;
}

/* Rotação dupla LR - Rotação Esquerda-Direita*/
void LR(Arvore *t) {
	Arvore aux, aux2;

	aux = (*t)->esq;
	aux2 = aux->dir;
	aux->dir = aux2->esq;
	aux2->esq = aux;
	(*t)->esq = aux2->dir;
	aux2->dir = (*t);
	if(aux2->bal==-1)
		(*t)->bal = 1;
	else
		(*t)->bal = 0;
	if(aux2->bal==1)
		aux->bal = -1;
	else
		aux->bal = 0;
	aux2->bal = 0;
	(*t) = aux2;
}

/** Rotinas auxiliares para inserção. */

/* Cria um novo nó, com registro do aluno 'a'. */
Arvore novoNo(Aluno a) {
	Arvore t = (Arvore) malloc(sizeof(No));
	if(t==NULL)
		return(NULL);
	t->info = a;
	t->esq = NULL;
	t->dir = NULL;
	t->bal = 0;
	return(t);
}

/* Faz os ajustes quando a sub-árvore esquerda cresceu. */
void SubArvoreEsquerdaCresceu(Arvore *t, int *cresceu) {
	if((*cresceu)==TRUE){
		if((*t)->bal==1){
			(*t)->bal = 0;
			(*cresceu) = FALSE;
		}
		else if((*t)->bal==0){
			(*t)->bal = -1;
			(*cresceu) = TRUE;
		}
		else{
			if((*t)->esq->bal<0){
				LL(t);
				(*cresceu) = FALSE;
			}
			else if((*t)->esq->bal>0){
				LR(t);
				(*cresceu) = FALSE;
			}
		}
	}
}

/* Faz os ajustes quando a sub-árvore direita cresceu. */
void SubArvoreDireitaCresceu(Arvore *t, int *cresceu) {
	if((*cresceu)==TRUE){
		if((*t)->bal==-1){
			(*t)->bal = 0;
			(*cresceu) = FALSE;
		}
		else if((*t)->bal==0){
			(*t)->bal = 1;
			(*cresceu) = TRUE;
		}
		else{
			if((*t)->dir->bal>0){
				RR(t);
				(*cresceu) = FALSE;
			}
			else if((*t)->dir->bal<0){
				RL(t);
				(*cresceu) = FALSE;
			}
		}
	}
}

/* Insere o aluno informado como parâmetro caso não exista aluno
 * com o mesmo RA e devolve TRUE. Caso contrário devolve FALSE.
 * A variável 'cresceu' recebe TRUE se a há aumento da altura da
 * árvore e FALSE, caso contrário. */
int insereAlunoAVL(Arvore *t, Aluno a, int *cresceu) {
	if((*t)==NULL){
		(*t) = novoNo(a);
		if((*t)==NULL)
			return(-1);
		*cresceu = TRUE;
		return(TRUE);
	}
	if((*t)->info.ra>a.ra){
		if(insereAlunoAVL(&((*t)->esq), a, cresceu)==TRUE){
			SubArvoreEsquerdaCresceu(t, cresceu);
			return(TRUE);
		}
		return(FALSE);
	}
	if((*t)->info.ra<a.ra){
		if(insereAlunoAVL(&((*t)->dir), a, cresceu)==TRUE){
			SubArvoreDireitaCresceu(t, cresceu);
			return(TRUE);
		}
		return(FALSE);
	}
	return(FALSE);
}
