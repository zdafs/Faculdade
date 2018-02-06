/* ================================================================== *
    Universidade Federal de Sao Carlos - UFSCar, Sorocaba
 
    Disciplina: Algoritmos e Programação 2
    Prof. Tiago A. Almeida
 
    Lista 04 - Exercício 05 - Calculos
 
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

void fatorial(int i, long long *resultado);
void fibonacci(int i, long long *resultado);
void bhaskara(double a, double b, double c, double *x1, double *x2);




/* --------------------------------- */
/* --- NÃO ALTERAR A FUNÇÃO MAIN --- */
/* --------------------------------- */
int main() {
    int opcao;
    int i;
    long long resultado;
    double a, b, c, x1, x2;
    
    while (scanf("%d", &opcao) > 0) {
        switch (opcao) {
        case 1:
            scanf("%d", &i);
            fatorial(i, &resultado);
            printf("%lld\n", resultado);
            
            break;
        case 2:
            scanf("%d", &i);
            fibonacci(i, &resultado);
            printf("%lld\n", resultado);
            
            break;
        case 3:
            scanf("%lf%lf%lf", &a, &b, &c);
            bhaskara(a, b, c, &x1, &x2);
            printf("%lf %lf\n", x1, x2);
        
            break;
        case 4:
            return 0;
        }
    }
    
    return 0;
}
/* --------------------------------- */

void fatorial(int i, long long *resultado)
{
	*resultado=1;
	for(; i>1; i--)
		*resultado=*resultado*i;
}

void fibonacci(int i, long long *resultado)
{
	long long int f1=0, f2=1;
	if(i==1)
		*resultado=0;
	else if(i==2)
		*resultado=1;
	else
	{
		for(;i>2; i--)
		{
			*resultado=f1+f2;
			f1=f2;
			f2=*resultado;
		}
	}
}

void bhaskara(double a, double b, double c, double *x1, double *x2)
{
	*x1=0;
	*x2=0;
	if(a!=0)
	{
		*x1=((-b+sqrt((pow(b,2)-(4*a*c))))/(2*a));
		*x2=((-b-sqrt((pow(b,2)-(4*a*c))))/(2*a));
	}
}
