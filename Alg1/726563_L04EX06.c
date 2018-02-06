/* ================================================================== *
  Universidade Federal de Sao Carlos - UFSCar, Sorocaba

  Disciplina: Algoritmos e Programação 1
  Prof. Tiago A. Almeida

  Lista 04 - Exercício 06 - Binário e Decimal

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

#define SAIR                0
#define OPC_BINARIO_DECIMAL 1
#define OPC_DECIMAL_BINARIO 2


int main()
{
	int pot, opcao, qnt_dig, temp, i, j, num, aux;
	do
	{
		i=0;
		num=0;
		scanf("%d", &opcao);
		if(opcao==OPC_BINARIO_DECIMAL)
		{
			scanf("%d", &qnt_dig);
			for(i=1;i<=qnt_dig;i++)
			{
				scanf("%d", &temp);
				pot=(int)pow(2,qnt_dig-i);
				num=num+(pot*temp);
			}
			printf("%d\n", num);
		}
		else if(opcao==OPC_DECIMAL_BINARIO)
		{
			scanf("%d", &qnt_dig);
			scanf("%d", &temp);
			for(i=1;i<=qnt_dig;i++)
			{
				aux=temp-((int)pow(2,qnt_dig-i));
				if(aux<0)
				{
					printf("0");
				}
				else
				{
					printf("1");
					temp=aux;
				}
			}
			printf("\n");
		}
				
	}
	while(opcao!=SAIR);

	return (0);
}
