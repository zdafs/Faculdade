/* ================================================================== *
   Universidade Federal de Sao Carlos - UFSCar, Sorocaba

   Disciplina: Algoritmos e Programação 2
   Prof. Tiago A. Almeida

   Lista 06 - Exercício 03 - Monta Texto

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
char *alocaEspaco(int tam);
char *montaTexto(char *texto, int tamanho, char *trecho, int tamanho_trecho);

/* ------------------------------ */
/* ROTINA PRINCIPAL - NAO ALTERAR */
/* ------------------------------ */
int main(){

   char *texto = NULL; // ponteiro para armazenar o texto completo
   char *trecho = NULL; // ponteiro para armazenar o trecho de entrada
   int tamanho_trecho = 0; // variavel para armazenar o tamanho do trecho de entrada
   int tamanho = 0; // variavel para armazenar o tamanho do texto

   // recebe o tamanho do trecho
   scanf("%d",&tamanho_trecho);
   while(tamanho_trecho != 0) {
      
      // libera espaco anterior e aloca novo espaco
      free(trecho);
      trecho = alocaEspaco(tamanho_trecho);
      if(texto == NULL)
         texto = alocaEspaco(tamanho_trecho);

      // le trecho
      scanf("%*[ ]%[^\n]",trecho);

      // monta texto com novas informacoes recebidas
      tamanho = tamanho + tamanho_trecho;
      texto = montaTexto(texto,tamanho,trecho,tamanho_trecho);

      scanf("%d",&tamanho_trecho);
   }

   printf("%s\n",texto);

   // libera memória alocada
   free(texto);
   free(trecho);   
  
   return 0;
}

/* ------------------------- */
/* IMPLEMENTACAO DAS FUNCOES */
/* ------------------------- */

char *alocaEspaco(int tam)
{
	char *p;
	if(tam>0)
		p = (char *) malloc(tam+1);
	else
	{
		p = (char *) malloc(1);
		*p='\n';
	}
	return(p);
}

char *montaTexto(char *texto, int tamanho, char *trecho, int tamanho_trecho)
{
	int i, j;
	texto = (char *) realloc(texto, tamanho+1);
	for(i=0, j=(tamanho-tamanho_trecho); trecho[i]!='\0'; i++, j++)
		texto[j]=trecho[i];
	texto[tamanho]='\0';
	return(texto);
}
