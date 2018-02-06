/* ================================================================== *
	Universidade Federal de Sao Carlos - UFSCar, Sorocaba

	Disciplina: Algoritmos e Programação 2
	Prof. Tiago A. Almeida

	Lista 03 - Exercício 02 - Conjectura de Collatz

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
int collatz(int n);
int main()
{
	int n;
	scanf("%d", &n);
	collatz(n);
	return(0);
}

int collatz(int n)
{
	printf("%d ", n);
	if(n==1)
	{
		return(0);
	}
	else if(n%2==0)
	{
		n=n/2;
		collatz(n);
		return(0);
	}
	else
	{
		n=(3*n)+1;
		collatz(n);
		return(0);
	}
}
