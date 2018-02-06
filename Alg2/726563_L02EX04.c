/* ================================================================== *
    Universidade Federal de Sao Carlos - UFSCar, Sorocaba
 
    Disciplina: Algoritmos e Programação 2
    Prof. Tiago A. Almeida
 
    Lista 02 - Exercício 04 - Cifra de Vigenere
 
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
#include <string.h>
#include <ctype.h>

#define MAX 1000 // tamanho maximo da mensagem e da chave


void upper(char str[]);
void c_prep(char str[], char str2[]);
void tira_esp(char str[]);


int main(){
	
	int n, m, i;
	char f[MAX+1], c[MAX+1];
	do
	{
		scanf("%d", &n);
		if(n>0)
		{
			do
			{
				fgets(f, MAX, stdin);
			}
			while(f[0]=='\n');
			fgets(c, MAX, stdin);
			tira_esp(f);
			tira_esp(c);
			upper(f);
			upper(c);
			c_prep(f, c);
			m=n;
			while(m>0)
			{
				for(i=0; i<strlen(f); i++)
				{
					f[i]=(f[i]+c[i])-65;
					if(f[i]>90)
					{
						f[i]=f[i]-26;
					}
				}
				m--;
			}
			puts(f);
		}
	}
	while(n>0);

    return (0);
}


void upper(char str[])
{
	int i;
	for(i=0; i<strlen(str); i++)
	{
		if(islower(str[i]))
		{
			str[i]=toupper(str[i]);
		}
	}
}
void c_prep(char str[], char str2[])
{
	int i, j;
	if(strlen(str)>strlen(str2))
	{
		for(i=strlen(str2), j=0; i<strlen(str); i++, j++)
		{
			str2[i]=str2[j];
		}
		str2[i]='\0';
	}
	else if(strlen(str)<strlen(str2))
	{
		strncpy(str2,str2,strlen(str));
		str2[strlen(str)]='\0';
	}
}
void tira_esp(char str[])
{
	int i;
	for(i=0; i<strlen(str); i++)
	{
		if(str[i]=='\n')
		{
			str[i]='\0';
		}
	}
}

