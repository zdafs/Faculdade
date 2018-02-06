/* ================================================================== *
	Universidade Federal de Sao Carlos - UFSCar, Sorocaba

	Disciplina: Estruturas de Dados 1
	Prof. Tiago A. Almeida

	Exercício 12 - Gerenciador Estratégico

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

// Frases pre-definidas
#define MSG_ERRO_ALOC 		"Erro de alocacao!\n"
#define MSG_NAO_EXISTE_POS	"Posicao inexistente!\n"
#define MSG_NAO_EXISTE_LC 	"Linha/coluna inexistente!\n"
#define MSG_NAO_EXISTE_MT	"Matriz inexistente!\n"
#define MSG_INCOMPATIVEL	"Dimensoes incompativeis!\n"
#define MSG_OPCAO_INV 		"Opcao invalida!\n"



// === TAD E DEMAIS REGISTROS ===
// <<< NAO ALTERAR >>>

typedef float TItem;

typedef struct SCelula *TApontador;

typedef struct SCelula
{
	int Linha, Coluna;
	TItem Item;
	TApontador Abaixo, Direita;
}
TCelula;

typedef struct
{
	TApontador Cabeca;
	int NLinhas, NColunas;
}
TMatriz;



/* ================================================================== */
/* ===================== PREAMBULO DAS FUNCOES ====================== */
/* ================================================================== */

int iniciaMatrizes(TMatriz *matrizes);
void liberaMatriz(TMatriz *matriz);
int iniciaMatriz(TMatriz *matriz, int l, int c);
int insereMatriz(TMatriz *matriz, int i, int j, float d);
int somaLinhas(TMatriz matriz_1, TMatriz matriz_2, TMatriz *matriz_Dst, int i1, int i2, int iDst);
int somaColunas(TMatriz matriz_1, TMatriz matriz_2, TMatriz *matriz_Dst, int i1, int i2, int iDst);
int buscaMaximo(char c, TMatriz matriz, int i, float *n);
int buscaMinimo(char c, TMatriz matriz, int i, float *n);
int somaMatrizes(TMatriz matriz_1, TMatriz matriz_2, TMatriz *matriz_Dst);
int transporMatriz(TMatriz matriz, TMatriz *matriz_Dst);
int exibePosicao(TMatriz matriz, int i, int j, float *n);
int exibe(char c, TMatriz matriz, int i);
void liberaMatrizes(TMatriz *matrizes);




/* ================================================================== */
/* ======================== ROTINA PRINCIPAL ======================== */
/* ================================================================== */

