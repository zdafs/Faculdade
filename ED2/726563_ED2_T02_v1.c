/* ==========================================================================
 * Universidade Federal de São Carlos - Campus Sorocaba
 * Disciplina: Estruturas de Dados 2
 * Prof. Tiago A. de Almeida
 *
 * Trabalho 02 - Árvore B
 *
 * RA: 726563
 * Aluno: Lucca La Fonte Albuquerque Carvalho
 * ========================================================================== */

/* Bibliotecas */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/* Tamanho dos campos dos registros */
#define TAM_PRIMARY_KEY 	11
#define TAM_NOME 			51
#define TAM_DESENVOLVEDORA 	51
#define TAM_DATA 			11
#define TAM_CLASSIFICACAO 	3
#define TAM_PRECO 			8
#define TAM_DESCONTO 		4
#define TAM_CATEGORIA 		51
#define TAM_STRING_INDICE 	(TAM_DESENVOLVEDORA + TAM_NOME)


#define TAM_REGISTRO 		192
#define MAX_REGISTROS 		1000
#define MAX_ORDEM 			150
#define TAM_ARQUIVO 		(MAX_REGISTROS * TAM_REGISTRO + 1)


/* Saídas do usuário */
#define OPCAO_INVALIDA 			 "Opcao invalida!\n"
#define MEMORIA_INSUFICIENTE	 "Memoria insuficiente!\n"
#define REGISTRO_N_ENCONTRADO 	 "Registro(s) nao encontrado!\n"
#define CAMPO_INVALIDO 			 "Campo invalido! Informe novamente.\n"
#define ERRO_PK_REPETIDA 		 "ERRO: Ja existe um registro com a chave primaria: %s.\n"
#define ARQUIVO_VAZIO 			 "Arquivo vazio!"
#define INICIO_BUSCA			 "********************************BUSCAR********************************\n"
#define INICIO_LISTAGEM 		 "********************************LISTAR********************************\n"
#define INICIO_ALTERACAO		 "********************************ALTERAR*******************************\n"
#define INICIO_ARQUIVO			 "********************************ARQUIVO*******************************\n"
#define INICIO_INDICE_PRIMARIO	 "***************************INDICE PRIMÁRIO****************************\n"
#define INICIO_INDICE_SECUNDARIO "***************************INDICE SECUNDÁRIO**************************\n"
#define SUCESSO  				 "OPERACAO REALIZADA COM SUCESSO!\n"
#define FALHA 					 "FALHA AO REALIZAR OPERACAO!\n"
#define NOS_PERCORRIDOS_IP 		 "Busca por %s. Nos percorridos:\n"
#define NOS_PERCORRIDOS_IS 		 "Busca por %s.\nNos percorridos:\n"


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


/*Estrutura da chave de um nó do Índice Primário*/
typedef struct Chaveip
{
	char pk[TAM_PRIMARY_KEY];
	int rrn;
} Chave_ip;

/*Estrutura da chave de um  do Índice Secundário*/
typedef struct Chaveis
{
	char string[TAM_STRING_INDICE];
	char pk[TAM_PRIMARY_KEY];
} Chave_is;

/* Estrutura das Árvores-B */
typedef struct nodeip
{
	int num_chaves;		/* numero de chaves armazenadas*/
	Chave_ip *chave;	/* vetor das chaves e rrns [m-1]*/
	int *desc;			/* ponteiros para os descendentes, *desc[m]*/
	char folha;			/* flag folha da arvore*/
} node_Btree_ip;

typedef struct nodeis
{
	int num_chaves;		/* numero de chaves armazenadas*/
	Chave_is *chave;	/* vetor das chaves e rrns [m-1]*/
	int *desc;			/* ponteiros para os descendentes, *desc[m]*/
	char folha;			/* flag folha da arvore*/
} node_Btree_is;

typedef struct {
	int raiz;
} Indice;

/* Variáveis globais */

char ARQUIVO[MAX_REGISTROS * TAM_REGISTRO];
char ARQUIVO_IP[2000*sizeof(Chave_ip) + 40];
char ARQUIVO_IS[2000*sizeof(Chave_is) + 40];
/*Ordem das árvores*/
int ordem_ip;
int ordem_is;
int nregistros;
int nregistrosip; /*Número de nós presentes no ARQUIVO_IP*/
int nregistrosis; /*Número de nós presentes no ARQUIVO_IS*/
/*Quantidade de bytes que ocupa cada nó da árvore nos arquivos de índice:*/
int tamanho_registro_ip;
int tamanho_registro_is;
/* ==========================================================================
 * ========================= PROTÓTIPOS DAS FUNÇÕES =========================
 * ========================================================================== */

 /********************FUNÇÕES DO MENU*********************/
 void cadastrar(Indice* iprimary, Indice* idev);

 int alterar(Indice iprimary);

 void buscar(Indice iprimary,Indice idev);

 void listar(Indice iprimary,Indice idev);

 /*******************************************************/

 /* Recebe do usuário uma string simulando o arquivo completo e retorna o número
  * de registros. */
 int carregar_arquivo();

