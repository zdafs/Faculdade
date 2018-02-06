/* ================================================================== *
   Universidade Federal de Sao Carlos - UFSCar, Sorocaba

   Disciplina: Algoritmos e Programação 2
   Prof. Tiago A. Almeida

   Lista 06 - Exercício 01 - Indentador de Código

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

// declaracoes das funcoes
char *alocaEspaco(int tamanho);
void indentaCodigo(char *codigoFonte, int tamanho);

/* ------------------------------ */
/* ROTINA PRINCIPAL - NAO ALTERAR */
/* ------------------------------ */
int main(){

   char *codigoFonte = NULL; // ponteiro para armazenar o codigo fonte de entrada
   int tamanho = 0; // variavel para armazenar o tamanho do codigo fonte de entrada

   // recebe o tamanho do codigo fonte a ser indentado
   scanf("%d",&tamanho);

   // deve alocar espaço para a variavel buffer
   codigoFonte = alocaEspaco(tamanho);

   // verifica se a alocação deu certo
   if (codigoFonte == NULL)
   {
      printf("Problema ao alocar memória.\n");
      exit(1);
   }

   // le o codigo a ser indentado
   scanf("%[^\n]",codigoFonte);

   // deve imprimir o codigo indentado
   indentaCodigo(codigoFonte, tamanho); 

   // libera a memória
   free(codigoFonte);
  
   return 0;
}

/* ------------------------- */
/* IMPLEMENTACAO DAS FUNCOES */
/* ------------------------- */

char *alocaEspaco(int tamanho)
{
	char *p;
	p = (char *) malloc(tamanho+1);
	return(p);
}

void indentaCodigo(char *codigoFonte, int tamanho)
{
	int cont=-1, i=0, aux;
	if(*(codigoFonte+i)==' ')
		i++;
	if(*(codigoFonte+i)=='#')
	{
		printf("%c", *(codigoFonte+i));
		i++;
	} 
	while(*(codigoFonte+i)!='\0')
	{
		if(*(codigoFonte+i)=='"')
		{
			printf("%c", *(codigoFonte+i));
			do
			{
				i++;
				printf("%c", *(codigoFonte+i));
			}
			while(*(codigoFonte+i)!='"');
			//if(*(codigoFonte+i+1)==' ')
			//	i++;
		}
		else if(*(codigoFonte+i)==27)
		{
			printf("%c", *(codigoFonte+i));
			do
			{
				i++;
				printf("%c", *(codigoFonte+i));
			}
			while(*(codigoFonte+i)==27);
			//if(*(codigoFonte+i+1)==' ')
			//	i++;
		}
		else if(*(codigoFonte+i)=='>'&&cont==-1)
		{
			printf("%c", *(codigoFonte+i));
			if(*(codigoFonte+i+1)==' ')
				i++;
			printf("\n");
		}
		else if((48<=*(codigoFonte+i)&&*(codigoFonte+i)<=57)&&cont==-1)
		{
			while((48<=*(codigoFonte+i)&&*(codigoFonte+i)<=57))
			{
				printf("%c", *(codigoFonte+i));
				i++;
			}
			if(*(codigoFonte+i)==' ')
				i++;
			printf("\n");
			printf("%c", *(codigoFonte+i));
		}
		else if((*(codigoFonte+i-1)=='"'||*(codigoFonte+i-1)==27)&&cont==-1)
		{
			printf("\n");
			if(*(codigoFonte+i-1)!=' ')
				printf("%c", *(codigoFonte+i));
		}
		else if(*(codigoFonte+i)=='{')
		{
			printf("%c", *(codigoFonte+i));
			if(*(codigoFonte+i+1)==' ')
				i++;
			if(cont==-1)
				cont=0;
			cont++;
			printf("\n");
			if(*(codigoFonte+i+1)!='}')
				for(aux=0; aux<cont; aux++)
					printf("\t");
		}
		else if(*(codigoFonte+i)=='}')
		{
			cont--;
			for(aux=0; aux<cont; aux++)
				printf("\t");
			printf("%c", *(codigoFonte+i));
			if(*(codigoFonte+i+1)=='\0')
				break;
			else if(*(codigoFonte+i+1)==' ')
				i++;
			printf("\n");
			if(*(codigoFonte+i+1)!='}')
				for(aux=0; aux<cont; aux++)
					printf("\t");
		}
		else if(*(codigoFonte+i)==';')
		{
			printf("%c", *(codigoFonte+i));
			if(*(codigoFonte+i+1)==' ')
				i++;
			printf("\n");
			if(*(codigoFonte+i+1)!='}')
				for(aux=0; aux<cont; aux++)
					printf("\t");
		}
		else if(*(codigoFonte+i)=='f'&&*(codigoFonte+i+1)=='o'&&*(codigoFonte+i+2)=='r')
		{
			printf("%c", *(codigoFonte+i));
			do
			{
				i++;
				printf("%c", *(codigoFonte+i));
			}
			while(*(codigoFonte+i+1)!='{');
		}
		else
		{
			printf("%c", *(codigoFonte+i));
		}
		i++;
	}
	printf("\n");
}
