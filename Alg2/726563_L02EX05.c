/* ================================================================== *
	Universidade Federal de Sao Carlos - UFSCar, Sorocaba

	Disciplina: Algoritmos e Programação 2
	Prof. Tiago A. Almeida

	Lista 02 - Exercício 05 - Dissertando

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


// MENSAGENS DE SAIDA
#define MSG_POBRE 	"Texto pobre.\n"
#define MSG_MEDIANO "Texto mediano.\n"
#define MSG_RICO 	"Texto rico.\n"

#define MAX_STR 1001 // tamanho maximo do texto

typedef struct plag{
	int verif, indx_inicio;
}Plag;
void imprimir(char texto[], int n);
void riqueza(char texto[]);
void plagio(char texto[], char texto2[]);
void paginas(char texto[], int l, int c);

int main()
{	
	
	char texto[MAX_STR], texto2[MAX_STR];
	int opcao, n;
	long unsigned int c, l;
	opcao=1;
	while(opcao!=0)
	{
		switch(opcao)
		{
			case 1:
				do
				{
					fgets(texto, MAX_STR, stdin);
				}
				while(texto[0]=='\n');
			break;

			case 2:
				scanf("%d", &n);
				imprimir(texto, n);
			break;

			case 3:
				riqueza(texto);
			break;

			case 4:
				scanf("%lu", &c);
				scanf("%lu", &l);
				paginas(texto, l, c);
			break;

			case 5:
				do
				{
					fgets(texto2, MAX_STR-1, stdin);
				}
				while(texto2[0]=='\n');
				plagio(texto, texto2);
			break;
					
		}
		scanf("%d", &opcao);
	}	
	
	return (0);
}

void imprimir(char texto[], int n)
{
	int i, cont;
	for(i=0, cont=0; i<strlen(texto)&&cont<n; i++)
	{
		if(texto[i]==' ')
		{
			cont++;
			if(cont==n)
			{
				printf("\n");
			}
			else
			{
				printf("%c", texto[i]);
			}
		}
		else
		{
			printf("%c", texto[i]);
		}
	}
}
void riqueza(char texto[])
{
	int i, j, cont=0, entrou;
	char aux[MAX_STR];
	strcpy(aux, texto);
	for(i=0; i<strlen(texto); i++)
	{
		if(islower(aux[i]))
		{
			aux[i]=toupper(aux[i]);
		}
	}
	for(j=65; j<=90; j++)
	{
		for(i=0,entrou=0; i<strlen(texto)&&entrou==0; i++)
		{
			if(aux[i]==j)
			{
				cont++;
				entrou++;
			}
		}
	}
	if(cont==26)
	{
		printf(MSG_RICO);
	}
	else if(cont<26&&cont>=13)
	{
		printf(MSG_MEDIANO);
	}
	else
	{
		printf(MSG_POBRE);
	}
}
void plagio(char texto[], char texto2[])
{
	int i, j, k, l, cont=0, maior=0;
	char aux[MAX_STR];	
	strcpy(aux, texto);
	for(i=0; i<strlen(aux)-1; i++)
	{
		aux[i]=toupper(aux[i]);
	}
	for(i=0; i<strlen(texto2)-1; i++)	
	{
		texto2[i]=toupper(texto2[i]);
	}
	for(i=0; i<strlen(aux)-1; i++)
	{
		for(j=0; j<strlen(texto2)-1; j++)
		{
			if(aux[i]==texto2[j])
			{
				k=i;
				l=j;
				cont=0;
				while(aux[k]==texto2[l]&&aux[k]!='\n'&&texto2[l]!='\n')
				{
					cont++;
					k++;
					l++;

				}
				if(maior<cont)
				{
					maior=cont;		
				}
			}
		}
	}
	printf("%d\n", maior);
}
void paginas(char texto[], int l, int c)
{
	int i, j=0, k=0; 
	for(i=0; i<strlen(texto)-1; i++)
	{
		if(j>0||texto[i]!=' ')
			j++;
		if(j==c&&i<strlen(texto)-2)
		{
			if(texto[i]!=' ')
			{
				if((texto[i+1]!=' '))
				{
					while(texto[i]!=' ')
					{
						i--;
					}
				}
			}
			k++;
			j=0;
		}
	}
	k++;
	if(k%l==0)
	{
		printf("%d\n", k/l);
	}
	else
	{
		printf("%d\n", (k/l)+1);
	}
}
