/* ================================================================== *
    Universidade Federal de Sao Carlos - UFSCar, Sorocaba
 
    Disciplina: Algoritmos e Programação 1
    Prof. Tiago A. Almeida
 
    Lista 01 - Exercício 01 - Operações Aritméticas
 
    Instrucoes
    ----------
 
    Este arquivo contem o codigo que auxiliara no desenvolvimento do
    exercicio. Voce precisara completar as partes requisitadas.
 
* ================================================================== *
    Dados do aluno:
 
    RA: 726563
    Nome: Lucca La Fonte Albuquerque Carvalho
 
* ================================================================== */
 
#include<stdio.h>
int main()
{
	int num1, num2;
	scanf("%d", &num1);
	scanf("%d", &num2);
	printf("%d\n", (num1+num2));
	printf("%d\n", (num1-num2));
	printf("%d\n", (num2-num1));
	printf("%d\n", (num1*num2));
	printf("%.2f\n", ((float)num1/num2));
	printf("%.2f\n", ((float)num2/num1));
	printf("%d\n", (num1/num2));
	printf("%d\n", (num2/num1));
	printf("%d\n", (num1%num2));
	printf("%d\n", (num2%num1));
	return(0);
}
