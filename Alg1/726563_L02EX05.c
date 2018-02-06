/* ================================================================== *
    Universidade Federal de Sao Carlos - UFSCar, Sorocaba
 
    Disciplina: Algoritmos e Programação 1
    Prof. Tiago A. Almeida
 
    Lista 02 - Exercício 05 - Geometria
 
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
	int n, l1, l2, l3, l4;
	scanf("%d", &n);
	if(n==3)
	{
		scanf("%d %d %d", &l1, &l2, &l3);
		printf("T\n");
		if(l1==l2 && l1==l3)
		{
			printf("E\n");
		}
		else if((l1==l2&&l1!=l3)||(l1!=l2&&l1==l3)||(l2==l3&&l2!=l1))
		{
			printf("I\n");
		}
		else
		{
			printf("S\n");
		}
	}
	else
	{
		scanf("%d %d %d %d", &l1, &l2, &l3, &l4);
		printf("Q\n");
		if(l1==l2 && l1==l3 && l1==l4)
		{
			printf("Q\n");
		}
		else
		{
			printf("R\n");
		}
	}
	return(0);
}
