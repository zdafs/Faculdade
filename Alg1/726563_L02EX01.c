	/* ================================================================== *
    Universidade Federal de Sao Carlos - UFSCar, Sorocaba
 
    Disciplina: Algoritmos e Programação 1
    Prof. Tiago A. Almeida
 
    Lista 02 - Exercício 01 - Jokenpo
 
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
	char Gab, Mar;
	scanf("%c %c", &Gab, &Mar);
	if(Gab==Mar)
	{
		printf("%c\n", 'E');
	}
	else if(Gab=='d')
	{
		if(Mar=='p')
		{
			printf("%c\n", 'M');
		}
		else
		{
			printf("%c\n", 'G');
		}
	}
	else if(Gab=='p')
	{
		if(Mar=='d')
		{
			printf("%c\n", 'G');
		}
		else
		{
			printf("%c\n", 'M');
		}
	}
	else
	{
		if(Mar=='d')
		{
			printf("%c\n", 'M');
		}
		else
		{
			printf("%c\n", 'G');
		}
	}
	return(0);
}