/* (Re)faz o Cria iprimary*/
void criar_iprimary(Indice *iprimary);

/* (Re)faz o índice de jogos  */
void criar_idev(Indice *idev) ;

/*Escreve um nó da árvore no arquivo de índice,
* O terceiro parametro serve para informar qual indice se trata */
void write_btree(void *salvar, int rrn, char ip);

/*Lê um nó do arquivo de índice e retorna na estrutura*/
void *read_btree(int rrn, char ip);

/* Aloca um nó de árvore para ser utilizado em memória primária, o primeiro parametro serve para informar que árvore se trata
* É conveniente que essa função também inicialize os campos necessários com valores nulos*/
void *criar_no(char ip);

/*Libera todos os campos dinâmicos do nó, inclusive ele mesmo*/
void libera_no(void *node, char ip);

/*
*	Caro aluno,
*	caso não queira trabalhar com void*, é permitido dividir as funções que utilizam
* em duas, sendo uma para cada índice...
* Um exemplo, a write_btree e read_btree ficariam como:
*
*	void write_btree_ip(node_Btree_ip *salvar, int rrn),  node_Btree_ip *read_btree_ip(int rrn),
*	void write_btree_is(node_Btree_is *salvar, int rrn) e node_Btree_is *read_btree_is(int rrn).
*/



/* Atualiza os dois índices com o novo registro inserido */
void inserir_registro_indices(Indice *iprimary, Indice *idev, Jogo j);

/* Exibe o jogo */
int exibir_registro(int rrn);

/*Faz split do nó. Recebe o nó em que será feito o split, a chave a ser inserida e o descendente a direita dessa chave.
Devolve o nó criado, a chave que será promovida e o descendente a direita desse nó*/
void *split(void *no, void *chave, int *desc, char ip);

//Por comentários
int insereIp(node_Btree_ip *no, Chave_ip *chave, int *desc, int rrn);

//Por comentáros
int insereIs(node_Btree_is *no, Chave_is *chave, int *desc, int rrn);

//Busca uma pk e retorna o rrn. Se n for encontrada retorna -1. Caso caminho seja 1 é impresso o caminho feito
int buscaIp(node_Btree_ip *no, char *pk, char caminho);


char *buscaIs(node_Btree_is *no, char *string, char caminho);

/* Salva os dados da entrada para a struct jogo*/
void ler_entrada(char* registro, Jogo *novo);

/* Recupera do arquivo o registro com o rrn informado e retorna os dados na
 * struct Jogo */
Jogo recuperar_registro(int rrn);

int main()
{
	char *p;
	int carregarArquivo = 0; nregistros = 0, nregistrosip = 0, nregistrosis = 0;
	scanf("%d\n", &carregarArquivo); /* 1 (sim) | 0 (nao) */
	if (carregarArquivo)
		nregistros = carregar_arquivo();

	scanf("%d %d%*c", &ordem_ip, &ordem_is);

	tamanho_registro_ip = 3 + 14*(ordem_ip-1) + 1 + 3*ordem_ip; /* = Deixarei esse cálculo pesado para você aluno... */
	tamanho_registro_is = 3 + 111*(ordem_is-1) + 1 + 3*ordem_is; /* = E esse também. */

	/* Índice primário */
	Indice iprimary ;
	criar_iprimary(&iprimary);

	/* Índice secundário de nomes dos Jogos */
	Indice idev;
	criar_idev(&idev);

	/* Execução do programa */
	int opcao = 0;
	while(1)
	{
		scanf("%d%*c", &opcao);
		switch(opcao) {
		case 1: /* Cadastrar um novo jogo */
			cadastrar(&iprimary, &idev);
			break;
		case 2: /* Alterar o desconto de um Jogo */
			printf(INICIO_ALTERACAO);
			if (alterar(iprimary))
				printf(SUCESSO);
			else
				printf(FALHA);
			break;
		case 3: /* Buscar um jogo */
			printf(INICIO_BUSCA);
			buscar(iprimary, idev);
			break;
		case 4: /* Listar todos os Jogos */
			printf(INICIO_LISTAGEM);
			listar(iprimary, idev);
			break;
		case 5: /* Imprimir o arquivo de dados */
			printf(INICIO_ARQUIVO);
			printf("%s\n", (*ARQUIVO!='\0') ? ARQUIVO : ARQUIVO_VAZIO);
			break;
		case 6: /* Imprime o Arquivo de Índice Primário*/
			printf(INICIO_INDICE_PRIMARIO);
			if(!*ARQUIVO_IP)
				puts(ARQUIVO_VAZIO);
			else
				for(p = ARQUIVO_IP; *p!='\0'; p+=tamanho_registro_ip)
				{
					fwrite( p , 1 ,tamanho_registro_ip,stdout);
					puts("");
				}
			break;
		case 7: /* Imprime o Arquivo de Índice Secundário*/
			printf(INICIO_INDICE_SECUNDARIO);
			if(!*ARQUIVO_IS)
				puts(ARQUIVO_VAZIO);
			else
				for(p = ARQUIVO_IS; *p!='\0'; p+=tamanho_registro_is)
				{
					fwrite( p , 1 ,tamanho_registro_is,stdout);
					puts("");

				}
			break;
		case 8: /*Libera toda memória alocada dinâmicamente (se ainda houver) e encerra*/
			return 0;
		default: /* Exibe mensagem de erro */
			printf(OPCAO_INVALIDA);
			break;
		}
	}
	return -1;
}

