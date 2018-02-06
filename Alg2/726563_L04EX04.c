/* ================================================================== *
   Universidade Federal de Sao Carlos - UFSCar, Sorocaba

   Disciplina: Algoritmos e Programação 2
   Prof. Tiago A. Almeida

   Lista 4 - Exercício 4 - Canivete Suico para Vetores

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
         OPC_SAIR,
         OPC_IMPRIMIR,
         OPC_MAXMIN,
         OPC_SOMA,
         OPC_ESTATISTICA,
         OPC_BUSCARVALOR,
         OPC_CONTAGEM
};


// Declaração das funções.
int tamanhoVetor();
void popularVetor(int vet[], int tamanho);
void imprimirVetor(int vet[], int tamanho);
void calcularMaxMin(int vetor[], int numElementos, int *maximo, int *minimo);
void calcularSomas(int vetor[], int numElementos, int *somaPares, int *somaImpares, int *somaPositivos, int *somaNegativos);
void calcularEstatistica(int vetor[], int numElementos, float *media, float *mediaHarmonica, float *mediana, float *desvioPadrao);
void buscarValor(int vetor[], int numElementos, int numero, int *totalOcorrencia, int *primeiraOcorrencia, int *ultimaOcorrencia);
void contarEspecial(int vetor[], int numElementos, int *qtPares, int *qtImpares, int *qtPrimos, int *qtFibonacci);
int Fibonacci(int a);
int primo(int a);


/* ---------------- */
/* ROTINA PRINCIPAL */
/* ---------------- */
int main(){

   int numElementos = 0,   //Armazena o tamanho do vetor.
       opcao,              //Armazena o a opção selecionada pelo usuário.
       vetor[MAX],
       numero;             //Armazena o número digitado pelo usuário para contagem e busca.

   // variaveis para a rotina de maximo e minimo
   int maximo, minimo;

   // variaveis para a rotina de soma
   int somaPares, somaImpares, somaPositivos, somaNegativos;

   // variaveis para a rotina de estatistica
   float media, mediaHarmonica, mediana, desvioPadrao;

   // variaveis para a rotina de contagem
   int qtPares, qtImpares, qtPrimos, qtFibonacci;

   // variaveis para a rotina de busca por valor
   int totalOcorrencia, primeiraOcorrencia, ultimaOcorrencia;

   numElementos = tamanhoVetor();
   popularVetor(vetor, numElementos);

   scanf("%d", &opcao);     //Lê a opção selecionada pelo usuário.

   //Executa as opções enquanto o usuário não digitar a opção 0 - Sair.
   while(opcao != OPC_SAIR){

      switch(opcao){         

         //----------------------------------------------------------
            case OPC_IMPRIMIR:
               imprimirVetor(vetor, numElementos);
            break;
         //----------------------------------------------------------

         //----------------------------------------------------------
            case OPC_MAXMIN:
               calcularMaxMin(vetor, numElementos, &maximo, &minimo);
               printf("%d %d\n", minimo, maximo);
            break;
         //----------------------------------------------------------

         //----------------------------------------------------------
            case OPC_SOMA:
               calcularSomas(vetor, numElementos, &somaPares, &somaImpares, &somaPositivos, &somaNegativos);
               printf("%d %d %d %d\n", somaPares, somaImpares, somaPositivos, somaNegativos);
            break;
         //----------------------------------------------------------

         //----------------------------------------------------------
            case OPC_ESTATISTICA:
               // lembre-se de considerar apenas numeros maiores que zero na media harmonica
               // para o desvio padrao, considere o vetor como amostra e nao a populacao toda
               calcularEstatistica(vetor, numElementos, &media, &mediaHarmonica, &mediana, &desvioPadrao);
               printf("%.2f %.2f %.2f %.2f\n", media, mediaHarmonica, mediana, desvioPadrao);
            break;
         //----------------------------------------------------------

         //----------------------------------------------------------
            case OPC_BUSCARVALOR:
               scanf("%d",&numero); //le qual numero esta sendo buscado
               buscarValor(vetor, numElementos, numero, &totalOcorrencia, &primeiraOcorrencia, &ultimaOcorrencia);
               printf("%d %d %d\n", totalOcorrencia, primeiraOcorrencia, ultimaOcorrencia);
            break;
         //----------------------------------------------------------

         //----------------------------------------------------------
            case OPC_CONTAGEM:
               contarEspecial(vetor, numElementos, &qtPares, &qtImpares, &qtPrimos, &qtFibonacci);
               printf("%d %d %d %d\n", qtPares, qtImpares, qtPrimos, qtFibonacci);
            break;
         //----------------------------------------------------------

      }

      scanf("%d", &opcao);      
   }

   return 0;

}

/* --------------------------------------- */
/* IMPLEMENTACAO DAS FUNCOES - NAO ALTERAR */
/* --------------------------------------- */

//Lê o tamanho do vetor passado pelo usuário e retorna o valor.
int tamanhoVetor(){
   int tamanho;

   do{
      scanf("%d", &tamanho);
   }while(tamanho < 1 || tamanho > 100);

   return tamanho;
}

