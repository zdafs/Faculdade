/* ================================================================== *
	Universidade Federal de Sao Carlos - UFSCar, Sorocaba

	Disciplina: Algoritmos e Programação 2
	Prof. Tiago A. Almeida

	Lista 01 - Exercício 06 - TEY Code

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
#include <math.h>


typedef struct Key{
	long long n, c, s, b;
}key;

int main(void) {
    key senha;

	int i, eh_primo=0;
	scanf("%lld", &senha.c);
	scanf("%lld", &senha.n);
	for(senha.b=3; eh_primo==0; senha.b=senha.b+2)
	{
		eh_primo=1;
		for(i=3; i<senha.b&&eh_primo==1; i=i+2)
		{
			if(senha.b%i==0)
			{
				eh_primo=0;
			}
		}
		if(eh_primo)
		{
			if((senha.c*senha.b)%((long long)pow(senha.b,2)+senha.n)==0)
			{
				senha.s=(senha.c*senha.b)/((long long)pow(senha.b,2)+senha.n);
			}
			else
			{
				eh_primo=0;
			}
		}
	}
	printf("%lld", senha.s);
					
    
    return (0);
}