/* ==========================================================================
 * ================================= FUNÇÕES ================================
 * ========================================================================== */

/* Recebe do usuário uma string simulando o arquivo completo e retorna o número
 * de registros. */
int carregar_arquivo()
{
	scanf("%[^\n]\n", ARQUIVO);
	return strlen(ARQUIVO) / TAM_REGISTRO;
}

/* Recupera do arquivo o registro com o rrn informado e retorna os dados na
 * struct Jogo */
Jogo recuperar_registro(int rrn){
	Jogo novo;
	char aux[TAM_REGISTRO+1], *aux2;

	strncpy(aux, ARQUIVO+(rrn*TAM_REGISTRO), TAM_ARQUIVO);
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

  	for (cat = strtok (categorias, "|"); cat != NULL; cat = strtok (NULL, "|"))
    	printf("%s ", cat);
	printf("\n");

	return 1;
}

/*Escreve um nó da árvore no arquivo de índice,
* O terceiro parametro serve para informar qual indice se trata */
void write_btree(void *salvar, int rrn, char ip){
	char *p;
	//char aux[3 + 111*MAX_ORDEM + 1 + 3*MAX_ORDEM];
	int i, j, k;

	if(ip=='p'){
		char *aux = (char *) malloc(tamanho_registro_ip+1);
		//node_Btree_ip *save = (node_Btree_ip *) salvar;
		p = ARQUIVO_IP + rrn*tamanho_registro_ip;
		sprintf(aux, "%03d", ((node_Btree_ip *) salvar)->num_chaves);
		for(i=0, j=3; i<((node_Btree_ip *) salvar)->num_chaves; i++, j=j+14){
			strcpy(aux+j, ((node_Btree_ip *) salvar)->chave[i].pk);
			sprintf(aux+j+10, "%04d", ((node_Btree_ip *) salvar)->chave[i].rrn);
		}
		for(; i<ordem_ip-1; i++){
			for(j=0; j<14; j++)
				*(aux+3+(i*14)+j) = '#';
		}
		*(aux+3+(ordem_ip-1)*14) = ((node_Btree_ip *) salvar)->folha;
		for(i=0, j=3+(ordem_ip-1)*14+1; i<ordem_ip; i++, j=j+3){
			if(((node_Btree_ip *) salvar)->desc[i]==-1)
				strcpy(aux+j, "***");
			else
				sprintf(aux+j, "%03d", ((node_Btree_ip *) salvar)->desc[i]);
		}
		strncpy(p, aux, tamanho_registro_ip);
		free(aux);
	}
	else{
		char *aux = (char *) malloc(tamanho_registro_is+1);
		aux[0] = '\0';
		//node_Btree_is *save = (node_Btree_is *) salvar;
		p = ARQUIVO_IS + rrn*tamanho_registro_is;
		sprintf(aux, "%03d", ((node_Btree_is *) salvar)->num_chaves);
		for(i=0, j=3; i<((node_Btree_is *) salvar)->num_chaves; i++, j=j+111){
			strcpy(aux+j, ((node_Btree_is *) salvar)->chave[i].pk);
			strcpy(aux+j+10, ((node_Btree_is *) salvar)->chave[i].string);
			for(k=strlen(((node_Btree_is *) salvar)->chave[i].string); k<TAM_STRING_INDICE-1; k++)
				*(aux+j+10+k) = '#';
		}
		for(; i<ordem_is-1; i++){
			for(j=0; j<111; j++)
				*(aux+3+(i*111)+j) = '#';
		}
		*(aux+3+(ordem_is-1)*111) = ((node_Btree_is *) salvar)->folha;
		for(i=0, j=3+(ordem_is-1)*111+1; i<ordem_is; i++, j=j+3){
			if(((node_Btree_is *) salvar)->desc[i]==-1)
				strcpy(aux+j, "***");
			else
				sprintf(aux+j, "%03d", ((node_Btree_is *) salvar)->desc[i]);
		}
		//printf("%d:%d\n", tamanho_registro_is, strlen(aux));
		strncpy(p, aux, tamanho_registro_is);
		free(aux);
	}
}

