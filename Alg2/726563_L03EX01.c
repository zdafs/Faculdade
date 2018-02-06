/* ================================================================== *
	Universidade Federal de Sao Carlos - UFSCar, Sorocaba

	Disciplina: Algoritmos e Programação 2
	Prof. Tiago A. Almeida

	Lista 03 - Exercício 01 - Coeficiente Binomial

	Instrucoes
	----------

	Este arquivo contem o codigo que auxiliara no desenvolvimento do
	exercicio. Voce precisara completar as partes requisitadas.

* ================================================================== *
	Dados do aluno:

	RA: 726563
	Nome: Lucca La Fonte Albuquerque Carvalho

* ================================================================== */

#include<stdio.h>
double binomio(int n, int k, int diff, double vet[]);
double div(int n);
int main()
{
	int n, k;
	double vet[3];
	vet[0]=0;
	scanf("%d", &n);
	scanf("%d", &k);
	printf("%.0lf\n", binomio(n, k, (n-k), vet));
	return(0);
}
double binomio(int n, int k, int diff, double vet[])
{
	vet[0]++;
	if((n==0&&k==0&&diff==0)||(n==k&&diff==0)||(n==diff&&k==0))
	{
		return(1);
	}
	else if(n==k)
	{
		vet[1]=div(diff);  	
		return(1);
	}
	else if(n==diff)
	{
		vet[1]=div(k);
		return(1);
	}
	else
	{
		vet[2]=n*(binomio(n-1, k, diff, vet));
		vet[0]--;
		if(vet[0]==1)
			return(vet[2]/vet[1]);
		else
			return(vet[2]);
	}
}

double div(int n)
{
	if(n==1)
		return(1);
	else
		return(n*div(n-1));
}
