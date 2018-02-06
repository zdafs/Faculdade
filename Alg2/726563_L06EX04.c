/* ================================================================== *
    Universidade Federal de Sao Carlos - UFSCar, Sorocaba
 
    Disciplina: Algoritmos e Programação 2
    Prof. Tiago A. Almeida
 
    Lista 06 - Exercício 04 - Grau de Parentesco
 
    Instrucoes
    ----------
 
    Este arquivo contem o codigo que auxiliara no desenvolvimento do
    exercicio. Voce precisara completar as partes requisitadas.
 
* ================================================================== *
    Dados do aluno:
 
    RA: 726563
    Nome: Lucca La Fonte Albuquerque Carvalho
 
* ================================================================== */

/* Bibliotecas */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Codigo de grau de parentesco */
enum graus { PAI = 1, MAE, IRMAO, CONJUGE, FILHO, TIO, DESCONHECIDO };

/* Exibe na tela */
void exibe_parentes(char *cidadao, char **parentes, int grau_parentesco[], int qt_parentes);

/* <<<<<<<< FUNCOES QUE DEVEM SER IMPLEMENTADAS >>>>>>>> */

/* Recebe um nome alocando de maneira dinâmica e retorna um apontador para este nome */
char* recebe_nome();

/* Inicializa o vetor *grau_parentesco alocando qt_parentes espacos dinamicamente */
void inicializa_grau_parenteso(int **grau_parentesco, int qt_parentes);

/* Define os graus de parentesco de cada nome, atribuindo o codigo especifico no vetor grau_parentesco */
/* Cada posicao do vetor corresponde ao nome naquela posicao (ordem de entrada do usuario) */
void define_parentesco(char *cidadao, char **parentes, int grau_parentesco[], int qt_parentes);

/* <<<<<<<< ESCREVA O PROTOTIPO DE DEMAIS FUNCOES - SE NECESSARIO - AQUI >>>>>>>> */

/* ============================================================================================== */


/* ------------------------------ */
/* ROTINA PRINCIPAL - NAO ALTERAR */
/* ------------------------------ */
int main () {
	/* Variaveis */
	char *cidadao;
	char **parentes;
	int *grau_parentesco;
	int qt_parentes, i;

	/* Recebe o nome do cidadao */
	cidadao = recebe_nome();

	/* Recebe a quantidade de parentes */
	scanf("%d", &qt_parentes);	

	/* Aloca espaco no vetor de grau_parentes */
	inicializa_grau_parenteso(&grau_parentesco, qt_parentes);

	/* Aloca espaco na matriz de nome dos possiveis parentes */
	parentes = (char**) malloc(sizeof(char*) * qt_parentes);
	
	/* Recebe o nome de cada parente */
	for (i = 0; i < qt_parentes; i++)
		parentes[i] = recebe_nome();	

	/* Define o parentesco */
	define_parentesco(cidadao, parentes, grau_parentesco, qt_parentes);
	
	/* Exibe na tela */
	exibe_parentes(cidadao, parentes, grau_parentesco, qt_parentes);

	return 0;
}

/* ============================================================================================== */

/* Exibe na tela */
void exibe_parentes(char *cidadao, char **parentes, int grau_parentesco[], int qt_parentes) {
	int i;
	/* Exibe o nome do cidadao */
	printf("=================================\nCIDADAO: %s\n=================================\n", cidadao);
	
	/* Percorre o vetor grau_parentesco e exibe os resultados encontrados */
	printf("PAI:\n");
	for (i = 0; i < qt_parentes; i++)
		if (grau_parentesco[i] == PAI) {
			printf("   %s\n", parentes[i]);
			break;
		}

	printf("MAE:\n");
	for (i = 0; i < qt_parentes; i++)
		if (grau_parentesco[i] == MAE) {
			printf("   %s\n", parentes[i]);
			break;
		}

	printf("IRMAOS:\n");
	for (i = 0; i < qt_parentes; i++)
		if (grau_parentesco[i] == IRMAO)
			printf("   %s\n", parentes[i]);

	printf("CONJUGE:\n");
	for (i = 0; i < qt_parentes; i++)
		if (grau_parentesco[i] == CONJUGE) {
			printf("   %s\n", parentes[i]);
			break;
		}					

	printf("FILHOS:\n");
	for (i = 0; i < qt_parentes; i++)
		if (grau_parentesco[i] == FILHO)
			printf("   %s\n", parentes[i]);		

	printf("TIOS:\n");
	for (i = 0; i < qt_parentes; i++)
		if (grau_parentesco[i] == TIO)
			printf("   %s\n", parentes[i]);		

	printf("DESCONHECIDOS:\n");
	for (i = 0; i < qt_parentes; i++)
		if (grau_parentesco[i] == DESCONHECIDO)
			printf("   %s\n", parentes[i]);				
}

