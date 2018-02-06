/* ================================================================== *
    Universidade Federal de Sao Carlos - UFSCar, Sorocaba
 
    Disciplina: Algoritmos e Programação 1
    Prof. Tiago A. Almeida
 
    Lista 01 - Exercício 04 - Area do setor circular
 
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

#define PI 3.141519

int main()
{
	float angulo, raio, AGraus, ARadianos;
	scanf("%f", &raio);
	scanf("%f", &angulo);
	AGraus=(PI*raio*raio*angulo)/360;
	ARadianos=(raio*raio*angulo)/2;
	printf("%.2f\n", AGraus);
	printf("%.2f\n", ARadianos);
	return(0);
}
