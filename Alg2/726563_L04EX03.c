/* ================================================================== *
   Universidade Federal de Sao Carlos - UFSCar, Sorocaba

   Disciplina: Algoritmos e Programação 2
   Prof. Tiago A. Almeida

   Lista 04 - Exercício 03 - Troca Valores

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

/* comprimento maximo da cadeia de caracteres para troca */
#define MAX 20


// declaracoes das funcoes
void troca(int *x, int *y);
void trocaValores(int *a, int *b, int *c, char trocas[], int total_char);
int *verificaOrdenacao(int a, int b, int c, int *ordenado, int *desordenado);


/* ------------------------------ */
/* ROTINA PRINCIPAL - NAO ALTERAR */
/* ------------------------------ */
int main()
{

   // variaveis utilizadas para entrada
   char trocas[MAX];
   int a,b,c,total_char;
   int i;

   // variaveis de ordenacao
   int ordenado = 1;
   int desordenado = -1;
   int *status;

   // faz leitura dos dados de entrada
   scanf("%d %d %d %d", &a, &b, &c, &total_char);
   for(i=0; i<total_char; i++) {
      do { 
         scanf("%c", &trocas[i]); 
      } while (trocas[i] == ' ');
   }
   
   // faz a troca dos valores conforme a regra
   trocaValores(&a, &b, &c, trocas, total_char);

   // verifica se as variaveis ficaram com valores ordenados
   // --> este metodo retorna ponteiro para a variavel ordenado se a, b e c estiverem
   //     na seguinte condicao: a eh menor ou igual a b e b eh menor ou igual a c;
   //     senao, o metodo retorna ponteiro para a variavel desordenado.
   status = verificaOrdenacao(a,b,c,&ordenado,&desordenado);

   // imprime resultado apos a troca
   printf("%d %d %d (%d)", a, b, c, *status);

   return 0;
}


/* ------------------------- */
/* IMPLEMENTACAO DAS FUNCOES */
/* ------------------------- */

void troca(int *x, int *y)
{
	int aux;
	aux=*x;
	*x=*y;
	*y=aux;
}

void trocaValores(int *a, int *b, int *c, char trocas[], int total_char)
{
	int i;
	//scanf("%c", &trocas[total_char]);
	//trocas[total_char+1]='\0';
	for(i=0; i<total_char; i++)
	{
		if(trocas[i]=='A')
		{
			if(trocas[i+1]=='B')
				troca(a,b);
			else if(trocas[i+1]=='C')
				troca(a,c);
		}
		else if(trocas[i]=='B')
		{
			if(trocas[i+1]=='A')
				troca(a,b);
			else if(trocas[i+1]=='C')
				troca(b,c);
		}
		else if(trocas[i]=='C')
		{
			if(trocas[i+1]=='A')
				troca(a,c);
			else if(trocas[i+1]=='B')
				troca(b,c);
		}
	}
}

int *verificaOrdenacao(int a, int b, int c, int *ordenado, int *desordenado)
{
	if(a<=b && b<=c)
		return(ordenado);
	else
		return(desordenado);
}
