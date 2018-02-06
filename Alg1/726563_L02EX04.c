/* ================================================================== *
    Universidade Federal de Sao Carlos - UFSCar, Sorocaba

    Disciplina: Algoritmos e Programação 1
    Prof. Tiago A. Almeida

    Lista 02 - Exercício 04 - Multa

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

// Mensagens padrao de saida para ocorrencia de multa
#define MSG_SIM "sim\n"
#define MSG_NAO "nao\n"

// Quantidade de pes em um metro
#define FT 3.28

int main() {    

	float dist, tempo, Vmax, padrao_multa, Vveic;
	scanf("%f %f %f", &dist, &tempo, &Vmax);
	scanf("%f", &padrao_multa);
	Vveic=(dist/(tempo*60))*FT;
	if(Vveic<Vmax*1.07)
	{
		printf("%.2f\n", Vveic);
		printf(MSG_NAO);
	}
	else if(Vveic>=Vmax*1.07 && Vveic<Vmax*1.1)
	{
		printf("%.2f\n", Vveic);
		printf(MSG_SIM);
		printf("$%.2f\n", 0.55*padrao_multa);
		printf("04 ptos\n");
	}
	else if(Vveic>=Vmax*1.1 && Vveic<=Vmax*1.13)
	{
		printf("%.2f\n", Vveic);
		printf(MSG_SIM);
		printf("$%.2f\n", 0.75*padrao_multa);
		printf("05 ptos\n");
	}
	else
	{
		printf("%.2f\n", Vveic);
		printf(MSG_SIM);
		printf("$%.2f\n", padrao_multa);
		printf("07 ptos\n");
	} 
	return (0);
}    
