/* ================================================================== *
	Universidade Federal de Sao Carlos - UFSCar, Sorocaba

	Disciplina: Algoritmos e Programação 1
	Prof. Tiago A. Almeida

	Lista 08 - Exercício 02 - Funcoes e Procedimentos com Vetores

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


#define MAX 100 //Tamanho máximo do vetor.

//Enumeração das opções do menu.
enum opcoes{
	OPC_SAIR,				// Encerra o programa
	OPC_TAMANHOVETOR,		// Inserir o tamanho do vetor
	OPC_POPULARVETOR,		// Popular o vetor
	OPC_IMPRIMIR,			// Imprimir os elementos do vetor
	OPC_IMPRIMIRINVERSO,	// Imprimir os elementos do vetor em ordem inversa
	OPC_SOMA,				// Exibir a soma dos elementos do vetor
	OPC_SOMAPOSITIVOS,		// Exibir a soma dos elementos positivos do vetor
	OPC_SOMANEGATIVOS,		// Exibir a soma dos elementos negativos do vetor
	OPC_MAXIMO,				// Exibir o maior elemento do vetor
	OPC_MINIMO,				// Exibir o menor elemento do vetor
	OPC_MEDIA,				// Exibir a media dos elementos do vetor
	OPC_MEDIAHARMONICA,		// Exibir a media harmonica dos elementos do vetor
	OPC_DESVIOPADRAO,		// Exibir o desvio padrao dos elementos do vetor
	OPC_MEDIANA,			// Exibir a mediana dos elementos do vetor
	OPC_ENCONTRARPRIMEIRO,	// Exibir a posicao da primeira ocorrencia de um numero n passado pelo usuario
	OPC_ENCONTRARULTIMO,	// Exibir a posicao da ultima ocorrencia de um numero n passado pelo usuario
	OPC_CONTAR,				// Exibir a contagem do numero de ocorrencias de um numero n passado pelo usuario
	OPC_ORDENARCRESCENTE,	// Ordenar definitivamente o vetor em ordem crescente
	OPC_ORDENARDECRESCENTE	// Ordenar definitivamente o vetor em ordem decrescente
};


/* ---------------------- */
/* DECLARACAO DAS FUNCOES */
/* ---------------------- */

int tamanhoVetor();
void popularVetor(float vet[], int tamanho);
void imprimeVetor(float vet[], int tamanho);
void imprimeVetorInverso(float vet[], int tamanho);
float somaVetor(float vet[], int tamanho);
float somaPositivosVetor(float vet[], int tamanho);
float somaNegativosVetor(float vet[], int tamanho);
float maiorElem(float vet[], int tamanho);
float menorElem(float vet[], int tamanho);
float mediaVetor(float vet[], int tamanho);
float mediaHarmonica(float vet[], int tamanho);
float desvioVetor(float vet[], int tamanho);
float medianaVetor(float vet[], int tamanho);
int primeiraAp(float vet[], int tamanho, int num);
int ultimaAp(float vet[], int tamanho, int num);
int nAp(float vet[], int tamanho, int num);
void crescente(float vet[], int tamanho);
void decrescente(float vet[], int tamanho);



