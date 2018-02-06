/* ================================================================== *
	Universidade Federal de Sao Carlos - UFSCar, Sorocaba

	Disciplina: Algoritmos e Programação 1
	Prof. Tiago A. Almeida

	Lista 07 - Exercício 04 - Ponto de sela

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

//Ordem maxima da matriz. 
#define ORDEM_MAXIMA  50

//Resposta para a operacao que verifica 
//se a matriz apresenta pontos de sela.
#define FALSO           0
#define VERDADEIRO      1

//Resposta a serem impressas na tela
#define RESP_SIM	"sim\n"
#define RESP_NAO	"nao\n"



int main() {


	int matriz[ORDEM_MAXIMA][ORDEM_MAXIMA], n, entrou, ja_passou, i, j, k;
	do
	{	
		scanf("%d", &n);
	}
	while(n<1||n>ORDEM_MAXIMA);
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			scanf("%d", &matriz[i][j]);
		}
	}
	for(j=0,ja_passou=FALSO;j<n;j++)
	{
		for(i=0;i<n;i++)
		{
			for(k=0,entrou=0;k<n;k++)
			{
				if(k==j)
				{
					k++;
				}
				if(matriz[i][j]<matriz[i][k])
				{
					entrou++;
				}
			}
			if(entrou==0)
			{
				for(k=0,entrou=0;k<n;k++)
				{
					if(k==i)
					{
						k++;
					}
					if(matriz[i][j]>matriz[k][j])
					{
						entrou++;
					}
				}
				if(entrou==0)
				{
					if(ja_passou==FALSO)
					{
						printf(RESP_SIM);
						ja_passou=VERDADEIRO;
					}
					printf("%d %d\n", i+1, j+1);
				}
			}
			else if(entrou==n-1)
			{
				for(k=0,entrou=0;k<n;k++)
				{
					if(k==i)
					{
						k++;
					}
					if(matriz[i][j]<matriz[k][j])
					{
						entrou++;
					}
				}
				if(entrou==0)
				{
					if(ja_passou==FALSO)
					{
						printf(RESP_SIM);
						ja_passou=VERDADEIRO;
					}
					printf("%d %d\n", i+1, j+1);
				}
			}
		}
	}
	if(ja_passou==FALSO)
	{
		printf(RESP_NAO);
	}

	return(0);
}
