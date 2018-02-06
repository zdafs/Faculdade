/* ================================================================== *
    Universidade Federal de Sao Carlos - UFSCar, Sorocaba
 
    Disciplina: Algoritmos e Programação 1
    Prof. Tiago A. Almeida
 
    Lista 07 - Exercício 05 - Sudoku
 
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

#define SAIDA "(%d,%d) -> (%d,%d)\n"

typedef struct num_trocado
{
	int valor, indexLin, indexCol, conf;
}Num_Trocado;

int main()
{

	int Sudoku[9][9], i, j, k, l, tam, entrou;
	Num_Trocado num[8];
	
	//preenche o vetor
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
		{
			scanf("%d", &Sudoku[i][j]);
		}
	}

	//confere e guarda as repetições
	for(i=0,tam=0;i<9;i++)//anda pelas linhas
	{
		for(j=0;j<9;j++)//anda pelas colunas
		{
			for(k=j+1;k<9;k++)//anda pelas colunas
			{
				if(Sudoku[i][j]==Sudoku[i][k])//confere se tem termos iguais
				{
					//confere qual dos dois termos é o trocado
					for(l=0,entrou=0;l<9&&entrou==0;l++)//confere o primeiro termo com sua coluna
					{
						if(l==i)
						{
							l++;
						}
						if(Sudoku[i][j]==Sudoku[l][j])//se tiver algum numero igual na coluna, é o termo trocado
						{
							entrou=1;
							num[tam].valor=Sudoku[i][j];
							num[tam].indexLin=i;
							num[tam].indexCol=j;
							tam++;
						}
					}
					if(entrou==0)//se não entrar no primeiro caso o segundo numero é o trocado
					{
						num[tam].valor=Sudoku[i][k];
						num[tam].indexLin=i;
						num[tam].indexCol=k;
						tam++;
					}
				}
			}
		}
	}
	for(i=0;i<tam;i++)//inicializa a variavel de conferencia
	{
		num[i].conf=0;
	}
	
	//retorna os numeros para as posições originais
	for(i=0;i<tam;i++)//anda na linha
	{
		for(j=i+1;j<tam&&num[i].conf==0;j++)//anda na coluna
		{
			if(num[j].conf==0)//confere se o numero ja foi destrocado
			{
				Sudoku[num[i].indexLin][num[i].indexCol]=num[j].valor;
				//confere se o numero esta na posição certa
				for(k=0,entrou=0;k<9&&entrou==0;k++)
				{
					if(k==num[i].indexCol)
					{
						k++;
					}
					if(Sudoku[num[i].indexLin][num[i].indexCol]==Sudoku[num[i].indexLin][k])
					{
						entrou=1;
					}
				}
				if(entrou==0)
				{
					printf(SAIDA, num[i].indexLin+1, num[i].indexCol+1, num[j].indexLin+1, num[j].indexCol+1);
					num[i].conf=1;
					num[j].conf=1;
				}
			}
		}
	}	

					
	return (0);
}
