/* ================================================================== *
	Universidade Federal de Sao Carlos - UFSCar, Sorocaba

	Disciplina: Algoritmos e Programação 1
	Prof. Tiago A. Almeida

	Lista 07 - Exercício 03 - Quadrado mágico

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


// Ordem maxima do quadrado
#define MAX 100
#define MSG_NAO "NAO\n"
#define MSG_MAGICO "MAGICO\n"

int main() {


	int quadrado[MAX][MAX], n, i, j, k, entrou, rep, soma, somaAux;

	scanf("%d", &n);
	while(n!=0)
	{
		for(i=0;i<n;i++)
		{
			for(j=0;j<n;j++)
			{
				scanf("%d", &quadrado[i][j]);
			}
		}
		entrou=0;
		rep=0;
		for(k=1;k<=(n*n)&&rep<2;k++)
		{
			rep=0;
			for(i=0;i<n;i++)
			{
				for(j=0;j<n&&rep<2;j++)
				{
					if(quadrado[i][j]==k)
					{
						rep++;
						if(rep<2)
						{
							entrou++;
						}
					}
				}
			}
		}
		if(entrou==(n*n))
		{
			soma=0;
			for(i=0,j=0;j<n;j++)
			{
				soma=soma+quadrado[i][j];
			}
			entrou=0;
			for(i=0;i<n&&entrou==0;i++)
			{
				somaAux=0;
				for(j=0;j<n;j++)
				{
					somaAux=somaAux+quadrado[i][j];
				}
				if(soma!=somaAux)
				{
					entrou=1;
					printf(MSG_NAO);
				}
			}
			if(entrou==0)
			{
				for(j=0;j<n&&entrou==0;j++)
				{
					somaAux=0;
					for(i=0;i<n;i++)
					{
						somaAux=somaAux+quadrado[i][j];
					}
					if(soma!=somaAux)
					{
						entrou=1;
						printf(MSG_NAO);
					}
				}
				if(entrou==0)
				{
					somaAux=0;
					for(i=0,j=0;i<n&&j<n;i++,j++)
					{
						somaAux=somaAux+quadrado[i][j];
					}
					if(soma==somaAux)
					{
						somaAux=0;
						for(i=0,j=n-1;i<n&&j>=0;i++,j--)
						{
							somaAux=somaAux+quadrado[i][j];
						}
						if(soma==somaAux)
						{
							printf(MSG_MAGICO);
						}
						else
						{
							printf(MSG_NAO);
						}
					}
					else
					{
						printf(MSG_NAO);
					}
				}
			}
		}
		else
		{
			printf(MSG_NAO);
		}
		scanf("%d", &n);
	}


	return (0);
}

