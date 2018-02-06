/* ================================================================== *
    Universidade Federal de Sao Carlos - UFSCar, Sorocaba

    Disciplina: Algoritmos e Programação 1
    Prof. Tiago A. Almeida

    Lista 03 - Exercício 05 - Numero minimo

    Instrucoes
    ----------

    Este arquivo contem o codigo que auxiliara no desenvolvimento do
    exercicio. Voce precisara completar as partes requisitadas.

* ================================================================== *
    Dados do aluno:

    RA: 
    Nome: 

* ================================================================== */

#include <stdio.h>
#define ELEV 1000000000
int main() {    
	double num, digito, div;
	int n=1, i;
	do
	{
		scanf("%lf", &num);
		if(num!=0)
		{
			while(n<=9)
			{
				i=1;
				do
				{			
					div = ELEV/i;
					digito = (num/div)-(((int)(num/(div*10)))*10);
					i=i*10;
					if((int)digito==n)
					{
						printf("%d", n);
					}
				}
				while(div>1);
				n++;
			}
			printf("\n\n");
			n=1;
		}
	}
	while(num!=0);
	

	return (0);
}
