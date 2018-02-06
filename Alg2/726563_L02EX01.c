/* ================================================================== *
	Universidade Federal de Sao Carlos - UFSCar, Sorocaba

	Disciplina: Algoritmos e Programação 2
	Prof. Tiago A. Almeida

	Lista 02 - Exercício 01 - Caça-palavras

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


/* máximo de linhas (m) e colunas (n) */
#define MAX 10

/* constantes booleanas */	
#define VERDADEIRO	1
#define FALSO		0


/* Protótipos das funções */
void lerGrade(char grade[][MAX], int m, int n);
void imprimirGrade(char grade[][MAX], int m, int n);
int procurarHorizontal(char palavra[], char grade[][MAX], int marcas[][MAX], int m, int n);
int procurarVertical(char palavra[], char grade[][MAX], int marcas[][MAX], int m, int n);
int procurarDPrincipal(char palavra[], char grade[][MAX], int marcas[][MAX], int m, int n);
int procurarDSecundaria(char palavra[], char grade[][MAX], int marcas[][MAX], int m, int n);
void inverterString(char palavra[]);
void esconderMarcas(char grade[][MAX], int marcas[][MAX], int m, int n);


/* ------------------------------ */
/* ROTINA PRINCIPAL - NAO ALTERAR */
/* ------------------------------ */

int main(void)
{
	char grade[MAX][MAX]; 	/* matriz de letras do caça-palavras */
	int marcas[MAX][MAX]; 	/* cada posição vale 1 se é para esconder a letra na resposta, ou 0 caso contrário */
	int num_palavras;		/* qtde de palavras que usuário deseja procurar na grade */
	char palavra[MAX];		/* palavra que o usuário deseja buscar */
	int m, n;				/* dimensões da grade de letras */ 
	int i, j;				/* iteradores para percorrer linhas e colunas */
	int achou;				/* variavel que indica se palavra foi encontrada na grade (achou=1) ou não (achou=0)*/
	

	/* lê dimensão e a grade */
	scanf("%d %d", &m, &n);
	lerGrade(grade, m, n);

	
	/* marca todas as posições da grade como fora da resposta final */
	for (i = 0; i < m; i++){
		for (j = 0; j < n; j++){
			marcas[i][j] = 1;
		}
	}


	/* lê número de palavras e procura cada uma delas na grade */
	scanf("%d", &num_palavras);

	/* para cada palavra desejada */
	for(i = 0; i < num_palavras; i++) {
		scanf("%s", palavra); // le a palavra desejada
		
		// procura em todas as linhas da grade
		achou = procurarHorizontal(palavra, grade, marcas, m, n);

		if (achou == FALSO) {

			// procura em todas as colunas da grade
			achou = procurarVertical(palavra, grade, marcas, m, n);
		
			if (achou == FALSO) {

				// procura na diagonal principal
				achou = procurarDPrincipal(palavra, grade, marcas, m, n);

				if (achou == FALSO) {

					// procura na diagonal secundária
					achou = procurarDSecundaria(palavra, grade, marcas, m, n);
					if (achou == FALSO) {

						// Inverte a palavra e reinicias as buscas
						inverterString(palavra);

						// procura em todas as linhas da grade
						achou = procurarHorizontal(palavra, grade, marcas, m, n);

						if (achou == FALSO)	{

							// procura em todas as colunas da grade
							achou = procurarVertical(palavra, grade, marcas, m, n);

							if (achou == FALSO) {

								// procura na diagonal principal
								achou = procurarDPrincipal(palavra, grade, marcas, m, n);
								
								if (achou == FALSO) {
									// procura na diagonal secundária
									achou = procurarDSecundaria(palavra, grade, marcas, m, n);
								}
							}
						}
					}
				}
			}
		}
	}
	
	// coloca '#' na grade no lugar de letras não usadas
	esconderMarcas(grade, marcas, m, n);

	// imprime a grade final
	imprimirGrade(grade, m, n);
	
	return 0;
}


/* ------------------------- */
/* IMPLEMENTACAO DAS FUNCOES */
/* ------------------------- */

/* lerGrade: preenche grade lendo do teclado cada caractere */
void lerGrade(char grade[][MAX], int m, int n)
{
	int i, j;
	
	for (i = 0; i < m; i++)	{
		for (j = 0; j < n; j++) {
			do {
				scanf("%c", &grade[i][j]);
			/* ignora espaços e quebras de linha */
			} while (grade[i][j] == ' ' || grade[i][j] == '\n');
		}
	}
}


/* imprimirGrade: imprime a grade de caracteres */
void imprimirGrade(char grade[][MAX], int m, int n)
{
	int i, j;
	
	for (i = 0; i < m; i++) {
	 	for (j = 0; j < n; j++) {
			printf("%c ", grade[i][j]);
		}
		printf("\n");
	}
}

/* <<< IMPLEMENTE AS DEMAIS FUNCOES AQUI >>> */

