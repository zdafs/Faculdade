/* ================================================================== *
    Universidade Federal de Sao Carlos - UFSCar, Sorocaba
 
    Disciplina: Algoritmos e Programação 1
    Prof. Tiago A. Almeida
 
    Lista 02 - Exercício 06 - Montadora de Carros
 
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
	char modelo, cor, direcao;
	double valor_un=0, valor_prod=0;
	int qtde;
	scanf("%c %c %c %d", &modelo, &cor, &direcao, &qtde);
	if(modelo=='p')
	{
		valor_un=70000;
	}
	else
	{
		valor_un=102000;
	}
	if(cor=='b')
	{
		valor_un=valor_un+1300;
	}
	else if(cor=='p')
	{
		valor_un=valor_un+2400;
	}
	else
	{
		valor_un=valor_un+3100;
	}
	if(direcao=='s')
	{
		valor_un=valor_un+2000;
	}
	if(modelo=='p'&&direcao=='n')
	{
		valor_un=valor_un*1.05;
	}
	else if(modelo=='c'&&cor=='v')
	{
		valor_un=valor_un*1.08;
	}
	else if(cor=='p'&&direcao=='s')
	{
		valor_un=valor_un*1.1;
	}
	else
	{
		valor_un=valor_un*1.15;
	}
	valor_prod=valor_un*qtde;
	printf("%.2lf\n", valor_un);
	printf("%.2lf\n", valor_prod);
	return(0);
}
