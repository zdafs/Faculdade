/* ================================================================== *
    Universidade Federal de Sao Carlos - UFSCar, Sorocaba

    Disciplina: Algoritmos e Programação 1
    Prof. Tiago A. Almeida

    Lista 05 - Exercício 01 - Médias

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

#define MSG_ALG1 	"Aluno %02d (Alg 1)\n"
#define MSG_LOGICA 	"Aluno %02d (Logica)\n"
#define MSG_IGUAL 	"Medias iguais (%.2f)\n"


enum disciplina {alg1 = 1, logica};

/* <<<DEFINA AQUI O TIPO NOTA COMO UM FLOAT>>> */
typedef float Nota;

// Registro para armazenar os dados de cada aluno
typedef struct aluno {
    enum disciplina disc;
    Nota p1;
    Nota p2;
    Nota p3;
    Nota listas;
    Nota media;
} Aluno;


int main() {
	Aluno aluno1;
	Aluno aluno2;
	do
	{
		scanf("%u", &aluno1.disc);
		if(aluno1.disc==alg1)
		{
			scanf("%f %f %f", &aluno1.p1, &aluno1.p2, &aluno1.listas);
			aluno1.media = ((3*aluno1.p1)+(4*aluno1.p2)+(3*aluno1.listas))/10;
		}
		else if(aluno1.disc==logica)
		{
			scanf("%f %f %f", &aluno1.p1, &aluno1.p2, &aluno1.p3);
			aluno1.media = (aluno1.p1+aluno1.p2+aluno1.p3)/3;
		}
		else
		{
			return (0);
		}
		scanf("%u", &aluno2.disc);
		if(aluno2.disc==alg1)
		{
			scanf("%f %f %f", &aluno2.p1, &aluno2.p2, &aluno2.listas);
			aluno2.media = ((3*aluno2.p1)+(4*aluno2.p2)+(3*aluno2.listas))/10;
		}
		else if(aluno2.disc==logica)
		{
			scanf("%f %f %f", &aluno2.p1, &aluno2.p2, &aluno2.p3);
			aluno2.media = (aluno2.p1+aluno2.p2+aluno2.p3)/3;
		}
		else
		{
			return (0);
		}
		if(aluno1.media!=0 && aluno2.media!=0)
		{
			if(aluno1.media>aluno2.media)
			{
				if(aluno1.disc==alg1)
				{
					printf(MSG_ALG1, 1);
					printf("%.2f\n", aluno1.media);
					printf("%.2f %.2f %.2f\n", aluno1.p1, aluno1.p2, aluno1.listas);
				}
				else
				{
					printf(MSG_LOGICA, 1);
					printf("%.2f\n", aluno1.media);
					printf("%.2f %.2f %.2f\n", aluno1.p1, aluno1.p2, aluno1.p3);
				}
			}
			else if(aluno2.media>aluno1.media)
			{
				if(aluno2.disc==alg1)
				{
					printf(MSG_ALG1, 2);
					printf("%.2f\n", aluno2.media);
					printf("%.2f %.2f %.2f\n", aluno2.p1, aluno2.p2, aluno2.listas);
				}
				else
				{
					printf(MSG_LOGICA, 2);
					printf("%.2f\n", aluno2.media);
					printf("%.2f %.2f %.2f\n", aluno2.p1, aluno2.p2, aluno2.p3);
				}
			}
			else
			{
				printf(MSG_IGUAL, aluno1.media);
			}
		}
	}
	while(aluno1.media!=0&&aluno2.media!=0);

	return (0);

}