/* inverterString: inverte a ordem da string, p. ex, troca "AMOR" por "ROMA" */
void inverterString(char palavra[])
{
	char aux[MAX];
	int i, j;
	for(i=0, j=strlen(palavra)-1; i<strlen(palavra); i++,j--)
	{
		aux[i]=palavra[j];
	}
	aux[i+1]='\0';
	strcpy(palavra,aux);
}

/* procurarHorizontal: procura a palavra nas linhas da grade. Remove as marcas, se a palavra for 
encontrada e retorna TRUE ou FALSE se a palavra foi encontrada ou nao */
int procurarHorizontal(char palavra[], char grade[][MAX], int marcas[][MAX], int m, int n)
{
	int cont=0, col, lin, i, j;
	for(i=0; i<m&&cont<strlen(palavra); i++)
	{
		for(j=0, cont=0; j<n&&cont<strlen(palavra); j++)
		{
			if(palavra[cont]==grade[i][j]&&cont==0)
			{
				lin=i;
				col=j;
				cont++;
			}
			else if(palavra[cont]==grade[i][j]&&cont>0)
				cont++;
			else
				cont=0;
		}
	}
	if(cont==strlen(palavra))
	{
		if(cont==n)
		{
			for(j=0	; j<cont; j++)
			{
				marcas[lin][j]=0;
			}
		}
		else
		{
			for(j=col; j<cont+col; j++)
			{
				marcas[lin][j]=0;
			}
		}
		return(VERDADEIRO);
	}
	return(FALSO);
}
/* procurarVertical: procura a palavra nas colunas da grade. Remove as marcas, se a palavra for 
encontrada e retorna TRUE ou FALSE se a palavra foi encontrada ou nao */
int procurarVertical(char palavra[], char grade[][MAX], int marcas[][MAX], int m, int n)
{
	int cont=0, col, lin, i, j;
	for(j=0; j<n&&cont<strlen(palavra); j++)
	{
		for(i=0, cont=0; i<m&&cont<strlen(palavra); i++)
		{
			if(palavra[cont]==grade[i][j]&&cont==0)
			{
				lin=i;
				col=j;
				cont++;
			}
			else if(palavra[cont]==grade[i][j]&&cont>0)
				cont++;
			else
				cont=0;
		}
	}
	if(cont==strlen(palavra))
	{
		if(cont==m)
		{
			for(i=0; i<cont; i++)
			{
				marcas[i][col]=0;
			}
		}
		else
		{
			for(i=lin; i<cont+lin; i++)
			{
				marcas[i][col]=0;
			}
		}
		return(VERDADEIRO);
	}
	return(FALSO);
}

/* procurarDPrincipal: procura a palavra na diagonal principal da grade. Remove as marcas, se a palavra for 
encontrada e retorna TRUE ou FALSE se a palavra foi encontrada ou nao */
int procurarDPrincipal(char palavra[], char grade[][MAX], int marcas[][MAX], int m, int n)
{
	int cont=0, col, lin, i, j;
	for(i=0, cont=0; i<m&&cont<strlen(palavra); i++)
	{
		if(palavra[cont]==grade[i][i]&&cont==0)
		{
			lin=i;
			cont++;
		}
		else if(palavra[cont]==grade[i][i]&&cont>0)
			cont++;
		else
				cont=0;
	}
	if(cont==strlen(palavra))
	{
		if(cont==m)
		{
			for(i=0; i<cont; i++)
			{
				marcas[i][i]=0;
			}
		}
		else
		{	
			for(i=lin; i<cont+lin; i++)
			{
				marcas[i][i]=0;
			}
		}
		return(VERDADEIRO);
	}
	return(FALSO);
}

/* procurarDSecundaria: procura a palavra na diagonal secundaria da grade. Remove as marcas, se a palavra for 
encontrada e retorna TRUE ou FALSE se a palavra foi encontrada ou nao */
int procurarDSecundaria(char palavra[], char grade[][MAX], int marcas[][MAX], int m, int n)
{
	int cont=0, col, lin, i, j;
	for(i=0, j=n-1, cont=0; i<m&&j>=0&&cont<strlen(palavra); i++,j--)
	{
		if(palavra[cont]==grade[i][j]&&cont==0)
		{
			lin=i;
			col=j;
			cont++;
		}
		else if(palavra[cont]==grade[i][j]&&cont>0)
			cont++;
		else
				cont=0;
	}
	if(cont==strlen(palavra))
	{
		if(cont==m)
		{
			for(i=0, j=0; i<cont; i++,j--)
			{
				marcas[i][j]=0;
			}
		}
		else
		{
			for(i=lin, j=col; i<cont+lin; i++,j--)
			{
				marcas[i][j]=0;
			}
		}
		return(VERDADEIRO);
	}
	return(FALSO);
}
          
/* esconderMarcas: substitui caracteres da grade por '#' onde estiver marcado */
void esconderMarcas(char grade[][MAX], int marcas[][MAX], int m, int n)
{
	int i, j;
	for(i=0; i<m; i++)
	{
		for(j=0; j<n; j++)
		{
			if(marcas[i][j]==1)
			{
				grade[i][j]='#';
			}
		}
	}
}