/* Aloca um nó de árvore para ser utilizado em memória primária, o primeiro parametro serve para informar que árvore se trata
* É conveniente que essa função também inicialize os campos necessários com valores nulos*/
void *criar_no(char ip){
	int i;

	if(ip=='p'){
		node_Btree_ip *no = (node_Btree_ip *) malloc(sizeof(node_Btree_ip));
		no->chave = (Chave_ip *) malloc((ordem_ip-1)*sizeof(Chave_ip));
		no->desc = (int *) malloc(ordem_ip*sizeof(int));
		for(i=0; i<ordem_ip; i++)
			no->desc[i] = -1;
		return((void *) no);
	}
	else{
		node_Btree_is *no = (node_Btree_is *) malloc(sizeof(node_Btree_is));
		no->chave = (Chave_is *) malloc((ordem_is-1)*sizeof(Chave_is));
		no->desc = (int *) malloc(ordem_is*sizeof(int));
		for(i=0; i<ordem_is; i++)
			no->desc[i] = -1;
		return((void *) no);
	}
}

/*Lê um nó do arquivo de índice e retorna na estrutura*/
void *read_btree(int rrn, char ip){
	void *no;
	int i, j;

	if(rrn==-1)
		return(NULL);
	no = criar_no(ip);
	if(ip=='p'){
		char *p = ARQUIVO_IP + rrn*tamanho_registro_ip;
		sscanf(p, "%03d", (&((node_Btree_ip *) no)->num_chaves));
		p = p + 3;
		for(i=0; i<((node_Btree_ip *) no)->num_chaves; i++){
			strncpy(((node_Btree_ip *) no)->chave[i].pk, p, 10);
			p = p + 10;
			sscanf(p, "%04d", (&((node_Btree_ip *) no)->chave[i].rrn));
			p = p + 4;
		}
		p = p + 14*(ordem_ip-1-i);
		((node_Btree_ip *) no)->folha = *p;
		p++;
		for(i=0; i<ordem_ip; i++){
			if(*p=='*')
				((node_Btree_ip *) no)->desc[i] = -1;
			else
				sscanf(p, "%03d", (&((node_Btree_ip *) no)->desc[i]));
			p = p + 3;	
		}
	}
	else{
		char *p = ARQUIVO_IS + rrn*tamanho_registro_is;
		sscanf(p, "%03d", (&((node_Btree_is *) no)->num_chaves));
		p = p + 3;
		for(i=0, j=0; i<((node_Btree_is *) no)->num_chaves; i++, j=0){
			strncpy(((node_Btree_is *) no)->chave[i].pk, p, 10);
			p = p + 10;
			while(j<TAM_STRING_INDICE-1 && p[j]!='#'){
				((node_Btree_is *) no)->chave[i].string[j] = p[j];
				j++;
			}
			((node_Btree_is *) no)->chave[i].string[j] = '\0';
			p = p + TAM_STRING_INDICE-1;
		}
		p = p + 111*(ordem_is-1-i);
		((node_Btree_is *) no)->folha = *p;
		p++;
		for(i=0; i<ordem_is; i++){
			if(*p=='*')
				((node_Btree_is *) no)->desc[i] = -1;
			else
				sscanf(p, "%03d", (&((node_Btree_is *) no)->desc[i]));
			p = p + 3;	
		}
	}
	return(no);
}

