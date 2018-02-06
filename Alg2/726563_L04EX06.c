/* ================================================================== *
    Universidade Federal de Sao Carlos - UFSCar, Sorocaba
 
    Disciplina: Algoritmos e Programação 2
    Prof. Tiago A. Almeida
 
    Lista 04 - Exercício 06 - Calculadora Financeira
 
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
#include <stdlib.h>

enum opcoes {SAIR = 0, CONVERSAO, JUROS, RENDIMENTO };


void conversaoMoedas(double *dolar, double *euro, double real);
void calcularJuros(double valor_inicial, int mes, double taxa, double *juros_simples, double *juros_compostos);
void calcularRendimentos(double valor_inicial, int mes, double *rendimento_semanal, double *rendimento_mensal, double *rendimento_anual, double *rendimento_final);




/* --------------------------------- */
/* --- NÃO ALTERAR A FUNÇÃO MAIN --- */
/* --------------------------------- */
int main(){
	/* Vairavel de Opcao */
	int op;

	/* Variaveis Opcao 1 */
	double dolar, euro, real;

	/* Variaveis Opcao 2 */
	double taxa, juros_simples, juros_compostos;
	
	/* Variaveis Opcao 3 */
	double rendimento_semanal, rendimento_mensal, rendimento_anual, rendimento_final;

	/* Variaveis Opcao 2 e 3 */
	double valor_inicial;
	int mes;

	while(1){
		/* Lê a opcao */
		scanf("%d", &op);

		switch (op){
			/* Sai do programa */
			case SAIR:
				return 0;
				break;

			/* Converte as moedas */
			case CONVERSAO:
				scanf("%lf %lf %lf", &dolar, &euro, &real);
				conversaoMoedas(&dolar, &euro, real);
				printf("R$ %.2lf = U$ %.2lf = E$ %.2lf\n", real, dolar, euro);
				break;

			/* Calcula juros simples e compostos */
			case JUROS:
				scanf("%lf %d %lf", &valor_inicial, &mes, &taxa);
				calcularJuros(valor_inicial, mes, taxa, &juros_simples, &juros_compostos);
				printf("Juros Simples = %.2lf\nJuros Compostos = %.2lf\n", juros_simples, juros_compostos);
				break;

			/* Calcula o rendimento final para taxas de rendimento semanal, mensal e anual */
			case RENDIMENTO:
				scanf("%lf %d %lf %lf %lf", &valor_inicial, &mes, &rendimento_semanal, &rendimento_mensal, &rendimento_anual);
				calcularRendimentos(valor_inicial, mes, &rendimento_semanal, &rendimento_mensal, &rendimento_anual, &rendimento_final);
				printf("Rendimento Semanal = %.2lf\nRendimento Mensal = %.2lf\nRendimento Anual = %.2lf\nMelhor rendimento = %.2lf\n", rendimento_semanal, rendimento_mensal, rendimento_anual, rendimento_final);
				break;
		}
	}
}
/* --------------------------------- */

void conversaoMoedas(double *dolar, double *euro, double real)
{
	*dolar=(*dolar)*real;
	*euro=(*euro)*real;
}
void calcularJuros(double valor_inicial, int mes, double taxa, double *juros_simples, double *juros_compostos)
{
	*juros_simples=valor_inicial+(valor_inicial*(taxa/100)*mes);
	*juros_compostos=valor_inicial*pow((1+(taxa/100)),mes);
}

void calcularRendimentos(double valor_inicial, int mes, double *rendimento_semanal, double *rendimento_mensal, double *rendimento_anual, double *rendimento_final)
{
	int anos;
	anos=mes/12;
	*rendimento_semanal=valor_inicial*pow((1+(*rendimento_semanal/100)),(mes*4));
	*rendimento_mensal=valor_inicial*pow((1+(*rendimento_mensal/100)),(mes));
	if(anos>0)
	{
		*rendimento_anual=valor_inicial*pow((1+(*rendimento_anual/100)),anos);
	}
	else
		*rendimento_anual=valor_inicial;
	*rendimento_final=*rendimento_semanal;
	if(*rendimento_mensal>*rendimento_final)
		*rendimento_final=*rendimento_mensal;
	if(*rendimento_anual>*rendimento_final)
		*rendimento_final=*rendimento_anual;
}

