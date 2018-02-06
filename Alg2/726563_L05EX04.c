/* ================================================================== *
   Universidade Federal de Sao Carlos - UFSCar, Sorocaba

   Disciplina: Algoritmos e Programação 2
   Prof. Tiago A. Almeida

   Lista 05 - Exercício 04 - Cadastro de Super-Herois

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

// SAIR ****************** //
#define SAIR               0
// HEROI ***************** //    
#define ADICIONAR_HEROI    11
#define ALTERAR_HEROI      12
#define EXCLUIR_HEROI      13
#define CONSULTAR_HEROI    14
// PODER ***************** //
#define ADICIONAR_PODER    21
#define ALTERAR_PODER      22
#define EXCLUIR_PODER      23
#define CONSULTAR_PODER    24
#define ASSOCIAR_PODER     25
// EVENTO **************** //
#define ADICIONAR_EVENTO   31
#define ALTERAR_EVENTO     32
#define EXCLUIR_EVENTO     33
#define CONSULTAR_EVENTO   34
#define ASSOCIAR_EVENTO    35

// MENSAGENS ******************************************************** //
#define HEROI_CADASTRADO "O heroi foi cadastrado com sucesso.\n"
#define HEROI_ALTERADO "O heroi foi alterado com sucesso.\n"
#define HEROI_EXCLUIDO "O heroi foi excluido com sucesso.\n"
#define COD_HEROI_JA_CADASTRADO "Ja existe um heroi com este codigo.\n"
#define COD_HEROI_NAO_CADASTRADO "Nao existe um heroi com este codigo.\n"
#define PODER_CADASTRADO "O poder foi cadastrado com sucesso.\n"
#define PODER_ALTERADO "O poder foi alterado com sucesso.\n"
#define PODER_EXCLUIDO "O poder foi excluido com sucesso.\n"
#define PODER_ASSOCIADO "O poder e o heroi foram associados.\n"
#define COD_PODER_JA_CADASTRADO "Ja existe um poder com este codigo.\n"
#define COD_PODER_NAO_CADASTRADO "Nao existe um poder com este codigo.\n"
#define PROBLEMA_ASSOCIAR_PODER "Houve um problema ao tentar associar o poder.\n"
#define EVENTO_CADASTRADO "O evento foi cadastrado com sucesso.\n"
#define EVENTO_ALTERADO "O evento foi alterado com sucesso.\n"
#define EVENTO_EXCLUIDO "O evento foi excluido com sucesso.\n"
#define EVENTO_ASSOCIADO "O evento e o heroi foram associados.\n"
#define COD_EVENTO_JA_CADASTRADO "Ja existe um evento com este codigo.\n"
#define COD_EVENTO_NAO_CADASTRADO "Nao existe um evento com este codigo.\n"
#define PROBLEMA_ASSOCIAR_EVENTO "Houve um problema ao tentar associar o evento.\n"

// VARIAVEIS DE TAMANHO //
#define MAX_NOME 100
#define MAX_HEROI 20
#define MAX_EVENTO 20
#define MAX_PODER 60

typedef struct poder{
   int codPoder;
   char nome[MAX_NOME];
   int tempoRecarga; // medido em minutos
} Poder;

typedef struct heroi{
   int codHeroi;
   char nome[MAX_NOME];
   int ano;
   Poder *poder;
} Heroi;

typedef struct evento{
   int codEvento;
   char nome[MAX_NOME];
   int ano;
   int numHerois;
   Heroi *heroisEnvolvidos[MAX_HEROI];
} Evento;


// declaracoes das funcoes
void adicionaHeroi(Heroi herois[], int *numHerois, int codHeroi, int ano, char nome[]);
void alteraHeroi(Heroi herois[], int numHerois, int codHeroi, int ano, char nome[]);
void excluiHeroi(Heroi herois[], int *numHerois, int codHeroi);
int consultaHeroi(Heroi herois[], int numHerois, int codHeroi);
void adicionaPoder(Poder poderes[], int *numPoderes, int codPoder, int tempoRecarga, char nome[]);
void alteraPoder(Poder poderes[], int numPoderes, int codPoder, int tempoRecarga, char nome[]);
void excluiPoder(Poder poderes[], int *numPoderes, int codPoder);
int consultaPoder(Poder poderes[], int numPoderes, int codPoder);
void associaPoder(Heroi herois[], int numHerois, Poder poderes[], int numPoderes, int codHeroi, int codPoder);
void adicionaEvento(Evento eventos[], int *numEventos, int codEvento, int ano, char nome[]);
void alteraEvento(Evento eventos[], int numEventos, int codEvento, int ano, char nome[]);
void excluiEvento(Evento eventos[], int *numEventos, int codEvento);
int consultaEvento(Evento eventos[], int numEventos, int codEvento);
void associaEvento(Evento eventos[], int numEventos, Heroi herois[], int numHerois, int codEvento, int codHeroi);
void imprimeHeroisPorEvento(Heroi *heroisEnvolvidos[], int numHerois);


/* ------------------------------ */
/* ROTINA PRINCIPAL - NAO ALTERAR */
/* ------------------------------ */
int main(){

   Heroi herois[MAX_HEROI]; // vetor com todos herois do sistema
   Poder poderes[MAX_PODER]; // vetor com todos herois do sistema
   Evento eventos[MAX_EVENTO]; // vetor com todos herois do sistema

   int numHerois = 0, numPoderes = 0, numEventos = 0;
   int indice;

   // Variaveis para receber os valores de entrada
   int codHeroi, codEvento, codPoder, codPoder2, codPoder3, tempoRecarga, ano;
   char nome[MAX_NOME];

   int opcao = 1;
   while(opcao != 0){
      scanf("%d",&opcao);
      switch(opcao){
         case ADICIONAR_HEROI:
            scanf("%d %d %[^\n]s",&codHeroi, &ano, nome);
            adicionaHeroi(herois, &numHerois, codHeroi, ano, nome);
         break;

         case ALTERAR_HEROI:
            scanf("%d %d %[^\n]s",&codHeroi, &ano, nome);
            alteraHeroi(herois, numHerois, codHeroi, ano, nome);
         break;

         case EXCLUIR_HEROI:
            scanf("%d",&codHeroi);
            excluiHeroi(herois, &numHerois, codHeroi);
         break;

         case CONSULTAR_HEROI:
            scanf("%d",&codHeroi);
            indice = consultaHeroi(herois, numHerois, codHeroi);
            if (indice >= 0) {
               printf("Cod: %d - Ano: %d - Heroi: %s\n", herois[indice].codHeroi, herois[indice].ano, herois[indice].nome);  
            } else {
               printf(COD_HEROI_NAO_CADASTRADO);
            }
         break;

         case ADICIONAR_PODER:
            scanf("%d %d %[^\n]s",&codPoder, &tempoRecarga, nome);
            adicionaPoder(poderes, &numPoderes, codPoder, tempoRecarga, nome);
         break;

         case ALTERAR_PODER:
            scanf("%d %d %[^\n]s",&codPoder, &tempoRecarga, nome);
            alteraPoder(poderes, numPoderes, codPoder, tempoRecarga, nome);
         break;

         case EXCLUIR_PODER:
            scanf("%d",&codPoder);
            excluiPoder(poderes, &numPoderes, codPoder);
         break;

         case CONSULTAR_PODER:
            scanf("%d",&codPoder);
            indice = consultaPoder(poderes, numPoderes, codPoder);
            if (indice >= 0) {
               printf("Cod: %d - Tempo Recarga: %d - Poder: %s\n",
                          poderes[indice].codPoder, poderes[indice].tempoRecarga, poderes[indice].nome);  
            } else {
               printf(COD_PODER_NAO_CADASTRADO);
            }
         break;

         case ASSOCIAR_PODER:
            scanf("%d %d",&codHeroi, &codPoder);
            associaPoder(herois, numHerois, poderes, numPoderes, codHeroi, codPoder);
         break;

         case ADICIONAR_EVENTO:
            scanf("%d %d %[^\n]s",&codEvento, &ano, nome);
            adicionaEvento(eventos, &numEventos, codEvento, ano, nome);
         break;

         case ALTERAR_EVENTO:
            scanf("%d %d %[^\n]s",&codEvento, &ano, nome);
            alteraEvento(eventos, numEventos, codEvento, ano, nome);
         break;

         case EXCLUIR_EVENTO:
            scanf("%d",&codEvento);
            excluiEvento(eventos, &numEventos, codEvento);
         break;

         case CONSULTAR_EVENTO:
            scanf("%d",&codEvento);
            indice = consultaEvento(eventos, numEventos, codEvento);
            if (indice >= 0) {
               printf("Cod: %d - Ano: %d - Evento: %s\n", 
                        eventos[indice].codEvento, eventos[indice].ano, eventos[indice].nome);
               imprimeHeroisPorEvento(eventos[indice].heroisEnvolvidos, eventos[indice].numHerois);
            } else {
               printf(COD_EVENTO_NAO_CADASTRADO);
            }
         break;

         case ASSOCIAR_EVENTO:
            scanf("%d %d",&codEvento, &codHeroi);
            associaEvento(eventos, numEventos, herois, numHerois, codEvento, codHeroi);
         break;
      }
   }
  
   return 0;
}

