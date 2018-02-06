/* ================================================================== *
   Universidade Federal de Sao Carlos - UFSCar, Sorocaba

   Disciplina: Algoritmos e Programação 2
   Prof. Tiago A. Almeida

   Lista 06 - Exercício 05 - Vetor associativo

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
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define OPCAO_ATRIBUIR 1
#define OPCAO_OBTER 2
#define OPCAO_FINALIZAR 3

#define MSG_CHAVE_INSERIDA "A chave \"%s\" foi inserida com valor %d.\n"
#define MSG_VALOR_MODIFICADO "O valor de \"%s\" foi modificado de %d para %d.\n"
#define MSG_VALOR_DE_CHAVE "Valor de \"%s\": %d.\n"
#define MSG_CHAVE_NAO_ENCONTRADA "Chave não encontrada: \"%s\".\n"

typedef struct ass
{
	char *chave;
	int valor;
}Ass;

int main()
{
	Ass *vetor;
	char *chave_prov, c;
	long long int i, j=0;
	int flag, opcao, val;
	vetor = (Ass *) malloc(sizeof(Ass));
	//chave_prov = (char *) malloc(1);//aqui
	scanf("%d", &opcao);
	while(opcao!=OPCAO_FINALIZAR)
	{
		i=0;
		chave_prov = (char *) malloc(1);//aqui
		if(opcao==OPCAO_ATRIBUIR)
		{
			c=getchar();
			if(!isgraph(c))
				c=getchar();
			do
			{
				chave_prov[i]=c;
				i++;
				chave_prov = (char *) realloc(chave_prov, i+1);
				c=getchar();
 			}
			while(isgraph(c));
			chave_prov[i]='\0';
			for(i=0, flag=0; i<j&&flag==0; i++)
			{
				if(strcmp(chave_prov, vetor[i].chave)==0)
				{
					//free(chave_prov);//aqui
					flag=1;
					scanf("%d", &val);
					printf(MSG_VALOR_MODIFICADO, vetor[i].chave, vetor[i].valor, val);
					vetor[i].valor=val;
				}
			}
			if(flag==0)
			{
				vetor[j].chave = (char *) malloc(strlen(chave_prov)+1);
				strcpy(vetor[j].chave, chave_prov);
				//free(chave_prov);//aqui
				scanf("%d", &vetor[j].valor);
				printf(MSG_CHAVE_INSERIDA, vetor[j].chave, vetor[j].valor);
				j++;
				vetor = (Ass *) realloc(vetor, (j+1)*sizeof(Ass));
			}
		}
		else if(opcao==OPCAO_OBTER)
		{
			c=getchar();
			if(!isgraph(c))
				c=getchar();
			do
			{
				chave_prov[i]=c;
				i++;
				chave_prov = (char *) realloc(chave_prov, i+1);
				c=getchar();
 			}
			while(isgraph(c));
			chave_prov[i]='\0';
			for(i=0, flag=0; i<j&&flag==0; i++)
			{
				if(strcmp(chave_prov, vetor[i].chave)==0)
				{
					//free(chave_prov);//aqui
					flag=1;
					printf(MSG_VALOR_DE_CHAVE, vetor[i].chave, vetor[i].valor);
				}
			}
			if(flag==0)
			{
				printf(MSG_CHAVE_NAO_ENCONTRADA, chave_prov);
				//free(chave_prov);//aqui
			}
		}
		scanf("%d", &opcao);
		free(chave_prov);
	}
	for(i=0; i<j; i++)
		free(vetor[i].chave);
	free(vetor);
	//free(chave_prov);//aqui
	return(0);
}
