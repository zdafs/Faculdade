/* ================================================================== *
    Universidade Federal de Sao Carlos - UFSCar, Sorocaba
 
    Disciplina: Algoritmos e Programação 1
    Prof. Tiago A. Almeida
 
    Lista 02 - Exercício 02 - Quadrantes
 
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
	int x, y;
	scanf("%d %d", &x, &y);
	if(x>0 && y>0)
	{
		printf("1\n");
	}
	else if(x>0 && y<0)
	{
		printf("4\n");
	}
	else if(x<0 && y>0)
	{
		printf("2\n");
	}
	else if(x<0 && y<0)
	{
		printf("3\n");
	}
	else if(x!=0 && y==0)
	{
		printf("%c\n", 'X');
	}
	else if(x==0 && y!=0)
	{
		printf("%c\n", 'Y');
	}
	else
	{
		printf("%c\n", 'O');
	}
	return(0);
}