int main(){
	int op, l, c, m, aux, aux2, aux3, aux4;
	TMatriz matrizes[4];
	float d;
	char p;

	if(!iniciaMatrizes(matrizes)){
		printf(MSG_ERRO_ALOC);
		return(0);
	}
	scanf("%d", &op);
	while(op!=11){
		if(op==1){
			scanf("%d %d %d", &m, &l, &c);
			if(!iniciaMatriz(&(matrizes[m-1]), l, c)){
				printf(MSG_ERRO_ALOC);
				return(0);
			}
			scanf("%d %d", &l, &c);
			while(l!=0 || c!=0){
				scanf("%f", &d);
				aux = insereMatriz(&(matrizes[m-1]), l, c, d);
				if(aux==-1)
					printf(MSG_NAO_EXISTE_POS);
				else if(aux==0){
					printf(MSG_ERRO_ALOC);
					return(0);
				}
				scanf("%d %d", &l, &c);
			}
		}

		else if(op==2){
			scanf("%d %d %d", &m, &l, &c);
			scanf("%f", &d);
			aux = insereMatriz(&(matrizes[m-1]), l, c, d);
			if(aux==-2)
				printf(MSG_NAO_EXISTE_MT);
			else if(aux==-1)
				printf(MSG_NAO_EXISTE_POS);
			else if(aux==0){
				printf(MSG_ERRO_ALOC);
				return(0);
			}
		}

		else if(op==3){
			scanf("%d %d", &m, &l);
			scanf("%d %d", &aux, &c);
			scanf("%d %d", &aux2, &aux3);
			aux4 = somaLinhas(matrizes[m-1], matrizes[aux-1], &(matrizes[aux2-1]), l, c, aux3);
			if(aux4==-3)
				printf(MSG_NAO_EXISTE_MT);
			else if(aux4==-2)
				printf(MSG_NAO_EXISTE_LC);
			else if(aux4==-1)
				printf(MSG_INCOMPATIVEL);
			else if(aux4==0){
				printf(MSG_ERRO_ALOC);
				return(0);
			}
		}

		else if(op==4){
			scanf("%d %d", &m, &l);
			scanf("%d %d", &aux, &c);
			scanf("%d %d", &aux2, &aux3);
			aux4 = somaColunas(matrizes[m-1], matrizes[aux-1], &(matrizes[aux2-1]), l, c, aux3);
			if(aux4==-3)
				printf(MSG_NAO_EXISTE_MT);
			else if(aux4==-2)
				printf(MSG_NAO_EXISTE_LC);
			else if(aux4==-1)
				printf(MSG_INCOMPATIVEL);
			else if(aux4==0){
				printf(MSG_ERRO_ALOC);
				return(0);
			}
		}

		else if(op==5){
			scanf("%d %c %d", &m, &p, &l);
			aux = buscaMaximo(p, matrizes[m-1], l, &d);
			if(aux==-2)
				printf(MSG_NAO_EXISTE_MT);
			else if(aux==-1)
				printf(MSG_NAO_EXISTE_LC);
			else
				printf("%.2f\n", d);
		}

		else if(op==6){
			scanf("%d %c %d", &m, &p, &l);
			aux = buscaMinimo(p, matrizes[m-1], l, &d);
			if(aux==-2)
				printf(MSG_NAO_EXISTE_MT);
			else if(aux==-1)
				printf(MSG_NAO_EXISTE_LC);
			else
				printf("%.2f\n", d);
		}

		else if(op==7){
			scanf("%d %d %d", &m, &l, &c);
			aux = somaMatrizes(matrizes[m-1], matrizes[l-1], &(matrizes[c-1]));
			if(aux==-2)
				printf(MSG_NAO_EXISTE_MT);
			else if(aux==-1)
				printf(MSG_INCOMPATIVEL);
			else if(aux==0){
				printf(MSG_ERRO_ALOC);
				return(0);
			}
		}

		else if(op==8){
			scanf("%d %d", &m, &l);
			aux = transporMatriz(matrizes[m-1], &(matrizes[l-1]));
			if(aux==-1)
				printf(MSG_NAO_EXISTE_MT);
			else if(aux==0){
				printf(MSG_ERRO_ALOC);
				return(0);
			}
		}

		else if(op==9){
			scanf("%d %d %d", &m, &l, &c);
			aux = exibePosicao(matrizes[m-1], l, c, &d);
			if(aux==-2)
				printf(MSG_NAO_EXISTE_MT);
			else if(aux==-1)
				printf(MSG_NAO_EXISTE_POS);
			else
				printf("%.2f\n", d);
		}

		else if(op==10){
			scanf("%d %c %d", &m, &p, &l);
			aux = exibe(p, matrizes[m-1], l);
			if(aux==-2)
				printf(MSG_NAO_EXISTE_MT);
			else if(aux==-1)
				printf(MSG_NAO_EXISTE_LC);
		}

		else if(op!=11)
			printf(MSG_OPCAO_INV);
		scanf("%d", &op);
	}
	liberaMatrizes(matrizes);

	return (0);
}



/* ================================================================== */
/* ========== FUNCOES QUE DETERMINAM AS OPERACOES POSSIVEIS ========= */
/* ================================================================== */

int iniciaMatrizes(TMatriz *matrizes){
	int i;

	for(i=0; i<4; i++){
		matrizes[i].Cabeca = (TApontador) malloc(sizeof(TCelula));
		if(matrizes[i].Cabeca==NULL)
			return(0);
		matrizes[i].NLinhas = 0;
		matrizes[i].NColunas = 0;
		matrizes[i].Cabeca->Abaixo = NULL;
		matrizes[i].Cabeca->Direita = NULL;
	}
	return(1);
}

void liberaMatriz(TMatriz *matriz){
	TApontador aux, aux2;

	for(aux=matriz->Cabeca->Abaixo; aux!=NULL; aux=matriz->Cabeca->Abaixo){
		matriz->Cabeca->Abaixo = aux->Abaixo;
		for(aux2=aux; aux2!=NULL; aux2=aux){
			aux = aux->Direita;
			free(aux2);
		}
	}
	for(aux=matriz->Cabeca->Direita; aux!=NULL; aux=matriz->Cabeca->Direita){
		matriz->Cabeca->Direita = aux->Direita;
		free(aux);
	}
	matriz->NLinhas = 0;
	matriz->NColunas = 0;
}