/* ------------------------------ */
/* ROTINA PRINCIPAL 			  */
/* ------------------------------ */
int main(){
	int numElementos = 0,	//Armazena o tamanho do vetor.
		opcao;				//Armazena o a opção selecionada pelo usuário.
	float vetor[MAX],
		  numero;			//Armazena o número digitado pelo usuário para contagem e busca.

	scanf("%d", &opcao);	//Lê a opção selecionada pelo usuário.

	//Executa as opções enquanto o usuário não digitar a opção 0 - Sair.
	while(opcao != OPC_SAIR){

		switch(opcao){			

		//----------------------------------------------------------
		case OPC_TAMANHOVETOR:
			numElementos = tamanhoVetor();
		break;
		//----------------------------------------------------------

		//----------------------------------------------------------
		case OPC_POPULARVETOR:
			popularVetor(vetor, numElementos);
		break;
		//----------------------------------------------------------

		//----------------------------------------------------------
		case OPC_IMPRIMIR:
			imprimeVetor(vetor,numElementos);
		break;
		//----------------------------------------------------------

		//----------------------------------------------------------
		case OPC_IMPRIMIRINVERSO:
			imprimeVetorInverso(vetor,numElementos);
		break;
		//----------------------------------------------------------

		//----------------------------------------------------------
		case OPC_SOMA:
			printf("%.2f\n", somaVetor(vetor,numElementos)); // COMPLETE O PRINTF
		break;
		//----------------------------------------------------------

		//----------------------------------------------------------
		case OPC_SOMAPOSITIVOS:
			printf("%.2f\n", somaPositivosVetor(vetor,numElementos)); // COMPLETE O PRINTF
		break;
		//----------------------------------------------------------

		//----------------------------------------------------------
		case OPC_SOMANEGATIVOS:
			printf("%.2f\n", somaNegativosVetor(vetor,numElementos)); // COMPLETE O PRINTF
		break;
		//----------------------------------------------------------

		//----------------------------------------------------------
		case OPC_MAXIMO:
			printf("%.2f\n", maiorElem(vetor,numElementos)); // COMPLETE O PRINTF
		break;
		//----------------------------------------------------------

		//----------------------------------------------------------
		case OPC_MINIMO:
			printf("%.2f\n", menorElem(vetor,numElementos)); // COMPLETE O PRINTF
		break;
		//----------------------------------------------------------

		//----------------------------------------------------------
		case OPC_MEDIA:
			printf("%.2f\n", mediaVetor(vetor,numElementos)); // COMPLETE O PRINTF
		break;
		//----------------------------------------------------------

		//----------------------------------------------------------
		case OPC_MEDIAHARMONICA:
			printf("%.2f\n", mediaHarmonica(vetor,numElementos)); // COMPLETE O PRINTF
		break;
		//----------------------------------------------------------

		//----------------------------------------------------------
		case OPC_DESVIOPADRAO:
			printf("%.2f\n", desvioVetor(vetor,numElementos)); // COMPLETE O PRINTF
		break;
		//----------------------------------------------------------

		//----------------------------------------------------------
		case OPC_MEDIANA:
			printf("%.2f\n", medianaVetor(vetor,numElementos)); // COMPLETE O PRINTF
		break;
		//----------------------------------------------------------

		//----------------------------------------------------------
		case OPC_ENCONTRARPRIMEIRO:
			scanf("%f", &numero);
			printf("%d\n", primeiraAp(vetor,numElementos,numero)); // COMPLETE O PRINTF
		break;
		//----------------------------------------------------------

		//----------------------------------------------------------
		case OPC_ENCONTRARULTIMO:
			scanf("%f", &numero);
			printf("%d\n", ultimaAp(vetor,numElementos,numero)); // COMPLETE O PRINTF
		break;
		//----------------------------------------------------------

		//----------------------------------------------------------
		case OPC_CONTAR:
			scanf("%f", &numero);
			printf("%d\n", nAp(vetor,numElementos,numero)); // COMPLETE O PRINTF
		break;
		//----------------------------------------------------------

		//----------------------------------------------------------
		case OPC_ORDENARCRESCENTE:
			crescente(vetor,numElementos);
		break;
		//----------------------------------------------------------

		//----------------------------------------------------------
		case OPC_ORDENARDECRESCENTE:
			decrescente(vetor,numElementos);
		break;
		//----------------------------------------------------------
		}

		scanf("%d", &opcao);		
	}

	return (0);
}



/* ------------------------- */
/* IMPLEMENTACAO DAS FUNCOES */
/* ------------------------- */

//Lê o tamanho do vetor passado pelo usuário e retorna o valor.
int tamanhoVetor(){
	int tamanho;

	do {
		scanf("%d", &tamanho);
	} while(tamanho < 1 || tamanho > 100);

	return (tamanho);
}


//Lê os elementos do vetor passados pelo usuário.
void popularVetor(float vet[], int tamanho){
	int i;

	for(i = 0; i < tamanho; i++)
		scanf("%f", &vet[i]);
}


void imprimeVetor(float vet[], int tamanho)
{
	int i;

	for(i = 0; i < tamanho; i++)
		printf("%.2f ", vet[i]);
	printf("\n");
}

void imprimeVetorInverso(float vet[], int tamanho)
{
	int i;

	for(i = tamanho-1; i >= 0; i--)
		printf("%.2f ", vet[i]);
	printf("\n");
}

