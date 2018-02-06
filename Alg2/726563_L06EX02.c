/* ================================================================== *
   Universidade Federal de Sao Carlos - UFSCar, Sorocaba

   Disciplina: Algoritmos e Programação 2
   Prof. Tiago A. Almeida

   Lista 06 - Exercício 02 - Xadrez

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
#include <string.h>
#include <math.h>

// times
#define TIME_PRETO 	100
#define TIME_BRANCO 	101

// tipos de pecas
#define PEAO	1
#define	BISPO	2
#define	TORRE	3
#define CAVALO	4
#define RAINHA	5
#define REI	6

typedef struct peca
{
	int time, tipo;
	//int pos_l, pos_c;
}Peca;

// declaracoes das funcoes
Peca **criaTabuleiro(int l, int c);
Peca criaPeca(int time, int tipo);
void posicionaPecaNoTabuleiro(Peca **tabuleiro, Peca peca, int pos_l, int pos_c);
void executaJogada(Peca **tabuleiro, int l, int c, int time, int l_orig, int c_orig, int l_dest, int c_dest, int *jogadasValidas, int *pecasPretasDestruidas, int *pecasBrancasDestruidas);
void liberaMemoria(Peca **tabuleiro, int l);

/* ------------------------------ */
/* ROTINA PRINCIPAL - NAO ALTERAR */
/* ------------------------------ */
int main(){

   // tabuleiro para armazenar as pecas em suas posicoes
   Peca **tabuleiro; 

   // variaveis para armazenar tamanho de linhas e colunas do tabuleiro
   int l,c; 
   l = c = 0;

   // variaveis para armazenar os resultados do jogo
   int jogadasValidas, pecasPretasDestruidas, pecasBrancasDestruidas;
   jogadasValidas = pecasPretasDestruidas = pecasBrancasDestruidas = 0;

   // variaveis para fazer a jogada (linha e coluna de origem, linha e coluna de destino)
   int l_orig, c_orig, l_dest, c_dest;
   l_orig = c_orig = l_dest = c_dest = 0;
  
   // faz alocacao de memoria para o tabuleiro do jogo
   scanf("%d %d", &l, &c);
   tabuleiro = criaTabuleiro(l,c);

   int time, tipo,pos_l,pos_c; // variaveis para criar as pecas

   // le as pecas ateh encontrar o valor zero em time
   scanf("%d", &time);
   while(time != 0) {

      scanf("%d %d %d", &tipo, &pos_l, &pos_c);

      posicionaPecaNoTabuleiro(tabuleiro,criaPeca(time, tipo), pos_l, pos_c);

      scanf("%d", &time);

   }

   // le as jogadas ateh encontrar o valor zero em time
   scanf("%d", &time);
   while(time != 0) {

      scanf("%d %d %d %d", &l_orig, &c_orig, &l_dest, &c_dest);

      executaJogada(tabuleiro, l, c, time, l_orig, c_orig, l_dest, c_dest, &jogadasValidas, &pecasPretasDestruidas, &pecasBrancasDestruidas);

      scanf("%d", &time);

   }

   printf("Total de jogadas validas: %d\n",jogadasValidas);
   printf("Total de pecas pretas destruidas: %d\n",pecasPretasDestruidas);
   printf("Total de pecas brancas destruidas: %d\n",pecasBrancasDestruidas);
  
   // libera memoria do tabuleiro e das pecas
   liberaMemoria(tabuleiro,l);

   return (0);
}

/* ------------------------- */
/* IMPLEMENTACAO DAS FUNCOES */
/* ------------------------- */

Peca **criaTabuleiro(int l, int c)
{
	int i, j;
	Peca **p;
	p = (Peca **) malloc(l*sizeof(Peca *));
	for(i=0; i<l; i++)
	{
		p[i] = (Peca *) malloc(c*sizeof(Peca));
		for(j=0; j<c; j++)
			p[i][j].time=0;
	}
	return(p);
}

Peca criaPeca(int time, int tipo)
{
	Peca peca;
	peca.time=time;
	peca.tipo=tipo;
	return(peca);
}

void posicionaPecaNoTabuleiro(Peca **tabuleiro, Peca peca, int pos_l, int pos_c)
{
	tabuleiro[pos_l][pos_c]=peca;
}

