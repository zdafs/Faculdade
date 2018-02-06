/* ================================================================== *
    Universidade Federal de Sao Carlos - UFSCar, Sorocaba
 
    Disciplina: Algoritmos e Programação 1
    Prof. Tiago A. Almeida
 
    Lista 04 - Exercício 02 - Calculadora
 
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
	int n_oper, num, i, j;
	char oper;
	int res, aux;
	do
	{
		res=0;
		scanf("%d", &n_oper);
		if(n_oper!=0)
		{
			for(i=1; i<=n_oper; i++)
			{
				scanf("\n%c", &oper);
				if(oper=='!')
				{
					if(res==0)
					{
						res=1;
					}
					else
					{
						for(j=res-1; j>1; j--)
						{
							res=res*j;
						}
					}
				}
				else if(oper=='+')
				{
					scanf("%d", &num);
					res=res+num;
				}
				else if(oper=='-')
				{
					scanf("%d", &num);
					res=res-num;
				}
				else if(oper=='*')
				{
					scanf("%d", &num);
					res=res*num;
				}
				else if(oper=='/')
				{
					scanf("%d", &num);
					res=res/num;
				}
				else
				{
					scanf("%d", &num);
					aux=res;
					res=1;
					for(j=0; j<num; j++)
					{
						res=res*aux;
					}
				}
			}
			printf("%d\n", res);
		}
	}
	while(n_oper!=0);
	return(0);
}