float somaVetor(float vet[], int tamanho)
{
	int i;
	float soma=0;

	for(i = 0; i < tamanho; i++)
		soma=soma+vet[i];
	return(soma);
}

float somaPositivosVetor(float vet[], int tamanho)
{
	int i;
	float soma=0;

	for(i = 0; i < tamanho; i++)
	{
		if(vet[i]>0)
		{
			soma=soma+vet[i];
		}
	}
	return(soma);
}

float somaNegativosVetor(float vet[], int tamanho)
{
	int i;
	float soma=0;

	for(i = 0; i < tamanho; i++)
	{
		if(vet[i]<0)
		{
			soma=soma+vet[i];
		}
	}
	return(soma);
}

float maiorElem(float vet[], int tamanho)
{
	int i;
	float aux=vet[0];

	for(i = 1; i < tamanho; i++)
	{
		if(aux<vet[i])
		{
			aux=vet[i];
		}
	}
	return(aux);
}

float menorElem(float vet[], int tamanho)
{
	int i;
	float aux=vet[0];

	for(i = 1; i < tamanho; i++)
	{
		if(aux>vet[i])
		{
			aux=vet[i];
		}
	}
	return(aux);
}

float mediaVetor(float vet[], int tamanho)
{
	float media;
	media=somaVetor(vet,tamanho)/tamanho;
	return(media);
}

float mediaHarmonica(float vet[], int tamanho)
{
	int i;
	float media, som=0;
	for(i = 0; i < tamanho; i++)
	{
		som=som+(1/vet[i]);
	}
	media=tamanho/som;
	return(media);
}

float desvioVetor(float vet[], int tamanho)
{
	float desvio=0;
	float media=0;
	int i;
	for(i = 0; i < tamanho; i++)
	{
		media=media+vet[i];
	}
	media=media/tamanho;
	for(i = 0; i < tamanho; i++)
	{
		desvio=desvio+pow((vet[i]-media),2);
	}
	desvio=sqrt((desvio/(tamanho-1)));
	return(desvio);
}

float medianaVetor(float vet[], int tamanho)
{
	float vetAUX[MAX], aux, mediana;
	int i, j;
	for(i=0;i<tamanho;i++)
	{
		vetAUX[i]=vet[i];
	}
	for(i=0;i<tamanho;i++)
	{
		for(j=i+1;j<tamanho;j++)
		{
			if(vetAUX[i]>vetAUX[j])
			{
				aux=vetAUX[i];
				vetAUX[i]=vetAUX[j];
				vetAUX[j]=aux;
			}
		}
	}
	if(tamanho%2==0)
	{
		mediana=(((float)vetAUX[(tamanho/2)]+vetAUX[((tamanho-2)/2)])/2);
	}
	else
	{
		mediana=vetAUX[((tamanho-1)/2)];
	}
	return(mediana);
}

int primeiraAp(float vet[], int tamanho, int num)
{
	int i;
	for(i=0;i<tamanho;i++)
	{
		if(vet[i]==num)
		{
			return(i);
		}
	}
	return(-1);
}

int ultimaAp(float vet[], int tamanho, int num)
{
	int i;
	for(i=tamanho-1;i>=0;i--)
	{
		if(vet[i]==num)
		{
			return(i);
		}
	}
	return(-1);
}

int nAp(float vet[], int tamanho, int num)
{
	int i, n=0;
	for(i=0;i<tamanho;i++)
	{
		if(vet[i]==num)
		{
			n++;
		}
	}
	return(n);
}

void crescente(float vet[], int tamanho)
{
	int i, j;
	float aux;
	for(i=0;i<tamanho;i++)
	{
		for(j=i+1;j<tamanho;j++)
		{
			if(vet[i]>vet[j])
			{
				aux=vet[i];
				vet[i]=vet[j];
				vet[j]=aux;
			}
		}
	}
}

void decrescente(float vet[], int tamanho)
{
	int i, j;
	float aux;
	for(i=0;i<tamanho;i++)
	{
		for(j=i+1;j<tamanho;j++)
		{
			if(vet[i]<vet[j])
			{
				aux=vet[i];
				vet[i]=vet[j];
				vet[j]=aux;
			}
		}
	}
}
