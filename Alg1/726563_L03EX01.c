/* ================================================================== *
	Universidade Federal de Sao Carlos - UFSCar, Sorocaba

	Disciplina: Algoritmos e Programação 1
	Prof. Tiago A. Almeida

	Lista 03 - Exercício 01 - Conjectura de Collatz

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
int main()
{
	int n;
	do
	{
		scanf("%d", &n);
		if(n!=0)
		{			
			printf("%d ", n);
			do
			{
				if(n%2==0)
				{
					n=n/2;
				}
				else
				{
					n=(3*n)+1;
				}
				printf("%d ", n);
			}while(n!=1);
			printf("\n");
		}
	}while(n!=0);
	return(0);
}
