/* ================================================================== *
    Universidade Federal de Sao Carlos - UFSCar, Sorocaba

    Disciplina: Algoritmos e Programação 1
    Prof. Tiago A. Almeida

    Lista 06 - Exercício 05 - Estante de livros

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

#define MAX 100
#define MSG_INSIRA_LIVROS 	"coloque os livros primeiro\n"
#define MSG_TAM_MAX 		"impossivel colocar, a estante esta cheia\n"
#define MSG_VAZIA			"a estante esta vazia\n"
#define MSG_JA_EXISTE 		"o exemplar ja esta na estante\n"
#define MSG_N_ENCONTRADO 	"livro nao encontrado\n"
#define MSG_INDICE 			"indice do livro: %02d\n"
#define MSG_EXIBICAO_ORD	"[%03d, a:%02d](%02d) "
#define MSG_EXIBICAO		"[%03d, a:%02d] "


typedef struct marcacao
{
	int titulo, autor, index;
}Marcacao;

int main() {    

	int op, numLivros=0, aux, entrou, i, j, conf=0;
	Marcacao estante[MAX], est_aux, est_aux2, VetAUX[MAX];

	do {
		do
		{
			scanf("%d", &op);
		}
		while(op<0||op>9);

		if(op==1||conf!=0)
		{

			// A estrutura do switch pode ser alterada caso deseje
			switch (op) {

				case 1: // Le o vetor
				
					conf++;
					do
					{
						scanf("%d", &numLivros);
					}
					while(numLivros<0||numLivros>MAX);
					for(i=0;i<numLivros;i++)
					{
						do
						{
							entrou=0;
							scanf("%d %d", &estante[i].titulo, &estante[i].autor);
							for(j=i-1;j>=0&&entrou==0;j--)
							{
								if(estante[i].titulo==estante[j].titulo)
								{
									entrou++;
									printf(MSG_JA_EXISTE);
								}
							}
						}
						while(entrou!=0);
					}
				
					break;

				case 2: // Insere no inicio

					scanf("%d %d", &est_aux.titulo, &est_aux.autor);
					if(numLivros==MAX)
					{
						printf(MSG_TAM_MAX);
					}
					else
					{
						entrou=0;
						for(i=0;i<numLivros&&entrou==0;i++)
						{
							if(est_aux.titulo==estante[i].titulo)
							{
								entrou++;
								printf(MSG_JA_EXISTE);
							}	
						}
						if(entrou==0)
						{
							for(i=0;i<numLivros;i++)
							{
								est_aux2=estante[i];
								estante[i]=est_aux;
								est_aux=est_aux2;
							}
							estante[numLivros]=est_aux;
							numLivros++;
						}
					}

					break;

				case 3: // Insere no final

					scanf("%d %d", &estante[numLivros].titulo, &estante[numLivros].autor);
					if(numLivros==MAX)
					{
						printf(MSG_TAM_MAX);
					}
					else
					{
						entrou=0;
						for(i=0;i<numLivros&&entrou==0;i++)
						{
							if(estante[numLivros].titulo==estante[i].titulo)
							{
								entrou++;
								printf(MSG_JA_EXISTE);
							}	
						}
						if(entrou==0)
						{
							numLivros++;
						}
					}

					break;

				case 4: // Busca

					scanf("%d", &aux);
					if(numLivros==0)
					{
						printf(MSG_VAZIA);
					}
					else
					{
						entrou=0;
						for(i=0;i<numLivros;i++)
						{
							if(aux==estante[i].titulo)
							{
								entrou++;
								printf(MSG_INDICE, i+1);
							}
						}
						if(entrou==0)
						{
							printf(MSG_N_ENCONTRADO);
						}
					}

					break;

				case 5: // Remove

					scanf("%d", &aux);
					if(numLivros==0)
					{
						printf(MSG_VAZIA);
					}
					else
					{
						entrou=0;
						for(i=0;i<numLivros&&entrou==0;i++)
						{
							if(aux==estante[i].titulo)
							{
								j=i;
								entrou++;
								printf(MSG_INDICE, i+1);
							}
						}
						if(entrou==0)
						{
							printf(MSG_N_ENCONTRADO);
						}
						else
						{
							for(;j<numLivros;j++)
							{
								estante[j]=estante[j+1];
							}
							numLivros--;
						}
					}

					break;

				case 6: // Imprime ordenado

					if(numLivros==0)
					{
						printf(MSG_VAZIA);
					}
					else
					{
						for(i=0;i<numLivros;i++)
						{
							estante[i].index=i+1;
							VetAUX[i]=estante[i];
						}
						for(i=0;i<numLivros;i++)
						{
							for(j=i+1;j<numLivros;j++)
							{
								if(VetAUX[i].autor>VetAUX[j].autor)
								{
									est_aux=VetAUX[i];
									VetAUX[i]=VetAUX[j];
									VetAUX[j]=est_aux;
								}
								if(VetAUX[i].autor==VetAUX[j].autor)
								{
									if(VetAUX[i].titulo>VetAUX[j].titulo)
									{
										est_aux=VetAUX[i];
										VetAUX[i]=VetAUX[j];
										VetAUX[j]=est_aux;
									}
								}
							}
						}
						for(i=0;i<numLivros;i++)
						{
							printf(MSG_EXIBICAO_ORD, VetAUX[i].titulo, VetAUX[i].autor, VetAUX[i].index);
						}
						printf("\n");
					}

					break;

				case 7: // Imprime

					if(numLivros==0)
					{
						printf(MSG_VAZIA);
					}
					else
					{
						for(i=0;i<numLivros;i++)
						{
							printf(MSG_EXIBICAO, estante[i].titulo, estante[i].autor);
						}
						printf("\n");
					}

					break;

				case 8: // Imprime invertido

					if(numLivros==0)
					{
						printf(MSG_VAZIA);
					}
					else
					{
						for(i=numLivros-1;i>=0;i--)
						{
							printf(MSG_EXIBICAO, estante[i].titulo, estante[i].autor);
						}
						printf("\n");
					}

					break;

				case 9: // Imprime a quantidade de livros

			
					printf("%d\n", numLivros);

					break;

			}
		}
		else if(op!=0)
		{
			printf(MSG_INSIRA_LIVROS);
		}


	} while (op != 0);

	return (0);
}
