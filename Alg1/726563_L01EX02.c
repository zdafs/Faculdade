/* ================================================================== *
    Universidade Federal de Sao Carlos - UFSCar, Sorocaba
 
    Disciplina: Algoritmos e Programação 1
    Prof. Tiago A. Almeida
 
    Lista 01 - Exercício 02 - Rendimento e Valor Total
 
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
	float deposito, juros, rendimento, valor_total;
	scanf("%f", &deposito);
	scanf("%f", &juros);
	rendimento=deposito*juros/100;
	valor_total=deposito+rendimento;
	printf("%8.2f\n", rendimento);
	printf("%8.2f\n", valor_total);
	return(0);
}
