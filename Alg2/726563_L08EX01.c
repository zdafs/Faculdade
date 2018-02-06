/* ================================================================== *
Universidade Federal de Sao Carlos - UFSCar, Sorocaba

Disciplina: Algoritmos e Programação 2
Prof. Tiago A. Almeida

Lista 08 - Exercício 01 - Campeonato de Futebol

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
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define TAM_NOME_CAMPEONATO 30
#define TAM_NOME_ARQUIVO 	50
#define ARQUIVO_N_ENCONTRADO "Arquivo %s nao encontrado\n"

#define OPCAO_CRIAR_CAMPEONATO 			1
#define OPCAO_CALCULAR_RESULTADOS		2
#define OPCAO_CALCULAR_PONTOS			3
#define OPCAO_SALVAR_GOLS_POR_JOGADOR 	4
#define OPCAO_GERAR_GOLS_POR_TIME 		5
#define OPCAO_GERAR_ARTILHEIROS 		6
#define OPCAO_GERAR_TABELA_GERAL 		7
#define OPCAO_SAIR 						0

void criar_campeonato(char nome_campeonato[]);
void calcular_resultados(char nome_campeonato[]);
void calcular_pontos(char nome_campeonato[]);
void salvar_gols_por_jogador(char nome_campeonato[]);
void gerar_gols_por_time(char nome_campeonato[]);
void gerar_artilheiros(char nome_campeonato[]);
void gerar_tabela_geral(char nome_campeonato[]);

/* ------------------------------ */
/* ROTINA PRINCIPAL - NAO ALTERAR */
/* ------------------------------ */

int main() {
    int opcao;
    char nome_campeonato[TAM_NOME_CAMPEONATO];

    while (scanf("%d", &opcao) != EOF && opcao != OPCAO_SAIR) {
        scanf("\n%[^\n]s", nome_campeonato);

        switch (opcao) {
        case OPCAO_CRIAR_CAMPEONATO:
            criar_campeonato(nome_campeonato);
            break;
        case OPCAO_CALCULAR_RESULTADOS:
            calcular_resultados(nome_campeonato);
            break;
        case OPCAO_CALCULAR_PONTOS:
            calcular_pontos(nome_campeonato);
            break;
        case OPCAO_SALVAR_GOLS_POR_JOGADOR:
            salvar_gols_por_jogador(nome_campeonato);
            break;
        case OPCAO_GERAR_GOLS_POR_TIME:
            gerar_gols_por_time(nome_campeonato);
            break;
        case OPCAO_GERAR_ARTILHEIROS:
            gerar_artilheiros(nome_campeonato);
            break;
        case OPCAO_GERAR_TABELA_GERAL:
            gerar_tabela_geral(nome_campeonato);
            break;
        }
    }

    return 0;
}

/* ------------------------- */
/* IMPLEMENTACAO DAS FUNCOES */
/* ------------------------- */

