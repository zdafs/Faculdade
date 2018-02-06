/* ================================================================== *
    Universidade Federal de Sao Carlos - UFSCar, Sorocaba
 
    Disciplina: Algoritmos e Programação 1
    Prof. Tiago A. Almeida
 
    Lista 03 - Exercício 04 - Crescimento de Números
 
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
#define ELEV 1000000000
int main()
{
	int r=0;
	double i=1, d1, d2, soma, a=0, b=0;
	scanf("%lf", &a);
	scanf("%lf", &b);
	r=0;
	do
	{
		soma=ELEV/i;
		d1 = (b/soma)-(((int)(b/(soma*10)))*10);
		d2 = (a/soma)-(((int)(a/(soma*10)))*10);
		i=i*10;
		if((int)d1<(int)d2||r!=0)
		{
			r++;
			while(b<a)
			{
				b = b+soma;
				
				if(b<a)
				{
					if((int)b%3==0||(int)b%5==0)
					{
						printf("%.0lf\n", b);
					}
				}
			}
			b = b-soma;
		}
	}
	while(soma>1);
	return(0);
}
