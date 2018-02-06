/* ================================================================== *
    Universidade Federal de Sao Carlos - UFSCar, Sorocaba

    Disciplina: Algoritmos e Programação 1
    Prof. Tiago A. Almeida

    Lista 04 - Exercício 03 - Sequencia de Fibonacci

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

int main(){
	int pos, i, j, entrou;
	long long f1=1, f2=1, f3=1, soma=0;
	do
	{
		scanf("%d", &pos);
	}
	while(pos<1);
	for(i=1; i<=pos-2; i++)
	{
		f3=f2+f1;
		f1=f2;
		f2=f3;
		if(f3%2!=0||f3==2)
		{
			entrou=0;
			for(j=3; j<=f3/2&&entrou==0; j+=2)
			{
				if(f3%j==0)
				{
					entrou++;
				}
			}
			if(entrou==0)
			{
				soma=soma+f3;
			}
		}
	}
	printf("%lld\n", f3);
	printf("%lld\n", soma);			

	return (0);
}
