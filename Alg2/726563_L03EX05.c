/* ================================================================== *
	Universidade Federal de Sao Carlos - UFSCar, Sorocaba

	Disciplina: Algoritmos e Programação 2
	Prof. Tiago A. Almeida

	Lista 03 - Exercício 05 - Recursao em Matrizes

	Instrucoes
	----------

	Este arquivo contem o codigo que auxiliara no desenvolvimento do
	exercicio. Voce precisara completar as partes requisitadas.

* ================================================================== *
	Dados do aluno:

	RA: 726563
	Nome: Lucca La Fonte ALbuquerque Carvalho

* ================================================================== */

#include <stdio.h>

#define MAX 100

#define OPCAO_OBTER_MENOR   1
#define OPCAO_OBTER_MAIOR   2
#define OPCAO_OBTER_SOMA    3
#define OPCAO_NOVA_MATRIZ   4
#define OPCAO_SAIR          5

int m, n;
int matriz[MAX][MAX];

int obter_menor(int i);
int obter_maior(int i);
int obter_soma(int i);

int main() {
    int i, j, opcao, nova_matriz;
    
    while (scanf("%d %d", &m, &n) > 0 && m > 0 && n > 0) {
        for (i = 0; i < n; ++i) {
            for (j = 0; j < m; ++j)
                scanf("%d", &matriz[i][j]);
        }
        
        nova_matriz = 0;
        while (!nova_matriz && scanf("%d", &opcao) > 0) {
            switch(opcao) {
            case OPCAO_OBTER_MENOR:
                printf("%d\n", obter_menor(0));
                break;
            case OPCAO_OBTER_MAIOR:
                printf("%d\n", obter_maior(0));
                break;
            case OPCAO_OBTER_SOMA:
                printf("%d\n", obter_soma(0));
                break;
            case OPCAO_NOVA_MATRIZ:
                nova_matriz = 1;
                break;
            case OPCAO_SAIR:
                return 0;
            }
        }
    }
    
    return (0);
}

int obter_menor(int i) {
    
	int aux=m-1, menor;
	if(i==n-1&&aux==0)
	{
		return(matriz[i][aux]);
	}
	else if(i<n-1)
	{
		menor=obter_menor(i+1);
		m=aux+1;
		if(matriz[i][aux]<menor)
			return(matriz[i][aux]);
		else
			return(menor);
	}
	else if(i==n-1)
	{
		m--;
		menor=obter_menor(0);
		m=aux+1;
		if(matriz[i][aux]<menor)
			return(matriz[i][aux]);
		else
			return(menor);
	}
		
    
}

int obter_maior(int i) {
    
    int aux=m-1, maior;
	if(i==n-1&&aux==0)
	{
		return(matriz[i][aux]);
	}
	else if(i<n-1)
	{
		maior=obter_maior(i+1);
		m=aux+1;
		if(matriz[i][aux]>maior)
			return(matriz[i][aux]);
		else
			return(maior);
	}
	else if(i==n-1)
	{
		m--;
		maior=obter_maior(0);
		m=aux+1;
		if(matriz[i][aux]>maior)
			return(matriz[i][aux]);
		else
			return(maior);
	}
    
}

int obter_soma(int i) {    
    
	int aux=m-1, soma;
	if(i==n-1&&aux==0)
	{
		return(matriz[i][aux]);
	}
	else if(i<n-1)
	{
		soma=matriz[i][aux]+obter_soma(i+1);
		m=aux+1;
		return(soma);
	}
	else if(i==n-1)
	{
		m--;
		soma=matriz[i][aux]+obter_soma(0);
		m=aux+1;
		return(soma);
	}
    
}