/*Faz split do nó. Recebe o nó em que será feito o split, a chave a ser inserida e o descendente a direita dessa chave.
Devolve o nó criado, a chave que será promovida e o descendente a direita desse nó*/
void *split(void *no, void *chave, int *desc, char ip){
	int i, j, inseriu=0;

	if(ip=='p'){
		node_Btree_ip *resp = (node_Btree_ip *) criar_no(ip);
		resp->folha = ((node_Btree_ip *) no)->folha;
		resp->num_chaves = (ordem_ip-1)/2;
		for(i=resp->num_chaves-1, j=((node_Btree_ip *)no)->num_chaves-1; i>=0; i--){
			if(!inseriu && strcmp(((Chave_ip *) chave)->pk, ((node_Btree_ip *) no)->chave[j].pk)>0){
				strcpy(resp->chave[i].pk, ((Chave_ip *) chave)->pk);
				resp->chave[i].rrn = ((Chave_ip *) chave)->rrn;
				resp->desc[i+1] = *desc;
				inseriu = 1;
			}
			else{
				strcpy(resp->chave[i].pk, ((node_Btree_ip *) no)->chave[j].pk);
				resp->chave[i].rrn = ((node_Btree_ip *) no)->chave[j].rrn;
				resp->desc[i+1] = ((node_Btree_ip *) no)->desc[j+1];
				j--;
			}
		}
		if(!inseriu){
			while(j>=0 && strcmp(((Chave_ip *) chave)->pk, ((node_Btree_ip *) no)->chave[j].pk)<0){
				strcpy(((node_Btree_ip *) no)->chave[j+1].pk, ((node_Btree_ip *) no)->chave[j].pk);
				((node_Btree_ip *) no)->chave[j+1].rrn = ((node_Btree_ip *) no)->chave[j].rrn;
				((node_Btree_ip *) no)->desc[j+2] = ((node_Btree_ip *) no)->desc[j+1];
				j--;
			}
			strcpy(((node_Btree_ip *) no)->chave[j+1].pk,  ((Chave_ip *) chave)->pk);
			((node_Btree_ip *) no)->chave[j+1].rrn = ((Chave_ip *) chave)->rrn;
			((node_Btree_ip *) no)->desc[j+2] = *desc;
		}
		strcpy(((Chave_ip *) chave)->pk, ((node_Btree_ip *) no)->chave[(ordem_ip/2)].pk);
		((Chave_ip *) chave)->rrn = ((node_Btree_ip *) no)->chave[(ordem_ip/2)].rrn;
		resp->desc[0] = ((node_Btree_ip *) no)->desc[(ordem_ip/2)+1];
		((node_Btree_ip *) no)->desc[(ordem_ip/2)+1] = -1;
		((node_Btree_ip *) no)->num_chaves = ordem_ip/2;
		*desc = nregistrosip;
		return((void *) resp);
	}
	else{
		node_Btree_is *resp = (node_Btree_is *) criar_no(ip);
		resp->folha = ((node_Btree_is *) no)->folha;
		resp->num_chaves = (ordem_is-1)/2;
		for(i=resp->num_chaves-1, j=((node_Btree_is *)no)->num_chaves-1; i>=0; i--){
			if(!inseriu && strcmp(((Chave_is *) chave)->string, ((node_Btree_is *) no)->chave[j].string)>0){
				strcpy(resp->chave[i].pk, ((Chave_is *) chave)->pk);
				strcpy(resp->chave[i].string, ((Chave_is *) chave)->string);
				resp->desc[i+1] = *desc;
				inseriu = 1;
			}
			else{
				strcpy(resp->chave[i].pk, ((node_Btree_is *) no)->chave[j].pk);
				strcpy(resp->chave[i].string, ((node_Btree_is *) no)->chave[j].string);
				resp->desc[i+1] = ((node_Btree_is *) no)->desc[j+1];
				j--;
			}
		}
		if(!inseriu){
			while(j>=0 && strcmp(((Chave_is *) chave)->string, ((node_Btree_is *) no)->chave[j].string)<0){
				strcpy(((node_Btree_is *) no)->chave[j+1].pk, ((node_Btree_is *) no)->chave[j].pk);
				strcpy(((node_Btree_is *) no)->chave[j+1].string, ((node_Btree_is *) no)->chave[j].string);
				((node_Btree_is *) no)->desc[j+2] = ((node_Btree_is *) no)->desc[j+1];
				j--;
			}
			strcpy(((node_Btree_is *) no)->chave[j+1].pk,  ((Chave_is *) chave)->pk);
			strcpy(((node_Btree_is *) no)->chave[j+1].string, ((Chave_is *) chave)->string);
			((node_Btree_is *) no)->desc[j+2] = *desc;
		}
		strcpy(((Chave_is *) chave)->pk, ((node_Btree_is *) no)->chave[(ordem_is/2)].pk);
		strcpy(((Chave_is *) chave)->string, ((node_Btree_is *) no)->chave[(ordem_is/2)].string);
		resp->desc[0] = ((node_Btree_is *) no)->desc[(ordem_is/2)+1];
		((node_Btree_is *) no)->desc[(ordem_is/2)+1] = -1;
		((node_Btree_is *) no)->num_chaves = ordem_is/2;
		*desc = nregistrosis;
		return((void *) resp);
	}
}


