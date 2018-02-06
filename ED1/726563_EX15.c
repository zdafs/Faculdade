/* ================================================================== *
	Universidade Federal de Sao Carlos - UFSCar, Sorocaba

	Disciplina: Estruturas de Dados 1
	Prof. Tiago A. Almeida

	Exercício 15 - Hierarquia de Guildas

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
#define MSG_ERRO_ALOC 	"Erro de alocacao!\n"
#define MSG_JA_EXISTE	"Membro ja registrado na guilda!\n"
#define MSG_NAO_EXISTE	"Membro nao registado na guilda!\n"
#define MSG_JA_TUTORA	"O tutor ja e responsavel por um membro desta funcao!\n"
#define MSG_EXP_LIDER	"Nao se pode expulsar o lider da guilda!\n"
#define MSG_EXB_MEMBRO	"Alcunha: %s\nFuncao: %s\nPoder: %d\nTutor: %s\n\n"
#define MSG_EXB_CAPITAO	"Alcunha: %s\nFuncao: %s\nPoder: %d\nCapitao do esquadrao\n\n"
#define MSG_EMPATE 		"Empate\nPoderio: %d\n"
#define MSG_GANHADOR	"Vencedor: %s\nPoderio: %d\n"
#define MSG_CPT_COMUM	"Capitao comum: %s\n"
#define MSG_OPCAO_INV 	"Opcao invalida!\n"



// === TAD E DEMAIS REGISTROS ===

typedef struct membro{
	char nome[21], func;
	int poder;
	struct membro *sup;
	struct membro *comb;
}Membro;





/* ================================================================== */
/* ===================== PREAMBULO DAS FUNCOES ====================== */
/* ================================================================== */

void iniciaGuilda(Membro *lider, char *nome, int poder);
int inserirMembroSup(Membro *lider, char *nome, int poder, char *tutor);
int inserirMembroComb(Membro *lider, char *nome, int poder, char *tutor);
void liberaMembros(Membro *lider);
void imprimeMembros(Membro *lider, char *aux);
int simularBatalha(Membro *lider);
Membro *buscar(Membro *lider, char *nome);
Membro *determinarCapitao(Membro *lider, Membro *m1, Membro *m2);
void imprimeGanhador(Membro *m1, Membro *m2);
void imprimeMenorEsquadrao(Membro *m1);
int expulsarEsquadrao(Membro *lider, Membro *m1);
void setNome(char *nome);




/* ================================================================== */
/* ======================== ROTINA PRINCIPAL ======================== */
/* ================================================================== */

int main(){

	int op, poder, i;
	Membro *lider, *p, *q;
	char nome[21], func[11], tutor[21];

	lider = (Membro *) malloc(sizeof(Membro));
	if(lider==NULL){
		printf(MSG_ERRO_ALOC);
		return(0);
	}
	setNome(nome);
	scanf("%d", &poder);
	iniciaGuilda(lider, nome, poder);
	scanf("%d", &op);
	while(op!=6){
		getchar();
		if(op==1){
			setNome(nome);
			setNome(func);
			scanf("%d", &poder);
			getchar();
			setNome(tutor);
			p = buscar(lider, nome);
			if(p==NULL){
				p = buscar(lider, tutor);
				if(p!=NULL){
					if(strcmp(func, "Suporte")==0)
						i = inserirMembroSup(p, nome, poder, tutor);
					else
						i = inserirMembroComb(p, nome, poder, tutor);
					if(i==-1)
						printf(MSG_JA_TUTORA);
					else if(i==0){
						printf(MSG_ERRO_ALOC);
						return(0);
					}
				}
				else
					printf(MSG_NAO_EXISTE);
			}
			else
				printf(MSG_JA_EXISTE);
		}

		else if(op==2){
			setNome(nome);
			p = buscar(lider, nome);
			if(p!=NULL){
				if(p==lider)
					printf(MSG_EXP_LIDER);
				else
					expulsarEsquadrao(lider, p);
			}
			else
				printf(MSG_NAO_EXISTE);
		}

		else if(op==3){
			setNome(nome);
			p = buscar(lider, nome);
			if(p!=NULL){
				strcpy(func, "Capitao");
				imprimeMembros(p, func);
			}
			else
				printf(MSG_NAO_EXISTE);
		}

		else if(op==4){
			setNome(nome);
			p = buscar(lider, nome);
			setNome(nome);
			q = buscar(lider, nome);
			if(p!=NULL && q!=NULL){
				imprimeGanhador(p, q);
			}
			else
				printf(MSG_NAO_EXISTE);
		}

		else if(op==5){
			setNome(nome);
			p = buscar(lider, nome);
			setNome(nome);
			q = buscar(lider, nome);
			if(p!=NULL && q!=NULL){
				imprimeMenorEsquadrao(determinarCapitao(lider, p, q));
			}
			else
				printf(MSG_NAO_EXISTE);
		}

		else
			printf(MSG_OPCAO_INV);
		scanf("%d", &op);
	}
	liberaMembros(lider);

	return (0);
}