int iniciaMatriz(TMatriz *matriz, int l, int c){
	int i;
	TApontador aux;

	liberaMatriz(matriz);
	matriz->NLinhas = l;
	matriz->NColunas = c;
	for(i=1, aux=matriz->Cabeca; i<=matriz->NLinhas; i++){
		aux->Abaixo = (TApontador) malloc(sizeof(TCelula));
		if(aux->Abaixo==NULL)
			return(0);
		aux=aux->Abaixo;
		aux->Direita = NULL;
		aux->Linha = i;
		aux->Coluna = 0;
	}
	aux->Abaixo = NULL;
	for(i=1, aux=matriz->Cabeca; i<=matriz->NColunas; i++){
		aux->Direita = (TApontador) malloc(sizeof(TCelula));
		if(aux->Direita==NULL)
			return(0);
		aux=aux->Direita;
		aux->Abaixo = NULL;
		aux->Linha = 0;
		aux->Coluna = i;
	}
	aux->Direita = NULL;
	return(1);
}

int insereMatriz(TMatriz *matriz, int i, int j, float d){
	TApontador aux, p;

	if(matriz->NLinhas==0)
		return(-2);
	if(i<=0 || i>matriz->NLinhas || j<=0 || j>matriz->NColunas)
		return(-1);
	p = matriz->Cabeca->Abaixo;
	while(p->Linha!=i)
		p = p->Abaixo;
	while(p->Direita!=NULL && p->Direita->Coluna<j)
		p = p->Direita;
	if(p->Direita!=NULL && p->Direita->Coluna==j){
		p->Direita->Item = d;
		return(1);
	}	
	aux = (TApontador) malloc(sizeof(TCelula));
	if(aux==NULL)
		return(0);
	aux->Linha = i;
	aux->Coluna = j;
	aux->Item = d;
	aux->Direita = p->Direita;
	p->Direita = aux;
	p = matriz->Cabeca->Direita;
	while(p->Coluna!=j)
		p = p->Direita;
	while(p->Abaixo!=NULL && p->Abaixo->Linha<i)
		p = p->Abaixo;
	aux->Abaixo = p->Abaixo;
	p->Abaixo = aux;
	return(1);
}

int somaLinhas(TMatriz matriz_1, TMatriz matriz_2, TMatriz *matriz_Dst, int i1, int i2, int iDst){
	TApontador p, q, r;

	if(matriz_1.NLinhas==0 || matriz_2.NLinhas==0 || matriz_Dst->NLinhas==0)
		return(-3);
	if(i1<=0 || i1>matriz_1.NLinhas || i2<=0 || i2>matriz_2.NLinhas || iDst<=0 || iDst>matriz_Dst->NLinhas)
		return(-2);
	if(matriz_1.NColunas!=matriz_2.NColunas || matriz_1.NColunas!=matriz_Dst->NColunas)
		return(-1);
	if(!((matriz_1.Cabeca==matriz_Dst->Cabeca && i1==iDst) || (matriz_2.Cabeca==matriz_Dst->Cabeca && i2==iDst))){
		p = matriz_Dst->Cabeca->Abaixo;
		while(p->Linha!=iDst)
			p = p->Abaixo;
		for(q=p->Direita, r=matriz_Dst->Cabeca->Direita; q!=NULL; q=p->Direita){
			p->Direita = q->Direita;
			while(r->Coluna!=q->Coluna)
				r = r->Direita;
			while(r->Abaixo!=q)
				r = r->Abaixo;
			r->Abaixo = q->Abaixo;
			free(q);
		}
	}
	p = matriz_1.Cabeca->Abaixo;
	while(p->Linha!=i1)
		p = p->Abaixo;
	q = matriz_2.Cabeca->Abaixo;
	while(q->Linha!=i2)
		q = q->Abaixo;
	for(p=p->Direita, q=q->Direita; p!=NULL || q!=NULL;){
		if(q==NULL || (p!=NULL && p->Coluna<q->Coluna)){
			if(insereMatriz(matriz_Dst, iDst, p->Coluna, p->Item)==0)
				return(0);
			p = p->Direita;
		}
		else if(p==NULL || q->Coluna<p->Coluna){
			if(insereMatriz(matriz_Dst, iDst, q->Coluna, q->Item)==0)
				return(0);
			q = q->Direita;
		}
		else{
			if((q->Item + p->Item)!=0){
				if(insereMatriz(matriz_Dst, iDst, p->Coluna, (q->Item + p->Item))==0)
					return(0);
			}
			p = p->Direita;
			q = q->Direita;	
		}
	}
	return(1);
}

