/* ================================================================== *
	Universidade Federal de Sao Carlos - UFSCar, Sorocaba

	Disciplina: Algoritmos e Programação 2
	Prof. Tiago A. Almeida

	Lista 02 - Exercício 02 - Cadastro de alunos

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
#include <stdlib.h>
#include <string.h>

// menu de opcoes
#define INSERIR 			1
#define ALTERAR 			2
#define REMOVER 			3
#define BUSCAR 				4
#define LISTAR				5
#define LISTARPORNOME		6
#define SAIR 				0

// frases pre-definidas para saida
#define FRASE_ALUNO_NAO_ENCONTRADO "Cadastro nao encontrado!\n"
#define FRASE_CADASTRO_CHEIO "O limite de alunos foi atingido!\n"
#define FRASE_CADASTRO_VAZIO "Nao ha nenhum aluno cadastrado!\n"
#define FRASE_JACADASTRADO "Aluno ja cadastrado!\n"

// Limitantes
#define TAM_NOME 1000	// tamamnho maximo do nome do aluno
#define MAX_ALUNOS 100 	// quantidade maxima de alunos


// Definicoes dos registros para armazenar dados de um aluno
typedef struct di
{
	int dia, mes, ano;
}dIngresso;
typedef struct Aluno
{
	int ra, creditos;
	dIngresso dataIngresso;
	char nome[TAM_NOME+1];
}aluno;


//Declaracoes das funcoes
int inserir (aluno Alunos[], int qtAlunos, aluno novoAluno);
int alterar(aluno Alunos[], int qtAlunos, int ra);
int remover(aluno Alunos[], int qtAlunos, int ra);
int buscar(aluno Alunos[], int qtAlunos, int ra);
void listar (aluno Alunos[], int qtAlunos);
void listarPorNome(aluno Alunos[], int qtAlunos);


/* ------------------------------ */
/* ROTINA PRINCIPAL - NAO ALTERAR */
/* ------------------------------ */
int main(){
	
	int opcao;
	int qtAlunos=0, indice, retorno;
	int ra;
	aluno Alunos[MAX_ALUNOS];
	aluno novoAluno;
	
	do {
		scanf("%d",&opcao);

		switch(opcao){

			case INSERIR:
				scanf("%d %d/%d/%d %d %[^\n]s", &(novoAluno.ra), 
				&(novoAluno.dataIngresso.dia), &(novoAluno.dataIngresso.mes), &(novoAluno.dataIngresso.ano),
				&(novoAluno.creditos),(novoAluno.nome));

				retorno = inserir(Alunos, qtAlunos, novoAluno);
				if (retorno == 1)
					qtAlunos++;
				else if (retorno == -1)
					printf(FRASE_CADASTRO_CHEIO);
				else 
					printf(FRASE_JACADASTRADO);

				break;


			case ALTERAR:
				scanf("%d",&ra);

				if (alterar(Alunos, qtAlunos, ra) == 0)
					printf(FRASE_ALUNO_NAO_ENCONTRADO);

				break;


			case REMOVER:
				scanf("%d",&ra);

				if (remover(Alunos, qtAlunos, ra))
					qtAlunos--;
				else
					printf(FRASE_ALUNO_NAO_ENCONTRADO);

				break;


			case BUSCAR:
				scanf("%d",&ra);

				indice = (buscar(Alunos, qtAlunos, ra));

				if (indice != -1){
					printf("%06d - ",Alunos[indice].ra);
					printf("%s - ",Alunos[indice].nome);
					printf("%02d/%02d/%04d - ",Alunos[indice].dataIngresso.dia, Alunos[indice].dataIngresso.mes, Alunos[indice].dataIngresso.ano);
					printf("%04d\n",Alunos[indice].creditos);
				} else
					printf(FRASE_ALUNO_NAO_ENCONTRADO);

				break;


			case LISTAR:

				if (qtAlunos > 0)
					listar(Alunos, qtAlunos);
				else
					printf(FRASE_CADASTRO_VAZIO);
				break;


			case LISTARPORNOME:

				if (qtAlunos > 0)
					listarPorNome(Alunos, qtAlunos);
				else
					printf(FRASE_CADASTRO_VAZIO);
				break;

			
		}	
	} while(opcao != 0);
	
	
	return (0);

}

