/* ================================================================== *
    Universidade Federal de Sao Carlos - UFSCar, Sorocaba

    Disciplina: Algoritmos e Programação 1
    Prof. Tiago A. Almeida

    Lista 02 - Exercício 03 - Vestibular

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

int main() 
{    
	char curso, cota;
	int Ce, Cn, Ch,r;
	float Mf;
	scanf("%c", &curso);
	scanf("%d %d %d %d", &Ce, &Cn, &Ch, &r);
	scanf("\n%c", &cota);
	if(curso=='b'||curso=='B')
	{
		Mf=((float)2*Ce+4*Cn+1*Ch+2*r)/9;
	}
	else if(curso=='c'||curso=='C')
	{
		Mf=((float)4*Ce+2*Cn+1*Ch+3*r)/10;
	}
	else
	{
		Mf=((float)4*Ce+4*Cn+1*Ch+2*r)/11;
	}
	if(cota=='p'||cota=='P')
	{
		Mf=Mf*1.15;
	}	
	else if(cota=='d'||cota=='D')
	{
		Mf=Mf*1.12;
	}
	else if(cota=='e'||cota=='E')
	{
		Mf=Mf*1.1;
	}
	if((Mf-(int)Mf)>=0.5)
	{
		Mf=Mf+1;
	}
	if(Mf>1000)
	{
		Mf=1000;
	}
	printf("%d\n", (int)Mf);
	return(0);
}    