//Nao equecer de liberar os nós
int insereIp(node_Btree_ip *no, Chave_ip *chave, int *desc, int rrn){
	int i=0, j;

	if(no==NULL)
		return(1);
	while(i<no->num_chaves && strcmp(chave->pk, no->chave[i].pk)>0)
		i++;
	if(no->folha=='F'){
		if(no->num_chaves<ordem_ip-1){
			j = no->num_chaves;
			while(j>i){
				strcpy(no->chave[j].pk, no->chave[j-1].pk);
				no->chave[j].rrn = no->chave[j-1].rrn;
				no->desc[j+1] = no->desc[j];
				j--;
			}
			strcpy(no->chave[j].pk, chave->pk);
			no->chave[j].rrn = chave->rrn;
			no->desc[j+1] = *desc;
			no->num_chaves++;
			write_btree((void *) no, rrn, 'p');
			libera_no((void *) no, 'p');
			return(0);
		}
		else{
			node_Btree_ip *new = (node_Btree_ip *) split(no, chave, desc, 'p');
			write_btree((void *) no, rrn, 'p');
			write_btree((void *) new, nregistrosip, 'p');
			nregistrosip++;
			libera_no((void *) new, 'p');
			libera_no((void *) no, 'p');
			return(1);
		}
	}
	if(insereIp((node_Btree_ip *) read_btree(no->desc[i], 'p'), chave, desc, no->desc[i])){
		if(no->num_chaves<ordem_ip-1){
			j = no->num_chaves;
			while(j>i){
				strcpy(no->chave[j].pk, no->chave[j-1].pk);
				no->chave[j].rrn = no->chave[j-1].rrn;
				no->desc[j+1] = no->desc[j];
				j--;
			}
			strcpy(no->chave[j].pk, chave->pk);
			no->chave[j].rrn = chave->rrn;
			no->desc[j+1] = *desc;
			no->num_chaves++;
			write_btree((void *) no, rrn, 'p');
			libera_no((void *) no, 'p');
			return(0);
		}
		else{
			node_Btree_ip *new = (node_Btree_ip *) split(no, chave, desc, 'p');
			write_btree((void *) no, rrn, 'p');
			write_btree((void *) new, nregistrosip, 'p');
			nregistrosip++;
			libera_no((void *) new, 'p');
			libera_no((void *) no, 'p');
			return(1);
		}	
	}
	return(0);
}

//Nao esquecer de liberar nos
int insereIs(node_Btree_is *no, Chave_is *chave, int *desc, int rrn){
	int i=0, j;

	if(no==NULL)
		return(1);
	while(i<no->num_chaves && strcmp(chave->string, no->chave[i].string)>0)
		i++;
	if(no->folha=='F'){
		if(no->num_chaves<ordem_is-1){
			j = no->num_chaves;
			while(j>i){
				strcpy(no->chave[j].pk, no->chave[j-1].pk);
				strcpy(no->chave[j].string, no->chave[j-1].string);
				no->desc[j+1] = no->desc[j];
				j--;
			}
			strcpy(no->chave[j].pk, chave->pk);
			strcpy(no->chave[j].string, chave->string);
			no->desc[j+1] = *desc;
			no->num_chaves++;
			write_btree((void *) no, rrn, 's');
			libera_no((void *) no, 's');
			return(0);
		}
		else{
			node_Btree_is *new = (node_Btree_is *) split(no, chave, desc, 's');
			write_btree((void *) no, rrn, 's');
			write_btree((void *) new, nregistrosis, 's');
			nregistrosis++;
			libera_no((void *) new, 's');
			libera_no((void *) no, 's');
			return(1);
		}
	}
	if(insereIs((node_Btree_is *) read_btree(no->desc[i], 's'), chave, desc, no->desc[i])){
		if(no->num_chaves<ordem_is-1){
			j = no->num_chaves;
			while(j>i){
				strcpy(no->chave[j].pk, no->chave[j-1].pk);
				strcpy(no->chave[j].string, no->chave[j-1].string);
				no->desc[j+1] = no->desc[j];
				j--;
			}
			strcpy(no->chave[j].pk, chave->pk);
			strcpy(no->chave[j].string, chave->string);
			no->desc[j+1] = *desc;
			no->num_chaves++;
			write_btree((void *) no, rrn, 's');
			libera_no((void *) no, 's');
			return(0);
		}
		else{
			node_Btree_is *new = (node_Btree_is *) split(no, chave, desc, 's');
			write_btree((void *) no, rrn, 's');
			write_btree((void *) new, nregistrosis, 's');
			nregistrosis++;
			libera_no((void *) new, 's');
			libera_no((void *) no, 's');
			return(1);
		}	
	}
	return(0);
}

