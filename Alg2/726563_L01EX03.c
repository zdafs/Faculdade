/* ================================================================== *
	Universidade Federal de Sao Carlos - UFSCar, Sorocaba

	Disciplina: Algoritmos e Programação 2
	Prof. Tiago A. Almeida

	Lista 01 - Exercício 03 - Conjectura de Goldbach

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
	int m, n, i, j, k, l, eh_primo;
	scanf("%d %d", &m, &n);
	for( ; m<=n; m++)
	{
		if(m%2==0)
		{
			if(m==2)
			{
				m=4;
			}
			for(i=2, eh_primo=0; eh_primo==0; i++)
			{
				eh_primo=1;
				for(j=2; j<i&&eh_primo==1; j++)
				{
					if(i%j==0)
					{
						eh_primo=0;
					}
				}
				if(eh_primo)
				{
					for(k=2; k<m-i&&eh_primo==1; k++)
					{
						if((m-i)%k==0)
						{
							eh_primo=0;
						}
					}
				}
				if(eh_primo)
				{
					l=m-i;
					printf("%d = %d + %d\n", m, i, l);
				}
			}
		}
	}
	return(0);
}
