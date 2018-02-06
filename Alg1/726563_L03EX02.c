/* ================================================================== *
	Universidade Federal de Sao Carlos - UFSCar, Sorocaba

	Disciplina: Algoritmos e Programação 1
	Prof. Tiago A. Almeida

	Lista 03 - Exercício 02 - Anos Bissextos

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

//Definindo a frase de erro
#define FRASE_ERRO "Erro: O primeiro ano deve ser menor que o segundo.\n" 

/* ================================================================== */
/* ======================== ROTINA PRINCIPAL ======================== */
/* ================================================================== */

int main(){
	int ano1, ano2, qtde_bissextos;
	do
	{
		scanf("%d", &ano1);
		scanf("%d", &ano2);
		if(ano1+ano2!=0)
		{
			if(ano1>ano2)
			{
				printf(FRASE_ERRO);
			}
			else
			{
				qtde_bissextos=0;
				do
				{
					if(ano1%4==0)
					{
						if(ano1%100==0)
						{
							if(ano1%400==0)
							{
								printf("%d ", ano1);
								qtde_bissextos++;
							}
						}
						else
						{
							printf("%d ", ano1);
							qtde_bissextos++;
						}
					}	
					ano1++;
				}
				while(ano1<=ano2);
				printf("\n");
				printf("%d\n", qtde_bissextos);
			}
		}
	}
	while(ano1>ano2 || (ano1+ano2)!=0);
	return (0);
}	