int somaColunas(TMatriz matriz_1, TMatriz matriz_2, TMatriz *matriz_Dst, int i1, int i2, int iDst){
	TApontador p, q, r;

	if(matriz_1.NLinhas==0 || matriz_2.NLinhas==0 || matriz_Dst->NLinhas==0)
		return(-3);
	if(i1<=0 || i1>matriz_1.NColunas || i2<=0 || i2>matriz_2.NColunas || iDst<=0 || iDst>matriz_Dst->NColunas)
		return(-2);
	if(matriz_1.NLinhas!=matriz_2.NLinhas || matriz_1.NLinhas!=matriz_Dst->NLinhas)
		return(-1);
	if(!((matriz_1.Cabeca==matriz_Dst->Cabeca && i1==iDst) || (matriz_2.Cabeca==matriz_Dst->Cabeca && i2==iDst))){
		p = matriz_Dst->Cabeca->Direita;
		while(p->Coluna!=iDst)
			p = p->Direita;
		for(q=p->Abaixo, r=matriz_Dst->Cabeca->Abaixo; q!=NULL; q=p->Abaixo){
			p->Abaixo = q->Abaixo;
			while(r->Linha!=q->Linha)
				r = r->Abaixo;
			while(r->Direita!=q)
				r = r->Direita;
			r->Direita = q->Direita;
			free(q);
		}
	}
	p = matriz_1.Cabeca->Direita;
	while(p->Coluna!=i1)
		p = p->Direita;
	q = matriz_2.Cabeca->Direita;
	while(q->Coluna!=i2)
		q = q->Direita;
	for(p=p->Abaixo, q=q->Abaixo; p!=NULL || q!=NULL;){
		if(q==NULL || (p!=NULL && p->Linha<q->Linha)){
			if(insereMatriz(matriz_Dst, p->Linha, iDst, p->Item)==0)
				return(0);
			p = p->Abaixo;
		}
		else if(p==NULL || q->Linha<p->Linha){
			if(insereMatriz(matriz_Dst, q->Linha, iDst, q->Item)==0)
				return(0);
			q = q->Abaixo;
		}
		else{
			if((q->Item + p->Item)!=0){
				if(insereMatriz(matriz_Dst, p->Linha, iDst, (q->Item + p->Item))==0)
					return(0);
			}
			p = p->Abaixo;
			q = q->Abaixo;	
		}
	}
	return(1);
}

int buscaMaximo(char c, TMatriz matriz, int i, float *n){
	TApontador p;
	int cont=1;

	if(matriz.NLinhas==0)
		return(-2);
	if(c=='L'){
		if(i<=0 || i>matriz.NLinhas)
			return(-1);
		p = matriz.Cabeca->Abaixo;
		while(p->Linha!=i)
			p = p->Abaixo;
		if(p->Direita==NULL){
			*n = 0;
			return(1);
		}
		for(*n=p->Direita->Item, p=p->Direita->Direita; p!=NULL; p=p->Direita, cont++){
			if(p->Item>*n)
				*n = p->Item;
		}
		if(cont<matriz.NColunas && *n<0)
			*n = 0;
	}
	if(c=='C'){
		if(i<=0 || i>matriz.NColunas)
			return(-1);
		p = matriz.Cabeca->Direita;
		while(p->Coluna!=i)
			p = p->Direita;
		if(p->Abaixo==NULL){
			*n = 0;
			return(1);
		}
		for(*n=p->Abaixo->Item, p=p->Abaixo->Abaixo; p!=NULL; p=p->Abaixo, cont++){
			if(p->Item>*n)
				*n = p->Item;
		}
		if(cont<matriz.NLinhas && *n<0)
			*n = 0;
	}
	return(1);
}

int buscaMinimo(char c, TMatriz matriz, int i, float *n){
	TApontador p;
	int cont=1;

	if(matriz.NLinhas==0)
		return(-2);
	if(c=='L'){
		if(i<=0 || i>matriz.NLinhas)
			return(-1);
		p = matriz.Cabeca->Abaixo;
		while(p->Linha!=i)
			p = p->Abaixo;
		if(p->Direita==NULL){
			*n = 0;
			return(1);
		}
		for(*n=p->Direita->Item, p=p->Direita->Direita; p!=NULL; p=p->Direita, cont++){
			if(p->Item<*n)
				*n = p->Item;
		}
		if(cont<matriz.NColunas && *n>0)
			*n = 0;
	}
	if(c=='C'){
		if(i<=0 || i>matriz.NColunas)
			return(-1);
		p = matriz.Cabeca->Direita;
		while(p->Coluna!=i)
			p = p->Direita;
		if(p->Abaixo==NULL){
			*n = 0;
			return(1);
		}
		for(*n=p->Abaixo->Item, p=p->Abaixo->Abaixo; p!=NULL; p=p->Abaixo, cont++){
			if(p->Item<*n)
				*n = p->Item;
		}
		if(cont<matriz.NLinhas && *n>0)
			*n = 0;
	}
	return(1);
}

