/* Universidade Federal de Sao Carlos - UFSCar, Sorocaba

  Disciplina: Estruturas de Dados 1
  Prof. Tiago A. Almeida

  Exercício 1 - Ponteiros e Alocacao Dinamica

  Instrucoes
  ----------

  Este arquivo contem o codigo que auxiliara no desenvolvimento do
  exercicio. Voce precisara completar as funcoes requisitadas.

  Voce nao podera criar nenhuma outra funcao. Complete apenas as rotinas
  fornecidas. 														*/


#include <stdio.h>
#include <stdlib.h>
/************************************************/

typedef struct unidade
{
	int codigo, num_total_alunos;
	int num_alunos;
	int *vet;
}
Unidade;



/************************************************/

void recebeUnidade(Unidade *p, int n);
void recebeAluno(Unidade *p, int n);
int maiorFaltante(Unidade *p, int n);

/************************************************/

int main()
{
  int n, m, i, maior;
  Unidade *p;

  scanf("%d", &n);
  p = (Unidade *) malloc(n*sizeof(Unidade));
  recebeUnidade(p, n);
  scanf("%d", &m);
  recebeAluno(p, n);
  maior = maiorFaltante(p, n);
  printf("%d\n", p[maior].codigo);
  for(m=0; m<p[maior].num_alunos; m++)
  {
  	printf("%d\n", p[maior].vet[m]);
  }

  for(m=0; m<n; m++)
  {
  	free(p[m].vet);
  }
  free(p);
 
  return (0);
}


void recebeUnidade(Unidade *p, int n)
{
	int i;
	for(i=0; i<n; i++)
	{
		scanf("%d", &(p[i].codigo));
		scanf("%d", &(p[i].num_total_alunos));
		p[i].vet=NULL;
	}
}
void recebeAluno(Unidade *p, int n)
{
	int i=0, c, flag;
	do
	{
		scanf("%d", &c);
		if(c!=-1)
		{
			for(i=0, flag=0; i<n&&flag==0; i++)
			{
				if(p[i].codigo==c)
				{
					flag=1;
					if(p[i].vet==NULL)
					{
						p[i].vet = (int *) malloc(sizeof(int));
						p[i].num_alunos=1;
						scanf("%d", &(p[i].vet[0]));
					}
					else
					{
						p[i].num_alunos++;
						p[i].vet = (int *) realloc(p[i].vet, p[i].num_alunos*sizeof(int));
						scanf("%d", &(p[i].vet[p[i].num_alunos-1]));
					}
				}
			}
		}
	}
	while(c!=-1);
}
int maiorFaltante(Unidade *p, int n)
{
	int maior, i;
	float razao, aux;
	razao = ((float)p[0].num_alunos/(float)p[0].num_total_alunos);
	maior=0;
	for(i=1; i<n; i++)
	{
		aux = ((float)p[i].num_alunos/(float)p[i].num_total_alunos);
		if(razao>aux)
		{
			razao=aux;
			maior=i;
		}
	}
	return(maior);
}