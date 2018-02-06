/* ==========================================================================
 * Universidade Federal de São Carlos - Campus Sorocaba
 * Disciplina: Estruturas de Dados 2
 * Prof. Tiago A. de Almeida
 *
 * Trabalho 03A - Hashing com reespalhamento linear
 *
 * RA: 726563
 * Aluno: Lucca La Fonte Albuquerque Carvalho
 * ========================================================================== */

 /* Bibliotecas */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

/* Tamanho dos campos dos registros */
#define TAM_PRIMARY_KEY 11
#define TAM_NOME 51
#define TAM_DESENVOLVEDORA 51
#define TAM_DATA 11
#define TAM_CLASSIFICACAO 3
#define TAM_PRECO 8
#define TAM_DESCONTO 4
#define TAM_CATEGORIA 51

#define TAM_REGISTRO 192
#define MAX_REGISTROS 1000
#define TAM_ARQUIVO (MAX_REGISTROS * TAM_REGISTRO + 1)


#define POS_OCUPADA 	"[%d] Ocupado: %s\n"
#define POS_LIVRE 		"[%d] Livre\n"
#define POS_REMOVIDA 	"[%d] Removido\n"

/* Estado das posições da tabela hash */
#define LIVRE       0
#define OCUPADO     1
#define REMOVIDO    2

/* Saídas do usuário */
#define OPCAO_INVALIDA "Opcao invalida!\n"
#define MEMORIA_INSUFICIENTE "Memoria insuficiente!\n"
#define REGISTRO_N_ENCONTRADO "Registro(s) nao encontrado!\n"
#define CAMPO_INVALIDO "Campo invalido! Informe novamente.\n"
#define ERRO_PK_REPETIDA "ERRO: Ja existe um registro com a chave primaria: %s.\n\n"
#define ARQUIVO_VAZIO "Arquivo vazio!"
#define INICIO_BUSCA 							 "********************************BUSCAR********************************\n"
#define INICIO_LISTAGEM						  "********************************LISTAR********************************\n"
#define INICIO_ALTERACAO 						"********************************ALTERAR*******************************\n"
#define INICIO_ARQUIVO					    "********************************ARQUIVO*******************************\n"
#define INICIO_EXCLUSAO 			 			"**********************EXCLUIR*********************\n"

#define SUCESSO  				 "OPERACAO REALIZADA COM SUCESSO!\n"
#define FALHA 					 "FALHA AO REALIZAR OPERACAO!\n"
#define ERRO_TABELA_CHEIA 		"ERRO: Tabela Hash esta cheia!\n\n"
#define REGISTRO_INSERIDO 		"Registro %s inserido com sucesso. Numero de colisoes: %d.\n\n"


/* Registro do jogo */
typedef struct {
	char pk[TAM_PRIMARY_KEY];
	char nome[TAM_NOME];
	char desenvolvedora[TAM_DESENVOLVEDORA];
	char data[TAM_DATA];	/* DD/MM/AAAA */
	char classificacao[TAM_CLASSIFICACAO];
	char preco[TAM_PRECO];
	char desconto[TAM_DESCONTO];
	char categoria[TAM_CATEGORIA];
} Jogo;

/* Registro da Tabela Hash
 * Contém o estado da posição, a chave primária e o RRN do respectivo registro */
typedef struct {
	int estado;
	char pk[TAM_PRIMARY_KEY];
	int rrn;
} Chave;

/* Estrutura da Tabela Hash */
typedef struct {
    int tam;
    Chave *v;
  } Hashtable;

  /* Variáveis globais */
char ARQUIVO[TAM_ARQUIVO];
int nregistros;




/* ==========================================================================
 * ========================= PROTÓTIPOS DAS FUNÇÕES =========================
 * ========================================================================== */


/* Recebe do usuário uma string simulando o arquivo completo. */
void carregar_arquivo();

/* Exibe o jogo */
int exibir_registro(int rrn);

/*Função de Hash*/
short hash(const char* chave, int tam);


/*Auxiliar para a função de hash*/
short f(char x);

/*Retorna o primeiro número primo >= a*/
int  prox_primo(int a);

/*Funções do Menu*/
void carregar_tabela(Hashtable* tabela);
void cadastrar(Hashtable* tabela);
int  alterar(Hashtable tabela);
void buscar(Hashtable tabela);
int  remover(Hashtable* tabela);
void liberar_tabela(Hashtable* tabela);


