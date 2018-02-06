
/* ================================================================== *
   Universidade Federal de Sao Carlos - UFSCar, Sorocaba

   Disciplina: Algoritmos e Programação 2
   Prof. Tiago A. Almeida

   Lista 05 - Exercício 01 - Calendario

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

#define PRIMAVERA 0
#define OUTONO    1
#define VERAO     2
#define INVERNO   3

#define TOTAL_DATAS 5

// Definicao do registro
typedef struct data{
	int dia, mes, ano, estacao;
}Data;


// declaracoes das funcoes
void alimentaData(Data *datas, int dias);
void descobreEstacao(Data datas,int estacoes[]);


/* ------------------------------ */
/* ROTINA PRINCIPAL - NAO ALTERAR */
/* ------------------------------ */
int main() {

   Data datas[TOTAL_DATAS]; // vetor para armazenar as datas
   int estacoes[4]; // vetor para armazenar quantidade de datas por estacoes
   
   int dias = 0, // quantidade de dias que serao convertidos
       i = 0;

   // inicializa registros
   for (i=0; i < TOTAL_DATAS; i++) {
      datas[i].ano = 0;
      datas[i].mes = 0;
      datas[i].dia = 0;
      datas[i].estacao = 0;
   }

   // inicializa contador das estacoes
   estacoes[PRIMAVERA] = 0;
   estacoes[OUTONO] = 0;
   estacoes[VERAO] = 0;
   estacoes[INVERNO] = 0;
   
   // le os dias de entrada e converte para registros de data
   for (i=0; i < TOTAL_DATAS; i++) {
      scanf("%d",&dias);
      alimentaData(&datas[i],dias); // recebe a qtde de dias e converte para data dd/mm/aaaa a partir da data 01/01/0001
      printf("%02d/%02d/%04d\n", datas[i].dia, datas[i].mes, datas[i].ano); // imprime a data no formato dd/mm/aaaa
      descobreEstacao(datas[i],estacoes); // descobre a estacao da data informada
   }

   // imprime quantas datas ficaram em cada estacao do ano
   printf("Primavera: %d\n", estacoes[PRIMAVERA]);
   printf("Outono: %d\n", estacoes[OUTONO]);
   printf("Verao: %d\n", estacoes[VERAO]);
   printf("Inverno: %d\n", estacoes[INVERNO]);

   return (0);

}

/* ------------------------- */
/* IMPLEMENTACAO DAS FUNCOES */
/* ------------------------- */

void alimentaData(Data *datas, int dias)
{
	datas->ano=datas->mes=datas->dia=1;
	if(dias/365>0)
	{
		datas->ano=(dias/365)+1;
		dias=dias%365;
	}
	if(dias/32>0)
	{
		datas->mes=2;
		dias=dias-31;
		if(dias/29>0)
		{
			datas->mes=3;
			dias=dias-28;
			if(dias/32>0)
			{
				datas->mes=4;
				dias=dias-31;
				if(dias/31>0)
				{
					datas->mes=5;
					dias=dias-30;
					if(dias/32>0)
					{
						datas->mes=6;
						dias=dias-31;
						if(dias/31>0)
						{
							datas->mes=7;
							dias=dias-30;
							if(dias/32>0)
							{
								datas->mes=8;
								dias=dias-31;
								if(dias/32>0)
								{
									datas->mes=9;
									dias=dias-31;
									if(dias/31>0)
									{
										datas->mes=10;
										dias=dias-30;
										if(dias/32>0)
										{
											datas->mes=11;
											dias=dias-31;
											if(dias/31>0)
											{
												datas->mes=12;
												dias=dias-30;
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}								
	datas->dia=dias;
}

void descobreEstacao(Data datas,int estacoes[])
{
	if(datas.mes>=3&&datas.mes<=6)
	{
		if(datas.mes==4||datas.mes==5)
			estacoes[OUTONO]++;
		if(datas.mes==3)
			if(datas.dia>=20)
				estacoes[OUTONO]++;
		if(datas.mes==6)
			if(datas.dia<=20)
				estacoes[OUTONO]++;
	}
	if(datas.mes>=6&&datas.mes<=9)
	{
		if(datas.mes==7||datas.mes==8)
			estacoes[INVERNO]++;
		if(datas.mes==6)
			if(datas.dia>20)
				estacoes[INVERNO]++;
		if(datas.mes==9)
			if(datas.dia<=22)
				estacoes[INVERNO]++;
	}
	if(datas.mes>=9&&datas.mes<=12)
	{
		if(datas.mes==10||datas.mes==11)
			estacoes[PRIMAVERA]++;
		if(datas.mes==9)
			if(datas.dia>22)
				estacoes[PRIMAVERA]++;
		if(datas.mes==12)
			if(datas.dia<=21)
				estacoes[PRIMAVERA]++;
	}
	if(datas.mes==12||datas.mes<=3)
	{
		if(datas.mes==1||datas.mes==2)
			estacoes[VERAO]++;
		if(datas.mes==12)
			if(datas.dia>21)
				estacoes[VERAO]++;
		if(datas.mes==3)
			if(datas.dia<20)
				estacoes[VERAO]++;
	}
}