/* ------------------------- */
/* IMPLEMENTACAO DAS FUNCOES */
/* ------------------------- */

void adicionaHeroi(Heroi herois[], int *numHerois, int codHeroi, int ano, char nome[])
{
	int i, flag=0;
	for(i=0; i<*numHerois&&flag==0; i++)
		if(codHeroi==herois[i].codHeroi)
			flag=1;
	if(flag)
		printf(COD_HEROI_JA_CADASTRADO);
	else
	{
		herois[*numHerois].codHeroi=codHeroi;
		herois[*numHerois].ano=ano;
		strcpy(herois[*numHerois].nome,nome);
		*numHerois=*numHerois+1;
		printf(HEROI_CADASTRADO);
	}
}

void alteraHeroi(Heroi herois[], int numHerois, int codHeroi, int ano, char nome[])
{
	int i, flag=0;
	for(i=0; i<numHerois&&flag==0; i++)
	{
		if(codHeroi==herois[i].codHeroi)
		{
			flag=1;
			herois[i].ano=ano;
			strcpy(herois[i].nome,nome);
		}
	}
	if(flag)
		printf(HEROI_ALTERADO);
	else
		printf(COD_HEROI_NAO_CADASTRADO);
}

void excluiHeroi(Heroi herois[], int *numHerois, int codHeroi)
{
	int i, flag=0;
	for(i=0; i<*numHerois-1; i++)
	{
		if(flag)
			herois[i]=herois[i+1];
		else if(herois[i].codHeroi==codHeroi)
		{
			flag=1;
			herois[i]=herois[i+1];
		}
	}
	if(flag==0&&herois[*numHerois-1].codHeroi==codHeroi)
	{
		*numHerois=*numHerois-1;
		printf(HEROI_EXCLUIDO);
	}
	else if(flag==1)
	{
		*numHerois=*numHerois-1;
		printf(HEROI_EXCLUIDO);
	}
	else
		printf(COD_HEROI_NAO_CADASTRADO);
}