/* <<< DECLARE AQUI OS PROTOTIPOS >>> */
int recuperar_rrn(const char* chave, Hashtable tabela, short *index);
void ler_entrada(char* registro, Jogo *novo);
void imprimir_tabela(Hashtable tabela);
void criar_tabela(Hashtable *tabela, int tam);
Jogo recuperar_registro(int rrn);

/* ==========================================================================
 * ============================ FUNÇÃO PRINCIPAL ============================
 * =============================== NÃO ALTERAR ============================== */
int main() 
{    
	/* Arquivo */
	int carregarArquivo = 0;
	scanf("%d\n", &carregarArquivo); // 1 (sim) | 0 (nao)
	if (carregarArquivo) 
		carregar_arquivo();

	/* Tabela Hash */
	int tam;
	scanf("%d", &tam);
	tam = prox_primo(tam);

	Hashtable tabela;
	criar_tabela(&tabela, tam);
	if (carregarArquivo) 
		carregar_tabela(&tabela);

	/* Execução do programa */
	int opcao = 0;
	while(opcao != 6) {
			scanf("%d%*c", &opcao);
			switch(opcao) 
			{
				case 1:
					cadastrar(&tabela);
					break;
				case 2:
					printf(INICIO_ALTERACAO);
					if(alterar(tabela))
						printf(SUCESSO);
					else
						printf(FALHA);
					break;
				case 3:
					printf(INICIO_BUSCA);
					buscar(tabela);
					break;
				case 4:
					printf(INICIO_EXCLUSAO);
					if(	remover(&tabela))
						printf(SUCESSO);
					else
						printf(FALHA);
					break;
				case 5:
					printf(INICIO_LISTAGEM);
					imprimir_tabela(tabela);
					break;
				case 6:
					liberar_tabela(&tabela);
					break;
				case 10:
					printf(INICIO_ARQUIVO);
					printf("%s\n", (*ARQUIVO!='\0') ? ARQUIVO : ARQUIVO_VAZIO);
					break;
				default:
					printf(OPCAO_INVALIDA);
					break;
			}
	}
	return 0;
}

/* <<< IMPLEMENTE AQUI AS FUNCOES >>> */

/* Recebe do usuário uma string simulando o arquivo completo. */
void carregar_arquivo() {
	scanf("%[^\n]\n", ARQUIVO);
}

/*Auxiliar para a função de hash*/
short f(char x)
{
	return (x < 59) ? x - 48 : x - 54; 
}

/* Exibe o jogo */
int exibir_registro(int rrn)
{
	if(rrn<0)
		return 0;
	float preco;
	int desconto;
	Jogo j = recuperar_registro(rrn);
  char *cat, categorias[TAM_CATEGORIA];
	printf("%s\n", j.pk);
	printf("%s\n", j.nome);
	printf("%s\n", j.desenvolvedora);
	printf("%s\n", j.data);
	printf("%s\n", j.classificacao);
	sscanf(j.desconto,"%d",&desconto);
	sscanf(j.preco,"%f",&preco);
	preco = preco *  (100-desconto);
	preco = ((int) preco)/ (float) 100 ;
	printf("%07.2f\n",  preco);
	strncpy(categorias, j.categoria, strlen(j.categoria));
	categorias[strlen(j.categoria)] = '\0';
  for (cat = strtok (categorias, "|"); cat != NULL; cat = strtok (NULL, "|"))
    printf("%s ", cat);
	printf("\n");
	return 1;
}

/*Função de Hash*/
short hash(const char* chave, int tam){
	short h, i;

	for(i=1, h=0; i<=8; i++)
		h = h + i*f(chave[i-1]);
	return(h%((short) tam));
}

int recuperar_rrn(const char* chave, Hashtable tabela, short *index){
	short h;
	int i;

	h = hash(chave, tabela.tam);
	if(tabela.v[h].estado==OCUPADO && strcmp(tabela.v[h].pk, chave)==0){
		*index = h;
		return(tabela.v[h].rrn);
	}
	for(i=1; tabela.v[(h+i)%tabela.tam].estado!=LIVRE && (h+i)%tabela.tam!=h; i++){
		if(tabela.v[(h+i)%tabela.tam].estado==OCUPADO && strcmp(tabela.v[(h+i)%tabela.tam].pk, chave)==0){
			*index = (h+i)%tabela.tam;
			return(tabela.v[(h+i)%tabela.tam].rrn);
		}
	}
	return(-1);
}

