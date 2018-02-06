/* ================================================================== *
   Universidade Federal de Sao Carlos - UFSCar, Sorocaba

   Disciplina: Algoritmos e Programação 2
   Prof. Tiago A. Almeida

   Lista 05 - Exercício 02 - Casa de Cambio

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

// Definicao do registro
typedef struct camb{
	float *valorOriginal, *txCambio, valorConvertido;
	int nota100, nota50, nota20, nota10, nota5, nota2, moeda1real, moeda50, moeda25, moeda10, moeda5, moeda1;
}Cambio;


// declaracoes das funcoes
Cambio calculaCambio(float *valor, float *txCambio);


/* ------------------------------ */
/* ROTINA PRINCIPAL - NAO ALTERAR */
/* ------------------------------ */
int main() {

   Cambio conversao; // variavel para armazenar o resultado da conversao
   float valor, txCambio; // valores de entrada para calcular o cambio
   valor = 0.00;
   txCambio = 0.00;

   scanf("%f %f", &valor, &txCambio);
  
   conversao = calculaCambio(&valor, &txCambio);

   printf("Valor: %.2f\n",*conversao.valorOriginal);
   printf("Cambio: %.2f\n",*conversao.txCambio);
   printf("Total: %.2f\n",conversao.valorConvertido);
   if (conversao.nota100 > 0) printf("100,00: %d\n",conversao.nota100);
   if (conversao.nota50 > 0) printf("50,00: %d\n",conversao.nota50);
   if (conversao.nota20 > 0) printf("20,00: %d\n",conversao.nota20);
   if (conversao.nota10 > 0) printf("10,00: %d\n",conversao.nota10);
   if (conversao.nota5 > 0) printf("5,00: %d\n",conversao.nota5);
   if (conversao.nota2 > 0) printf("2,00: %d\n",conversao.nota2);
   if (conversao.moeda1real > 0) printf("1,00: %d\n",conversao.moeda1real);
   if (conversao.moeda50 > 0) printf("0,50: %d\n",conversao.moeda50);
   if (conversao.moeda25 > 0) printf("0,25: %d\n",conversao.moeda25);
   if (conversao.moeda10 > 0) printf("0,10: %d\n",conversao.moeda10);
   if (conversao.moeda5 > 0) printf("0,05: %d\n",conversao.moeda5);
   if (conversao.moeda1 > 0) printf("0,01: %d\n",conversao.moeda1);

   return 0;

}

/* ------------------------- */
/* IMPLEMENTACAO DAS FUNCOES */
/* ------------------------- */

Cambio calculaCambio(float *valor, float *txCambio)
{
	Cambio aux;
	float conv;
	aux.nota100=aux.nota50=aux.nota20=aux.nota10=aux.nota5=aux.nota2=aux.moeda1real=aux.moeda50=aux.moeda25=aux.moeda10=aux.moeda5=aux.moeda1=0;
	aux.valorOriginal=valor;
	aux.txCambio=txCambio;
	aux.valorConvertido=(*valor)*(*txCambio);
	conv=aux.valorConvertido;
	if((((int)conv)/100)>0)
	{
		aux.nota100=((int)conv)/100;
		conv=conv-100*(aux.nota100);
	}
	if((((int)conv)/50)>0)
	{
		aux.nota50=((int)conv)/50;
		conv=conv-50*(aux.nota50);
	}
	if((((int)conv)/20)>0)
	{
		aux.nota20=((int)conv)/20;
		conv=conv-20*(aux.nota20);
	}
	if((((int)conv)/10)>0)
	{
		aux.nota10=((int)conv)/10;
		conv=conv-10*(aux.nota10);
	}
	if((((int)conv)/5)>0)
	{
		aux.nota5=((int)conv)/5;
		conv=conv-5*(aux.nota5);
	}
	if((((int)conv)/2)>0)
	{
		aux.nota2=((int)conv)/2;
		conv=conv-2*(aux.nota2);
	}
	if((int)conv>0)
	{
		aux.moeda1real=(int)conv;
		conv=conv-aux.moeda1real;
	}
	if(conv/0.5>0)
	{
		aux.moeda50=(int)(conv/0.5);
		conv=conv-0.5*(aux.moeda50);
	}
	if(conv/0.25>0)
	{
		aux.moeda25=(int)(conv/0.25);
		conv=conv-0.25*(aux.moeda25);
	}
	if(conv/0.1>0)
	{
		aux.moeda10=(int)(conv/0.1);
		conv=conv-0.1*(aux.moeda10);
	}
	if(conv/0.05>0)
	{
		aux.moeda5=(int)(conv/0.05);
		conv=conv-0.05*(aux.moeda5);
	}
	if(conv/0.01>0)
	{
		aux.moeda1=(int)(conv/0.01);
		conv=conv-0.01*(aux.moeda1);
	}
	return(aux);
}