/* ------------------------- */
/* IMPLEMENTACAO DAS FUNCOES */
/* ------------------------- */

// listar(): lista todos os registros em ordem crescente de RA
void listar (aluno Alunos[], int qtAlunos){
	int i=0;

	for (i=0; i<qtAlunos; i++){
		printf("%06d - ",Alunos[i].ra);
		printf("%s - ",Alunos[i].nome);
		printf("%02d/%02d/%04d - ",Alunos[i].dataIngresso.dia, Alunos[i].dataIngresso.mes, Alunos[i].dataIngresso.ano);
		printf("%04d\n",Alunos[i].creditos);
	}
}


/* <<< IMPLEMENTE AS DEMAIS FUNCOES AQUI >>> */

// inserir(): retorna 1 se o cadastro foi efetuado com sucesso, -1 caso não haja espaço suficiente ou 0 caso
// o RA já esteja cadastrado
int inserir (aluno Alunos[], int qtAlunos, aluno novoAluno)
{
	int i;
	aluno aux;
	if(qtAlunos>MAX_ALUNOS)
	{
		return(-1);
	}
	for(i=0;i<qtAlunos;i++)
	{
		if(novoAluno.ra==Alunos[i].ra)
		{
			return(0);
		}
	}
	for(i=0;i<qtAlunos;i++)
	{
		if(novoAluno.ra<Alunos[i].ra)
		{
			aux=novoAluno;
			novoAluno=Alunos[i];
			Alunos[i]=aux;
		}
	}
	Alunos[qtAlunos]=novoAluno;
	return(1);
}
// alterar(): retorna 1 se a alteracao foi efetuada com sucesso ou 0 caso não o registro não tenha sido encontrado
int alterar(aluno Alunos[], int qtAlunos, int ra)
{
	int i;
	for(i=0; i<qtAlunos; i++)
	{
		if(ra==Alunos[i].ra)
		{
			scanf("%d/%d/%d %d %[^\n]s", &(Alunos[i].dataIngresso.dia), 
				&(Alunos[i].dataIngresso.mes), &(Alunos[i].dataIngresso.ano),
				&(Alunos[i].creditos),(Alunos[i].nome));
			return(1);
		}
	}
	return(0);
}

// remover(): retorna 1 se a remocao foi efetuada com sucesso ou 0 caso não o registro não tenha sido encontrado
int remover(aluno Alunos[], int qtAlunos, int ra)
{
	int i;
	for(i=0; i<qtAlunos; i++)
	{
		if(ra==Alunos[i].ra)
		{
			for(;i<qtAlunos-1;i++)
			{
				Alunos[i]=Alunos[i+1];
			}
			return(1);
		}
	}
	return(0);
}

// buscar(): retorna o índice do registro caso ele tenha sido encontrado ou -1 caso contrario
int buscar(aluno Alunos[], int qtAlunos, int ra)
{
	int i;
	for(i=0;i<qtAlunos;i++)
	{
		if(ra==Alunos[i].ra)
		{
			return(i);
		}
	}
	return(-1);
}

// listarPorNome(): lista todos os registros em ordem alfabetica
void listarPorNome(aluno Alunos[], int qtAlunos)
{
	int i, j;
	aluno aux;
	for(i=0; i<qtAlunos; i++)
	{
		for(j=i+1;j<qtAlunos;j++)
		{
			if(strcmp(Alunos[i].nome,Alunos[j].nome)>0)
			{
				aux=Alunos[i];
				Alunos[i]=Alunos[j];
				Alunos[j]=aux;
			}
		}
	}
	for (i=0; i<qtAlunos; i++)
	{
		printf("%06d - ",Alunos[i].ra);
		printf("%s - ",Alunos[i].nome);
		printf("%02d/%02d/%04d - ",Alunos[i].dataIngresso.dia, Alunos[i].dataIngresso.mes, Alunos[i].dataIngresso.ano);
		printf("%04d\n",Alunos[i].creditos);
	}
	for(i=0; i<qtAlunos; i++)
	{
		for(j=i+1;j<qtAlunos;j++)
		{
			if(Alunos[i].ra>Alunos[j].ra)
			{
				aux=Alunos[i];
				Alunos[i]=Alunos[j];
				Alunos[j]=aux;
			}
		}
	}
}

