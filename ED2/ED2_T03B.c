/* ==========================================================================
 * Universidade Federal de São Carlos - Campus Sorocaba
 * Disciplina: Estruturas de Dados 2
 * Prof. Tiago A. de Almeida
 *
 * Trabalho 03A - Hashing com encadeamento
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
#define INICIO_EXCLUSAO  "**********************EXCLUIR*********************\n"
#define SUCESSO  				 "OPERACAO REALIZADA COM SUCESSO!\n"
#define FALHA 					 "FALHA AO REALIZAR OPERACAO!\n"
#define REGISTRO_INSERIDO "Registro %s inserido com sucesso.\n\n"



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
 * Contém a chave primária, o RRN do registro atual e o ponteiro para o próximo
 * registro. */
typedef struct chave {
	char pk[TAM_PRIMARY_KEY];
	int rrn;
	struct chave *prox;
} Chave;

/* Estrutura da Tabela Hash */
typedef struct {
  int tam;
  Chave **v;
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
int recuperar_rrn(const char* chave, Hashtable tabela);
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
	scanf("%d%*c", &carregarArquivo); // 1 (sim) | 0 (nao)
	if (carregarArquivo) 
		carregar_arquivo();

	/* Tabela Hash */
	int tam;
	scanf("%d%*c", &tam);
	tam = prox_primo(tam);

	Hashtable tabela;
	criar_tabela(&tabela, tam);
	if (carregarArquivo) 
		carregar_tabela(&tabela);
	


	/* Execução do programa */
	int opcao = 0;
	while(opcao != 6) {
		scanf("%d%*c", &opcao);
		switch(opcao) {

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

int recuperar_rrn(const char* chave, Hashtable tabela){
	short h;
	Chave **aux;

	h = hash(chave, tabela.tam);
	aux = &(tabela.v[h]);
	while(*aux!=NULL && strcmp((*aux)->pk, chave)!=0)
		aux = &((*aux)->prox);
	if(*aux==NULL)
		return(-1);
	return((*aux)->rrn);
}

void cadastrar(Hashtable* tabela){
	char registro[TAM_REGISTRO+1], aux[TAM_NOME], *aux2;
	int i;
	Jogo novo;
	short h;
	Chave **aux3, *new;

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
	aux3 = &(tabela->v[h]);
	while(*aux3!=NULL && strcmp((*aux3)->pk, novo.pk)<0)
		aux3 = &((*aux3)->prox);
	if(*aux3!=NULL && strcmp((*aux3)->pk, novo.pk)==0){
		printf(ERRO_PK_REPETIDA, novo.pk);
		return;
	}
	strcat(ARQUIVO, registro);
	new = (Chave *) malloc(sizeof(Chave));
	strcpy(new->pk, novo.pk);
	new->rrn = nregistros;
	new->prox = *aux3;
	*aux3 = new;
	nregistros++;
	printf(REGISTRO_INSERIDO, novo.pk);
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

	scanf("%s%*c", pk);
	if((rrn=recuperar_rrn(pk, tabela))==-1){//caso o registro nao seja encontrado
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
	int rrn;
	char pk[TAM_PRIMARY_KEY];

	scanf("%s%*c", pk);
	if((rrn=recuperar_rrn(pk, tabela))==-1)//caso o registro nao seja encontrado
		printf(REGISTRO_N_ENCONTRADO);
	else
		exibir_registro(rrn);
}

int  remover(Hashtable* tabela){
	char pk[TAM_PRIMARY_KEY], *p;
	short h;
	Chave **aux, *rm;

	scanf("%s%*c", pk);
	h = hash(pk, tabela->tam);
	aux = &(tabela->v[h]);
	while(*aux!=NULL && strcmp((*aux)->pk, pk)!=0)
		aux = &((*aux)->prox);
	if(*aux==NULL){
		printf(REGISTRO_N_ENCONTRADO);
		return(0);
	}
	p = ARQUIVO + ((*aux)->rrn)*TAM_REGISTRO;//Coloca o apontador na posicao em que sera alterada
	p[0] = '*';
	p[1] = '|';
	rm = *aux;
	*aux = (*aux)->prox;
	free(rm);
	return(1);
}

void imprimir_tabela(Hashtable tabela){
	int i;
	Chave *aux;

	for(i=0; i<tabela.tam; i++){
		aux = tabela.v[i];
		printf("[%d]", i);
		while(aux!=NULL){
			printf(" %s", aux->pk);
			aux = aux->prox;
		}
		printf("\n");
	}
}

void liberar_tabela(Hashtable* tabela){
	int i;
	Chave *aux;

	for(i=0; i<tabela->tam; i++){
		do{
			aux = tabela->v[i];
			if(aux!=NULL){
				tabela->v[i] = aux->prox;
				free(aux);
			}
		}while(aux!=NULL);
	}
	free(tabela->v);
}

int  prox_primo(int a){
	int i;

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
	tabela->v = (Chave **) malloc(tam*sizeof(Chave *));
	for(i=0; i<tam; i++)
		tabela->v[i] = NULL;
}

void carregar_tabela(Hashtable* tabela){
	int i;
	Jogo novo;
	short h;
	Chave **aux, *new;

	nregistros = strlen(ARQUIVO) / TAM_REGISTRO;
	for(i=0; i<nregistros; i++){
		novo = recuperar_registro(i);
		h = hash(novo.pk, tabela->tam);
		aux = &(tabela->v[h]);
		while(*aux!=NULL && strcmp((*aux)->pk, novo.pk)<0)
			aux = &((*aux)->prox);
		new = (Chave *) malloc(sizeof(Chave));
		strcpy(new->pk, novo.pk);
		new->rrn = i;
		new->prox = *aux;
		*aux = new;
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