/* ================================================================== *
	Universidade Federal de Sao Carlos - UFSCar, Sorocaba

	Disciplina: Algoritmos e Programação 1
	Prof. Tiago A. Almeida

	Lista 04 - Exercício 01 - Brincadeira

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

// Frase padrao de saida. Use essa constante na saida do programa.
#define	SAIDA "Alice ganhou %d e Beto ganhou %d\n"
int main()
{
	int n, r, i, Alice, Beto;
	do
	{
		Alice=0;
		Beto=0;
		scanf("%d", &n);
		if(n!=0)
		{
			for(i=1; i<=n; i++)
			{	
				scanf("%d", &r);
				if(r==1)
				{
					Beto++;
				}
				else
				{
					Alice++;
				}
			}
			printf(SAIDA, Alice, Beto);
		}
	}
	while(n!=0);
	return(0);
}
