/* ================================================================== *
   Universidade Federal de Sao Carlos - UFSCar, Sorocaba

   Disciplina: Algoritmos e Programação 2
   Prof. Tiago A. Almeida

   Lista 07 - Exercício 01 - Polinomio

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

// Opcoes ***********************
#define SAIR 				0
#define ADICIONAR_POLI 		1
#define REMOVER_POLI 		2
#define SOMAR_POLI 			3
#define SUBTRAIR_POLI 		4
#define MULTIPLICAR_POLI 	5
#define CALCULAR_POLI 		6


// declaracoes de registros
typedef struct termo
{
	int coef;
	int exp;
	struct termo *prox;
}Termo;//estrutura que guarda e liga todos os termos do polinomio
typedef struct poli
{
	Termo *inicio;
}Polinomio;//estrutura que guarda o inicio do polinomio

// declaracoes das funcoes
void adicionarPolinomio(Polinomio **p, int coef, int exp);
void removerPolinomio(Polinomio **p, int exp);
Polinomio *somarPolinomios(Polinomio *p1, Polinomio *p2);
Polinomio *subtrairPolinomios(Polinomio *p1, Polinomio *p2);
Polinomio *multiplicarPolinomios(Polinomio *p1, Polinomio *p2);
int calcularPolinomio(Polinomio *p, int x);
void libera(Polinomio *p);

/* ------------------------------ */
/* ROTINA PRINCIPAL - NAO ALTERAR */
/* ------------------------------ */
int main() {

   int x, coef, exp, poliEscolhido, operando1, operando2;
   Polinomio *p1 = NULL;
   Polinomio *p2 = NULL;
   Polinomio *resultado = NULL;

   scanf("%d",&x);

   int opcao = 1;
   while(opcao != 0){
      scanf("%d",&opcao);
      switch(opcao){

         case ADICIONAR_POLI:
            scanf("%d %d %d", &poliEscolhido, &coef, &exp);
            poliEscolhido == 1 ? adicionarPolinomio(&p1,coef,exp) : adicionarPolinomio(&p2,coef,exp);
         break;

         case REMOVER_POLI:
            scanf("%d %d", &poliEscolhido, &exp);
            poliEscolhido == 1 ? removerPolinomio(&p1,exp) : removerPolinomio(&p2,exp);
         break;

         case SOMAR_POLI:
            if(resultado != NULL) libera(resultado);
            resultado = somarPolinomios(p1,p2);
         break;

         case SUBTRAIR_POLI:
            scanf("%d %d", &operando1, &operando2);
            if(resultado != NULL) libera(resultado);
            resultado = subtrairPolinomios(operando1 == 1 ? p1 : p2, operando2 == 2 ? p2 : p1);
         break;

         case MULTIPLICAR_POLI:
            if(resultado != NULL) libera(resultado);
            resultado = multiplicarPolinomios(p1,p2);
         break;

         case CALCULAR_POLI:
            scanf("%d",&poliEscolhido);
            switch(poliEscolhido) {
               case 1: printf("%d\n",calcularPolinomio(p1,x)); break;
               case 2: printf("%d\n",calcularPolinomio(p2,x)); break;
               case 3: printf("%d\n",calcularPolinomio(resultado,x)); break;
            }
         break;

      }
   }

   return (0);

}

/* ------------------------- */
/* IMPLEMENTACAO DAS FUNCOES */
/* ------------------------- */