void cadastrar(Hashtable* tabela){
	char registro[TAM_REGISTRO+1], aux[TAM_NOME], *aux2;
	int i;
	Jogo novo;
	short h;

	strcpy(registro, "AAAAAAAAAA@");
	for(i=0; i<7; i++){
		fgets(aux, TAM_NOME, stdin);//pega a string passada pelo usuario (ate \n)
		strcat(registro, aux);//concatena na string que armazena o registro como um todo
		aux2 = strchr(registro, '\n');//encontra a primeira ocorrencia de \n e troca o mesmo por @
		*aux2 = '@';
	}
	for(aux2=aux2+1; aux2<registro+TAM_REGISTRO; aux2++)
		*aux2 = '#';//preenche os espaços não utilizados com #
	*aux2 = '\0';
	ler_entrada(registro+11, &novo);
	strncpy(registro, novo.pk, 10);
	h = hash(novo.pk, tabela->tam);
	if(tabela->v[h].estado!=OCUPADO){
		strcat(ARQUIVO, registro);
		strcpy(tabela->v[h].pk, novo.pk);
		tabela->v[h].rrn = nregistros;
		tabela->v[h].estado = OCUPADO;
		nregistros++;
		printf(REGISTRO_INSERIDO, novo.pk, 0);
		return;
	}
	if(strcmp(tabela->v[h].pk, novo.pk)==0){
		printf(ERRO_PK_REPETIDA, novo.pk);
		return;
	}
	for(i=1; (h+i)%tabela->tam!=h; i++){
		if(tabela->v[(h+i)%tabela->tam].estado!=OCUPADO){
			strcat(ARQUIVO, registro);
			strcpy(tabela->v[(h+i)%tabela->tam].pk, novo.pk);
			tabela->v[(h+i)%tabela->tam].rrn = nregistros;
			tabela->v[(h+i)%tabela->tam].estado = OCUPADO;
			nregistros++;
			printf(REGISTRO_INSERIDO, novo.pk, i);
			return;
		}
		if(strcmp(tabela->v[(h+i)%tabela->tam].pk, novo.pk)==0){
			printf(ERRO_PK_REPETIDA, novo.pk);
			return;
		}
	}
	printf(ERRO_TABELA_CHEIA);
}

/* Salva os dados da entrada para a struct jogo*/
void ler_entrada(char* registro, Jogo *novo){
	char aux[TAM_REGISTRO+1], *aux2;

	strncpy(aux, registro, TAM_REGISTRO);
	aux[TAM_REGISTRO] = '\0';
	//Preenche o novo registro com os devido dados
	aux2 = strtok(aux, "@");
	strcpy(novo->nome, aux2);
	aux2 = strtok(NULL, "@");
	strcpy(novo->desenvolvedora, aux2);
	aux2 = strtok(NULL, "@");
	strcpy(novo->data, aux2);
	aux2 = strtok(NULL, "@");
	strcpy(novo->classificacao, aux2);
	aux2 = strtok(NULL, "@");
	strcpy(novo->preco, aux2);
	aux2 = strtok(NULL, "@");
	strcpy(novo->desconto, aux2);
	aux2 = strtok(NULL, "@");
	strcpy(novo->categoria, aux2);
	//Constroi a chave primaria
	novo->pk[0] = toupper(novo->nome[0]);
	novo->pk[1] = toupper(novo->nome[1]);
	novo->pk[2] = toupper(novo->desenvolvedora[0]);
	novo->pk[3] = toupper(novo->desenvolvedora[1]);
	novo->pk[4] = novo->data[0];
	novo->pk[5] = novo->data[1];
	novo->pk[6] = novo->data[3];
	novo->pk[7] = novo->data[4];
	novo->pk[8] = novo->classificacao[0];
	novo->pk[9] = novo->classificacao[1];
	novo->pk[10] = '\0';
}

int  alterar(Hashtable tabela){
	int i, rrn, flag=0;
	char desconto[TAM_DESCONTO], pk[TAM_PRIMARY_KEY], c, *aux;
	short index;

	scanf("%s%*c", pk);
	if((rrn=recuperar_rrn(pk, tabela, &index))==-1){//caso o registro nao seja encontrado
		printf(REGISTRO_N_ENCONTRADO);
		return(0);
	}
	do{//loop continua enquanto campo nao é valido
		i = 0;
		while((c=getchar())!='\n'){//pega o campo desconto
			if(i<TAM_DESCONTO)
				desconto[i] = c;
			i++;
		}
		desconto[TAM_DESCONTO-1] = '\0';
		if(i==TAM_DESCONTO-1 && ((desconto[0]=='0' && (desconto[1]>='0' && desconto[1]<='9')
			&& (desconto[2]>='0' && desconto[2]<='9')) || !strcmp(desconto, "100")))//caso o campo seja valido levanta a flag
			flag = 1;
		else//caso contrario imprime que o campo é invalido
			printf(CAMPO_INVALIDO);
	}while(!flag);
	aux = ARQUIVO + rrn*TAM_REGISTRO;
	for(i=0; i<6; i++)
		aux = strchr(aux+1, '@');//vai ate o @ antes do campo de desconto
	aux++;
	/*substitui o campo desconto*/
	aux[0] = desconto[0];
	aux[1] = desconto[1];
	aux[2] = desconto[2];
	return(1);
}

