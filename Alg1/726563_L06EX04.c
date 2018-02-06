/* ================================================================== *
    Universidade Federal de Sao Carlos - UFSCar, Sorocaba

    Disciplina: Algoritmos e Programação 1
    Prof. Tiago A. Almeida

    Lista 06 - Exercício 04 - Operacoes com Conjuntos

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


#define VERDADEIRO	1
#define FALSO		0    

#define MINIMO 1	//Tamanho minimo de cada conjunto
#define MAXIMO 50	//Tamanho maximo de cada conjunto

#define FRASE_VERDADEIRO	"VERDADEIRO\n"
#define FRASE_FALSO			"FALSO\n"
#define FRASE_VAZIO			"VAZIO\n"
#define FRASE_OPC_INVALIDA	"OPCAO INVALIDA\n"    


// Opcoes do menu    
enum{
	OPC_SAIR,					//Finaliza o programa.
	OPC_INTERSECCAO,			//Interseccao entre os conjuntos.
	OPC_SUBTRACAO,				//Subtração de conjuntos.
	OPC_PERTINENCIA			//Relação de pertinencia (contido) entre conjuntos.	
};



int main(){
	int conjuntoA[MAXIMO], conjuntoB[MAXIMO], //Conjuntos A e B.
		conjuntoC[MAXIMO], //Conjunto resultante das operacoes de A e B
		qtElementosA, qtElementosB, qtElementosC, //Armazenam o número de elementos de A, B e C.
		opcao, //Armazena a opção selecionada pelo usuário.
		i, j; //Contadores (iteradores) para os laços.
	int entrou;


	//Le o tamanho do conjunto A e os valores do Conjunto A.
	do
	{
		scanf("%d", &qtElementosA);
	}
	while(qtElementosA<MINIMO||qtElementosA>MAXIMO);
	for(i=0;i<qtElementosA;i++)
	{
		scanf("%d", &conjuntoA[i]);
	}



	//Le o tamanho do conjunto A e os valores do Conjunto B.
	do
	{
		scanf("%d", &qtElementosB);
	}
	while(qtElementosB<MINIMO||qtElementosB>MAXIMO);
	for(i=0;i<qtElementosB;i++)
	{
		scanf("%d", &conjuntoB[i]);
	}


	//Lê a opção selecionada pelo usuário.
	scanf("%d", &opcao); 


	//Executa o programa até que o usuário seleciona a opção 4: Sair do programa.
	while(opcao != OPC_SAIR){

		//Executa de acordo com a opção selecionada.
		switch(opcao){			

			case OPC_SAIR: return (0);


			//Operação de intersecção de conjuntos ---------------------------------
			case OPC_INTERSECCAO:

			
				
				for(i=0,qtElementosC=0;i<qtElementosA;i++)
				{
					entrou=0;
					for(j=0;j<qtElementosB;j++)
					{
						if(conjuntoA[i]==conjuntoB[j])
						{
							entrou++;
						}
					}
					if(entrou)
					{
						conjuntoC[qtElementosC]=conjuntoA[i];
						qtElementosC++;
					}
				}
				if(qtElementosC==0)
				{
					printf(FRASE_VAZIO);
				}
				else
				{
					for(i=0;i<qtElementosC;i++)
					{
						printf("%d ", conjuntoC[i]);
					}
					printf("\n");
				}


				break;


			//Operação de subtração de conjuntos -----------------------------------
			case OPC_SUBTRACAO:



				for(i=0,qtElementosC=0;i<qtElementosA;i++)
				{
					entrou=0;
					for(j=0;j<qtElementosB;j++)
					{
						if(conjuntoA[i]==conjuntoB[j])
						{
							entrou++;
						}
					}
					if(entrou==0)
					{
						conjuntoC[qtElementosC]=conjuntoA[i];
						qtElementosC++;
					}
				}
				if(qtElementosC==0)
				{
					printf(FRASE_VAZIO);
				}
				else
				{
					for(i=0;i<qtElementosC;i++)
					{
						printf("%d ", conjuntoC[i]);
					}
					printf("\n");
				}



				break;


			//Relação de pertinencia entre conjuntos -------------------------------
			case OPC_PERTINENCIA:


				entrou=0;
				for(i=0;i<qtElementosA;i++)
				{
					for(j=0;j<qtElementosB;j++)
					{
						if(conjuntoA[i]==conjuntoB[j])
						{
							entrou++;
						}
					}
				}
				if(entrou==qtElementosA)
				{
					printf(FRASE_VERDADEIRO);
				}
				else
				{
					printf(FRASE_FALSO);
				}



				break;


			//Opcao inexistente ----------------------------------------------------
			default:
				printf(FRASE_OPC_INVALIDA);
				break;

		}

		scanf("%d", &opcao);//Lẽ novamente a opçao do usuário.
	}
	return (0);
}