void executaJogada(Peca **tabuleiro, int l, int c, int time, int l_orig, int c_orig, int l_dest, int c_dest, int *jogadasValidas, int *pecasPretasDestruidas, int *pecasBrancasDestruidas)
{
	int i, j;
	if(l_dest>=l||l_dest<0||c_dest>=c||c_dest<0)
		return;
	else if(l_dest==l_orig&&c_dest==c_orig)
		return;
	else if(tabuleiro[l_orig][c_orig].time==0)
		return;
	else if(tabuleiro[l_orig][c_orig].time!=time)
		return;
	else if(tabuleiro[l_dest][c_dest].time==time)
		return;
	else if(tabuleiro[l_orig][c_orig].tipo==TORRE)
	{
		if(l_orig==l_dest)
		{
			for(i=c_orig+1; i<c_dest; i++)
				if(tabuleiro[l_orig][i].time!=0)
					return;
			(*jogadasValidas)++;
			if(tabuleiro[l_dest][c_dest].time==TIME_PRETO)
				(*pecasPretasDestruidas)++;
			else if(tabuleiro[l_dest][c_dest].time==TIME_BRANCO)
				(*pecasBrancasDestruidas)++;
			tabuleiro[l_dest][c_dest]=tabuleiro[l_orig][c_orig];
			tabuleiro[l_orig][c_orig].time=0;
		}
		else if(c_orig==c_dest)
		{
			for(i=l_orig+1; i<l_dest; i++)
				if(tabuleiro[i][c_orig].time!=0)
					return;
			(*jogadasValidas)++;
			if(tabuleiro[l_dest][c_dest].time==TIME_PRETO)
				(*pecasPretasDestruidas)++;
			else if(tabuleiro[l_dest][c_dest].time==TIME_BRANCO)
				(*pecasBrancasDestruidas)++;
			tabuleiro[l_dest][c_dest]=tabuleiro[l_orig][c_orig];
			tabuleiro[l_orig][c_orig].time=0;
		}
		return;
	}
	else if(tabuleiro[l_orig][c_orig].tipo==BISPO)
	{
		if((l_orig-c_orig)==(l_dest-c_dest))
		{
			if(l_orig>l_dest)
			{
				for(i=l_orig-1, j=c_orig-1; i>l_dest&&j>c_dest; i--, j--)
					if(tabuleiro[i][j].time!=0)
						return;
			}
			else
			{
				for(i=l_orig+1, j=c_orig+1; i<l_dest&&j<c_dest; i++, j++)
					if(tabuleiro[i][j].time!=0)
						return;
			}
			(*jogadasValidas)++;
			if(tabuleiro[l_dest][c_dest].time==TIME_PRETO)
				(*pecasPretasDestruidas)++;
			else if(tabuleiro[l_dest][c_dest].time==TIME_BRANCO)
				(*pecasBrancasDestruidas)++;
			tabuleiro[l_dest][c_dest]=tabuleiro[l_orig][c_orig];
			tabuleiro[l_orig][c_orig].time=0;
		}
		else if((l_orig+c_orig)==(l_dest+c_dest))
		{
			if(l_orig>l_dest)
			{
				for(i=l_orig-1, j=c_orig+1; i>l_dest&&j<c_dest; i--, j++)
					if(tabuleiro[i][j].time!=0)
						return;
			}
			else
			{
				for(i=l_orig+1, j=c_orig-1; i<l_dest&&j>c_dest; i++, j--)
					if(tabuleiro[i][j].time!=0)
						return;
			}
			(*jogadasValidas)++;
			if(tabuleiro[l_dest][c_dest].time==TIME_PRETO)
				(*pecasPretasDestruidas)++;
			else if(tabuleiro[l_dest][c_dest].time==TIME_BRANCO)
				(*pecasBrancasDestruidas)++;
			tabuleiro[l_dest][c_dest]=tabuleiro[l_orig][c_orig];
			tabuleiro[l_orig][c_orig].time=0;
		}
		return;
	}
	else if(tabuleiro[l_orig][c_orig].tipo==CAVALO)
	{
		if((l_orig+2==l_dest&&c_orig+1==c_dest)||(l_orig+2==l_dest&&c_orig-1==c_dest)||(l_orig-2==l_dest&&c_orig+1==c_dest)||
		   (l_orig-2==l_dest&&c_orig-1==c_dest)||(l_orig+1==l_dest&&c_orig+2==c_dest)||(l_orig-1==l_dest&&c_orig+2==c_dest)||
		   (l_orig+1==l_dest&&c_orig-2==c_dest)||(l_orig-1==l_dest&&c_orig-2==c_dest))
		{
			(*jogadasValidas)++;
			if(tabuleiro[l_dest][c_dest].time==TIME_PRETO)
				(*pecasPretasDestruidas)++;
			else if(tabuleiro[l_dest][c_dest].time==TIME_BRANCO)
				(*pecasBrancasDestruidas)++;
			tabuleiro[l_dest][c_dest]=tabuleiro[l_orig][c_orig];
			tabuleiro[l_orig][c_orig].time=0;
		}
		return;
	}
	else if(tabuleiro[l_orig][c_orig].tipo==PEAO)
	{
		if(((l_orig+1==l_dest&&c_orig==c_dest)||(l_orig-1==l_dest&&c_orig==c_dest))&&tabuleiro[l_dest][c_dest].time==0)
		{
			(*jogadasValidas)++;
			tabuleiro[l_dest][c_dest]=tabuleiro[l_orig][c_orig];
			tabuleiro[l_orig][c_orig].time=0;
		}
		else if(((l_orig+1==l_dest&&c_orig+1==c_dest)||(l_orig+1==l_dest&&c_orig-1==c_dest)||(l_orig-1==l_dest&&c_orig+1==c_dest)||
			 (l_orig-1==l_dest&&c_orig-1==c_dest))&&tabuleiro[l_dest][c_dest].time!=0)
		{
			(*jogadasValidas)++;
			if(tabuleiro[l_dest][c_dest].time==TIME_PRETO)
				(*pecasPretasDestruidas)++;
			else if(tabuleiro[l_dest][c_dest].time==TIME_BRANCO)
				(*pecasBrancasDestruidas)++;
			tabuleiro[l_dest][c_dest]=tabuleiro[l_orig][c_orig];
			tabuleiro[l_orig][c_orig].time=0;
		}
		return;
	}
	else if(tabuleiro[l_orig][c_orig].tipo==REI)
	{
		if((l_orig+1==l_dest&&c_orig==c_dest)||(l_orig+1==l_dest&&c_orig+1==c_dest)||(l_orig==l_dest&&c_orig+1==c_dest)||
		   (l_orig-1==l_dest&&c_orig+1==c_dest)||(l_orig-1==l_dest&&c_orig==c_dest)||(l_orig-1==l_dest&&c_orig-1==c_dest)||
		   (l_orig==l_dest&&c_orig-1==c_dest)||(l_orig+1==l_dest&&c_orig-1==c_dest))
		{
			(*jogadasValidas)++;
			if(tabuleiro[l_dest][c_dest].time==TIME_PRETO)
				(*pecasPretasDestruidas)++;
			else if(tabuleiro[l_dest][c_dest].time==TIME_BRANCO)
				(*pecasBrancasDestruidas)++;
			tabuleiro[l_dest][c_dest]=tabuleiro[l_orig][c_orig];
			tabuleiro[l_orig][c_orig].time=0;
		}
		return;
	}
	else if(tabuleiro[l_orig][c_orig].tipo==RAINHA)
	{
		if(l_orig==l_dest)
		{
			for(i=c_orig+1; i<c_dest; i++)
				if(tabuleiro[l_orig][i].time!=0)
					return;
			(*jogadasValidas)++;
			if(tabuleiro[l_dest][c_dest].time==TIME_PRETO)
				(*pecasPretasDestruidas)++;
			else if(tabuleiro[l_dest][c_dest].time==TIME_BRANCO)
				(*pecasBrancasDestruidas)++;
			tabuleiro[l_dest][c_dest]=tabuleiro[l_orig][c_orig];
			tabuleiro[l_orig][c_orig].time=0;
		}
		else if(c_orig==c_dest)
		{
			for(i=l_orig+1; i<l_dest; i++)
				if(tabuleiro[i][c_orig].time!=0)
					return;
			(*jogadasValidas)++;
			if(tabuleiro[l_dest][c_dest].time==TIME_PRETO)
				(*pecasPretasDestruidas)++;
			else if(tabuleiro[l_dest][c_dest].time==TIME_BRANCO)
				(*pecasBrancasDestruidas)++;
			tabuleiro[l_dest][c_dest]=tabuleiro[l_orig][c_orig];
			tabuleiro[l_orig][c_orig].time=0;
		}
		else if((l_orig-c_orig)==(l_dest-c_dest))
		{
			if(l_orig>l_dest)
			{
				for(i=l_orig-1, j=c_orig-1; i>l_dest&&j>c_dest; i--, j--)
					if(tabuleiro[i][j].time!=0)
						return;
			}
			else
			{
				for(i=l_orig+1, j=c_orig+1; i<l_dest&&j<c_dest; i++, j++)
					if(tabuleiro[i][j].time!=0)
						return;
			}
			(*jogadasValidas)++;
			if(tabuleiro[l_dest][c_dest].time==TIME_PRETO)
				(*pecasPretasDestruidas)++;
			else if(tabuleiro[l_dest][c_dest].time==TIME_BRANCO)
				(*pecasBrancasDestruidas)++;
			tabuleiro[l_dest][c_dest]=tabuleiro[l_orig][c_orig];
			tabuleiro[l_orig][c_orig].time=0;
		}
		else if((l_orig+c_orig)==(l_dest+c_dest))
		{
			if(l_orig>l_dest)
			{
				for(i=l_orig-1, j=c_orig+1; i>l_dest&&j<c_dest; i--, j++)
					if(tabuleiro[i][j].time!=0)
						return;
			}
			else
			{
				for(i=l_orig+1, j=c_orig-1; i<l_dest&&j>c_dest; i++, j--)
					if(tabuleiro[i][j].time!=0)
						return;
			}
			(*jogadasValidas)++;
			if(tabuleiro[l_dest][c_dest].time==TIME_PRETO)
				(*pecasPretasDestruidas)++;
			else if(tabuleiro[l_dest][c_dest].time==TIME_BRANCO)
				(*pecasBrancasDestruidas)++;
			tabuleiro[l_dest][c_dest]=tabuleiro[l_orig][c_orig];
			tabuleiro[l_orig][c_orig].time=0;
		}
		return;
	}
}
void liberaMemoria(Peca **tabuleiro, int l)
{
	int i;
	for(i=0; i<l; i++)
	{
		free(tabuleiro[i]);
	}
	free(tabuleiro);
}
