/* ================================================================== *
    Universidade Federal de Sao Carlos - UFSCar, Sorocaba

    Disciplina: Algoritmos e Programação 1
    Prof. Tiago A. Almeida

    Lista 05 - Exercício 06 - Retas

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

//Estrutura que armazena os dados de um ponto.
typedef struct ponto
{
	float x;
	float y;
}Ponto;

//Estrutura aninhada, armazena informações sobre um segmento de reta.
typedef struct reta
{
	Ponto p1;
	Ponto p2;
}Reta;

#define NAO_EXISTE_INTERCESSAO 		0
#define EXISTE_INTERCESSAO 			1
#define COEFICIENTE_NAO_DEFINIDO 	0
#define COEFICIENTE_DEFINIDO 		1
#define MENSAGEM_COEFICIENTE_NAO_DEFINIDO "indefinido"

int main(){
	Reta r1, r2; //Armazenam as informações de ambos os segmentos de reta.
	Ponto pontoInterseccao; //Armazena o ponto de interseccao entre os dois segmentos, se existir.
	float dx1, dx2, dy1, dy2; //Armazenam os comprimentos dos catetos dos triângulos formados pelas retas.
	float coeficiente1, coeficiente2; //Armazenam os coeficientes angulares das retas;
	float comprimento1, comprimento2; //Armazenam os comprimentos das retas.
	/* <<< DECLARE MAIS VARIAVEIS SE FOR NECESSARIO >>> */
	float aux, aux2;

	scanf("%f %f", &r1.p1.x, &r1.p1.y);
	scanf("%f %f", &r1.p2.x, &r1.p2.y);
	scanf("%f %f", &r2.p1.x, &r2.p1.y);
	scanf("%f %f", &r2.p2.x, &r2.p2.y);
	if(r1.p1.x>r1.p2.x)
	{
		aux=r1.p2.x;
		aux2=r1.p2.y;
		r1.p2.x=r1.p1.x;
		r1.p2.y=r1.p1.y;
		r1.p1.x=aux;
		r1.p1.y=aux2;
	}
	if(r2.p1.x>r2.p2.x)
	{
		aux=r2.p2.x;
		aux2=r2.p2.y;
		r2.p2.x=r2.p1.x;
		r2.p2.y=r2.p1.y;
		r2.p1.x=aux;
		r2.p1.y=aux2;
	}
	comprimento1=sqrt(((pow((r1.p2.x-r1.p1.x),2))+(pow((r1.p2.y-r1.p1.y),2))));
	comprimento2=sqrt(((pow((r2.p2.x-r2.p1.x),2))+(pow((r2.p2.y-r2.p1.y),2))));
	if((r1.p2.x-r1.p1.x)!=0&&(r2.p2.x-r2.p1.x)!=0)
	{
		coeficiente1=(r1.p2.y-r1.p1.y)/(r1.p2.x-r1.p1.x);
		coeficiente2=(r2.p2.y-r2.p1.y)/(r2.p2.x-r2.p1.x);
		printf("%.2f %.2f \n", coeficiente1, coeficiente2);
		printf("%.2f %.2f\n", comprimento1, comprimento2);
		if(coeficiente1!=coeficiente2)
		{
			pontoInterseccao.x=((coeficiente1*r1.p1.x)-(coeficiente2*r2.p1.x)-(r1.p1.y)+(r2.p1.y))/(coeficiente1-coeficiente2);
			if(pontoInterseccao.x>=r1.p1.x&&pontoInterseccao.x<=r1.p2.x)
			{
				if(pontoInterseccao.x>=r2.p1.x&&pontoInterseccao.x<=r2.p2.x)
				{
					pontoInterseccao.y=(coeficiente1*pontoInterseccao.x)-(coeficiente1*r1.p1.x)+(r1.p1.y);
					printf("%.2f %.2f\n", pontoInterseccao.x, pontoInterseccao.y);
				}
			}
		}
	}
	else
	{
		if((r1.p2.x-r1.p1.x)!=0&&(r2.p2.x-r2.p1.x)==0)
		{
			coeficiente1=(r1.p2.y-r1.p1.y)/(r1.p2.x-r1.p1.x);
			printf("%.2f indefinido\n", coeficiente1);
			printf("%.2f %.2f\n", comprimento1, comprimento2);
			pontoInterseccao.x=r2.p1.x;
			pontoInterseccao.y=(coeficiente1*pontoInterseccao.x)-(coeficiente1*r1.p1.x)+(r1.p1.y);
			if(r1.p1.y>r1.p2.y)
			{
				aux=r1.p2.y;
				r1.p2.y=r1.p1.y;
				r1.p1.y=aux;
			}
			if(r2.p1.y>r2.p2.y)
			{
				aux=r2.p2.y;
				r2.p2.y=r2.p1.y;
				r2.p1.y=aux;
			}
			if(pontoInterseccao.y>=r1.p1.y&&pontoInterseccao.y<=r1.p2.y)
			{
				if(pontoInterseccao.y>=r2.p1.y&&pontoInterseccao.y<=r2.p2.y)
				{
					printf("%.2f %.2f\n", pontoInterseccao.x, pontoInterseccao.y);
				}
			}
		}
		else if((r1.p2.x-r1.p1.x)==0&&(r2.p2.x-r2.p1.x)!=0)
		{
			coeficiente2=(r2.p2.y-r2.p1.y)/(r2.p2.x-r2.p1.x);
			printf("indefinido %.2f\n", coeficiente2);
			printf("%.2f %.2f\n", comprimento1, comprimento2);
			pontoInterseccao.x=r1.p1.x;
			pontoInterseccao.y=(coeficiente2*pontoInterseccao.x)-(coeficiente2*r2.p1.x)+(r2.p1.y);
			if(r1.p1.y>r1.p2.y)
			{
				aux=r1.p2.y;
				r1.p2.y=r1.p1.y;
				r1.p1.y=aux;
			}
			if(r2.p1.y>r2.p2.y)
			{
				aux=r2.p2.y;
				r2.p2.y=r2.p1.y;
				r2.p1.y=aux;
			}
			if(pontoInterseccao.y>=r1.p1.y&&pontoInterseccao.y<=r1.p2.y)
			{
				if(pontoInterseccao.y>=r2.p1.y&&pontoInterseccao.y<=r2.p2.y)
				{
					printf("%.2f %.2f\n", pontoInterseccao.x, pontoInterseccao.y);
				}
			}
		}
		else
		{
			printf("indefinido indefinido\n");
			printf("%.2f %.2f\n", comprimento1, comprimento2);
			if(r1.p1.y==r1.p2.y)
			{
				if(r2.p1.y==r2.p2.y)
				{
					if(r1.p1.x==r2.p1.x&&r1.p1.y==r2.p1.y)
					{
						printf("%.2f %.2f\n", r1.p1.x, r1.p1.y);
					}
				}
			}
		}

	}
	return 0;
}
