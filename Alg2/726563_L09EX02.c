/* ================================================================== *
    Universidade Federal de Sao Carlos - UFSCar, Sorocaba
 
    Disciplina: Algoritmos e Programação 2
    Prof. Tiago A. Almeida
 
    Lista 09 - Exercício 02 - Cadastro de Alunos (Arquivo Binario)
  
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

/* Constantes */
#define MAX_ALUNO 1000
#define MAX_NOME 100

/* Arquivo */
#define ARQUIVO "Alunos.dat"

/* Mensagens de erro */
#define ALUNO_JA_CADASTRADO "Aluno já está cadastrado\n"
#define ALUNO_N_CADASTRADO "Aluno não cadastrado.\n"

/* Menu de opcoes */
#define CADASTRAR 1
#define ALTERAR 2
#define REMOVER 3
#define BUSCAR 4
#define LISTAR 5

/* Aluno */
typedef struct aluno{
    int ra;
    char nome[MAX_NOME];
    int ano;
    int creditos;
}aluno;

/* /* ===================== PROTORIPO DAS FUNCOES ===================== */

/* Exibe os dados do aluno da posicao i */
void exibir(aluno alunos[MAX_ALUNO], int i);

/* Verifica se o arquivo existe e carrega para a memoria
 Retorna o numero de alunos lido, e 0 caso nao exista arquivo */
int carregar_arquivo(aluno alunos[MAX_ALUNO]);

/* Verifica se o RA ja esta cadastrado, informando o erro
    Caso contrario, insere o aluno no vetor
    Retorna 1 para cadastro com sucesso e 0 caso contrario */
int cadastrar(aluno alunos[MAX_ALUNO], aluno alunoTemp, int numAlunos);

/* Verifica se o RA ja esta cadastrado, informando o erro
    Caso contrario, solicita os dados e altera os dados do aluno */
void alterar(aluno alunos[MAX_ALUNO], int ra, int numAlunos);

/* Verifica se o RA ja esta cadastrado, informando o erro
    Caso contrario, remove o aluno do vetor 
    Retorna 1 para remocao com sucesso e 0 caso contrario */
int remover(aluno alunos[MAX_ALUNO], int ra, int numAlunos);

/* Verifica se o RA ja esta cadastrado, informando o erro
    Caso contrario, remove o aluno do vetor */
void buscar(aluno alunos[MAX_ALUNO], int ra, int numAlunos);

/* Lista todos os alunos em ordem crescente de RA */
void listar(aluno alunos[MAX_ALUNO], int numAlunos);

/* Escreve o vetor no arquivo */
void escrever_arquivo(aluno alunos[MAX_ALUNO], int numAlunos);

/* ============================ MAIN ============================ */

int main() {
    int opcao = 0;
    int ra;
    int numAlunos;
    aluno alunos[MAX_ALUNO];
    aluno alunoTemp;
    
    numAlunos = carregar_arquivo(alunos);

    while (opcao != 6) {
        scanf("%d", &opcao);
        switch (opcao) {
            case CADASTRAR:
                scanf("%d\n%d\n%d\n%[^\n]s", &(alunoTemp.ra), &(alunoTemp.ano), &(alunoTemp.creditos), (alunoTemp.nome));
                numAlunos += cadastrar(alunos, alunoTemp, numAlunos);
                break;
            case ALTERAR:
                scanf("%d",&ra);
                alterar(alunos, ra, numAlunos);
                break;
            case REMOVER:
                scanf("%d",&ra);
                numAlunos -= remover(alunos, ra, numAlunos);
                break;
            case BUSCAR:
                scanf("%d",&ra);
                buscar(alunos, ra, numAlunos);
                break;
            case LISTAR:
                listar(alunos, numAlunos);
                break;
        }
    }

    escrever_arquivo(alunos, numAlunos);
    return 0;
}

/* ========================= FUNCOES ========================= */

/* Exibe os dados do aluno da posicao i */
void exibir(aluno alunos[MAX_ALUNO], int i) {
    printf("\nDados:\n");    
    printf("RA: %d\n",alunos[i].ra);
    printf("Nome: %s\n",alunos[i].nome);
    printf("Ano: %d\n",alunos[i].ano);
    printf("Creditos: %d\n",alunos[i].creditos);
}

int carregar_arquivo(aluno alunos[MAX_ALUNO])
{
	FILE *ptr;
	int i=0, j=0;
	char c;
	ptr = fopen(ARQUIVO, "rb");
	if(ptr==NULL)
	{
		return(0);
	}
	fread(alunos+i, sizeof(aluno), 1, ptr);
	while(!feof(ptr))
	{
		i++;
		fread(alunos+i, sizeof(aluno), 1, ptr);
	}
	fclose(ptr);
	return(i);
}

int cadastrar(aluno alunos[MAX_ALUNO], aluno alunoTemp, int numAlunos)
{
	int i;
	aluno aux;
	for(i=0; i<numAlunos; i++)
	{
		if(alunos[i].ra==alunoTemp.ra)
		{
			printf(ALUNO_JA_CADASTRADO);
			return(0);
		}
		else if(alunoTemp.ra<alunos[i].ra)
		{
			for(;i<numAlunos; i++)
			{
				aux=alunos[i];
				alunos[i]=alunoTemp;
				alunoTemp=aux;
			}
			i--;
		}
	}
	alunos[i]=alunoTemp;
	return(1);
}

void alterar(aluno alunos[MAX_ALUNO], int ra, int numAlunos)
{
	int i;
	for(i=0; i<numAlunos; i++)
	{
		if(ra==alunos[i].ra)
		{
			scanf("%d\n%d\n%[^\n]s", &alunos[i].ano, &alunos[i].creditos, alunos[i].nome);
			return;
		}
	}
	printf(ALUNO_N_CADASTRADO);
}

int remover(aluno alunos[MAX_ALUNO], int ra, int numAlunos)
{
	int i;
	for(i=0; i<numAlunos; i++)
	{
		if(ra==alunos[i].ra)
		{
			for(; i<numAlunos-1; i++)
			{
				alunos[i]=alunos[i+1];
			}
			return(1);
		}
	}
	printf(ALUNO_N_CADASTRADO);
	return(0);
}

void buscar(aluno alunos[MAX_ALUNO], int ra, int numAlunos)
{
	int i;
	for(i=0; i<numAlunos; i++)
	{
		if(ra==alunos[i].ra)
		{
			exibir(alunos, i);
			return;
		}
	}
	printf(ALUNO_N_CADASTRADO);
}

void listar(aluno alunos[MAX_ALUNO], int numAlunos)
{
	int i;
	for(i=0; i<numAlunos; i++)
		exibir	(alunos, i);
}

void escrever_arquivo(aluno alunos[MAX_ALUNO], int numAlunos)
{
	FILE *ptr;
	int i;
	ptr=fopen(ARQUIVO, "wb");
	fwrite(alunos, sizeof(aluno), numAlunos, ptr);
	fclose(ptr);
}