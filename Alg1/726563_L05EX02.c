/* ================================================================== *
    Universidade Federal de Sao Carlos - UFSCar, Sorocaba
 
    Disciplina: Algoritmos e Programação 1
    Prof. Tiago A. Almeida
 
    Lista 05 - Exercício 02 - Dia da Semana
 
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


// constantes de saida
#define SEGUNDA "Segunda-feira\n"
#define TERCA 	"Terça-feira\n"
#define QUARTA 	"Quarta-feira\n"
#define QUINTA 	"Quinta-feira\n"
#define SEXTA 	"Sexta-feira\n"
#define SABADO 	"Sabado\n"
#define DOMINGO "Domingo\n"

// mensagem de erro padrao
#define ERRO 	"Data invalida\n"


// enumeracoes nos cases dos switches
enum { Jan = 1, Fev, Mar, Abr, Mai, Jun, Jul, Ago, Set, Out, Nov, Dez };
enum { Seg = 0, Ter, Qua, Qui, Sex, Sab, Dom };


/* <<< DEFINA AQUI O REGISTRO DATA */
typedef struct data
{
	int dia;
	int mes;
	int ano;
}Data;
typedef int boolean;

int main()
{	
	int n; 			// quantidade de datas
	Data data_in;	// registro data de entrada
	boolean bissexto, verif;
	int a, b, c, d, dia_sem, i;


	scanf("%d", &n);
	for (i = 0; i < n; i++)
	{
		scanf("%d/%d/%d", &data_in.dia, &data_in.mes, &data_in.ano); // recebe os campos do registro data
		if(data_in.dia>=1&&data_in.dia<=31&&data_in.mes>=Jan&&data_in.mes<=Dez&&data_in.ano>=1900&&data_in.ano<=2399)
		{
			bissexto=0;
			verif=1;
			//VERIFICAÇÃO BISSEXTO
			if(data_in.ano%4==0)
			{
				if(data_in.ano%100==0)
				{
					if(data_in.ano%400==0)
					{
						bissexto=1;
					}
				}
				else
				{
					bissexto=1;
				}
			}	
			//VERIFICAÇÃO BISSEXTO
			if((data_in.mes==Abr||data_in.mes==Jun||data_in.mes==Set||data_in.mes==Nov)&&(data_in.dia==31))
			{
				printf(ERRO);
				verif=0;
			}
			else if(data_in.mes==Fev&&data_in.dia>28)
			{
				if(bissexto==0||data_in.dia>29)
				{
					printf(ERRO);
					verif=0;
				}
			}
			if(verif)
			{
				a=data_in.ano-1900;
				b=a/4;
				if(bissexto==1&&(data_in.mes==Jan||data_in.mes==Fev))
				{
					b--;
				}
				switch(data_in.mes)
				{
					case Jan: c=0; break;
					case Fev: c=3; break;
					case Mar: c=3; break;
					case Abr: c=6; break;
					case Mai: c=1; break;
					case Jun: c=4; break;
					case Jul: c=6; break;
					case Ago: c=2; break;
					case Set: c=5; break;
					case Out: c=0; break;
					case Nov: c=3; break;
					case Dez: c=5; break;
				}
				d=data_in.dia-1;
				dia_sem=(a+b+c+d)%7;
				switch(dia_sem)
				{
					case Seg:
						printf(SEGUNDA);
						break;
					case Ter:
						printf(TERCA);
						break;
					case Qua:
						printf(QUARTA);
						break;
					case Qui:
						printf(QUINTA);
						break;	
					case Sex:
						printf(SEXTA);
						break;
					case Sab:
						printf(SABADO);
						break;
					case Dom:
						printf(DOMINGO);
						break;
				}
			}
		}
		else
		{
			printf(ERRO);
		}

	}		
	return (0);
}
