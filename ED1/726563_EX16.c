/* ================================================================== *
	Universidade Federal de Sao Carlos - UFSCar, Sorocaba

	Disciplina: Estruturas de Dados 1
	Prof. Tiago A. Almeida

	Exercício 16 - Arvore Binaria de Busca

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

#define MAX 	70
#define TRUE 	1
#define FALSE 	0

// Frase exibida quando houver erro nas operacoes
#define FRASE_ERROALOCACAO	"Erro de alocacao!\n"
#define FRASE_OPCAO_INVAL   "Opcao invalida!\n"

// Definicao do elemento da árvore
typedef struct {
	int ra;
	char nome[MAX];
} Aluno;

// Definicao do nó
typedef struct no {
	Aluno info;
	struct no *esq, *dir;
} No;

// Definicao da Arvore
typedef No *Arvore;

/* ================================================================== */
/* ===================== PREAMBULO DAS FUNCOES ====================== */
/* ================================================================== */

/* Inicializa uma arvore */
void inicArvore(Arvore *t);

/* Insere o aluno informado como parâmetro na árvore e retorna
 * TRUE. Caso já exista um aluno com o mesmo RA, não é feita a
 * inserção e retorna FALSE. Retorne -1 em caso de erro de
 * alocação.
 * IMPORTANTE: O aluno deve ser inserido em ordem crescente de ra.
 * Não se esqueça de alocar memória para o registro */
int insereAluno(Arvore *t, Aluno a);

/* Remove o aluno que possui o RA informado e retorna TRUE.
 * Retorna FALSE, caso o aluno não seja encontrado. */
int removeAluno(Arvore *t, int ra);

/* Caso exista um aluno com o RA informado, returne TRUE e atribua
 * em 'a' os dados do aluno. Caso contrário retorne FALSE. */
int consultaAluno(Arvore t, int ra, Aluno *a);

/* Imprime a arvore sob a forma de uma árvore 'deitada'. */
void imprimeArvore(Arvore t, int nivel);

/* Libera todos os nós da arvore apontada por 't', bem 
como todas as cadeias que guardam os nomes. */
void liberaArvore(Arvore *t);

/* Devolve o número de nós da arvore 't'. */
int numeroNosArvore(Arvore t);

/* Devolve a altura da arvore 't'. */
int alturaArvore(Arvore t); 

/* Executa um percurso inordem na arvore, imprimindo todos os elementos. */
void percorreArvore(Arvore t);


/* ================================================================== */
/* ======================== ROTINA PRINCIPAL ======================== */
/* ================================================================== */

int main() {
	int info, ra, nivel;
	Aluno aluno;
	Arvore t;
	char acao;

	inicArvore(&t);

	//Enquanto opcao for diferente de SAIR
	do { 

		//Pergunta a opcao que o usuario deseja realizar
		scanf("\n%c", &acao);

		//Verifica qual opcao foi escolhida.
		switch (acao) { 

			case 'i':
				scanf("%d %[^\n]\n",&aluno.ra, aluno.nome);

				info = insereAluno(&t, aluno);
				if (info == FALSE)
					printf("RA %d ja estava presente na arvore de dados.\n", aluno.ra);
				
				else if(info == -1){
					printf(FRASE_ERROALOCACAO);
					exit(0);
				}
				break;
			
			case 'r':
				scanf("%d",&ra);
				if (removeAluno(&t, ra))
					printf("Aluno removido com sucesso.\n");
				else
					printf("RA %d nao encontrado na arvore de dados.\n", ra);
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


/* Inicializa uma arvore */
void inicArvore(Arvore *t) {

	(*t) = NULL;
	
}

/* Insere o aluno informado como parâmetro na árvore e retorna
 * TRUE. Caso já exista um aluno com o mesmo RA, não é feita a
 * inserção e retorna FALSE. Retorne -1 em caso de erro de
 * alocação.
 * IMPORTANTE: O aluno deve ser inserido em ordem crescente de ra.
 * Não se esqueça de alocar memória para o registro */
int insereAluno(Arvore *t, Aluno a) {

	if((*t)==NULL){
		(*t) = (Arvore) malloc(sizeof(No));
		if((*t)==NULL)
			return(-1);
		(*t)->info = a;
		(*t)->esq = NULL;
		(*t)->dir = NULL;
		return(TRUE);
	}
	if((*t)->info.ra>a.ra)
		return(insereAluno(&((*t)->esq), a));
	if((*t)->info.ra<a.ra)
		return(insereAluno(&((*t)->dir), a));
	return(FALSE);
}

/* Remove o aluno que possui o RA informado e retorna TRUE.
 * Retorna FALSE, caso o aluno não seja encontrado. */
int removeAluno(Arvore *t, int ra) {
	Arvore *aux, p;

	if((*t)==NULL)
		return(FALSE);
	if((*t)->info.ra>ra)
		return(removeAluno(&((*t)->esq), ra));
	if((*t)->info.ra<ra)
		return(removeAluno(&((*t)->dir), ra));
	if((*t)->esq==NULL){
		p = (*t);
		(*t) = (*t)->dir;
	}
	else if((*t)->dir==NULL){
		p = (*t);
		(*t) = (*t)->esq;
	}
	else{
		aux = &((*t)->dir);
		while((*aux)->esq!=NULL)
			aux = &((*aux)->esq);
		p = (*aux);
		(*t)->info = (*aux)->info;
		(*aux) = (*aux)->dir;
	}
	free(p);
	return(TRUE);

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
	int i;

	if(t!=NULL){
		for(i=0; i<nivel; i++)
			printf("\t");
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