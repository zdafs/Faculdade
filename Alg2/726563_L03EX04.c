/* ================================================================== *
   Universidade Federal de Sao Carlos - UFSCar, Sorocaba

   Disciplina: Algoritmos e Programação 2
   Prof. Tiago A. Almeida

   Lista 03 - Exercício 04 - Operações recursivas em vetor

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

#define MAX 100 // tamanho maximo da lista

// booleanos
#define TRUE  1
#define FALSE 0

// menu de opcoes
#define IMPRIMIR_CONTEUDO	1
#define IMPRIMIR_MENOR		2
#define IMPRIMIR_MAIOR		3
#define IMPRIMIR_SOMA		4
#define IMPRIMIR_PRODUTO	5
#define ORDENAR_VETOR		6
#define BUSCAR_ELEMENTO		7   
#define SAIR			0

// frase pre-definida para saida
#define FRASE_ELEM_NAO_ENCONTRADO "Elemento nao encontrado!\n"


// declaracoes das funcoes
void inicializarLista(int Lista[], int qt_elementos);
void imprimirConteudo(int Lista[], int qt_elementos, int indice);
void ordenador(int indice, int Lista[], int qt_elementos);
int encontrarMenorValor(int Lista[], int qt_elementos, int indice);
int encontrarMaiorValor(int Lista[], int qt_elementos, int indice);
int calcularSoma(int Lista[], int qt_elementos, int indice);
int calcularProduto(int Lista[], int qt_elementos, int indice);
int realizarBuscaLinear(int Lista[], int qt_elementos, int valor, int indice);
int realizarBuscaBinaria(int Lista[], int valor, int inicio, int fim);



// variavel global de contagem
int contagem = 0;



/* ------------------------------ */
/* ROTINA PRINCIPAL - NAO ALTERAR */
/* ------------------------------ */
int main()
{
   int Lista[MAX],         // lista
       qt_elementos=0,     // quantidade de elementos na lista
       opcao,		         // opcao selecionada pelo usuario
       valor,              // valor informado pelo usuario
       posicao,            // posicao informada pelo usuario
       ordenado;           // mantem status se a lista esta ordenada

   scanf("%d", &qt_elementos);
   inicializarLista(Lista, qt_elementos);

   scanf("%d", &opcao);

   while (opcao != SAIR)
   {
      switch(opcao)
      {

         case IMPRIMIR_CONTEUDO:
            imprimirConteudo(Lista, qt_elementos, 0);

         break;

         case IMPRIMIR_MENOR:
            printf("%d\n",encontrarMenorValor(Lista, qt_elementos, 0));

         break;

         case IMPRIMIR_MAIOR:
            printf("%d\n",encontrarMaiorValor(Lista, qt_elementos, 0));

         break;

         case IMPRIMIR_SOMA:
            printf("%d\n",calcularSoma(Lista, qt_elementos, 0));

         break;

         case IMPRIMIR_PRODUTO:
            printf("%d\n",calcularProduto(Lista, qt_elementos, 0));

         break;

         case BUSCAR_ELEMENTO:

            contagem = 0;

            scanf("%d", &valor);

            if (ordenado == TRUE) {
               posicao = realizarBuscaBinaria(Lista, valor, 0, qt_elementos-1);
            } else {
               posicao = realizarBuscaLinear(Lista, qt_elementos, valor, 0);
            }

            if (posicao == -1) printf(FRASE_ELEM_NAO_ENCONTRADO);
            else
               printf("%d %d\n", contagem, posicao);

         break;

         case ORDENAR_VETOR:
            ordenador(0, Lista, qt_elementos);
            ordenado = TRUE;

         break;
      
      }

      scanf("%d", &opcao);
   }

   return 0;
}

/* ------------------------- */
/* IMPLEMENTACAO DAS FUNCOES */
/* ------------------------- */

int encontrarMenorValor(int Lista[], int qt_elementos, int indice) {

	int menor;
	if(indice==qt_elementos-1)
	{
		return(Lista[indice]);
	}
	else
	{
		menor=encontrarMenorValor(Lista, qt_elementos, indice+1);
		if(Lista[indice]<menor)
		{
			return(Lista[indice]);
		}
		else
		{
			return(menor);
		}
	}
}

int encontrarMaiorValor(int Lista[], int qt_elementos, int indice) {

	int maior;
	if(indice==qt_elementos-1)
	{
		return(Lista[indice]);
	}
	else
	{
		maior=encontrarMaiorValor(Lista, qt_elementos, indice+1);
		if(Lista[indice]>maior)
		{
			return(Lista[indice]);
		}
		else
		{
			return(maior);
		}
	}

}

int calcularSoma(int Lista[], int qt_elementos, int indice) {

	if(indice==qt_elementos-1)
	{
		return(Lista[indice]);
	}
	else
	{
		return(Lista[indice]+calcularSoma(Lista, qt_elementos, indice+1));
	}

}

int calcularProduto(int Lista[], int qt_elementos, int indice) {

	if(indice==qt_elementos-1)
	{
		return(Lista[indice]);
	}
	else
	{
		return(Lista[indice]*calcularProduto(Lista, qt_elementos, indice+1));
	}

}

int realizarBuscaLinear(int Lista[], int qt_elementos, int valor, int indice) {

   contagem++;
   
	if(Lista[indice]==valor)
	{
		return(indice);
	}
	else if(indice==qt_elementos-1)
	{
		return(-1);
	}
	else
	{
		return(realizarBuscaLinear(Lista, qt_elementos, valor, indice+1));
	}

}

int realizarBuscaBinaria(int Lista[], int valor, int inicio, int fim) {

   contagem++;

	int i;
	i=(inicio+fim)/2;
	if(Lista[i]==valor)
	{
		return(i);
	}
	else if(inicio>=fim)
	{
		return(-1);
	}
	else if(Lista[i]<valor)
	{
		return(realizarBuscaBinaria(Lista, valor, i+1, fim));
	}
	else
	{
		return(realizarBuscaBinaria(Lista, valor, inicio, i-1));
	}
}

/* ----------------------------------- */
/* ROTINAS QUE NAO DEVEM SER ALTERADAS */
/* ----------------------------------- */

void inicializarLista(int Lista[], int qt_elementos) {
   int i;

   for (i = 0; i < qt_elementos; i++)
      scanf("%d", &Lista[i]);
}


void imprimirConteudo(int Lista[], int qt_elementos, int indice) {

   if (qt_elementos - indice == 1) {
      printf("%d ", Lista[indice]);
      return;
   } else {
      printf("%d ", Lista[indice]);
      imprimirConteudo(Lista, qt_elementos, ++indice);
      return;
   }

   printf("\n");

}

void ordenador(int indice, int Lista[], int qt_elementos) {
   if (indice < qt_elementos) {
      int j;
      int temp = Lista[indice];
 
      for (j = indice; j > 0 && Lista[j-1] > temp; j--)
         Lista[j] = Lista[j-1];
      Lista[j] = temp;
 
      ordenador(++indice, Lista, qt_elementos);
   }
}

/* Observacoes */
/* As funcoes recursivas de lista descritas neste arquivo utilizam uma variavel chamada indice.
   A utilidade desta variavel eh informar a proxima chamada recursiva qual elemento a funcao deve tratar.
*/
