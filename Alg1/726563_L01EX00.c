/* ================================================================== *
    Universidade Federal de Sao Carlos - UFSCar, Sorocaba
 
    Disciplina: Algoritmos e Programação 1
    Prof. Tiago A. Almeida
 
    Lista 01 - Exercício 00 - Nota minima na P2 para atingir media M
 
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
	float media, P1, P2, lista;
	int peso1, peso2, pesoLista;
	scanf("%f", &media);
	scanf("%f %d", &P1, &peso1);
	scanf("%f %d", &lista, &pesoLista);
	scanf("%d", &peso2);
	P2=((media*(peso1+peso2+pesoLista)-(P1*peso1)-(lista*pesoLista)))/peso2;
	printf("%.1f\n", P2);
	return(0);
}
