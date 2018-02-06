/* ================================================================== *
	Universidade Federal de Sao Carlos - UFSCar, Sorocaba

	Disciplina: Algoritmos e Programação 1
	Prof. Tiago A. Almeida

	Lista 05 - Exercício 05 - Polinomios

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
#include <math.h>

#define SAIR      0
#define SOMA      1
#define SUBTRACAO 2
#define RESOLVER  3


//Estrutura que corresponde a um polinômio no formato ax² + bx + c.
typedef struct polinomio
{
	int a;
	int b;
	int c;
}Polinomio;


/* ================================================================== */
/* ======================== ROTINA PRINCIPAL ======================== */
/* ================================================================== */

int main()
{
	int opcao;
	Polinomio Px, Qx, Rx; // Polinomios de entrada (P e Q) e de saída (R)
	/* <<< DECLARE MAIS VARIAVEIS SE FOR NECESSARIO >>> */
	float r1, r2, aux;
	float delta;
	scanf("%d", &opcao);

	while (opcao != SAIR)
	{
		switch (opcao)
		{
			case SOMA:
				
				scanf("%d %d %d", &Px.a, &Px.b, &Px.c);
				scanf("%d %d %d", &Qx.a, &Qx.b, &Qx.c);
				Rx.a=Px.a+Qx.a;
				Rx.b=Px.b+Qx.b;
				Rx.c=Px.c+Qx.c;
				printf("%dx2", Rx.a);
				if(Rx.b>=0)
				{
					printf("+%dx", Rx.b);
				}
				else
				{
					printf("%dx", Rx.b);
				}
				if(Rx.c>=0)
				{
					printf("+%d\n", Rx.c);
				}
				else
				{
					printf("%d\n", Rx.c);
				}

			break;
				

			case SUBTRACAO:
			
				scanf("%d %d %d", &Px.a, &Px.b, &Px.c);
				scanf("%d %d %d", &Qx.a, &Qx.b, &Qx.c);
				Rx.a=Px.a-Qx.a;
				Rx.b=Px.b-Qx.b;
				Rx.c=Px.c-Qx.c;
				printf("%dx2", Rx.a);
				if(Rx.b>=0)
				{
					printf("+%dx", Rx.b);
				}
				else
				{
					printf("%dx", Rx.b);
				}
				if(Rx.c>=0)
				{
					printf("+%d\n", Rx.c);
				}
				else
				{
					printf("%d\n", Rx.c);
				}

			break;


			case RESOLVER:
			
				scanf("%d %d %d", &Px.a, &Px.b, &Px.c);
				delta=pow(Px.b,2)-(4*Px.a*Px.c);
				if(delta<0)
				{
					printf("nao existem raizes\n");
				}
				else if(delta==0)
				{
					r1=(-Px.b)/(2*Px.a);
					printf("%.2f\n", r1);
				}
				else
				{
					r1=(-Px.b+sqrt(delta))/(2*Px.a);
					r2=(-Px.b-sqrt(delta))/(2*Px.a);
					if(r2>r1)
					{
						aux=r1;
						r1=r2;
						r2=aux;
					}
					printf("%.2f\n", r1);
					printf("%.2f\n", r2);
				}

			break;

		}

		scanf("%d", &opcao);
	}

	return (0);
}
