/* ================================================================== *
    Universidade Federal de Sao Carlos - UFSCar, Sorocaba

    Disciplina: Algoritmos e Programação 1
    Prof. Tiago A. Almeida

    Lista 06 - Exercício 02 - Crivo de Eratóstenes

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
#include <math.h>

#define MAX 1000000
struct num
{
	long valor;
	int primo;
}; 
int main()
{

	struct num Num[MAX];
	long Tam, i, j;
	scanf("%ld", &Tam);
	for(i=0,j=2;i<Tam-2;i++,j++)
	{
		Num[i].valor=j;
		Num[i].primo=2;
	}
	for(i=0;i<Tam-2;i++)
	{
		if(Num[i].primo==2)
		{
			Num[i].primo=1;
			for(j=i+1;j<Tam-2;j++)
			{
				if(Num[j].valor%Num[i].valor==0)
				{
					Num[j].primo=0;
				}
			}
		}
	}
	for(i=0;i<Tam-2;i++)
	{
		if(Num[i].primo)
		{
			printf("%ld ", Num[i].valor);
		}
	}
	printf("\n");

	return (0);
}
