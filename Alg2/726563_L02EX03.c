/* ================================================================== *
	Universidade Federal de Sao Carlos - UFSCar, Sorocaba

	Disciplina: Algoritmos e Programação 2
	Prof. Tiago A. Almeida

	Lista 02 - Exercício 03 - Validacao de e-mails

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

int email_valido(char email[]);
int conf_Arrobas(char email[], int tam);
int conf_Server(char email[], int tam);
int conf_Simb(char email[], int tam);
int simb_num_test(char email[], int tam);

int main() {
    int tamanho;
    char email[51];
    
    while (scanf("%d", &tamanho) && tamanho > 0) {
        scanf(" %50[^\n]", email);
        
        if (email_valido(email))
            printf("Valido\n");
        else
            printf("Invalido\n");
    }
    
    return (0);
}

int email_valido(char email[]) {
    
	int tam=strlen(email);
	if(conf_Arrobas(email, tam))
	{
		if(conf_Server(email, tam))
		{
			if(conf_Simb(email,tam))
			{
    				if(simb_num_test(email, tam))
				{
					return(1);
				}
			}
		}
	}
	return(0);
}
int conf_Arrobas(char email[], int tam)
{
	int i, cont;
	for(i=0,cont=0; i<tam; i++)
	{
		if(email[i]=='@')
		{
			cont++;
			if(cont!=1)
			{	
				return(0);
			}
		}
	}
	return(1);
}
int conf_Server(char email[], int tam)
{
	int i, j, conf;
	char server[15];
	for(i=0,conf=0; i<tam&&conf==0; i++)
	{
		if(email[i]=='@')
		{
			conf=1;
			if((tam-i-1)>14)
			{
				return(0);
			}
		}
	}
	for(j=0;i<tam;i++,j++)
	{
		server[j]=email[i];
	}
	server[j]='\0';
	if(strcmp(server,"email.abc")==0||strcmp(server,"email.abc.br")==0||strcmp(server,"abcmail.xyz.br")==0||
	   strcmp(server,"abcweb.asd.br")==0||strcmp(server,"asdmail.xyz")==0)
	{
		return(1);
	}
	return(0);
}
int conf_Simb(char email[], int tam)
{
	int i;
	for(i=0; i<tam; i++)
	{
		if(email[i]<65||email[i]>90)
		{
			if(email[i]<97||email[i]>122)
			{
				if(email[i]<48||email[i]>57)
				{
					if(email[i]!=46&&email[i]!=44&&email[i]!=95&&email[i]!=45&&email[i]!=64)
					{
						return(0);
					}
				}
			}
		}
	}
	return(1);
}
int simb_num_test(char email[], int tam)
{
	int i;
	if((email[0]>=48&&email[0]<=57)||email[0]==46||email[0]==44||email[0]==95||email[0]==45)
	{
		return(0);
	}
	if(email[tam-1]==46||email[tam-1]==44||email[tam-1]==95||email[tam-1]==45)
	{
		return(0);
	}
	for(i=0; i<tam-1; i++)
	{
		if(email[i]==46||email[i]==44||email[i]==95||email[i]==45)
		{
			if((email[i+1]>=48&&email[i+1]<=57)||email[i+1]==46||email[i+1]==44||email[i+1]==95||email[i+1]==45)
			{
				return(0);
			}
		}
	}
	return(1);
}