int consultaHeroi(Heroi herois[], int numHerois, int codHeroi)
{
	int i;
	for(i=0; i<numHerois; i++)
		if(herois[i].codHeroi==codHeroi)
			return(i);
	return(-1);
}

void adicionaPoder(Poder poderes[], int *numPoderes, int codPoder, int tempoRecarga, char nome[])
{
	int i, flag=0;
	for(i=0; i<*numPoderes&&flag==0; i++)
		if(codPoder==poderes[i].codPoder)
			flag=1;
	if(flag)
		printf(COD_PODER_JA_CADASTRADO);
	else
	{
		poderes[*numPoderes].codPoder=codPoder;
		poderes[*numPoderes].tempoRecarga=tempoRecarga;
		strcpy(poderes[*numPoderes].nome,nome);
		*numPoderes=*numPoderes+1;
		printf(PODER_CADASTRADO);
	}
}

void alteraPoder(Poder poderes[], int numPoderes, int codPoder, int tempoRecarga, char nome[])
{
	int i, flag=0;
	for(i=0; i<numPoderes&&flag==0; i++)
	{
		if(codPoder==poderes[i].codPoder)
		{
			flag=1;
			poderes[i].tempoRecarga=tempoRecarga;
			strcpy(poderes[i].nome,nome);
		}
	}
	if(flag)
		printf(PODER_ALTERADO);
	else
		printf(COD_PODER_NAO_CADASTRADO);
}

void excluiPoder(Poder poderes[], int *numPoderes, int codPoder)
{
	int i, flag=0;
	for(i=0; i<*numPoderes-1; i++)
	{
		if(flag)
			poderes[i]=poderes[i+1];
		else if(poderes[i].codPoder==codPoder)
		{
			flag=1;
			poderes[i]=poderes[i+1];
		}
	}
	if(flag==0&&poderes[*numPoderes-1].codPoder==codPoder)
	{
		*numPoderes=*numPoderes-1;
		printf(PODER_EXCLUIDO);
	}
	else if(flag==1)
	{
		*numPoderes=*numPoderes-1;
		printf(PODER_EXCLUIDO);
	}
	else
		printf(COD_PODER_NAO_CADASTRADO);
}

