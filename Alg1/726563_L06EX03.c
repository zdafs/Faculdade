/* ================================================================== *
    Universidade Federal de Sao Carlos - UFSCar, Sorocaba

    Disciplina: Algoritmos e Programação 1
    Prof. Tiago A. Almeida

    Lista 06 - Exercício 03 - K-Vizinhos Mais Próximos

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
#include <math.h>

#define MAX	100000

struct notas
{
	float p1, p2, p3;
};

int main()
{

	struct notas alunos[MAX], aluno;
	float distancia[MAX], aux;
	int k;
	long i, j, qnt;
	scanf("%ld", &qnt);
	for(i=0;i<qnt;i++)
	{
		scanf("%f %f %f", &alunos[i].p1, &alunos[i].p2, &alunos[i].p3);
	}
	scanf("%d",&k);
	while(k!=0)
	{
		scanf("%f %f", &aluno.p1, &aluno.p2);
		aluno.p3=0.0;
		for(i=0;i<qnt;i++)
		{
			distancia[i]=sqrt((pow((aluno.p1-alunos[i].p1),2))+(pow((aluno.p2-alunos[i].p2),2)));
		}
		for(i=0;i<qnt;i++)
		{
			for(j=i+1;j<qnt;j++)
			{
				if(distancia[i]>distancia[j])
				{
					aux=distancia[i];
					distancia[i]=distancia[j];
					distancia[j]=aux;
					aux=alunos[i].p1;
					alunos[i].p1=alunos[j].p1;
					alunos[j].p1=aux;
					aux=alunos[i].p2;
					alunos[i].p2=alunos[j].p2;
					alunos[j].p2=aux;
					aux=alunos[i].p3;
					alunos[i].p3=alunos[j].p3;
					alunos[j].p3=aux;
		
				}
			}
		}
		for(i=0;i<k;i++)
		{
			aluno.p3=aluno.p3+alunos[i].p3;
		}
		aluno.p3=aluno.p3/k;
		printf("%.2f\n", aluno.p3);
		scanf("%d", &k);
	} 

	return (0);
}
