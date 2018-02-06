/* ================================================================== *
    Universidade Federal de Sao Carlos - UFSCar, Sorocaba
 
    Disciplina: Algoritmos e Programação 2
    Prof. Tiago A. Almeida
 
    Lista 03 - Exercício 06 - Sequencias Recursivas
 
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

enum opcoes { SAIR = 0, NUMERO, SOMA, PERTENCE };

/* Recebe um caractere (c) indicando a sequencia (Sc) e um numero n
	Retorna o numero da sequencia correspondente ao caractere (Sc(n)) */
long long int opNumero(char codigon, long long int n);

/* Recebe dois codigos indicando a sequencia dos numeros n e k respectivamente
	Retorna a soma entre o n-Esimo numero da sequencia correspondente a codigon e o k-Esimo da sequencia codigok */
long long int opSoma(char codigon, char codigok, long long int n, long long int k);

/* Recebe um codigo indicando a sequencia e um numero n
	Retorna 1 se o numero n faz parte da sequencia e 0 caso contrario */
int opPertence(char codigon, long long int n);

long long int tribonacci(long long int n);
long long int pell(long long int n);
long long int catalan(long long int n);
long long int hofs(long long int n);

int main(){
	/* Variaveis */
	int op;
	long long int n, k;
	char codigon, codigok;

	while(1){
		/* Le a opcao desejada */
		scanf("%d", &op);

		switch (op){
			/* Sai do programa */
			case SAIR:
				return 0;
				break;

			/* Exibe o n-Esimo numero da sequencia correspondente */
			case NUMERO:
				scanf("\n%c %Ld", &codigon, &n);
				printf("%Ld\n", opNumero(codigon, n));
				break;

			/* Exibe a soma entre o n-Esimo e o k-Esimo numero das sequencias correspondentes */
			case SOMA:
				scanf("\n%c %c %Ld  %Ld", &codigon, &codigok, &n, &k);
				printf("%Ld\n", opSoma(codigon, codigok, n, k));
				break;

			/* Informa se o numero n faz parte da sequencia correspondente */
			case PERTENCE:
				scanf("\n%c %Ld", &codigon, &n);
				printf("%d\n", opPertence(codigon, n));
				break;
		}
	}
}

long long int tribonacci(long long int n)
{
	if(n==0)
		return(0);
	else if(n==1)
		return(0);
	else if(n==2)
		return(1);
	else
		return(tribonacci(n-1)+tribonacci(n-2)+tribonacci(n-3));
}
	
long long int pell(long long int n)
{
	if(n==0)
		return(0);
	else if(n==1)
		return(1);
	else
		return((2*pell(n-1))+(pell(n-2)));
}

long long int catalan(long long int n)
{
	if(n==0)
		return(1);
	else
		return(((2*((2*n)-1)*(catalan(n-1)))/(n+1)));
}

long long int hofs(long long int n)
{
	if(n==0)
		return(0);
	else
		return(n-hofs(hofs(hofs(n-1))));
}

long long int opNumero(char codigon, long long int n)
{
	if(codigon=='T')
		return(tribonacci(n));
	else if(codigon=='P')
		return(pell(n));
	else if(codigon=='C')
		return(catalan(n));
	else if(codigon=='H')
		return(hofs(n));
}

long long int opSoma(char codigon, char codigok, long long int n, long long int k)
{
	long long int v1, v2;
	if(codigon=='T')
		v1=(tribonacci(n));
	else if(codigon=='P')
		v1=(pell(n));
	else if(codigon=='C')
		v1=(catalan(n));
	else if(codigon=='H')
		v1=(hofs(n));
	if(codigok=='T')
		v2=(tribonacci(k));
	else if(codigok=='P')
		v2=(pell(k));
	else if(codigok=='C')
		v2=(catalan(k));
	else if(codigok=='H')
		v2=(hofs(k));
	return(v1+v2);
}
int opPertence(char codigon, long long int n)
{
	long long int i;
	if(codigon=='T')
	{
		i=0;
		while(n>=tribonacci(i))
		{
			if(n==tribonacci(i))
			{
				return(1);
			}
			i++;
		}
		return(0);
	}
	else if(codigon=='P')
	{
		i=0;
		while(n>=pell(i))
		{
			if(n==pell(i))
			{
				return(1);
			}
			i++;
		}
		return(0);
	}
	else if(codigon=='C')
	{
		i=0;
		while(n>=catalan(i))
		{
			if(n==catalan(i))
			{
				return(1);
			}
			i++;
		}
		return(0);
	}
	else if(codigon=='H')
	{
		i=0;
		while(n>=hofs(i))
		{
			if(n==hofs(i))
			{
				return(1);
			}
			i++;
		}
		return(0);
	}
}
