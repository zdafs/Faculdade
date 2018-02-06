/* ================================================================== *
  Universidade Federal de Sao Carlos - UFSCar, Sorocaba

  Disciplina: Algoritmos e Programação 1
  Prof. Tiago A. Almeida

  Lista 04 - Exercício 05 - Menor natural divisivel por 1, ..., n

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

#define TRUE  1
#define FALSE 0


int main()
{
	int n1, n2, aux, num;
	do
	{
		scanf("%d", &n1);
	}
	while(n1<=0);
	do
	{
		scanf("%d", &n2);
	}
	while(n2<=0);
	if(n1>n2)
	{
		aux=n1;
		n1=n2;
		n2=aux;
	}
	num=n2*(n2-1);
	for(aux=n1;aux<=n2;aux++)
	{
		if(num%aux!=0)
		{
			aux=n1-1;
			num++;
		}
	}
	printf("%d\n", num);
	return(0);
}
