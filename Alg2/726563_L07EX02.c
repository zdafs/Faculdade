/* ================================================================== *
   Universidade Federal de Sao Carlos - UFSCar, Sorocaba

   Disciplina: Algoritmos e Programação 2
   Prof. Tiago A. Almeida

   Lista 07 - Exercício 02 - Fila e Pilha

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
#include <math.h>

// Estruturas *********************
#define FILA			100
#define PILHA			200

// Opcoes ***********************
#define SAIR 				0
#define ADICIONAR 			1
#define REMOVER				2
#define PROCURAR 			3
#define CALCULAR_TAMANHO 	4
#define IMPRIMIR 			5

// declaracoes de registros
/* <<< DEFINA OS REGISTROS AQUI >>> */
typedef struct registro {
   int valor;
   struct registro* prox;
} Registro;

// declaracoes das funcoes
Registro *adicionarElementoFila(Registro *fila, int valor);
Registro *adicionarElementoPilha(Registro *pilha, int valor);
Registro *removerElementoFila(Registro *fila);
Registro *removerElementoPilha(Registro *pilha);
int procurarElemento(Registro *x, int valor);
int calcularTamanho(Registro *x);
void imprimir(Registro *x);
void libera(Registro *x);

/* ------------------------------ */
/* ROTINA PRINCIPAL - NAO ALTERAR */
/* ------------------------------ */
int main() {

   int valor, estrutura;
   Registro *pilha = NULL;
   Registro *fila = NULL;

   int opcao = 1;
   while(opcao != 0){
      scanf("%d",&opcao);
      switch(opcao){

         case ADICIONAR:
            scanf("%d %d", &estrutura, &valor);
            if(estrutura == 100)
               fila = adicionarElementoFila(fila, valor);
            else
               pilha = adicionarElementoPilha(pilha, valor);
         break;

         case REMOVER:
            scanf("%d", &estrutura);
            if(estrutura == 100)
               fila = removerElementoFila(fila);
            else
               pilha = removerElementoPilha(pilha);
         break;

         case PROCURAR:
            scanf("%d %d", &estrutura, &valor);
            printf("%d\n", procurarElemento(estrutura == 100 ? fila : pilha, valor));
         break;

         case CALCULAR_TAMANHO:
            scanf("%d", &estrutura);
            printf("%d\n", calcularTamanho(estrutura == 100 ? fila : pilha));
         break;

         case IMPRIMIR:
            scanf("%d", &estrutura);
            imprimir(estrutura == 100 ? fila : pilha);
         break;

      }
   }

   libera(fila);
   libera(pilha);

   return (0);

}

/* ------------------------- */
/* IMPLEMENTACAO DAS FUNCOES */
/* ------------------------- */

Registro *adicionarElementoFila(Registro *fila, int valor)
{
   Registro *i=fila;
   if(i!=NULL)
   {
      while(i->prox!=NULL)
         i=i->prox;
      i->prox=(Registro *) malloc(sizeof(Registro));
      i->prox->valor=valor;
      i->prox->prox=NULL;
      return(fila);
   }
   else
   {
      i=(Registro *) malloc(sizeof(Registro));
      i->valor=valor;
      i->prox=NULL;  
   }
   return(i);

}
Registro *adicionarElementoPilha(Registro *pilha, int valor)
{
   Registro *i=pilha;
   //Guarda temporiariamente o novo valor da lista 
   Registro *aux=(Registro *)malloc(sizeof(Registro));
   aux->valor=valor;
   aux->prox=NULL;
   if(i!=NULL)
   {
      //faz o novo elemento apontar para o antigo topo da pilha
      aux->prox=pilha;
   }
   //aponta o topo da pilha para o novo elemento
   return(aux);
}
Registro *removerElementoFila(Registro *fila)
{
   if(fila!=NULL)
   {
      if(fila->prox==NULL)
      {
         free(fila);
         return(NULL);
      }
      Registro *aux;
      //Guarda a posição do primeiro da fila
      aux=fila;
      //passa o inicio da fila para a segunda posição
      fila=fila->prox;
      //libera a primeira posição
      free(aux);
      return(fila);
   }
   else
      return(NULL);
}
Registro *removerElementoPilha(Registro *pilha)
{
   if(pilha!=NULL)
   {
      if(pilha->prox==NULL)
      {
         free(pilha);
         return(NULL);
      }
      Registro *aux;
      //guarda o topo da pilha
      aux=pilha;
      //passa o topo da pilha para o anterior
      pilha=pilha->prox;
      //libera o antigo topo da pilha
      free(aux);
      return(pilha);
   }
   else
      return(NULL);
}
int procurarElemento(Registro *x, int valor)
{
   Registro *i=x;
   int cont=0;
   for(;i!=NULL;i=i->prox)
   {
      if(i->valor==valor)
         return(cont);
      cont++;
   }
   return(-1);
}
int calcularTamanho(Registro *x)
{
   Registro *i=x;
   int cont=0;
   for(;i!=NULL;i=i->prox)
      cont++;
   return(cont);
}
void imprimir(Registro *x)
{
   Registro *i=x;
   for(;i!=NULL;i=i->prox)
      printf("%d ", i->valor);
   printf("\n");
}
void libera(Registro *x)
{
   Registro *aux;
   while(x!=NULL)
   {
      aux=x;
      x=x->prox;
      free(aux);
   }
}