void buscar(Hashtable tabela){
	short index;
	int rrn;
	char pk[TAM_PRIMARY_KEY];

	scanf("%s%*c", pk);
	if((rrn=recuperar_rrn(pk, tabela, &index))==-1)//caso o registro nao seja encontrado
		printf(REGISTRO_N_ENCONTRADO);
	else
		exibir_registro(rrn);
}

int  remover(Hashtable* tabela){
	char pk[TAM_PRIMARY_KEY], *p;
	short index;
	int rrn;

	scanf("%s%*c", pk);
	if((rrn=recuperar_rrn(pk, *tabela, &index))==-1){//caso o registro nao seja encontrado
		printf(REGISTRO_N_ENCONTRADO);
		return(0);
	}
	p = ARQUIVO + rrn*TAM_REGISTRO;//Coloca o apontador na posicao em que sera alterada
	p[0] = '*';
	p[1] = '|';
	tabela->v[index].estado = REMOVIDO;
	return(1);
}

void imprimir_tabela(Hashtable tabela){
	int i;

	for(i=0; i<tabela.tam; i++){
		if(tabela.v[i].estado==OCUPADO)
			printf(POS_OCUPADA, i, tabela.v[i].pk);
		else if(tabela.v[i].estado==LIVRE)
			printf(POS_LIVRE, i);
		else if(tabela.v[i].estado==REMOVIDO)
			printf(POS_REMOVIDA, i);
	}
}

void liberar_tabela(Hashtable* tabela){
	free(tabela->v);
}

int  prox_primo(int a){
	int i, j;

	if(a==2)
		return(a);
	if(a==1 || a%2==0)
		return(prox_primo(a+1));
	for(i=3; i<=sqrt(a); i+=2){
		if(a%i==0)
			return(prox_primo(a+2));
	}
	return(a);
}

void criar_tabela(Hashtable *tabela, int tam){
	int i;

	tabela->tam = tam;
	tabela->v = (Chave *) malloc(tam*sizeof(Chave));
	for(i=0; i<tam; i++)
		tabela->v[i].estado = LIVRE;
}

void carregar_tabela(Hashtable* tabela){
	int i, j;
	Jogo novo;
	short h;

	nregistros = strlen(ARQUIVO) / TAM_REGISTRO;
	for(i=0; i<nregistros; i++){
		novo = recuperar_registro(i);
		h = hash(novo.pk, tabela->tam);
		if(tabela->v[h].estado!=OCUPADO){
			strcpy(tabela->v[h].pk, novo.pk);
			tabela->v[h].rrn = i;
			tabela->v[h].estado = OCUPADO;
		}
		else{
			for(j=1; (h+j)%tabela->tam!=h; j++){
				if(tabela->v[(h+j)%tabela->tam].estado!=OCUPADO){
					strcpy(tabela->v[(h+j)%tabela->tam].pk, novo.pk);
					tabela->v[(h+j)%tabela->tam].rrn = i;
					tabela->v[(h+j)%tabela->tam].estado = OCUPADO;
					break;
				}
			}
		}
	}
}

Jogo recuperar_registro(int rrn){
	Jogo novo;
	char aux[TAM_REGISTRO+1], *aux2;

	strncpy(aux, ARQUIVO+(rrn*TAM_REGISTRO), TAM_REGISTRO);
	aux[TAM_REGISTRO] = '\0';
	//Preenche o novo registro com os devido dados
	aux2 = strtok(aux, "@");
	strcpy(novo.pk, aux2);
	aux2 = strtok(NULL, "@");
	strcpy(novo.nome, aux2);
	aux2 = strtok(NULL, "@");
	strcpy(novo.desenvolvedora, aux2);
	aux2 = strtok(NULL, "@");
	strcpy(novo.data, aux2);
	aux2 = strtok(NULL, "@");
	strcpy(novo.classificacao, aux2);
	aux2 = strtok(NULL, "@");
	strcpy(novo.preco, aux2);
	aux2 = strtok(NULL, "@");
	strcpy(novo.desconto, aux2);
	aux2 = strtok(NULL, "@");
	strcpy(novo.categoria, aux2);
	return(novo);
}