void criar_campeonato(char nome_campeonato[])
{
	FILE *ptr;
	int times, linhas, flag=0;
	char arquivo[TAM_NOME_ARQUIVO];
	scanf("%d", &times);
	if(getchar()=='\n')
		flag=1;
	scanf("%d", &linhas);
	strcpy(arquivo, nome_campeonato);
	strcat(arquivo, " - Campeonato.txt");
	ptr = fopen(arquivo, "w");
	if(flag==1)
		fprintf(ptr, "%d\n%d\n", times, linhas);
	else
		fprintf(ptr, "%d %d\n", times, linhas);
	for(; linhas>0; linhas--)
	{
		int t1, t2;
		char c;
		scanf("%d %c %d", &t1, &c, &t2);
		fprintf(ptr, "%d %c %d\n", t1, c, t2);
	}
	fclose(ptr);

}
void calcular_resultados(char nome_campeonato[])
{
	char arquivo[TAM_NOME_ARQUIVO], c;
	FILE *ptr;
	int *vit, *der, *emp, times, linhas, t1, t2, i;
	strcpy(arquivo, nome_campeonato);
	strcat(arquivo, " - Campeonato.txt");
	ptr = fopen(arquivo, "r");
	if(ptr==NULL)
	{
		printf(ARQUIVO_N_ENCONTRADO, arquivo);
		return;
	}
	fscanf(ptr, "%d", &times);
	fscanf(ptr, "%d", &linhas);
	vit = (int *)calloc(times,sizeof(int));
	der = (int *)calloc(times,sizeof(int));
	emp = (int *)calloc(times,sizeof(int));
	for(i=linhas; i>0; i--)
	{
		fscanf(ptr, "%d %c %d", &t1, &c, &t2);
		if(c=='x')
		{
			vit[t1-1]++;
			der[t2-1]++;
		}
		else if(c=='-')
		{
			emp[t1-1]++;
			emp[t2-1]++;
		}
	}
	fclose(ptr);
	strcpy(arquivo, nome_campeonato);
	strcat(arquivo, " - Resultados.txt");
	ptr = fopen(arquivo, "w");
	for(i=0; times>0; times--, i++)
	{
		fprintf(ptr,"%d %d %d\n", vit[i], der[i], emp[i]);
	}
	fclose(ptr);
	free(vit);
	free(der);
	free(emp);
}
void calcular_pontos(char nome_campeonato[])
{
	FILE *ptr;
	int *pontos, vit, emp, i, tam;
	char arquivo[TAM_NOME_ARQUIVO];
	strcpy(arquivo, nome_campeonato);
	strcat(arquivo, " - Resultados.txt");
	ptr = fopen(arquivo, "r");
	if(ptr==NULL)
	{
		printf(ARQUIVO_N_ENCONTRADO, arquivo);
		return;
	}
	pontos = (int *)malloc(sizeof(int));
	for(tam=0; fscanf(ptr, "%d %*d %d", &vit, &emp)!=EOF; tam++)
	{
		pontos[tam]=(3*vit)+(emp);
		pontos=(int *)realloc(pontos,(tam+2)*sizeof(int));
	}
	fclose(ptr);
	strcpy(arquivo, nome_campeonato);
	strcat(arquivo, " - Pontos.txt");
	ptr = fopen(arquivo, "w");
	for(i=0; i<tam; i++)
	{
		fprintf(ptr, "%d\n", pontos[i]);
	}
	fclose(ptr);
	free(pontos);

}
void salvar_gols_por_jogador(char nome_campeonato[])
{
	FILE *ptr;
	char arquivo[TAM_NOME_ARQUIVO];
	int i, times, num;
	strcpy(arquivo, nome_campeonato);
	strcat(arquivo, " - Campeonato.txt");
	ptr = fopen(arquivo, "r");
	if(ptr==NULL)
	{
		printf(ARQUIVO_N_ENCONTRADO, arquivo);
		return;
	}
	fscanf(ptr, "%d", &times);
	fclose(ptr);
	strcpy(arquivo, nome_campeonato);
	strcat(arquivo, " - Gols por jogador.txt");
	ptr = fopen(arquivo, "w");
	for(i=0; times>1||i<11; i++)
	{
		scanf("%d", &num);
		if(i==11)
		{
			fprintf(ptr, "\n");
			times--;
			i=0;
		}
		fprintf(ptr, "%d ", num);
	}
	fclose(ptr);
}
void gerar_gols_por_time(char nome_campeonato[])
{
	FILE *ptr;
	int i, tam, num, *total_gols;
	char arquivo[TAM_NOME_ARQUIVO];
	strcpy(arquivo, nome_campeonato);
	strcat(arquivo, " - Gols por jogador.txt");
	ptr = fopen(arquivo, "r");
	if(ptr == NULL)
	{
		printf(ARQUIVO_N_ENCONTRADO, arquivo);
		return;
	}
	total_gols=(int *)malloc(sizeof(int));
	for(tam=0,i=0; fscanf(ptr, "%d", &num)!=EOF; tam++)
	{
		total_gols[tam]=0;
		while(i<10)
		{
			total_gols[tam]=total_gols[tam]+num;
			fscanf(ptr, "%d", &num);
			i++;
		}
		total_gols[tam]=total_gols[tam]+num;
		i=0;
		total_gols=(int *)realloc(total_gols,(tam+2)*sizeof(int));
	}
	fclose(ptr);
	strcpy(arquivo, nome_campeonato);
	strcat(arquivo, " - Gols por time.txt");
	ptr = fopen(arquivo, "w");
	for(i=0; i<tam; i++)
	{
		fprintf(ptr, "%d\n", total_gols[i]);
	}
	fclose(ptr);
	free(total_gols);
}
void gerar_artilheiros(char nome_campeonato[])
{
	FILE *ptr;
	int i, tam, maior, num, *artilheiros;
	char arquivo[TAM_NOME_ARQUIVO];
	strcpy(arquivo, nome_campeonato);
	strcat(arquivo, " - Gols por jogador.txt");
	ptr = fopen(arquivo, "r");
	if(ptr == NULL)
	{
		printf(ARQUIVO_N_ENCONTRADO, arquivo);
		return;
	}
	artilheiros=(int *)malloc(sizeof(int));
	for(tam=0,i=0; fscanf(ptr, "%d", &maior)!=EOF; tam++)
	{
		artilheiros[tam]=0;
		while(i<10)
		{
			i++;
			fscanf(ptr, "%d", &num);
			if(num>maior)
			{
				maior=num;
				artilheiros[tam]=i+1;
			}
		}
		i=0;
		artilheiros=(int *)realloc(artilheiros,(tam+2)*sizeof(int));
	}
	fclose(ptr);
	strcpy(arquivo, nome_campeonato);
	strcat(arquivo, " - Artilheiros.txt");
	ptr = fopen(arquivo, "w");
	for(i=0; i<tam; i++)
	{
		fprintf(ptr, "%d\n", artilheiros[i]);
	}
	fclose(ptr);
	free(artilheiros);
}
void gerar_tabela_geral(char nome_campeonato[])
{
	char arquivo[TAM_NOME_ARQUIVO];
	FILE *ptr;
	int times, *vit, *der, *emp, *pontos, *total_gols, *artilheiros, i;
	strcpy(arquivo, nome_campeonato);
	strcat(arquivo, " - Campeonato.txt");
	ptr = fopen(arquivo, "r");
	if(ptr==NULL)
	{
		printf(ARQUIVO_N_ENCONTRADO, arquivo);
		return;
	}
	fscanf(ptr, "%d", &times);
	fclose(ptr);
	strcpy(arquivo, nome_campeonato);
	strcat(arquivo, " - Resultados.txt");
	ptr = fopen(arquivo, "r");
	if(ptr==NULL)
	{
		printf(ARQUIVO_N_ENCONTRADO, arquivo);
		return;
	}
	vit = (int *)malloc(times*sizeof(int));
	der = (int *)malloc(times*sizeof(int));
	emp = (int *)malloc(times*sizeof(int));
	for(i=0; i<times; i++)
	{
		fscanf(ptr, "%d %d %d", &vit[i], &der[i], &emp[i]);
	}
	fclose(ptr);
	strcpy(arquivo, nome_campeonato);
	strcat(arquivo, " - Pontos.txt");
	ptr = fopen(arquivo, "r");
	if(ptr==NULL)
	{
		printf(ARQUIVO_N_ENCONTRADO, arquivo);
		return;
	}
	pontos = (int *)malloc(times*sizeof(int));
	for(i=0; i<times; i++)
	{
		fscanf(ptr, "%d", &pontos[i]);
	}
	fclose(ptr);
	strcpy(arquivo, nome_campeonato);
	strcat(arquivo, " - Gols por time.txt");
	ptr = fopen(arquivo, "r");
	if(ptr == NULL)
	{
		printf(ARQUIVO_N_ENCONTRADO, arquivo);
		return;
	}
	total_gols = (int *)malloc(times*sizeof(int));
	for(i=0; i<times; i++)
	{
		fscanf(ptr, "%d", &total_gols[i]);
	}
	fclose(ptr);
	strcpy(arquivo, nome_campeonato);
	strcat(arquivo, " - Artilheiros.txt");
	ptr = fopen(arquivo, "r");
	if(ptr == NULL)
	{
		printf(ARQUIVO_N_ENCONTRADO, arquivo);
		return;
	}
	artilheiros = (int *)malloc(times*sizeof(int));
	for(i=0; i<times; i++)
	{
		fscanf(ptr, "%d", &artilheiros[i]);
	}
	fclose(ptr);
	strcpy(arquivo, nome_campeonato);
	strcat(arquivo, " - Tabela geral.txt");
	ptr = fopen(arquivo, "w");
	for(i=0; i<times; i++)
	{
		fprintf(ptr, "%d %d %d %d %d %d\n", vit[i], der[i], emp[i], pontos[i], total_gols[i], artilheiros[i]);
	}
	free(vit);
	free(der);
	free(emp);
	free(pontos);
	free(total_gols);
	free(artilheiros);
	fclose(ptr);
}
