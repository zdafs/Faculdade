/* ================================================================== *
Universidade Federal de Sao Carlos - UFSCar, Sorocaba

Disciplina: Algoritmos e Programação 2
Prof. Tiago A. Almeida

Lista 09 - Exercício 01 - Campeonato de Futebol (Arquivos Binarios)

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
	scanf("%d", &linhas);
	strcpy(arquivo, nome_campeonato);
	strcat(arquivo, " - Campeonato.dat");
	ptr = fopen(arquivo, "wb");
	fwrite(&times, sizeof(int), 1, ptr);
	fwrite(&linhas, sizeof(int), 1, ptr);
	for(; linhas>0; linhas--)
	{
		int t1, t2;
		char c;
		scanf("%d %c %d", &t1, &c, &t2);
		fwrite(&t1, sizeof(int), 1, ptr);
		fwrite(&c, sizeof(char), 1, ptr);
		fwrite(&t2, sizeof(int), 1, ptr);
	}
	fclose(ptr);

}
void calcular_resultados(char nome_campeonato[])
{
	char arquivo[TAM_NOME_ARQUIVO], c;
	FILE *ptr;
	int *vit, *der, *emp, times, linhas, t1, t2, i;
	strcpy(arquivo, nome_campeonato);
	strcat(arquivo, " - Campeonato.dat");
	ptr = fopen(arquivo, "rb");
	if(ptr==NULL)
	{
		printf(ARQUIVO_N_ENCONTRADO, arquivo);
		return;
	}
	fread(&times, sizeof(int), 1, ptr);
	fread(&linhas, sizeof(int), 1, ptr);
	vit = (int *)calloc(times,sizeof(int));
	der = (int *)calloc(times,sizeof(int));
	emp = (int *)calloc(times,sizeof(int));
	for(i=linhas; i>0; i--)
	{
		fread(&t1, sizeof(int), 1, ptr);
		fread(&c, sizeof(char), 1, ptr);
		fread(&t2, sizeof(int), 1, ptr);
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
	strcat(arquivo, " - Resultados.dat");
	ptr = fopen(arquivo, "wb");
	for(i=0; times>0; times--, i++)
	{
		fwrite(vit+i, sizeof(int), 1, ptr);
		fwrite(der+i, sizeof(int), 1, ptr);
		fwrite(emp+i, sizeof(int), 1, ptr);
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
	strcat(arquivo, " - Resultados.dat");
	ptr = fopen(arquivo, "rb");
	if(ptr==NULL)
	{
		printf(ARQUIVO_N_ENCONTRADO, arquivo);
		return;
	}
	pontos = (int *)malloc(sizeof(int));
	fread(&vit, sizeof(int), 1, ptr);
	fseek(ptr, sizeof(int), SEEK_CUR);
	fread(&emp, sizeof(int), 1, ptr);
	for(tam=0; !feof(ptr); tam++)
	{
		pontos[tam]=(3*vit)+(emp);
		pontos=(int *)realloc(pontos,(tam+2)*sizeof(int));
		fread(&vit, sizeof(int), 1, ptr);
		fseek(ptr, sizeof(int), SEEK_CUR);
		fread(&emp, sizeof(int), 1, ptr);
	}
	fclose(ptr);
	strcpy(arquivo, nome_campeonato);
	strcat(arquivo, " - Pontos.dat");
	ptr = fopen(arquivo, "wb");
	fwrite(pontos, sizeof(int), tam, ptr);
	fclose(ptr);
	free(pontos);

}
void salvar_gols_por_jogador(char nome_campeonato[])
{
	FILE *ptr;
	char arquivo[TAM_NOME_ARQUIVO];
	int i, times, num;
	strcpy(arquivo, nome_campeonato);
	strcat(arquivo, " - Campeonato.dat");
	ptr = fopen(arquivo, "rb");
	if(ptr==NULL)
	{
		printf(ARQUIVO_N_ENCONTRADO, arquivo);
		return;
	}
	fread(&times, sizeof(int), 1, ptr);
	fclose(ptr);
	strcpy(arquivo, nome_campeonato);
	strcat(arquivo, " - Gols por jogador.dat");
	ptr = fopen(arquivo, "wb");
	for(i=1; times>0; i++)
	{
		scanf("%d", &num);
		if(i==11)
		{
			times--;
			i=0;
		}
		fwrite(&num, sizeof(int), 1, ptr);
	}
	fclose(ptr);
}
void gerar_gols_por_time(char nome_campeonato[])
{
	FILE *ptr;
	int i, tam, num, *total_gols;
	char arquivo[TAM_NOME_ARQUIVO];
	strcpy(arquivo, nome_campeonato);
	strcat(arquivo, " - Gols por jogador.dat");
	ptr = fopen(arquivo, "rb");
	if(ptr == NULL)
	{
		printf(ARQUIVO_N_ENCONTRADO, arquivo);
		return;
	}
	total_gols=(int *)malloc(sizeof(int));
	fread(&num, sizeof(int), 1, ptr);
	for(tam=0,i=0; !feof(ptr); tam++)
	{
		total_gols[tam]=0;
		while(i<10)
		{
			total_gols[tam]=total_gols[tam]+num;
			fread(&num, sizeof(int), 1, ptr);
			i++;
		}
		total_gols[tam]=total_gols[tam]+num;
		i=0;
		total_gols=(int *)realloc(total_gols,(tam+2)*sizeof(int));
		fread(&num, sizeof(int), 1, ptr);
	}
	fclose(ptr);
	strcpy(arquivo, nome_campeonato);
	strcat(arquivo, " - Gols por time.dat");
	ptr = fopen(arquivo, "wb");
	fwrite(total_gols, sizeof(int), tam, ptr);
	fclose(ptr);
	free(total_gols);
}
void gerar_artilheiros(char nome_campeonato[])
{
	FILE *ptr;
	int i, tam, maior, num, *artilheiros;
	char arquivo[TAM_NOME_ARQUIVO];
	strcpy(arquivo, nome_campeonato);
	strcat(arquivo, " - Gols por jogador.dat");
	ptr = fopen(arquivo, "rb");
	if(ptr == NULL)
	{
		printf(ARQUIVO_N_ENCONTRADO, arquivo);
		return;
	}
	artilheiros=(int *)malloc(sizeof(int));
	fread(&maior, sizeof(int), 1, ptr);
	for(tam=0,i=0; !feof(ptr); tam++)
	{
		artilheiros[tam]=1;
		while(i<10)
		{
			i++;
			fread(&num, sizeof(int), 1, ptr);
			if(num>maior)
			{
				maior=num;
				artilheiros[tam]=i+1;
			}
		}
		i=0;
		artilheiros=(int *)realloc(artilheiros,(tam+2)*sizeof(int));
		fread(&maior, sizeof(int), 1, ptr);
	}
	fclose(ptr);
	strcpy(arquivo, nome_campeonato);
	strcat(arquivo, " - Artilheiros.dat");
	ptr = fopen(arquivo, "wb");
	fwrite(artilheiros, sizeof(int), tam, ptr);
	fclose(ptr);
	free(artilheiros);
}
void gerar_tabela_geral(char nome_campeonato[])
{
	char arquivo[TAM_NOME_ARQUIVO];
	FILE *ptr;
	int times, *vit, *der, *emp, *pontos, *total_gols, *artilheiros, i;
	strcpy(arquivo, nome_campeonato);
	strcat(arquivo, " - Campeonato.dat");
	ptr = fopen(arquivo, "rb");
	if(ptr==NULL)
	{
		printf(ARQUIVO_N_ENCONTRADO, arquivo);
		return;
	}
	fread(&times, sizeof(int), 1, ptr);
	fclose(ptr);
	strcpy(arquivo, nome_campeonato);
	strcat(arquivo, " - Resultados.dat");
	ptr = fopen(arquivo, "rb");
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
		fread(vit+i, sizeof(int), 1, ptr);
		fread(der+i, sizeof(int), 1, ptr);
		fread(emp+i, sizeof(int), 1, ptr);
	}
	fclose(ptr);
	strcpy(arquivo, nome_campeonato);
	strcat(arquivo, " - Pontos.dat");
	ptr = fopen(arquivo, "rb");
	if(ptr==NULL)
	{
		printf(ARQUIVO_N_ENCONTRADO, arquivo);
		return;
	}
	pontos = (int *)malloc(times*sizeof(int));
	fread(pontos, sizeof(int), times, ptr);
	fclose(ptr);
	strcpy(arquivo, nome_campeonato);
	strcat(arquivo, " - Gols por time.dat");
	ptr = fopen(arquivo, "rb");
	if(ptr == NULL)
	{
		printf(ARQUIVO_N_ENCONTRADO, arquivo);
		return;
	}
	total_gols = (int *)malloc(times*sizeof(int));
	fread(total_gols, sizeof(int), times, ptr);
	fclose(ptr);
	strcpy(arquivo, nome_campeonato);
	strcat(arquivo, " - Artilheiros.dat");
	ptr = fopen(arquivo, "rb");
	if(ptr == NULL)
	{
		printf(ARQUIVO_N_ENCONTRADO, arquivo);
		return;
	}
	artilheiros = (int *)malloc(times*sizeof(int));
	fread(artilheiros, sizeof(int), times, ptr);
	fclose(ptr);
	strcpy(arquivo, nome_campeonato);
	strcat(arquivo, " - Tabela geral.dat");
	ptr = fopen(arquivo, "wb");
	for(i=0; i<times; i++)
	{
		fwrite(vit+i, sizeof(int), 1, ptr);
		fwrite(der+i, sizeof(int), 1, ptr);
		fwrite(emp+i, sizeof(int), 1, ptr);
		fwrite(pontos+i, sizeof(int), 1, ptr);
		fwrite(total_gols+i, sizeof(int), 1, ptr);
		fwrite(artilheiros+i, sizeof(int), 1, ptr);
	}
	free(vit);
	free(der);
	free(emp);
	free(pontos);
	free(total_gols);
	free(artilheiros);
	fclose(ptr);
}