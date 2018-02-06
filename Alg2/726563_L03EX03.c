/* ================================================================== *
	Universidade Federal de Sao Carlos - UFSCar, Sorocaba

	Disciplina: Algoritmos e Programação 2
	Prof. Tiago A. Almeida

	Lista 03 - Exercício 03 - Conversao Binaria

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
void binario(int n);
int main()
{
	int n;
	scanf("%d", &n);
	binario(n);
	printf("\n");
	return(0);
}

void binario(int n)
{
	if(n==1)
	{
		printf("1");
	}
	else if(n==0)
	{
		printf("0");
	}
	else if(n%2==0)
	{
		n=n/2;
		binario(n);
		printf("0");
	}
	else
	{
		n=n/2;
		binario(n);
		printf("1");
	}
}	
