/* ================================================================== *
	Universidade Federal de Sao Carlos - UFSCar, Sorocaba

	Disciplina: Algoritmos e Programação 1
	Prof. Tiago A. Almeida

	Lista 03 - Exercício 03 - Método de Heron

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


int main()
{
	int n1, n2, aux, i;
	float k;
	scanf("%d %d", &n1, &n2);
	if(n1>n2)
	{
		aux=n1;
		n1=n2;
		n2=aux;
	}
	while(n1<=n2)
	{
		i=0;
		k=1;
		while(i<10)
		{
			k=(k+(n1/k))/2;
			i++;
		}
		printf("%.2f\n", k);
		n1++;
	}
	return (0);
}
