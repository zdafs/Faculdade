/* ================================================================== *
	Universidade Federal de Sao Carlos - UFSCar, Sorocaba

	Disciplina: Algoritmos e Programação 1
	Prof. Tiago A. Almeida

	Lista 07 - Exercício 01 - Operacoes com matrizes

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

//Definindo limite para ordem da matriz
#define MAX 20

//Definindo mensagem de erro
#define FRASE_ERRO "Opcao invalida!\n"

//Enumeração das opções do programa
enum{
	OPC_SAIR,				//Finaliza o programa.
	OPC_SOMA_LINHA,			//Soma da linha i.
	OPC_SOMA_COLUNA,		//Soma da coluna j.
	OPC_SOMA_GERAL,			//Soma de todos os valores da matriz.
	OPC_SOMA_DIAG_PRINC,	//Soma da diagonal principal.
	OPC_SOMA_DIAG_SEC,		//Soma da diagonal secundaria.
	OPC_MAXMINMED_LIN,		//Imprime os valores máximo, mínimo e médio da linha i
	OPC_MAXMINMED_COL,		//Imprime os valores máximo, mínimo e médio da coluna j
	OPC_MAXMINMED_GERAL,	//Imprime os valores máximo, mínimo e médio da matriz
	OPC_SOMA_MATRIZ,		//B = A + A.
	OPC_PROD_MATRIZ,		//B = A * A'.
	OPC_TRANSPOSTA,			//B = A'.
	OPC_PROD_K,				//B = k * A.
};


int main(){


	int A[MAX][MAX], B[MAX][MAX], i, j, k, m, aux, op;
	float media;
	scanf("%d", &m);
	for(i=0;i<m;i++)
	{
		for(j=0;j<m;j++)
		{
			scanf("%d", &A[i][j]);
		}
	}
	do
	{
		scanf("%d", &op);
		if(op!=0)
		{
			switch(op)
			{
				case OPC_SOMA_LINHA:
					aux=0;
					scanf("%d", &k);
					for(j=0;j<m;j++)
					{
						aux=aux+A[k-1][j];
					}
					printf("%d\n", aux);
				break;
				
				case OPC_SOMA_COLUNA:
					aux=0;
					scanf("%d", &k);
					for(i=0;i<m;i++)
					{
						aux=aux+A[i][k-1];
					}
					printf("%d\n", aux);
				break;

				case OPC_SOMA_GERAL:
					aux=0;
					for(i=0;i<m;i++)
					{
						for(j=0;j<m;j++)
						{
							aux=aux+A[i][j];
						}
					}
					printf("%d\n", aux);
				break;

				case OPC_SOMA_DIAG_PRINC:
					aux=0;
					for(i=0,j=0;i<m&&j<m;i++,j++)
					{
						aux=aux+A[i][j];
					}
					printf("%d\n", aux);
				break;

				case OPC_SOMA_DIAG_SEC:
					aux=0;
					for(i=0,j=m-1;i<m&&j>=0;i++,j--)
					{
						aux=aux+A[i][j];
					}
					printf("%d\n", aux);
				break;

				case OPC_MAXMINMED_LIN:
					scanf("%d", &k);
					aux=A[k-1][0];
					for(j=1;j<m;j++)
					{
						if(aux>A[k-1][j])
						{
							aux=A[k-1][j];
						}
					}
					printf("%d ", aux);
					aux=A[k-1][0];
					for(j=1;j<m;j++)
					{
						if(aux<A[k-1][j])
						{
							aux=A[k-1][j];
						}
					}
					printf("%d ", aux);
					media=0;
					for(j=0;j<m;j++)
					{
						media=media+A[k-1][j];
					}
					media=(media/m);
					printf("%.2f\n", media);
				break;

				case OPC_MAXMINMED_COL:
					scanf("%d", &k);
					aux=A[0][k-1];
					for(i=1;i<m;i++)
					{
						if(aux>A[i][k-1])
						{
							aux=A[i][k-1];
						}
					}
					printf("%d ", aux);
					aux=A[0][k-1];
					for(i=1;i<m;i++)
					{
						if(aux<A[i][k-1])
						{
							aux=A[i][k-1];
						}
					}
					printf("%d ", aux);
					media=0;
					for(i=0;i<m;i++)
					{
						media=media+A[i][k-1];
					}
					media=(media/m);
					printf("%.2f\n", media);
				break;

				case OPC_MAXMINMED_GERAL:
					aux=A[0][0];
					for(i=0;i<m;i++)
					{
						for(j=1;j<m;j++)
						{
							if(aux>A[i][j])
							{
								aux=A[i][j];
							}
						}
					}
					printf("%d ", aux);
					aux=A[0][0];
					for(i=0;i<m;i++)
					{
						for(j=1;j<m;j++)
						{
							if(aux<A[i][j])
							{
								aux=A[i][j];
							}
						}
					}
					printf("%d ", aux);
					media=0;
					for(i=0;i<m;i++)
					{
						for(j=0;j<m;j++)
						{
							media=media+A[i][j];
						}
					}
					media=(media/(m*m));
					printf("%.2f\n", media);
				break;

				case OPC_SOMA_MATRIZ:
					for(i=0;i<m;i++)
					{
						for(j=0;j<m;j++)
						{
							B[i][j]=2*A[i][j];
						}
					}
					for(i=0;i<m;i++)
					{
						for(j=0;j<m;j++)
						{
							printf("%3d ", B[i][j]);
						}
						printf("\n");
					}
				break;

				case OPC_PROD_MATRIZ:
					for(i=0;i<m;i++)
					{
						for(j=0;j<m;j++)
						{
							B[i][j]=0;
							for(k=0;k<m;k++)
							{
								B[i][j]=B[i][j]+(A[i][k]*A[j][k]);
							}
						}
					}
					for(i=0;i<m;i++)
					{
						for(j=0;j<m;j++)
						{
							printf("%3d ", B[i][j]);
						}
						printf("\n");
					}
				break;

				case OPC_TRANSPOSTA:
					for(i=0;i<m;i++)
					{
						for(j=0;j<m;j++)
						{
							B[i][j]=A[j][i];
						}
					}
					for(i=0;i<m;i++)
					{
						for(j=0;j<m;j++)
						{
							printf("%3d ", B[i][j]);
						}
						printf("\n");
					}
				break;

				case OPC_PROD_K:
					scanf("%d", &k);
					for(i=0;i<m;i++)
					{
						for(j=0;j<m;j++)
						{
							B[i][j]=k*A[i][j];
						}
					}
					for(i=0;i<m;i++)
					{
						for(j=0;j<m;j++)
						{
							printf("%3d ", B[i][j]);
						}
						printf("\n");
					}
				break;

				default:
					printf(FRASE_ERRO);
				break;
			}
		}
					
	}
	while(op!=0);


	return (0);
}