/* ================================================================== */
/* ========== FUNCOES QUE DETERMINAM AS OPERACOES POSSIVEIS ========= */
/* ================================================================== */

void iniciaGuilda(Membro *lider, char *nome, int poder){
	strcpy(lider->nome, nome);
	lider->func = 'L';
	lider->poder = poder;
	lider->sup = NULL;
	lider->comb = NULL;
}

int inserirMembroSup(Membro *lider, char *nome, int poder, char *tutor){
	Membro *novo;
	if(lider->sup!=NULL)
		return(-1);
	novo = (Membro *) malloc(sizeof(Membro));
	if(novo==NULL)
		return(0);
	strcpy(novo->nome, nome);
	novo->poder = poder;
	novo->func = 'S';
	novo->sup = NULL;
	novo->comb = NULL;
	lider->sup = novo;
	return(1);
}

int inserirMembroComb(Membro *lider, char *nome, int poder, char *tutor){
	Membro *novo;
	if(lider->comb!=NULL)
		return(-1);
	novo = (Membro *) malloc(sizeof(Membro));
	if(novo==NULL)
		return(0);
	strcpy(novo->nome, nome);
	novo->poder = poder;
	novo->func = 'C';
	novo->sup = NULL;
	novo->comb = NULL;
	lider->comb = novo;
	return(1);
}

void liberaMembros(Membro *lider){
	if(lider!=NULL){
		liberaMembros(lider->sup);
		liberaMembros(lider->comb);
		free(lider);
	}
}

void imprimeMembros(Membro *lider, char *aux){
	if(lider!=NULL){
		if(lider->func=='L')
			printf(MSG_EXB_CAPITAO, lider->nome, "Lider da guilda", lider->poder);
		else if(strcmp(aux, "Capitao")==0){
			if(lider->func=='S')
				printf(MSG_EXB_CAPITAO, lider->nome, "Suporte", lider->poder);
			else
				printf(MSG_EXB_CAPITAO, lider->nome, "Combatente", lider->poder);
		}
		else if(lider->func=='S')
			printf(MSG_EXB_MEMBRO, lider->nome, "Suporte", lider->poder, aux);
		else
			printf(MSG_EXB_MEMBRO, lider->nome, "Combatente", lider->poder, aux);
		aux = lider->nome;
		imprimeMembros(lider->sup, aux);
		imprimeMembros(lider->comb, aux);
	}
}

int simularBatalha(Membro *lider){
	if(lider==NULL)
		return(0);
	return(simularBatalha(lider->sup) + simularBatalha(lider->comb) + lider->poder);
}

Membro *buscar(Membro *lider, char *nome){
	Membro *p;
	if(lider==NULL)
		return(NULL);
	if(strcmp(lider->nome, nome)==0)
		return(lider);
	p = buscar(lider->sup, nome);
	if(p==NULL)
		return(buscar(lider->comb, nome));
	return(p);
}

Membro *determinarCapitao(Membro *lider, Membro *m1, Membro *m2){
	Membro *arvSup;
	Membro *arvComb;
	if(lider==NULL)
		return(NULL);
	if(lider==m1 || lider==m2)
		return(lider);
	arvSup = determinarCapitao(lider->sup, m1, m2);
	arvComb = determinarCapitao(lider->comb, m1, m2);
	if(arvSup!=NULL && arvComb!=NULL)
		return(lider);
	if(arvSup!=NULL)
		return(arvSup);
	return(arvComb);
}

void imprimeGanhador(Membro *m1, Membro *m2){
	int i, j;
	i = simularBatalha(m1);
	j = simularBatalha(m2);
	if(i==j)
		printf(MSG_EMPATE, i);
	else if(i>j)
		printf(MSG_GANHADOR, m1->nome, i);
	else
		printf(MSG_GANHADOR, m2->nome, j);
}

void imprimeMenorEsquadrao(Membro *m1){
	printf(MSG_CPT_COMUM, m1->nome);
}

int expulsarEsquadrao(Membro *lider, Membro *m1){
	if(lider!=NULL){
		if(lider->sup==m1){
			lider->sup = NULL;
			liberaMembros(m1);
			return(0);
		}
		else if(lider->comb==m1){
			lider->comb = NULL;
			liberaMembros(m1);
			return(0);
		}
		if((expulsarEsquadrao(lider->sup, m1))!=0)
			return(expulsarEsquadrao(lider->comb, m1));
		return(0);
	}
	return(1);
}

void setNome(char *nome){
	int i=0;
	char c;
	while((c=getchar())!='\n'){
		nome[i] = c;
		i++;
	}
	nome[i] = '\0';
}