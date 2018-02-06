/* ================================================================== *
	Universidade Federal de Sao Carlos - UFSCar, Sorocaba

	Disciplina: Algoritmos e Programação 1
	Prof. Tiago A. Almeida

	Lista 07 - Exercício 02 - Jogo da velha

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


// FRASES PADROES	
#define FRASE_CASA_OCUPADA	"casa ocupada, jogue novamente\n"
#define FRASE_X_VENCEDOR	"Jogador X venceu.\n"
#define FRASE_O_VENCEDOR	"Jogador O venceu.\n"
#define FRASE_VELHA			"Deu velha.\n"


int main() {


	char jogo[3][3];
	int i, j, conf=0, conf2=0, conf3=0, entrou, entrouX, entrouO;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			jogo[i][j]='-';
		}
	}
	do
	{
		scanf("%d %d", &i, &j);
		while(jogo[i][j]=='X'||jogo[i][j]=='O')
		{
			printf(FRASE_CASA_OCUPADA);
			scanf("%d %d", &i, &j);
		}
		if(conf%2==0)
		{
			jogo[i][j]='X';
			conf++;
		}
		else
		{
			jogo[i][j]='O';
			conf++;
		}
		for(i=0;i<3;i++)
		{
			for(j=0;j<3;j++)
			{
				if(j<2)
				{
					printf("%c|", jogo[i][j]);
				}
				else
				{
					printf("%c\n", jogo[i][j]);
				}
			}
		}
		if(conf>=5)
		{
			for(i=0;i<3&&conf2==0;i++)
			{
				entrouX=0;
				entrouO=0;
				for(j=0;j<3;j++)
				{
					if(jogo[i][j]=='X')
					{
						entrouX++;
					}
					else if(jogo[i][j]=='O')
					{
						entrouO++;
					}
				}
				if(entrouX==3)
				{
					printf(FRASE_X_VENCEDOR);
					conf2=1;
				}
				else if(entrouO==3)
				{
					printf(FRASE_O_VENCEDOR);
					conf2=1;
				}
			}
			if(conf2)
			{
				conf=9;
			}
			else
			{
				for(j=0;j<3&&conf2==0;j++)
				{
					entrouX=0;
					entrouO=0;
					for(i=0;i<3;i++)
					{
						if(jogo[i][j]=='X')
						{
							entrouX++;
						}
						else if(jogo[i][j]=='O')
						{
							entrouO++;
						}
					}
					if(entrouX==3)
					{
						printf(FRASE_X_VENCEDOR);
						conf2=1;
					}
					else if(entrouO==3)
					{
						printf(FRASE_O_VENCEDOR);
						conf2=1;
					}
				}
				if(conf2)
				{
					conf=9;
				}
				else
				{
					entrouX=0;
					entrouO=0;
					for(i=0,j=0;i<3&&j<3;i++,j++)
					{
						if(jogo[i][j]=='X')
						{
							entrouX++;
						}
						else if(jogo[i][j]=='O')
						{
							entrouO++;
						}
					}
					if(entrouX==3)
					{
						printf(FRASE_X_VENCEDOR);
						conf=9;
					}
					else if(entrouO==3)
					{
						printf(FRASE_O_VENCEDOR);
						conf=9;
					}
					else
					{
						entrouX=0;
						entrouO=0;
						for(i=0,j=2;i<3&&j>=0;i++,j--)
						{
							if(jogo[i][j]=='X')
							{
								entrouX++;
							}
							else if(jogo[i][j]=='O')
							{
								entrouO++;
							}
						}
						if(entrouX==3)
						{
							printf(FRASE_X_VENCEDOR);
							conf=9;
						}
						else if(entrouO==3)
						{
							printf(FRASE_O_VENCEDOR);
							conf=9;
						}
						else if(conf==9)
						{
							conf3=1;
						}
					}
				}
			}
			if(conf3==1)
			{
				printf(FRASE_VELHA);
			}
		}
	}
	while(conf!=9);


	return (0);
}