//Lê os elementos do vetor passados pelo usuário.
void popularVetor(int vet[], int tamanho){
   int i;

   for(i = 0; i < tamanho; i++)
      scanf("%d", &vet[i]);
}

//Imprime os elementos do vetor.
void imprimirVetor(int vet[], int tamanho){
   int i;

   for(i = 0; i < tamanho; i++)
      printf("%d ", vet[i]);

   printf("\n");
}

/* ------------------------- */
/* IMPLEMENTACAO DAS FUNCOES */
/* ------------------------- */

void calcularMaxMin(int vetor[], int numElementos, int *maximo, int *minimo)
{
	int i;
	*maximo=*minimo=vetor[0];
	for(i=1; i<numElementos; i++)
	{
		if(vetor[i]>*maximo)
			*maximo=vetor[i];
		else if(vetor[i]<*minimo)
			*minimo=vetor[i];
	}
}

void calcularSomas(int vetor[], int numElementos, int *somaPares, int *somaImpares, int *somaPositivos, int *somaNegativos)
{
	int i;
	*somaPares=*somaImpares=*somaPositivos=*somaNegativos=0;
	for(i=0; i<numElementos; i++)
	{
		if(vetor[i]>0)
		{
			*somaPositivos=*somaPositivos+vetor[i];
		}
		else
		{
			*somaNegativos=*somaNegativos+vetor[i];
		}
			
		if(vetor[i]%2==0)
		{
			*somaPares=*somaPares+vetor[i];
		}
		else
		{
			*somaImpares=*somaImpares+vetor[i];
		}
	}
}

void calcularEstatistica(int vetor[], int numElementos, float *media, float *mediaHarmonica, float *mediana, float *desvioPadrao)
{
	int vetaux[MAX], i, j, aux, cont=0;
	*media=*mediaHarmonica=*mediana=*desvioPadrao=0;
	for(i=0; i<numElementos; i++)
		vetaux[i]=vetor[i];
	for(i=0; i<numElementos; i++)
	{
		for(j=i+1; j<numElementos; j++)
		{
			if(vetaux[i]>vetaux[j])
			{
				aux=vetaux[i];
				vetaux[i]=vetaux[j];
				vetaux[j]=aux;
			}
		}
	}
	for(i=0; i<numElementos; i++)
	{
		*media=*media+vetaux[i];
		if(vetaux[i]>0)
		{
			cont++;
			*mediaHarmonica=*mediaHarmonica+(1/((float)vetaux[i]));
		}
	}
	*media=*media/(float)numElementos;
	if(cont>0)
		*mediaHarmonica=((float)cont)/(*mediaHarmonica);
	if(numElementos%2==0)
	{
		*mediana=((float)vetaux[(numElementos/2)-1]+(float)vetaux[(numElementos/2)])/2;
		//*mediana=*mediana/2;
	}
	else
		*mediana=vetaux[((numElementos+1)/2)-1];
	for(i=0; i<numElementos; i++)
	{
			*desvioPadrao=*desvioPadrao+pow((*media-vetaux[i]),2);
	}
	*desvioPadrao=sqrt(*desvioPadrao/((float)numElementos-1));
}

void buscarValor(int vetor[], int numElementos, int numero, int *totalOcorrencia, int *primeiraOcorrencia, int *ultimaOcorrencia)
{
	int i;
	*totalOcorrencia=0;
	*primeiraOcorrencia=*ultimaOcorrencia=-1;
	for(i=0; i<numElementos; i++)
	{
		if(numero==vetor[i]&&*totalOcorrencia==0)
		{
			*primeiraOcorrencia=i;
			*ultimaOcorrencia=i;
			*totalOcorrencia=*totalOcorrencia+1;
		}
		else if(numero==vetor[i])
		{
			*ultimaOcorrencia=i;
			*totalOcorrencia=*totalOcorrencia+1;
		}
	}
}

int Fibonacci(int a)
{
	long int f1=0, f2=1, resp=0;
	if(a==f1||a==f2)
		return(1);
	while(a>resp)
	{
		resp=f1+f2;
		f1=f2;
		f2=resp;
		if(a==resp)
			return(1);
	}
	return(0);
}

int primo(int a)
{
	long int i, j;
	int flag;
	if(a==2)
		return(1);
	for(i=3; a>=i; i=i+2)
	{
		for(j=3, flag=0; j<i&&flag==0; j++)
		{
			if(i%j==0)
				flag=1;
		}
		if(flag==0&&a==i)
			return(1);
	}
	return(0);
}

void contarEspecial(int vetor[], int numElementos, int *qtPares, int *qtImpares, int *qtPrimos, int *qtFibonacci)
{
	int i;
	*qtPares=*qtImpares=*qtPrimos=*qtFibonacci=0;
	for(i=0; i<numElementos; i++)
	{
		if(vetor[i]%2==0)
			*qtPares=*qtPares+1;
		else
			*qtImpares=*qtImpares+1;
		if(primo(vetor[i]))
			*qtPrimos=*qtPrimos+1;
		if(Fibonacci(vetor[i]))
			*qtFibonacci=*qtFibonacci+1;
	}
}
