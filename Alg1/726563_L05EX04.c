/* ================================================================== *
    Universidade Federal de Sao Carlos - UFSCar, Sorocaba

    Disciplina: Algoritmos e Programação 1
    Prof. Tiago A. Almeida

    Lista 05 - Exercício 04 - Calculadora de números complexos

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


//Definindo a frase de opção inválida
#define FRASE_OPCAO_INVALIDA "Erro: Opção inválida!\n"

//Valores de controle
#define FALSE   0
#define TRUE    1

//Estrutura para armazenar os números complexos.
typedef struct complexo
{
	float a;
	float b;
}Complexo;

/* ================================================================== */
/* ======================== ROTINA PRINCIPAL ======================== */
/* ================================================================== */

int main () {
	int opcao; //opção desejada do menu 

	Complexo num1,   //primeiro número complexo
		 num2,   //segundo número complexo
                 result; //resultado das operações
    /* <<< DECLARE MAIS VARIAVEIS SE FOR NECESSARIO >>> */             
	
	scanf("%f", &num1.a);
	scanf("%f", &num1.b);
	scanf("%f", &num2.a);
	scanf("%f", &num2.b);
	do
	{
		scanf("%d", &opcao);
		switch(opcao)
		{
			case 1:
				result.a=num1.a+num2.a;
				result.b=num1.b+num2.b;
				if(result.b>=0)
				{
					printf("%.2f+%.2fi\n", result.a, result.b);
				}
				else
				{
					printf("%.2f%.2fi\n", result.a, result.b);
				}
				break;
			case 2:
				result.a=num1.a-num2.a;
				result.b=num1.b-num2.b;
				if(result.b>=0)
				{
					printf("%.2f+%.2fi\n", result.a, result.b);
				}
				else
				{
					printf("%.2f%.2fi\n", result.a, result.b);
				}
				break;
			case 3:
				result.a=(num1.a*num2.a)-(num1.b*num2.b);
				result.b=(num1.a*num2.b)+(num1.b*num2.a);
				if(result.b>=0)
				{
					printf("%.2f+%.2fi\n", result.a, result.b);
				}
				else
				{
					printf("%.2f%.2fi\n", result.a, result.b);
				}
				break;
			case 4:
				scanf("%f", &num1.a);
				scanf("%f", &num1.b);
				scanf("%f", &num2.a);	
				scanf("%f", &num2.b);
				break;
			case 5:
				break;
			default:
				printf(FRASE_OPCAO_INVALIDA);
				break;
		}
	}
	while(opcao!=5);
	return 0;       
} 
