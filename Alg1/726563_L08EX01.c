/* ================================================================== *
	Universidade Federal de Sao Carlos - UFSCar, Sorocaba

	Disciplina: Algoritmos e Programação 1
	Prof. Tiago A. Almeida

	Lista 08 - Exercício 01 - Funcoes e Procedimentos

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


// Enumeração das opções do menu.
enum opcoes{
	OPC_SAIR,
	OPC_FIBONACCI_1, 	// Exibir o n1-ésimo elemento da sequência Fibonacci
	OPC_FIBONACCI_2, 	// Exibir o n2-ésimo elemento da sequência Fibonacci
	OPC_FATORIAL_1,		// Exibir o fatorial de n1
	OPC_FATORIAL_2,		// Exibir o fatorial de n2
	OPC_POTENCIA,		// Exibir o resultado da potência (n1)^n2
	OPC_SOMAPARES,		// Exibir a soma de todos os números pares entre n1 e n2
	OPC_SOMAIMPARES,	// Exibir a soma de todos os números ímpares entre n1 e n2
	OPC_SOMAPRIMOS,		// Exibir a soma de todos os números primos entre n1 e n2
	OPC_MAIORPRIMO,		// Exibir o maior primo existente entre n1 e n2
	OPC_MMC,			// Exibir o valor do mínimo múltiplo comum (mmc) entre n1 e n2
	OPC_MDC,			// Exibir o valor do máximo divisor comum (mdc) entre n1 e n2
	OPC_DESVIOPADRAO,	// Exibir o desvio padrão dos valores entre n1 e n2
	OPC_COMBINACAO,		// Exibir a combinação C(n1,n2)
	OPC_MEDIAHARMONICA,	// Exibir a media harmonica dos valores entre n1 e n2
	OPC_COEFICIENTEVARIACAO // Exibir o coeficiente de variacao dos valores entre n1 e n2
};


/* ---------------------- */
/* DECLARACAO DAS FUNCOES */
/* ---------------------- */

int fibonacci(const int a);
int fatorial(int a);
float potencia(int a, int b);
int somaPares(int a, int b);
int somaImpares(int a, int b);
int somaPrimos(int a, int b);
int maiorPrimo(int a, int b);
int mmc(int a, int b);
int mdc(int a, int b);
float desvio(int a, int b);
float combinacao(int a, int b);
float harmonica(int a, int b);
float coeficiente(int a, int b);



/* ------------------------------ */
/* ROTINA PRINCIPAL				  */
/* ------------------------------ */
int main(){
	int n1, n2, //Armazenam os números n1 e n2 para os cálculos.
		opc; 	//Armazena a última opção selecionada pelo usuário.

	scanf("%d %d", &n1, &n2); //Lê os valores n1 e n2.
	scanf("%d", &opc);		  //Lê a opção do usuário.

	//Repete enquanto o usuário não selecionar a opção 0 - Sair.
	while(opc != OPC_SAIR){

		//Imprime o resultado de acordo com a opção selecionada.
		switch(opc){
			//-----------------------------------------------------------
			case OPC_FIBONACCI_1:
				printf("%d\n", fibonacci(n1)); // COMPLETE O PRINTF
			break;
			//-----------------------------------------------------------

			//-----------------------------------------------------------
			case OPC_FIBONACCI_2:
				printf("%d\n", fibonacci(n2));  // COMPLETE O PRINTF
			break;
			//-----------------------------------------------------------

			//-----------------------------------------------------------
			case OPC_FATORIAL_1:
				printf("%d\n", fatorial(n1));  // COMPLETE O PRINTF
			break;
			//-----------------------------------------------------------

			//-----------------------------------------------------------
			case OPC_FATORIAL_2:
				printf("%d\n", fatorial(n2));  // COMPLETE O PRINTF
			break;
			//-----------------------------------------------------------

			//-----------------------------------------------------------
			case OPC_POTENCIA:
				printf("%.0f\n", potencia(n1,n2));  // COMPLETE O PRINTF
			break;
			//-----------------------------------------------------------

			//-----------------------------------------------------------
			case OPC_SOMAPARES:
				printf("%d\n", somaPares(n1,n2));  // COMPLETE O PRINTF
			break;
			//-----------------------------------------------------------

			//-----------------------------------------------------------
			case OPC_SOMAIMPARES:
				printf("%d\n", somaImpares(n1,n2));  // COMPLETE O PRINTF
			break;
			//-----------------------------------------------------------

			//-----------------------------------------------------------
			case OPC_SOMAPRIMOS:
				printf("%d\n", somaPrimos(n1,n2));  // COMPLETE O PRINTF
			break;
			//-----------------------------------------------------------

			//-----------------------------------------------------------
			case OPC_MAIORPRIMO:
				printf("%d\n", maiorPrimo(n1,n2));  // COMPLETE O PRINTF
			break;
			//-----------------------------------------------------------

			//-----------------------------------------------------------
			case OPC_MMC:
				printf("%d\n", mmc(n1,n2));  // COMPLETE O PRINTF
			break;
			//-----------------------------------------------------------

			//-----------------------------------------------------------
			case OPC_MDC:
				printf("%d\n", mdc(n1,n2));  // COMPLETE O PRINTF
			break;
			//-----------------------------------------------------------

			//-----------------------------------------------------------
			case OPC_DESVIOPADRAO:
				printf("%.2f\n", desvio(n1,n2));  // COMPLETE O PRINTF
			break;
			//-----------------------------------------------------------

			//-----------------------------------------------------------
			case OPC_COMBINACAO:
				printf("%.2f\n", combinacao(n1,n2));  // COMPLETE O PRINTF
			break;
			//-----------------------------------------------------------

			//-----------------------------------------------------------
			case OPC_MEDIAHARMONICA:
				printf("%.2f\n", harmonica(n1,n2));  // COMPLETE O PRINTF
			break;
			//-----------------------------------------------------------

			//-----------------------------------------------------------
			case OPC_COEFICIENTEVARIACAO:
				printf("%.2f\n", coeficiente(n1,n2));  // COMPLETE O PRINTF
			break;
			//-----------------------------------------------------------
		}

		scanf("%d", &opc); //Lê a opção do usuário.

	}

	//Finaliza o programa.
	return (0);
}