/* ============================================================================================== */

/* <<<<<<<< COMPLETE AS FUNCOES ABAIXO >>>>>>>> */


/* Recebe um nome alocando de maneira dinâmica e retorna um apontador para este nome */ 
char* recebe_nome()
{
	char c, *p;
	int i=0;
	p = (char *) malloc(1);
	if((c=getchar())=='\n')
		c=getchar();
	do
	{
		p[i]=c;
		i++;
		p = (char *) realloc(p, i+1);
	}
	while((c=getchar())!='\n');
	p[i]='\0';
	return(p);
}

/* Inicializa o vetor *grau_parentesco alocando qt_parentes espacos dinamicamente */
void inicializa_grau_parenteso(int **grau_parentesco, int qt_parentes)
{
	*grau_parentesco = (int *) malloc(qt_parentes*sizeof(int));
}

/* Define os graus de parentesco de cada nome, atribuindo o codigo especifico no vetor grau_parentesco */
/* Cada posicao do vetor corresponde ao nome naquela posicao (ordem de entrada do usuario) */
void define_parentesco(char *cidadao, char **parentes, int grau_parentesco[], int qt_parentes)
{
	int i=0, j, k;
	char *sobr_c_1, *sobr_c_2, *sobr_p_1, *sobr_p_2, *sobr_pai, *sobr_mae, *sobr_conj;
	sobr_c_1 = (char *) malloc(1);
	sobr_c_2 = (char *) malloc(1);
	sobr_p_1 = (char *) malloc(1);
	sobr_p_2 = (char *) malloc(1);
	sobr_pai = (char *) malloc(1);
	sobr_mae = (char *) malloc(1);
	sobr_conj = (char *) malloc(1);
	for(j=0; j<qt_parentes; j++)
		grau_parentesco[j]=0;
	while(cidadao[i]!=' ')
		i++;
	i++;
	for(j=0; cidadao[i]!=' '; i++)
	{
		sobr_c_1[j]=cidadao[i];
		j++;
		sobr_c_1 = (char *) realloc(sobr_c_1, j+1);
	}
	sobr_c_1[j]='\0';
	i++;
	for(j=0; cidadao[i]!='\0'; i++)
	{
		sobr_c_2[j]=cidadao[i];
		j++;
		sobr_c_2 = (char *) realloc(sobr_c_2, j+1);
	}
	sobr_c_2[j]='\0';
	for(i=0; i<qt_parentes; i++)
	{
		j=0;
		while(parentes[i][j]!=' ')
			j++;
		j++;
		for(k=0; parentes[i][j]!=' '; j++)
		{
			sobr_p_1[k]=parentes[i][j];
			k++;
			sobr_p_1 = (char *) realloc(sobr_p_1, k+1);
		}
		sobr_p_1[k]='\0';
		j++;
		for(k=0; parentes[i][j]!='\0'; j++)
		{
			sobr_p_2[k]=parentes[i][j];
			k++;
			sobr_p_2 = (char *) realloc(sobr_p_2, k+1);
		}
		sobr_p_2[k]='\0';
		if(grau_parentesco[i]==0)
		{
			if(strcmp(sobr_c_2, sobr_p_2)==0&&strcmp(sobr_c_1, sobr_p_1)!=0)
			{
				grau_parentesco[i]=PAI;
				sobr_pai = (char *) realloc(sobr_pai, strlen(sobr_p_1)+1);
				strcpy(sobr_pai, sobr_p_1);
				break;
			}
		}
	}
	for(i=0; i<qt_parentes; i++)
	{
		j=0;
		while(parentes[i][j]!=' ')
			j++;
		j++;
		for(k=0; parentes[i][j]!=' '; j++)
		{
			sobr_p_1[k]=parentes[i][j];
			k++;
			sobr_p_1 = (char *) realloc(sobr_p_1, k+1);
		}
		sobr_p_1[k]='\0';
		j++;
		for(k=0; parentes[i][j]!='\0'; j++)
		{
			sobr_p_2[k]=parentes[i][j];
			k++;
			sobr_p_2 = (char *) realloc(sobr_p_2, k+1);
		}
		sobr_p_2[k]='\0';
		if(grau_parentesco[i]==0)
		{
			if(strcmp(sobr_c_2, sobr_p_1)==0&&strcmp(sobr_c_1, sobr_p_2)!=0)
			{
				grau_parentesco[i]=CONJUGE;
				sobr_conj = (char *) realloc(sobr_conj, strlen(sobr_p_2)+1);
				strcpy(sobr_conj, sobr_p_2);
				break;
			}
		}
	}
	for(i=0; i<qt_parentes; i++)
	{
		j=0;
		while(parentes[i][j]!=' ')
			j++;
		j++;
		for(k=0; parentes[i][j]!=' '; j++)
		{
			sobr_p_1[k]=parentes[i][j];
			k++;
			sobr_p_1 = (char *) realloc(sobr_p_1, k+1);
		}
		sobr_p_1[k]='\0';
		j++;
		for(k=0; parentes[i][j]!='\0'; j++)
		{
			sobr_p_2[k]=parentes[i][j];
			k++;
			sobr_p_2 = (char *) realloc(sobr_p_2, k+1);
		}
		sobr_p_2[k]='\0';
		if(grau_parentesco[i]==0)
		{
			if(strcmp(sobr_c_1, sobr_p_2)==0&&strcmp(sobr_c_2, sobr_p_1)!=0&&strcmp(sobr_p_1, sobr_conj)!=0)
			{
				grau_parentesco[i]=MAE;
				sobr_mae = (char *) realloc(sobr_mae, strlen(sobr_p_1)+1);
				strcpy(sobr_mae, sobr_p_1);
				break;
			}
		}
	}
	for(i=0; i<qt_parentes; i++)
	{
		j=0;
		while(parentes[i][j]!=' ')
			j++;
		j++;
		for(k=0; parentes[i][j]!=' '; j++)
		{
			sobr_p_1[k]=parentes[i][j];
			k++;
			sobr_p_1 = (char *) realloc(sobr_p_1, k+1);
		}
		sobr_p_1[k]='\0';
		j++;
		for(k=0; parentes[i][j]!='\0'; j++)
		{
			sobr_p_2[k]=parentes[i][j];
			k++;
			sobr_p_2 = (char *) realloc(sobr_p_2, k+1);
		}
		sobr_p_2[k]='\0';
		if(grau_parentesco[i]==0)
			if(strcmp(sobr_c_1, sobr_p_1)==0&&strcmp(sobr_c_2, sobr_p_2)==0)
				grau_parentesco[i]=IRMAO;
	}
	for(i=0; i<qt_parentes; i++)
	{
		j=0;
		while(parentes[i][j]!=' ')
			j++;
		j++;
		for(k=0; parentes[i][j]!=' '; j++)
		{
			sobr_p_1[k]=parentes[i][j];
			k++;
			sobr_p_1 = (char *) realloc(sobr_p_1, k+1);
		}
		sobr_p_1[k]='\0';
		j++;
		for(k=0; parentes[i][j]!='\0'; j++)
		{
			sobr_p_2[k]=parentes[i][j];
			k++;
			sobr_p_2 = (char *) realloc(sobr_p_2, k+1);
		}
		sobr_p_2[k]='\0';
		if(grau_parentesco[i]==0)
			if(strcmp(sobr_p_1, sobr_conj)==0&&strcmp(sobr_p_2, sobr_c_1)==0)
				grau_parentesco[i]=FILHO;
	}
	for(i=0; i<qt_parentes; i++)
	{
		j=0;
		while(parentes[i][j]!=' ')
			j++;
		j++;
		for(k=0; parentes[i][j]!=' '; j++)
		{
			sobr_p_1[k]=parentes[i][j];
			k++;
			sobr_p_1 = (char *) realloc(sobr_p_1, k+1);
		}
		sobr_p_1[k]='\0';
		j++;
		for(k=0; parentes[i][j]!='\0'; j++)
		{
			sobr_p_2[k]=parentes[i][j];
			k++;
			sobr_p_2 = (char *) realloc(sobr_p_2, k+1);
		}
		sobr_p_2[k]='\0';
		if(grau_parentesco[i]==0)
			if(strcmp(sobr_p_1, sobr_pai)==0||strcmp(sobr_p_2, sobr_pai)==0||strcmp(sobr_p_1, sobr_mae)==0||strcmp(sobr_p_2, sobr_mae)==0)
				grau_parentesco[i]=TIO;
	}
	for(i=0; i<qt_parentes; i++)
		if(grau_parentesco[i]==0)
			grau_parentesco[i]=DESCONHECIDO;
	free(sobr_c_1);
	free(sobr_c_2);
	free(sobr_p_1);
	free(sobr_p_2);
	free(sobr_pai);
	free(sobr_mae);
	free(sobr_conj);
}