int somaMatrizes(TMatriz matriz_1, TMatriz matriz_2, TMatriz *matriz_Dst){
	int i;

	if(matriz_1.NLinhas==0 || matriz_2.NLinhas==0)
		return(-2);
	if(matriz_1.NLinhas!=matriz_2.NLinhas || matriz_1.NColunas!=matriz_2.NColunas)
		return(-1);
	if((matriz_1.Cabeca!=matriz_Dst->Cabeca) && (matriz_2.Cabeca!=matriz_Dst->Cabeca)){
		if(iniciaMatriz(matriz_Dst, matriz_1.NLinhas, matriz_1.NColunas)==0)
			return(0);
	}
	for(i=1; i<=matriz_Dst->NLinhas; i++){
		if(somaLinhas(matriz_1, matriz_2, matriz_Dst, i, i, i)==0)
			return(0);
	}
	return(1);
}

int transporMatriz(TMatriz matriz, TMatriz *matriz_Dst){
	TApontador p, q;
	TMatriz aux;

	if(matriz.NLinhas==0)
		return(-1);
	aux.Cabeca = (TApontador) malloc(sizeof(TCelula));
	aux.Cabeca->Abaixo = NULL;
	aux.Cabeca->Direita = NULL;
	if(iniciaMatriz(&aux, matriz.NColunas, matriz.NLinhas)==0)
		return(0);
	for(p=matriz.Cabeca->Abaixo; p!=NULL; p=p->Abaixo){
		for(q=p->Direita; q!=NULL; q=q->Direita){
			if(insereMatriz(&aux, q->Coluna, q->Linha, q->Item)==0)
				return(0);
		}
	}
	liberaMatriz(matriz_Dst);
	free(matriz_Dst->Cabeca);
	matriz_Dst->Cabeca = aux.Cabeca;
	matriz_Dst->NLinhas = aux.NLinhas;
	matriz_Dst->NColunas = aux.NColunas;
	return(1);
}

int exibePosicao(TMatriz matriz, int i, int j, float *n){
	TApontador p;

	if(matriz.NLinhas==0)
		return(-2);
	if(i<=0 || i>matriz.NLinhas || j<=0 || j>matriz.NColunas)
		return(-1);
	p=matriz.Cabeca->Abaixo;
	while(p->Linha!=i)
		p=p->Abaixo;
	for(p=p->Direita; p!=NULL && p->Coluna<=j; p=p->Direita){
		if(p->Coluna==j){
			*n = p->Item;
			return(0);
		}
	}
	*n = 0;
	return(0);
}

int exibe(char c, TMatriz matriz, int i){
	TApontador p;

	if(matriz.NLinhas==0)
		return(-2);
	if(c=='L'){
		if(i<=0 || i>matriz.NLinhas)
			return(-1);
		p = matriz.Cabeca->Abaixo;
		while(p->Linha!=i)
			p = p->Abaixo;
		for(i=1, p=p->Direita; i<matriz.NColunas; i++){
			if(p!=NULL && p->Coluna==i){
				printf("%.2f ", p->Item);
				p = p->Direita;
			}
			else
				printf("0.00 ");
		}
		if(p!=NULL && p->Coluna==i)
			printf("%.2f\n", p->Item);
		else
			printf("0.00\n");
	}
	if(c=='C'){
		if(i<=0 || i>matriz.NColunas)
			return(-1);
		p = matriz.Cabeca->Direita;
		while(p->Coluna!=i)
			p = p->Direita;
		for(i=1, p=p->Abaixo; i<matriz.NLinhas; i++){
			if(p!=NULL && p->Linha==i){
				printf("%.2f ", p->Item);
				p = p->Abaixo;
			}
			else
				printf("0.00 ");
		}
		if(p!=NULL && p->Linha==i)
			printf("%.2f\n", p->Item);
		else
			printf("0.00\n");
	}
	return(1);
}

void liberaMatrizes(TMatriz *matrizes){
	int i;

	for(i=0; i<4; i++){
		liberaMatriz(&(matrizes[i]));
		free(matrizes[i].Cabeca);
	}
}