int consultaPoder(Poder poderes[], int numPoderes, int codPoder)
{
	int i;
	for(i=0; i<numPoderes; i++)
		if(poderes[i].codPoder==codPoder)
			return(i);
	return(-1);
}

void associaPoder(Heroi herois[], int numHerois, Poder poderes[], int numPoderes, int codHeroi, int codPoder)
{
	int i, j, flag=0;
	for(i=0; i<numHerois&&flag==0; i++)
	{
		if(herois[i].codHeroi==codHeroi)
		{
			for(j=0; j<numPoderes&&flag==0; j++)
			{
				if(poderes[j].codPoder==codPoder)
				{
					herois[i].poder=&poderes[j];
					flag=1;
				}
			}
		}
	}
	if(flag)
		printf(PODER_ASSOCIADO);
	else
		printf(PROBLEMA_ASSOCIAR_PODER);
}

void adicionaEvento(Evento eventos[], int *numEventos, int codEvento, int ano, char nome[])
{
	int i, flag=0;
	for(i=0; i<*numEventos&&flag==0; i++)
		if(codEvento==eventos[i].codEvento)
			flag=1;
	if(flag)
		printf(COD_EVENTO_JA_CADASTRADO);
	else
	{
		eventos[*numEventos].codEvento=codEvento;
		eventos[*numEventos].ano=ano;
		strcpy(eventos[*numEventos].nome,nome);
		*numEventos=*numEventos+1;
		printf(EVENTO_CADASTRADO);
	}
}

void alteraEvento(Evento eventos[], int numEventos, int codEvento, int ano, char nome[])
{
	int i, flag=0;
	for(i=0; i<numEventos&&flag==0; i++)
	{
		if(codEvento==eventos[i].codEvento)
		{
			flag=1;
			eventos[i].ano=ano;
			strcpy(eventos[i].nome,nome);
		}
	}
	if(flag)
		printf(EVENTO_ALTERADO);
	else
		printf(COD_EVENTO_NAO_CADASTRADO);
}

void excluiEvento(Evento eventos[], int *numEventos, int codEvento)
{
	int i, flag=0;
	for(i=0; i<*numEventos-1; i++)
	{
		if(flag)
			eventos[i]=eventos[i+1];
		else if(eventos[i].codEvento==codEvento)
		{
			flag=1;
			eventos[i]=eventos[i+1];
		}
	}
	if(flag==0&&eventos[*numEventos-1].codEvento==codEvento)
	{
		*numEventos=*numEventos-1;
		printf(EVENTO_EXCLUIDO);
	}
	else if(flag==1)
	{
		*numEventos=*numEventos-1;
		printf(EVENTO_EXCLUIDO);
	}
	else
		printf(COD_EVENTO_NAO_CADASTRADO);
}

int consultaEvento(Evento eventos[], int numEventos, int codEvento)
{
	int i;
	for(i=0; i<numEventos; i++)
		if(eventos[i].codEvento==codEvento)
			return(i);
	return(-1);
}

void associaEvento(Evento eventos[], int numEventos, Heroi herois[], int numHerois, int codEvento, int codHeroi)
{
	int i, j, flag=0;
	for(i=0; i<numEventos&&flag==0; i++)
	{
		if(eventos[i].codEvento==codEvento)
		{
			for(j=0; j<numHerois&&flag==0; j++)
			{
				if(herois[j].codHeroi==codHeroi)
				{
					if(eventos[i].numHerois>=20)
						eventos[i].numHerois=0;
					eventos[i].heroisEnvolvidos[eventos[i].numHerois]=&herois[j];
					eventos[i].numHerois++;
					flag=1;
				}
			}
		}
	}
	if(flag)
		printf(EVENTO_ASSOCIADO);
	else
		printf(PROBLEMA_ASSOCIAR_EVENTO);
}

void imprimeHeroisPorEvento(Heroi *heroisEnvolvidos[], int numHerois)
{
	int i;
	if(numHerois>=20)
		numHerois=0;
	for(i=0; i<numHerois; i++)
	{
		puts(heroisEnvolvidos[i]->nome);
	}
}
