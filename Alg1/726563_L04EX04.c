/* ================================================================== *
	Universidade Federal de Sao Carlos - UFSCar, Sorocaba

	Disciplina: Algoritmos e Programação 1
	Prof. Tiago A. Almeida

	Lista 04 - Exercício 04 - Propriedade do 3025

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

//Definindo a frase para quando não existir nenhum número com a propriedade
#define FRASE_NAO_EXISTE "nao existe\n" 


int main()
{

	int n1, n2, aux1, aux2, entrou=0;
	scanf("%d", &n1);
	scanf("%d", &n2);
	if(n1>n2)
	{
		aux1=n1;
		n1=n2;
		n2=aux1;
	}
	for( ; n1<=n2; n1++)
	{
		aux1=n1/100;
		aux2=n1-(aux1*100);
		if(((aux1+aux2)*(aux1+aux2))==n1)
		{
			printf("%d\n", n1);
			entrou++;
		}
	}
	if(entrou==0)
	{
		printf(FRASE_NAO_EXISTE);
	}


	return 0;
}