/* Atualiza os dois índices com o novo registro inserido */
void inserir_registro_indices(Indice *iprimary, Indice *idev, Jogo j){
	int desc = -1;
	Chave_ip ipkey;
	Chave_is iskey;
	node_Btree_ip *noip = (node_Btree_ip *) read_btree(iprimary->raiz, 'p');
	node_Btree_is *nois = (node_Btree_is *) read_btree(idev->raiz, 's');

	strcpy(iskey.pk, j.pk);
	sprintf(iskey.string, "%s$%s", j.desenvolvedora, j.nome);
	strcpy(ipkey.pk, j.pk);
	ipkey.rrn = nregistros;

	/*if(insereIs(nois, &iskey, &desc, idev->raiz)){
		nois = (node_Btree_is *) criar_no('s');
		nois->num_chaves = 1;
		strcpy(nois->chave[0].pk, iskey.pk);
		strcpy(nois->chave[0].string, iskey.string);
		nois->desc[0] = idev->raiz;
		nois->desc[1] = desc;
		if(idev->raiz==-1)
			nois->folha = 'F';
		else
			nois->folha = 'N';
		write_btree((void *) nois, nregistrosis, 's');
		idev->raiz = nregistrosis;
		nregistrosis++;
		libera_no((void *) nois, 's');
	}*/

	if(insereIp(noip, &ipkey, &desc, iprimary->raiz)){
		noip = (node_Btree_ip *) criar_no('p');
		noip->num_chaves = 1;
		strcpy(noip->chave[0].pk, ipkey.pk);
		noip->chave[0].rrn = ipkey.rrn;
		noip->desc[0] = iprimary->raiz;
		noip->desc[1] = desc;
		if(iprimary->raiz==-1)
			noip->folha = 'F';
		else
			noip->folha = 'N';
		write_btree((void *) noip, nregistrosip, 'p');
		iprimary->raiz = nregistrosip;
		nregistrosip++;
		libera_no((void *) noip, 'p');
	}

	desc = -1;
	/*strcpy(ipkey.pk, j.pk);
	ipkey.rrn = nregistros;

	if(insereIp(noip, &ipkey, &desc, iprimary->raiz)){
		noip = (node_Btree_ip *) criar_no('p');
		noip->num_chaves = 1;
		strcpy(noip->chave[0].pk, ipkey.pk);
		noip->chave[0].rrn = ipkey.rrn;
		noip->desc[0] = iprimary->raiz;
		noip->desc[1] = desc;
		if(iprimary->raiz==-1)
			noip->folha = 'F';
		else
			noip->folha = 'N';
		write_btree((void *) noip, nregistrosip, 'p');
		iprimary->raiz = nregistrosip;
		nregistrosip++;
		libera_no((void *) noip, 'p');
	}*/
	/*if(insereIs(nois, &iskey, &desc, idev->raiz)){
		nois = (node_Btree_is *) criar_no('s');
		nois->num_chaves = 1;
		strcpy(nois->chave[0].pk, iskey.pk);
		strcpy(nois->chave[0].string, iskey.string);
		nois->desc[0] = idev->raiz;
		nois->desc[1] = desc;
		if(idev->raiz==-1)
			nois->folha = 'F';
		else
			nois->folha = 'N';
		write_btree((void *) nois, nregistrosis, 's');
		idev->raiz = nregistrosis;
		nregistrosis++;
		libera_no((void *) nois, 's');
	}*/
}

/*Libera todos os campos dinâmicos do nó, inclusive ele mesmo*/
void libera_no(void *node, char ip){
	if(ip=='p'){
		free(((node_Btree_ip *) node)->chave);
		free(((node_Btree_ip *) node)->desc);
		free(((node_Btree_ip *) node));
	}
	else{
		free(((node_Btree_is *) node)->chave);
		free(((node_Btree_is *) node)->desc);
		free(((node_Btree_is *) node));	
	}
}

