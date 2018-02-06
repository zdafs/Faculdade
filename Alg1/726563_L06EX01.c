/* ================================================================== *
    Universidade Federal de Sao Carlos - UFSCar, Sorocaba

    Disciplina: Algoritmos e Programação 1
    Prof. Tiago A. Almeida

    Lista 06 - Exercício 01 - Manipulacao de vetores

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


#define MAX 100   // Limite do tamanho dos vetores A e B
#define OPC_INVALIDA "Opcao invalida\n" // Frase de opcao invalida
#define A 0	// Opcao para usar o vetor A
#define B 1	// Opcao para usar o vetor B
#define FALSO 0
#define VERDADEIRO 1


//Enumeração das opções do programa
enum{
	OPC_SAIR,					//Finaliza o programa.
	OPC_SOMAAOUB,				//Imprime a soma dos valores do vetor A ou B.
	OPC_SOMA, 					//Imprime a soma dos valores dos vetores.
	OPC_MEDIA_AOUB,				//Imprime a média dos valores do vetor A ou B.
	OPC_MEDIA,					//Imprime a média dos valores presentes nos vetores.
	OPC_DESVIO_AOUB,			//Imprime o desvio padrão dos valores do vetor A ou B.
	OPC_DESVIO,					//Imprime o desvio padrão dos valores dos vetores.
	OPC_MAX_AOUB,				//Imprime o maior valor do vetor A ou B.
	OPC_MAX,					//Imprime o maior valor presente nos vetores.
	OPC_MIN_AOUB,				//Imprime o menor valor do vetor A ou B.
	OPC_MIN,					//Imprime o menor valor presente nos vetores.
	OPC_IMPRIMIR_AOUB,			//Imprime os elementos do vetor A ou B.
	OPC_IMPRIMIR_INVERT_AOUB,	//Imprime os elementos do vetor A em ordem invertida.
	OPC_IMPRIMIR_PARES_AOUB,	//Imprime somente os números pares do vetor A ou B.
	OPC_IMPRIMIR_IMPARES_AOUB,	//Imprime somente os números ímpares do vetor A ou B.
	OPC_IMPRIMIR_PRIMOS_AOUB,	//Imprime somente os números primos do vetor A ou B.
	OPC_MEDIANA_AOUB, 			//Imprime a mediana do vetor A ou B.
	OPC_NUMERO_PERFEITO_AOUB,	//Imprime somente os números perfeitos do vetor A ou B.
	OPC_NUMERO_TRIANGULAR_AOUB,	//Imprime somente os números triangulares do vetor A ou B.
};



int main(){

	int VetA[MAX], VetB[MAX], VetC[200], VetAUX[MAX], TamA, TamB, TamC, opcao, opcao2, i, j, aux, eh_primo, soma;
	float media, desvio, mediana;
	do
	{
		scanf("%d", &TamA);
	}
	while(TamA<1||TamA>100);
	for(i=0; i<TamA; i++)
	{
		scanf("%d", &VetA[i]);
		VetC[i]=VetA[i];
	}
	do
	{
		scanf("%d", &TamB);
	}
	while(TamB<1||TamB>100);
	for(i=0,j=TamA; i<TamB; i++,j++)
	{
		scanf("%d", &VetB[i]);
		VetC[j]=VetB[i];
	}
	TamC=TamA+TamB;
	scanf("%d", &opcao);
	do
	{
		switch(opcao)
		{
			case OPC_SAIR: break;

			case OPC_SOMAAOUB:
				soma=0;
				scanf("%d", &opcao2);
				if(opcao2==A)
				{
					for(i=0;i<TamA;i++)
					{
						soma=soma+VetA[i];
					}
				}
				else if(opcao2==B)
				{
					for(i=0;i<TamB;i++)
					{
						soma=soma+VetB[i];
					}
				}
				printf("%d", soma);
			break;

			case OPC_SOMA:
				soma=0;
				for(i=0;i<TamC;i++)
				{
					soma=soma+VetC[i];
				}
				printf("%d", soma);
			break;

			case OPC_MEDIA_AOUB:
				media=0;
				scanf("%d", &opcao2);
				if(opcao2==A)
				{
					for(i=0;i<TamA;i++)
					{
						media=media+VetA[i];
					}
					media=media/TamA;
				}
				else if(opcao2==B)
				{
					for(i=0;i<TamB;i++)
					{
						media=media+VetB[i];
					}
					media=media/TamB;
				}
				printf("%.2f", media);
			break;

			case OPC_MEDIA:
				media=0;
				for(i=0;i<TamC;i++)
				{
					media=media+VetC[i];
				}
				media=media/TamC;
				printf("%.2f", media);
			break;

			case OPC_DESVIO_AOUB:
				desvio=0;
				media=0;
				scanf("%d", &opcao2);
				if(opcao2==A)
				{
					for(i=0;i<TamA;i++)
					{
						media=media+VetA[i];
					}
					media=media/TamA;
					for(i=0;i<TamA;i++)
					{
						desvio=desvio+pow((VetA[i]-media),2);
					}
					desvio=sqrt((desvio/(TamA-1)));
				}
				else if(opcao2==B)
				{
					for(i=0;i<TamB;i++)
					{
						media=media+VetB[i];
					}
					media=media/TamB;
					for(i=0;i<TamB;i++)
					{
						desvio=desvio+pow((VetB[i]-media),2);
					}
					desvio=sqrt((desvio/(TamB-1)));
				}
				printf("%.2f", desvio);
			break;

			case OPC_DESVIO:
				desvio=0;
				media=0;
				for(i=0;i<TamC;i++)
				{
					media=media+VetC[i];
				}
				media=media/TamC;
				for(i=0;i<TamC;i++)
				{
					desvio=desvio+pow((VetC[i]-media),2);
				}
				desvio=sqrt((desvio/(TamC-1)));
				printf("%.2f", desvio);
			break;

			case OPC_MAX_AOUB:
				scanf("%d", &opcao2);
				if(opcao2==A)
				{
					aux=VetA[0];
					for(i=1;i<TamA;i++)
					{
						if(VetA[i]>aux)
						{
							aux=VetA[i];
						}
					}
				}
				if(opcao2==B)
				{
					aux=VetB[0];
					for(i=1;i<TamB;i++)
					{
						if(VetB[i]>aux)
						{
							aux=VetB[i];
						}
					}
				}
				printf("%d", aux);
			break;

			case OPC_MAX:
				aux=VetC[0];
				for(i=1;i<TamC;i++)
				{
					if(VetC[i]>aux)
					{
						aux=VetC[i];
					}
				}
				printf("%d", aux);
			break;

			case OPC_MIN_AOUB:
				scanf("%d", &opcao2);
				if(opcao2==A)
				{
					aux=VetA[0];
					for(i=1;i<TamA;i++)
					{
						if(VetA[i]<aux)
						{
							aux=VetA[i];
						}
					}
				}
				if(opcao2==B)
				{
					aux=VetB[0];
					for(i=1;i<TamB;i++)
					{
						if(VetB[i]<aux)
						{
							aux=VetB[i];
						}
					}
				}
				printf("%d", aux);
			break;

			case OPC_MIN:
				aux=VetC[0];
				for(i=1;i<TamC;i++)
				{
					if(VetC[i]<aux)
					{
						aux=VetC[i];
					}
				}
				printf("%d", aux);
			break;

			case OPC_IMPRIMIR_AOUB:
				scanf("%d", &opcao2);
				if(opcao2==A)
				{
					for(i=0;i<TamA;i++)
					{
						printf("%d ", VetA[i]);
					}
				}
				else if(opcao2==B)
				{
					for(i=0;i<TamB;i++)
					{
						printf("%d ", VetB[i]);
					}
				}
			break;

			case OPC_IMPRIMIR_INVERT_AOUB:
				scanf("%d", &opcao2);
				if(opcao2==A)
				{
					for(i=TamA-1;i>=0;i--)
					{
						printf("%d ", VetA[i]);
					}
				}
				else if(opcao2==B)
				{
					for(i=TamB-1;i>=0;i--)
					{
						printf("%d ", VetB[i]);
					}
				}
			break;

			case OPC_IMPRIMIR_PARES_AOUB:
				scanf("%d", &opcao2);
				if(opcao2==A)
				{
					for(i=0;i<TamA;i++)
					{
						if(VetA[i]%2==0)
						{
							printf("%d ", VetA[i]);
						}
					}
				}
				else if(opcao2==B)
				{
					for(i=0;i<TamB;i++)
					{
						if(VetB[i]%2==0)
						{
							printf("%d ", VetB[i]);
						}
					}
				}
			break;

			case OPC_IMPRIMIR_IMPARES_AOUB:
				scanf("%d", &opcao2);
				if(opcao2==A)
				{
					for(i=0;i<TamA;i++)
					{
						if(VetA[i]%2!=0)
						{
							printf("%d ", VetA[i]);
						}
					}
				}
				else if(opcao2==B)
				{
					for(i=0;i<TamB;i++)
					{
						if(VetB[i]%2!=0)
						{
							printf("%d ", VetB[i]);
						}
					}
				}
			break;

			case OPC_IMPRIMIR_PRIMOS_AOUB:
				scanf("%d", &opcao2);
				if(opcao2==A)
				{
					for(i=0;i<TamA;i++)
					{
						eh_primo=VERDADEIRO;
						for(j=2;j<VetA[i];j++)
						{
							if(VetA[i]%j==0)
							{
								eh_primo=FALSO;
							}
						}
						if(eh_primo==VERDADEIRO&&VetA[i]>1)
						{
							printf("%d ", VetA[i]);
						}
					}
				}
				else if(opcao2==B)
				{
					for(i=0;i<TamB;i++)
					{
						eh_primo=VERDADEIRO;
						for(j=2;j<VetB[i];j++)
						{
							if(VetB[i]%j==0)
							{
								eh_primo=FALSO;
							}
						}
						if(eh_primo==VERDADEIRO&&VetB[i]>1)
						{
							printf("%d ", VetB[i]);
						}
					}
				}
			break;

			case OPC_MEDIANA_AOUB:
				scanf("%d", &opcao2);
				if(opcao2==A)
				{
					for(i=0;i<TamA;i++)
					{
						VetAUX[i]=VetA[i];
					}
					for(i=0;i<TamA;i++)
					{
						for(j=i+1;j<TamA;j++)
						{
							if(VetAUX[i]>VetAUX[j])
							{
								aux=VetAUX[i];
								VetAUX[i]=VetAUX[j];
								VetAUX[j]=aux;
							}
						}
					}
					if(TamA%2==0)
					{
						mediana=(((float)VetAUX[(TamA/2)]+VetAUX[((TamA-2)/2)])/2);
					}
					else
					{
						mediana=VetAUX[((TamA-1)/2)];
					}
				}
				else if(opcao2==B)
				{
					for(i=0;i<TamB;i++)
					{
						VetAUX[i]=VetB[i];
					}
					for(i=0;i<TamB;i++)
					{
						for(j=i+1;j<TamB;j++)
						{
							if(VetAUX[i]>VetAUX[j])
							{
								aux=VetAUX[i];
								VetAUX[i]=VetAUX[j];
								VetAUX[j]=aux;
							}
						}
					}
					if(TamB%2==0)
					{
						mediana=(((float)VetAUX[(TamB/2)]+VetAUX[((TamB-2)/2)])/2);
					}
					else
					{
						mediana=VetAUX[((TamB-1)/2)];
					}
				}
				printf("%.2f", mediana);
			break;

			case OPC_NUMERO_PERFEITO_AOUB:
				scanf("%d", &opcao2);
				if(opcao2==A)
				{
					for(i=0;i<TamA;i++)
					{
						soma=0;
						for(j=1;j<=VetA[i]/2;j++)
						{
							if(VetA[i]%j==0)
							{
								soma=soma+j;
							}
						}
						if(soma==VetA[i])
						{
							printf("%d ", VetA[i]);
						}
					}
				}
				else if(opcao2==B)
				{
					for(i=0;i<TamB;i++)
					{
						soma=0;
						for(j=1;j<=VetB[i]/2;j++)
						{
							if(VetB[i]%j==0)
							{
								soma=soma+j;
							}
						}
						if(soma==VetB[i])
						{
							printf("%d ", VetB[i]);
						}
					}
				}
			break;

			case OPC_NUMERO_TRIANGULAR_AOUB:
				scanf("%d", &opcao2);
				if(opcao2==A)
				{
					for(i=0;i<TamA;i++)
					{
						aux=0;
						for(j=1;aux<VetA[i];j++)
						{
							aux=j*(j+1)*(j+2);
						}
						if(aux==VetA[i])
						{
							printf("%d ", VetA[i]);
						}
					}
				}
				else if(opcao2==B)
				{
					for(i=0;i<TamB;i++)
					{
						aux=0;
						for(j=1;aux<VetB[i];j++)
						{
							aux=j*(j+1)*(j+2);
						}
						if(aux==VetB[i])
						{
							printf("%d ", VetB[i]);
						}
					}
				}
			break;

			default:
				printf(OPC_INVALIDA);
			break;
		}
		if(opcao>0&&opcao<=18)
		{
			printf("\n");
		}
		scanf("%d", &opcao);
	}
	while(opcao!=OPC_SAIR);
	
	return (0);
}