/* ------------------------- */
/* IMPLEMENTACAO DAS FUNCOES */
/* ------------------------- */

int fibonacci(int a)
{
	int f1=1, f2=1, f3=1;
	int i;
	for(i=1;i<a-1;i++)
	{
		f3=f2+f1;
		f1=f2;
		f2=f3;
	}
	return(f3);
}

int fatorial(int a)
{
	int fat=1;
	for(;a>1;a--)
	{
		fat=fat*a;
	}
	return(fat);
}

float potencia(int a, int b)
{
	float pot=1;
	for(;b>0;b--)
	{
		pot=pot*a;
	}
	return(pot);
}

int somaPares(int a, int b)
{
	int soma=0, aux;
	if(a>b)
	{
		aux=a;
		a=b;
		b=aux;
	}
	if(a%2!=0)
	{
		a++;
	}
	for(;a<=b;a=a+2)
	{
		soma=soma+a;
	}
	return(soma);
}

int somaImpares(int a, int b)
{
	int soma=0, aux;
	if(a>b)
	{
		aux=a;
		a=b;
		b=aux;
	}
	if(a%2==0)
	{
		a++;
	}
	for(;a<=b;a=a+2)
	{
		soma=soma+a;
	}
	return(soma);
}

int somaPrimos(int a, int b)
{
	int soma=0, i, entrou, aux;
	if(a>b)
	{
		aux=a;
		a=b;
		b=aux;
	}
	for(;a<=b;a++)
	{
		entrou=0;
		for(i=2;i<=a/2&&entrou==0;i++)
		{
			if(a%i==0)
			{
				entrou=1;
			}
		}
		if(entrou==0)
		{
			soma=soma+a;
		}
	}
	return(soma);
}

int maiorPrimo(int a, int b)
{
	int maior=0, i, entrou, aux;
	if(a>b)
	{
		aux=a;
		a=b;
		b=aux;
	}
	for(;a<=b;a++)
	{
		entrou=0;
		for(i=2;i<=a/2&&entrou==0;i++)
		{
			if(a%i==0)
			{
				entrou=1;
			}
		}
		if(entrou==0)
		{
			maior=a;
		}
	}
	return(maior);
}

int mmc(int a, int b)
{
	int i, aux, entrou=0;
	if(a>b)
	{
		aux=a;
		a=b;
		b=aux;
	}
	if(b%a==0)
	{
		return(b);
	}
	for(i=2*b;i<=a*b&&entrou==0;i=i+b)
	{
		if(i%a==0)
		{
			entrou=1;
			i=i-b;
		}
	}
	return(i);
}

int mdc(int a, int b)
{
	int i, aux, entrou=0;
	if(a>b)
	{
		aux=a;
		a=b;
		b=aux;
	}
	if(b%a==0)
	{
		return(a);
	}
	for(i=a-1;i>0&&entrou==0;i--)
	{
		if(a%i==0&&b%i==0)
		{
			entrou=1;
			i++;
		}
	}
	return(i);
}

float desvio(int a, int b)
{
	float desvio=0;
	float media=0;
	int i, aux, num=0;
	if(a>b)
	{
		aux=a;
		a=b;
		b=aux;
	}
	for(i=a;i<=b;i++)
	{
		media=media+i;
		num++;
	}
	media=media/num;
	for(i=a;i<=b;i++)
	{
		desvio=desvio+pow((i-media),2);
	}
	desvio=sqrt((desvio/(num-1)));
	return(desvio);
}

float combinacao(int a, int b)
{
	float comb;
	if(a<b)
	{
		return(0);
	}
	comb=((fatorial(a))/((fatorial(b))*(fatorial(a-b))));
	return(comb);
}

float harmonica(int a, int b)
{
	int i, aux, num=0;
	float resp, som=0;
	if(a>b)
	{
		aux=a;
		a=b;
		b=aux;
	}
	for(i=a;i<=b;i++)
	{
		som=som+(1/((float)i));
		num++;
	}
	resp=num/som;
	return(resp);
}

float coeficiente(int a, int b)
{
	int i, aux, num=0;
	float resp, media=0;
	if(a>b)
	{
		aux=a;
		a=b;
		b=aux;
	}
	for(i=a;i<=b;i++)
	{
		media=media+i;
		num++;
	}
	media=media/num;
	resp=desvio(a,b)/media;
	return(resp);
}
