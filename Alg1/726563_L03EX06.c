/* ================================================================== *
    Universidade Federal de Sao Carlos - UFSCar, Sorocaba

    Disciplina: Algoritmos e Programação 1
    Prof. Tiago A. Almeida

    Lista 03 - Exercício 06 - Criptografia

    Instrucoes
    ----------

    Este arquivo contem o codigo que auxiliara no desenvolvimento do
    exercicio. Voce precisara completar as partes requisitadas.

* ================================================================== *
    Dados do aluno:

    RA: Lucca La Fonte Albuquerque Carvalho
    Nome: 726563

* ================================================================== */

#include <stdio.h>
//#include <math.h>

int main() {    
	long long num;
	int dig, i, entrou;
	do
	{
		scanf("%lld", &num);
		entrou = 0;
		i=1000000000;
		if(num!=0)
		{
			do
			{
				dig = (num/i) - ((num/(i*10))*10);
				i=i/10;
				if(dig==0&&entrou!=0)
				{
					printf("Q");
				}
				else if(dig==1)
				{
					printf("R");
					entrou++;
				}
				else if(dig==2)
				{
					printf("S");
					entrou++;
				}
				else if(dig==3)
				{
					printf("W");
					entrou++;
				}
				else if(dig==4)
				{
					printf("US");
					entrou++;
				}
				else if(dig==5)
				{
					printf("QSR");
					entrou++;
				}
				else if(dig==6)
				{
					printf("QSX");
					entrou++;
				}
				else if(dig==7)
				{
					printf("QUQV");
					entrou++;
				}
				else if(dig==8)
				{
					printf("QSTQU");
					entrou++;
				}
				else if(dig==9)
				{
					printf("QYYSWT");
					entrou++;
				}
			}
			while(i>=1);
			printf("\n\n");
		}
	}
	while(num!=0);
	
	

	return (0);
}
