/* ================================================================== *
	Universidade Federal de Sao Carlos - UFSCar, Sorocaba

	Disciplina: Algoritmos e Programação 2
	Prof. Tiago A. Almeida

	Lista 01 - Exercício 02 - Palíndromos entre m e n

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
	long m, n, aux, soma, num;
	int dig=0, i;
	scanf("%ld %ld", &m, &n);
	for( ; m<=n; m++)
	{
		aux=m;
		do
		{
			aux=aux/10;
			dig++;
		}
		while(aux!=0);
		for(aux=m,soma=0 ; dig>0; dig--)
		{
			num=aux%10;
			for(i=1; i<dig; i++)
			{
				num=num*10;
			}
			soma=soma+num;
			aux=aux/10;
		}
		if(m==soma)
		{
			printf("%ld ", m);
		}
	}
	return(0);
}	