void adicionarPolinomio(Polinomio **p, int coef, int exp)
{
	if((*p)==NULL)//caso o polinomio ainda nao exista
	{
		(*p)=(Polinomio *)malloc(sizeof(Polinomio));//aloca espaço para o inicio do polinomio
		(*p)->inicio=(Termo *)malloc(sizeof(Termo));//aloca espaço para o primeiro termo
		//preenchedo o primeiro termo do polinomio
		(*p)->inicio->coef=coef;
		(*p)->inicio->exp=exp;
		(*p)->inicio->prox=NULL;
		//preenchedo o primeiro termo do polinomio
		return;
	}
	Termo *aux=(Termo *)malloc(sizeof(Termo));//caso tenha pelo menos um termo no polinomio
	Termo *i;
	Termo **j;
	aux->coef=coef;
	aux->exp=exp;
	aux->prox=NULL;
	/*insere o novo termo em ordem crescente na lista. i guarda a posiçao atual (para comparar coef e exp)
	 e j guarda o ponteiro que aponta para i (para poder inserir o novo termo, fazendo quem apontava para i)
	 passar a apontar para aux*/
	for(i=(*p)->inicio, j=&((*p)->inicio); i!=NULL; i=i->prox, j=&((*j)->prox))
	{
		if((aux->exp)==(i->exp))//caso os expoentes sejam iguais os coef sao somados e aux é jogado fora
		{
			i->coef=(aux->coef)+(i->coef);
			free(aux);
			return;
		}
		else if((aux->exp)<(i->exp))//se o expoente de aux for menor do que o de i acontece a inserçao de aux
		{
			aux->prox=i;
			*j=aux;
			return;
		}
	}
	*j=aux;//caso o expoente de aux seja o maior
}
void removerPolinomio(Polinomio **p, int exp)
{
	Termo *i, **j;
	if((*p)->inicio->prox==NULL&&(*p)->inicio->exp==exp)//caso tenha um termo e o usuario queira o returar
	{
		free((*p)->inicio);//libera o termo
		free((*p));//libera o polinomio
		(*p)=NULL;
		return;
	}
	for(i=(*p)->inicio, j=&((*p)->inicio); i!=NULL; i=i->prox, j=&((*j)->prox))//for igual ao adicionarPolinomio
	{
		if(i->exp==exp)
		{
			*j=i->prox;
			free(i);
			return;
		}
	}
}
Polinomio *somarPolinomios(Polinomio *p1, Polinomio *p2)
{
	if(p1==NULL&&p2==NULL)//caso os dois polinomios nao existam
		return(NULL);
	else if(p1==NULL)//caso apenas o primeiro nao exista
		return(p2);
	else if(p2==NULL)//caso apenas o segundo nao exista
		return(p1);
	Polinomio *aux=(Polinomio *)malloc(sizeof(Polinomio));
	aux->inicio=(Termo *)malloc(sizeof(Termo));//retornara o polinomio auxiliar como resultado
	Termo *i=p1->inicio, *j=p2->inicio, *k=aux->inicio;
	for(;i!=NULL&&j!=NULL; k=k->prox)//varre p1 e p2 para colocar cada termo em aux
	{
		if(i->exp==j->exp)//caso os dois expoentes sejam iguais juntara em 1 termo de aux
		{
			k->coef=(i->coef)+(j->coef);
			k->exp=i->exp;
			//andando com i e j
			i=i->prox;
			j=j->prox;
			k->prox=(Termo *)malloc(sizeof(Termo));//aloca espaço para o proximo termo
			if(i==NULL&&j==NULL)//caso os dois polinomios acabem junto
			{
				free(k->prox);//libera o termo nao utilizado
				k->prox=NULL;
			}
		}
		else if((i->exp)>(j->exp))//caso o expoente de i seja maior que j
		{
			//copia o coeficiente e o expoente de j em aux
			k->coef=j->coef;
			k->exp=j->exp;
			j=j->prox;//anda apenas com o j
			k->prox=(Termo *)malloc(sizeof(Termo));
		}
		else//caso o expoente de j seja maior que i
		{
			//copia o coeficiente e o expoente de i em aux
			k->coef=i->coef;
			k->exp=i->exp;
			i=i->prox;//anda apenas com i
			k->prox=(Termo *)malloc(sizeof(Termo));
		}
	}
	if(i==NULL&&j!=NULL)//caso saia do for mas nao tenha varrido j por compeleto
	{
		for(;j->prox!=NULL; j=j->prox,k=k->prox)//confere ate o j->prox para nao ter um termo nao utilizado em k
		{
			k->coef=j->coef;
			k->exp=j->exp;
			k->prox=(Termo *)malloc(sizeof(Termo));
		}
		//como a condiçao do for acima é ate j->prox o ultimo termo deve ser feito manualmente
		k->coef=j->coef;
		k->exp=j->exp;
		k->prox=NULL;
	}
	else if(i!=NULL&&j==NULL)//caso saia do for mas nao tenha varrido i por completo
	{
		//mesma logica do if anterior
		for(;i->prox!=NULL; i=i->prox,k=k->prox)
		{
			k->coef=i->coef;
			k->exp=i->exp;
			k->prox=(Termo *)malloc(sizeof(Termo));
		}
		k->coef=i->coef;
		k->exp=i->exp;
		k->prox=NULL;
	}
	return(aux);
}
Polinomio *subtrairPolinomios(Polinomio *p1, Polinomio *p2)
{
	//mesma logica de somarPolinomios
	if(p1==NULL&&p2==NULL)
		return(NULL);
	else if(p1==NULL)
		return(p2);
	else if(p2==NULL)
		return(p1);
	Polinomio *aux=(Polinomio *)malloc(sizeof(Polinomio));
	aux->inicio=(Termo *)malloc(sizeof(Termo));
	Termo *i=p1->inicio, *j=p2->inicio, *k=aux->inicio;
	for(;i!=NULL&&j!=NULL; k=k->prox)
	{
		if(i->exp==j->exp)
		{
			k->coef=(i->coef)-(j->coef);
			k->exp=i->exp;
			i=i->prox;
			j=j->prox;
			k->prox=(Termo *)malloc(sizeof(Termo));
			if(i==NULL&&j==NULL)
			{
				free(k->prox);
				k->prox=NULL;
			}
		}
		else if((i->exp)>(j->exp))
		{
			k->coef=-(j->coef);
			k->exp=j->exp;
			j=j->prox;
			k->prox=(Termo *)malloc(sizeof(Termo));
		}
		else
		{
			k->coef=i->coef;
			k->exp=i->exp;
			i=i->prox;
			k->prox=(Termo *)malloc(sizeof(Termo));
		}
	}
	if(i==NULL&&j!=NULL)
	{
		for(;j->prox!=NULL; j=j->prox,k=k->prox)
		{
			k->coef=-(j->coef);
			k->exp=j->exp;
			k->prox=(Termo *)malloc(sizeof(Termo));
		}
		k->coef=-(j->coef);
		k->exp=j->exp;
		k->prox=NULL;
	}
	else if(i!=NULL&&j==NULL)
	{
		for(;i->prox!=NULL; i=i->prox,k=k->prox)
		{
			k->coef=i->coef;
			k->exp=i->exp;
			k->prox=(Termo *)malloc(sizeof(Termo));
		}
		k->coef=i->coef;
		k->exp=i->exp;
		k->prox=NULL;
	}
	return(aux);	
}
Polinomio *multiplicarPolinomios(Polinomio *p1, Polinomio *p2)
{
	if(p1==NULL&&p2==NULL)
		return(NULL);
	else if(p1==NULL)
		return(p2);
	else if(p2==NULL)
		return(p1);
	Polinomio *aux=(Polinomio *)malloc(sizeof(Polinomio));
	aux->inicio=(Termo *)malloc(sizeof(Termo));
	Termo *i=p1->inicio, *j=p2->inicio, *k=aux->inicio, **l;
	/*multiplica cada coeficiente de i com j e soma cada expoente de i com j. k aponta para o termo atual e l
	apomta para quem aponta para k */
	for(;i!=NULL; i=i->prox)
	{
		for(j=p2->inicio; j!=NULL; j=j->prox, k=k->prox)
		{
			k->coef=(i->coef)*(j->coef);
			k->exp=(i->exp)+(j->exp);
			k->prox=(Termo *)malloc(sizeof(Termo));
			l=&(k->prox);
		}
	}
	free(k);//libera o ultimo termo(nao é utilizado)
	*l=NULL;//aponta *l (ponteiro que apontava para k) para null
	return(aux);
}
int calcularPolinomio(Polinomio *p, int x)
{
	int cont=0;
	Termo *i;
	//percorre o polinomio somando todos os termos
	for(i=p->inicio; i!=NULL; i=i->prox)
	{
		cont=cont+((i->coef)*(pow(x,(i->exp))));
	}
	return(cont);
}
void libera(Polinomio *p)
{
	Termo *aux, *i;
	for(i=p->inicio;i!=NULL;)
	{
		aux=i;
		i=i->prox;
		free(aux);
	}
	free(p);
	p=NULL;
}