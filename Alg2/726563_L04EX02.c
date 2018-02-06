/* ================================================================== *
   Universidade Federal de Sao Carlos - UFSCar, Sorocaba

   Disciplina: Algoritmos e Programação 2
   Prof. Tiago A. Almeida

   Lista 04 - Exercício 02 - Progressão Geométrica

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

// variavel global: mantem a quantidade de termos da progressao
int num_termos = 0;


// declaracoes das funcoes
void progressaoGeometrica(float termoInicial, float razao, int termoN1, int termoN2, float *resultado1, float *resultado2);


/* ------------------------------ */
/* ROTINA PRINCIPAL - NAO ALTERAR */
/* ------------------------------ */
int main()
{

   // variaveis utilizadas para o calculo da progressao geometrica
   float termoInicial, razao, resultado1, resultado2 = 0;
   int termoN1, termoN2;
          
   scanf("%f %f", &termoInicial, &razao);
   scanf("%d %d", &termoN1, &termoN2);
   
   progressaoGeometrica(termoInicial,razao,termoN1,termoN2,&resultado1,&resultado2);

   printf("%.2f %.2f", resultado1, resultado2);

   return 0;
}


/* ------------------------- */
/* IMPLEMENTACAO DA FUNCAO   */
/* ------------------------- */

void progressaoGeometrica(float termoInicial, float razao, int termoN1, int termoN2, float *resultado1, float *resultado2)
{
	int i;
	*resultado1=termoInicial;
	for(i=1; num_termos==0; i++)
	{
		if(termoN1==i)
		{
			num_termos++;
		}
		else
		{
			*resultado1=*resultado1*razao;
		}
	}
	*resultado2=*resultado1;
	for(i--; num_termos==1; i++)
	{
		if(termoN2==i)
		{
			num_termos++;
		}
		else
		{
			*resultado2=*resultado2*razao;
		}
	}
}
