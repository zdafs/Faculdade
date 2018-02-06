/* ================================================================== *
    Universidade Federal de Sao Carlos - UFSCar, Sorocaba
 
    Disciplina: Algoritmos e Programação 1
    Prof. Tiago A. Almeida
 
    Lista 01 - Exercício 05 - Areas e volume do cilindro
 
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

#define PI 3.14159

int main()
{
	float raio, altura, Al, Ab, At, v;
	scanf("%f", &raio);
	scanf("%f", &altura);
	Al=2*PI*raio*altura;
	Ab=PI*raio*raio;
	At=2*PI*raio*(altura+raio);
	v=Ab*altura;
	printf("%.2f\n", Al);
	printf("%.2f\n", Ab);
	printf("%.2f\n", At);
	printf("%.2f\n", v);
	return(0);
}
