/* ================================================================== *
   Universidade Federal de Sao Carlos - UFSCar, Sorocaba

   Disciplina: Algoritmos e Programação 2
   Prof. Tiago A. Almeida

   Lista 05 - Exercício 03 - Super Trunfo

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

#define TOTAL_CARTAS 60

#define ATAQUE     0
#define DEFESA     1
#define VELOCIDADE 2
#define MAGIA      3

// Definicao do registro
typedef struct carta{
	int ataque, defesa, velocidade, magia;
}Carta;

// declaracoes das funcoes
void defineVencedor(Carta *jogador1[], Carta *jogador2[], int qtTurnos);
void comparaCartas(Carta *jogador1[], Carta *jogador2[], int atributoEscolhido);
int retornaNulo(Carta *jogador[]);
void ordenaVetor(Carta *jogador[], int tam);


/* ------------------------------ */
/* ROTINA PRINCIPAL - NAO ALTERAR */
/* ------------------------------ */
int main() {

   Carta baralho[TOTAL_CARTAS]; // vetor que armazena todas as cartas existentes
   Carta *jogador1[TOTAL_CARTAS]; // vetor que armazena as cartas do jogador 1
   Carta *jogador2[TOTAL_CARTAS]; // vetor que armazena as cartas do jogador 2
   int qtTurnos = 0; // armazena quantidade de turnos do jogo

   int atributoEscolhido, // atributo escolhido pelo juiz a cada turno
       indice,            // indice do baralho que representa qual carta o jogador pega
       i = 0;

   // le a entrada das cartas
   for (i=0; i < TOTAL_CARTAS; i++) {
      scanf("%d",&baralho[i].ataque);
      scanf("%d",&baralho[i].defesa);
      scanf("%d",&baralho[i].velocidade);
      scanf("%d",&baralho[i].magia);
   }

   // divide as cartas entre os dois jogadores
   for (i=0; i < TOTAL_CARTAS/2; i++) {
      scanf("%d",&indice);
      jogador1[i] = &baralho[indice];
      scanf("%d",&indice);
      jogador2[i] = &baralho[indice];
   }

   // aponta as demais posicoes para null
   for (i=TOTAL_CARTAS/2; i < TOTAL_CARTAS; i++) {
      jogador1[i] = NULL;
      jogador2[i] = NULL;
   }

   // recebe os atributos escolhidos pelo juiz, compara quem venceu o turno,
   // o vencedor fica com as cartas e repete ateh um dos jogadores ficar sem cartas.
   while (jogador1[0] != NULL && jogador2[0] != NULL) {
      scanf("%d",&atributoEscolhido);
      comparaCartas(jogador1, jogador2, atributoEscolhido); // realiza um turno: compara as cartas dos dois jogadores
      //com base no atributo escolhido. O vencedor ganha a carta do oponente. Empate: ambos descartam as cartas.
      qtTurnos++;
   }

   defineVencedor(jogador1, jogador2, qtTurnos);

   return 0;

}

/* ------------------------- */
/* IMPLEMENTACAO DAS FUNCOES */
/* ------------------------- */

void defineVencedor(Carta *jogador1[], Carta *jogador2[], int qtTurnos) {

   if (jogador1[0] == NULL && jogador2[0] == NULL) // se nenhum jogador tem carta, o jogo empatou
      printf("Empate!\n");
   else if (jogador1[0] != NULL) // se o jogador1 ainda tem cartas, ele ganhou
      printf("Jogador 1 venceu!\n");
   else
      printf("Jogador 2 venceu!\n");

   printf("Turnos: %d", qtTurnos);

}

int retornaNulo(Carta *jogador[])
{
	int i=0;
	while(jogador[i]!=NULL)
		i++;
	return(i);
}

void ordenaVetor(Carta *jogador[], int tam)
{
	int i;
	for(i=0; i<tam; i++)
		jogador[i]=jogador[i+1];
}
	
void comparaCartas(Carta *jogador1[], Carta *jogador2[], int atributoEscolhido)
{
	int j;

	if(atributoEscolhido==ATAQUE)
	{
		if((jogador1[0]->ataque)>(jogador2[0]->ataque))
		{
			j=retornaNulo(jogador1);
			jogador1[j]=jogador1[0];
			ordenaVetor(jogador1, j);
			jogador1[j]=jogador2[0];
			ordenaVetor(jogador2, retornaNulo(jogador2));
		}
		else if((jogador1[0]->ataque)<(jogador2[0]->ataque))
		{
			j=retornaNulo(jogador2);
			jogador2[j]=jogador2[0];
			ordenaVetor(jogador2, j);
			jogador2[j]=jogador1[0];
			ordenaVetor(jogador1, retornaNulo(jogador1));
		}
		else
		{
			ordenaVetor(jogador1, retornaNulo(jogador1));
			ordenaVetor(jogador2, retornaNulo(jogador2));
		}
	}
	else if(atributoEscolhido==DEFESA)
	{
		if((jogador1[0]->defesa)>(jogador2[0]->defesa))
		{
			j=retornaNulo(jogador1);
			jogador1[j]=jogador1[0];
			ordenaVetor(jogador1, j);
			jogador1[j]=jogador2[0];
			ordenaVetor(jogador2, retornaNulo(jogador2));
		}
		else if((jogador1[0]->defesa)<(jogador2[0]->defesa))
		{
			j=retornaNulo(jogador2);
			jogador2[j]=jogador2[0];
			ordenaVetor(jogador2, j);
			jogador2[j]=jogador1[0];
			ordenaVetor(jogador1, retornaNulo(jogador1));
		}
		else
		{
			ordenaVetor(jogador1, retornaNulo(jogador1));
			ordenaVetor(jogador2, retornaNulo(jogador2));
		}
	}
	else if(atributoEscolhido==VELOCIDADE)
	{
		if((jogador1[0]->velocidade)>(jogador2[0]->velocidade))
		{
			j=retornaNulo(jogador1);
			jogador1[j]=jogador1[0];
			ordenaVetor(jogador1, j);
			jogador1[j]=jogador2[0];
			ordenaVetor(jogador2, retornaNulo(jogador2));
		}
		else if((jogador1[0]->velocidade)<(jogador2[0]->velocidade))
		{
			j=retornaNulo(jogador2);
			jogador2[j]=jogador2[0];
			ordenaVetor(jogador2, j);
			jogador2[j]=jogador1[0];
			ordenaVetor(jogador1, retornaNulo(jogador1));
		}
		else
		{
			ordenaVetor(jogador1, retornaNulo(jogador1));
			ordenaVetor(jogador2, retornaNulo(jogador2));
		}
	}
	else if(atributoEscolhido==MAGIA)
	{
		if((jogador1[0]->magia)>(jogador2[0]->magia))
		{
			j=retornaNulo(jogador1);
			jogador1[j]=jogador1[0];
			ordenaVetor(jogador1, j);
			jogador1[j]=jogador2[0];
			ordenaVetor(jogador2, retornaNulo(jogador2));
		}
		else if((jogador1[0]->magia)<(jogador2[0]->magia))
		{
			j=retornaNulo(jogador2);
			jogador2[j]=jogador2[0];
			ordenaVetor(jogador2, j);
			jogador2[j]=jogador1[0];
			ordenaVetor(jogador1, retornaNulo(jogador1));
		}
		else
		{
			ordenaVetor(jogador1, retornaNulo(jogador1));
			ordenaVetor(jogador2, retornaNulo(jogador2));
		}
	}
}
			