int buscaIp(node_Btree_ip *no, char *pk, char caminho){
	int rrn, i=0;

	while(i<no->num_chaves && strcmp(pk, no->chave[i].pk)>0)
		i++;
	if(no->folha=='F'){
		if(i==no->num_chaves || strcmp(pk, no->chave[i].pk)!=0)
			rrn = -1;
		else
			rrn = no->chave[i].rrn;
		libera_no((void *) no, 'p');
		return(rrn);
	}
	if(i==no->num_chaves || strcmp(pk, no->chave[i].pk)!=0){
		rrn = buscaIp((node_Btree_ip *) read_btree(no->desc[i], 'p'), pk, caminho);
		libera_no((void *) no, 'p');
		return(rrn);
	}
	rrn = no->chave[i].rrn;
	libera_no((void *) no, 'p');
	return(rrn);
}

char *buscaIs(node_Btree_is *no, char *string, char caminho){
	char *pk;
	int i=0;

	while(i<no->num_chaves && strcmp(string, no->chave[i].string)>0)
		i++;
	if(no->folha=='F'){
		if(i==no->num_chaves || strcmp(string, no->chave[i].string)!=0)
			pk = NULL;
		else
			pk = no->chave[i].pk;
		libera_no((void *) no, 's');
		return(pk);
	}
	if(i==no->num_chaves || strcmp(string, no->chave[i].string)!=0){
		pk = buscaIs((node_Btree_is *) read_btree(no->desc[i], 's'), string, caminho);
		libera_no((void *) no, 's');
		return(pk);
	}
	pk = no->chave[i].pk;
	libera_no((void *) no, 's');
	return(pk);	
}

void cadastrar(Indice* iprimary, Indice* idev){
	char registro[TAM_REGISTRO+1], aux[TAM_NOME], *aux2;
	int i;
	Jogo novo;
	float preco, preco_final;
	short int desconto;

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
	if(iprimary->raiz==-1 || buscaIp((node_Btree_ip *) read_btree(iprimary->raiz, 'p'), novo.pk, 0)==-1){
		strcat(ARQUIVO, registro);
		inserir_registro_indices(iprimary, idev, novo);
		nregistros++;
	}
	else
		printf(ERRO_PK_REPETIDA, novo.pk);
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

/* (Re)faz o Cria iprimary*/
void criar_iprimary(Indice *iprimary){
	int i;
	Jogo novo;
	int desc = -1;
	Chave_ip ipkey;
	node_Btree_ip *noip;

	iprimary->raiz = -1;
	for(i=0; i<nregistros; i++){
		novo = recuperar_registro(i);
		strcpy(ipkey.pk, novo.pk);
		ipkey.rrn = i;
		noip = (node_Btree_ip *) read_btree(iprimary->raiz, 'p');

		if(insereIp(noip, &ipkey, &desc, iprimary->raiz)){
			noip = (node_Btree_ip *) criar_no('p');
			noip->num_chaves = 1;
			strcpy(noip->chave[0].pk, ipkey.pk);
			noip->chave[0].rrn = ipkey.rrn;
			noip->desc[0] = iprimary->raiz;
			noip->desc[1] = desc;
			if(iprimary->raiz==-1)
				noip->folha = 'F';
			else
				noip->folha = 'N';
			write_btree((void *) noip, nregistrosip, 'p');
			iprimary->raiz = nregistrosip;
			nregistrosip++;
			libera_no((void *) noip, 'p');
		}
	}
}

/* (Re)faz o índice de jogos  */
void criar_idev(Indice *idev){
	int i;
	Jogo novo;
	int desc = -1;
	Chave_is iskey;
	node_Btree_is *nois;

	idev->raiz = -1;
	for(i=0; i<nregistros; i++){
		novo = recuperar_registro(i);
		strcpy(iskey.pk, novo.pk);
		sprintf(iskey.string, "%s$%s", novo.desenvolvedora, novo.nome);
		nois = (node_Btree_is *) read_btree(idev->raiz, 's');

		if(insereIs(nois, &iskey, &desc, idev->raiz)){
			nois = (node_Btree_is *) criar_no('s');
			nois->num_chaves = 1;
			strcpy(nois->chave[0].pk, iskey.pk);
			strcpy(nois->chave[0].string, iskey.string);
			nois->desc[0] = idev->raiz;
			nois->desc[1] = desc;
			if(idev->raiz==-1)
				nois->folha = 'F';
			else
				nois->folha = 'N';
			write_btree((void *) nois, nregistrosis, 's');
			idev->raiz = nregistrosis;
			nregistrosis++;
			libera_no((void *) nois, 's');
		}
	}
}

int alterar(Indice iprimary){return(0);}

void buscar(Indice iprimary,Indice idev){return;}

void listar(Indice iprimary,Indice idev){return;}