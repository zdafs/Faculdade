/* ==========================================================================
 * Universidade Federal de São Carlos - Campus Sorocaba
 * Disciplina: Estruturas de Dados 2
 * Prof. Tiago A. de Almeida
 *
 * Trabalho 01 - Indexação
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
#define TAM_DESENVOLVEDORA	51
#define TAM_DATA			11
#define TAM_CLASSIFICACAO 	3
#define TAM_PRECO 			8
#define TAM_DESCONTO 		4
#define TAM_CATEGORIA 		51


#define TAM_REGISTRO 		192
#define MAX_REGISTROS 		1000
#define MAX_CATEGORIAS 		10
#define TAM_ARQUIVO 		(MAX_REGISTROS * TAM_REGISTRO + 1)


/* Saídas do usuário */
#define OPCAO_INVALIDA 			"Opcao invalida!\n"
#define MEMORIA_INSUFICIENTE 	"Memoria insuficiente!"
#define REGISTRO_N_ENCONTRADO 	"Registro(s) nao encontrado!\n"
#define CAMPO_INVALIDO 			"Campo invalido! Informe novamente.\n"
#define ERRO_PK_REPETIDA 		"ERRO: Ja existe um registro com a chave primaria: %s.\n"
#define ARQUIVO_VAZIO 			"Arquivo vazio!"
#define INICIO_BUSCA 		 	"**********************BUSCAR**********************\n"
#define INICIO_LISTAGEM  		"**********************LISTAR**********************\n"
#define INICIO_ALTERACAO 		"**********************ALTERAR*********************\n"
#define INICIO_EXCLUSAO  		"**********************EXCLUIR*********************\n"
#define INICIO_ARQUIVO  		"**********************ARQUIVO*********************\n"
#define SUCESSO  				"OPERACAO REALIZADA COM SUCESSO!\n"
#define FALHA 					"FALHA AO REALIZAR OPERACAO!\n"

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

/* Registros dos Índices*/

/* Struct para índice Primário */
typedef struct primary_index{
  char pk[TAM_PRIMARY_KEY];
  int rrn;
} Ip;

//Struct de indice Secundário contendo o nome do jogo
typedef struct secundary_index_game{
  char pk[TAM_PRIMARY_KEY];
  char nome[TAM_NOME];
} Isg;

//Struct de indice Secundário contendo o preço do jogo
typedef struct secundary_index_price{
  char pk[TAM_PRIMARY_KEY];
  float valor;
} Isp;

typedef struct linked_list{
  char pk[TAM_PRIMARY_KEY];
  struct linked_list *prox;
} ll;

//Struct para indice secundario contendo as desenvolvedoras
typedef struct reverse_index_dev{
  char desenvolvedora[TAM_DESENVOLVEDORA];
  ll *lista;
} Ird;

//Struct para indice secundario contendo as categorias
typedef struct reverse_index_cat{
  char categoria[TAM_CATEGORIA];
  ll *lista;
} Irc;

/*	Você deve optar por utilizar índices secundários simples, ou listas invertidas.
 *  Seguem abaixo sugestões para suas EDs


*Struct para índice secundário comum:
typedef struct secundary_index{
  char pk[TAM_PRIMARY_KEY];
  void *chave; <- Trocar o tipo conforme item desejado.
} Is;


*Lista ligada simples para a lista invertida:
typedef struct linked_list{
  char pk[TAM_PRIMARY_KEY];
  struct linked_list *prox;
} ll;

*Struct para a lista invertida:
typedef struct reverse_index{
  void *chave; <- Trocar o tipo conforme item desejado.
  ll* lista;
} Ir;
*/

/* Variavel global que simula o arquivo de dados */
char ARQUIVO[TAM_ARQUIVO];

/* ==========================================================================
 * ========================= PROTÓTIPOS DAS FUNÇÕES =========================
 * ========================================================================== */
 /* Exibe o menu de opções */
void print_menu();

/* Recebe do usuário uma string simulando o arquivo completo e retorna o número
 * de registros. */
int carregar_arquivo();

/* Exibe o jogo, utilize com_desconto = 1 apenas para listagem por preço */
int exibir_registro(int rrn, char com_desconto);

/* Recupera do arquivo o registro com o rrn informado e retorna os dados na
 * struct Jogo */
Jogo recuperar_registro(int rrn);

/*Dada uma certa chave, retorna o rrn dela consultando o ip*/
int recuperar_rrn(Ip* iprimary, const char* pk, int nregistros);

/* (Re)faz o índice primário */
void criar_iprimary(Ip *indice_primario, int nregistros);

/* Salva os dados da entrada para a struct jogo*/
void ler_entrada(char* registro, Jogo *novo);

//Compara strings com registradores de chave primaria
int compStrIp(const void *a, const void *b){
	return (strcmp((char *) a, ((Ip *) b)->pk));
}

/*Insere um registro no arquivo de dados. Se o registro ja existir imprime uma msg de erro, caso contrario reordena o vetor
de chaves e insere o registro no arquivo de dados*/
void insereReg(Ip *iprimary, Isg *igame, Ird *idev, Irc *icat, Isp *iprice, int *nregistros, int *ndev, int *ncat);

// (Re)faz o indice secundário de nomes de jogos
void criar_igame(Isg *igame, int nregistros);

//Compara strings com registradores de chave secundaria da desenvolvedora
int compStrIrd(const void *a, const void *b){
	return (strcmp((char *) a, ((Ird *) b)->desenvolvedora));
}

//Compara strings com registradores de chave secundaria da categoria
int compStrIrc(const void *a, const void *b){
	return (strcmp((char *) a, ((Irc *) b)->categoria));
}

//Insere um novo registro no arquivo de indices secundarios de desenvolvedoras
void insere_idev(Ird *idev, char *desenvolvedora, char *pk, int *ndev);

// (Re)faz o indice secundário de nomes de desenvolvedoras
void criar_idev(Ird *idev, int *ndev, int nregistros);

//Libera o arquivo de indices secundarios das devs
void libera_idev(Ird *idev, int ndev);

//Insere um novo registro no arquivo de indices secundarios de categoria
void insere_icat(Irc *icat, char *categoria, char *pk, int *ncat);

// (Re)faz o indice secundário de categorias
void criar_icat(Irc *icat, int *ncat, int nregistros);

//Libera o arquivo de indices secundarios das categorias
void libera_icat(Irc *icat, int ncat);

//Altera o campo desconto de um jogo. Retorna 0 caso o registro nao seja encontrado e 1 caso contrario
int alterar(Ip *iprimary, Isp *iprice, int nregistros);

//Marca um registro como removido. Returna 0 caso nao encontre o registro e 1 caso contrario
int remover(Ip *iprimary, int nregistros);

//Reorganiza o arquivo de daodos e reconstroi os indices
void limpa_arquivo(Ip *iprimary, Isg *igame, Ird *idev, Irc *icat, Isp *iprice, int *nregistros, int *ndev, int *ncat);

// (Re)faz o indice secundário de preços
void criar_iprice(Isp *iprice, int nregistros);

void Ipsort(Ip *iprimary, int nregistros);

void Isgsort(Isg *igame, int nregistros);

void Ispsort(Isp *iprice, int nregistros);

void Irdsort(Ird *idev, int ndev);

void Ircsort(Irc *icat, int ncat);

int max(int i, int j){
	if(i>j)
		return(i);
	return(j);
}


/* ==========================================================================
 * ============================ FUNÇÃO PRINCIPAL ============================
 * ======================================================================= */
int main(){
  /* Arquivo */
	int carregarArquivo = 0, nregistros = 0, ncat = 0, ndev = 0, rrn;
	char pk[TAM_PRIMARY_KEY], nome[TAM_NOME], desenvolvedora[TAM_DESENVOLVEDORA];
	int i, j;
	ll *p, *q;
	
	scanf("%d%*c", &carregarArquivo); /* 1 (sim) | 0 (nao) */
	
	if (carregarArquivo)
		nregistros = carregar_arquivo();

	/* Índice primário */
	Ip *iprimary = (Ip *) malloc (MAX_REGISTROS * sizeof(Ip));
  	if (!iprimary) {
		perror(MEMORIA_INSUFICIENTE);
		exit(1);
	}
	criar_iprimary(iprimary, nregistros);

	/* Alocar e criar índices secundários */
	Isg *igame = (Isg *) malloc (MAX_REGISTROS*sizeof(Isg));
	if (!igame) {
		perror(MEMORIA_INSUFICIENTE);
		exit(1);
	}
	criar_igame(igame, nregistros);

	Ird *dev_aux, *idev = (Ird *) malloc (MAX_REGISTROS*sizeof(Ird));
	if (!idev) {
		perror(MEMORIA_INSUFICIENTE);
		exit(1);
	}
	criar_idev(idev, &ndev, nregistros);

	Irc *cat_aux, *icat = (Irc *) malloc (MAX_CATEGORIAS*sizeof(Irc));
	if(!icat) {
		perror(MEMORIA_INSUFICIENTE);
		exit(1);
	}
	criar_icat(icat, &ncat, nregistros);

	Isp *iprice = (Isp *) malloc (MAX_REGISTROS*sizeof(Isp));
	if (!iprice) {
		perror(MEMORIA_INSUFICIENTE);
		exit(1);
	}
	criar_iprice(iprice, nregistros);


    /* Execução do programa */
	int opcao = 0, opcaoSec = 0;
	while(1) {
		scanf("%d%*c", &opcao);
		switch(opcao) {
		case 1:
			/* inserir */
			insereReg(iprimary, igame, idev, icat, iprice, &nregistros, &ndev, &ncat);
			break;
		case 2:
			/* alterar */
			printf(INICIO_ALTERACAO);
			if(alterar(iprimary, iprice, nregistros))
				printf(SUCESSO);
			else
				printf(FALHA);
			break;
		case 3:
			/* excluir */
			printf(INICIO_EXCLUSAO);
			if(remover(iprimary, nregistros))
				printf(SUCESSO);
			else
				printf(FALHA);
			break;
		case 4:
			/* buscar */
			printf(INICIO_BUSCA );
			scanf("%d%*c", &opcaoSec);

			if(opcaoSec==1){
				scanf("%s%*c", pk);
				if(!exibir_registro(recuperar_rrn(iprimary, pk, nregistros), 0))
					printf(REGISTRO_N_ENCONTRADO);
			}

			else if(opcaoSec==2){
				fgets(nome, TAM_NOME, stdin);
				nome[strlen(nome)-1] = '\0';
				for(i=0, j=0; i<nregistros; i++){//ira percorrer sequencialmente o arquivo igame
					if(strcmp(igame[i].nome, nome)==0 && (rrn=recuperar_rrn(iprimary, igame[i].pk, nregistros))>=0){
						if(j!=0)
							printf("\n");
						exibir_registro(rrn, 0);
						j = 1;
					}
				}
				if(!j)//caso n tenha saido por causa da flag n foi encontrado nenhum registro
					printf(REGISTRO_N_ENCONTRADO);
			}

			else if(opcaoSec==3){
				fgets(desenvolvedora, TAM_DESENVOLVEDORA, stdin);
				desenvolvedora[strlen(desenvolvedora)-1] = '\0';
				dev_aux = bsearch(desenvolvedora, idev, ndev, sizeof(Ird), compStrIrd);
				fgets(nome, TAM_NOME, stdin);
				nome[strlen(nome)-1] = '\0';
				cat_aux = bsearch(nome, icat, ncat, sizeof(Irc), compStrIrc);
				if(dev_aux!=NULL && cat_aux!=NULL){
					p = dev_aux->lista;
					q = cat_aux->lista;
					i = 0;
					while(p!=NULL && q!=NULL){
						if(strcmp(p->pk, q->pk)<0)
							p = p->prox;
						else if(strcmp(p->pk, q->pk)>0)
							q = q->prox;
						else{
							if((rrn=recuperar_rrn(iprimary, p->pk, nregistros))>=0){
								if(i!=0)
									printf("\n");
								exibir_registro(rrn, 0);
								i = 1;
							}
							p = p->prox;
							q = q->prox;
						}
					}
					if(i==0)
						printf(REGISTRO_N_ENCONTRADO);
				}
				else
					printf(REGISTRO_N_ENCONTRADO);	
			}
			break;
		case 5:
			/* listar */
			printf(INICIO_LISTAGEM);
			scanf("%d%*c", &opcaoSec);

			/*if((nregistros-reg_remov)==0)
				printf(REGISTRO_N_ENCONTRADO);*/

			if(opcaoSec==1){
				for(i=0, j=0; i<nregistros; i++){
					if(j!=0 && iprimary[i].rrn>=0)
						printf("\n");
					if(exibir_registro(iprimary[i].rrn, 0))
						j = 1;
				}
			}

			else if(opcaoSec==2){
				fgets(nome, TAM_NOME, stdin);
				nome[strlen(nome)-1] = '\0';
				cat_aux = bsearch(nome, icat, ncat, sizeof(Irc), compStrIrc);
				if(cat_aux!=NULL){
					p = cat_aux->lista;
					j = 0;
					while(p!=NULL){
						if((rrn=recuperar_rrn(iprimary, p->pk, nregistros))>=0){
							if(j!=0)
								printf("\n");
							exibir_registro(rrn, 0);
							j = 1;
						}
						p = p->prox;
					}
				}
				else{
					j=1;
					printf(REGISTRO_N_ENCONTRADO);
				}
			}

			else if(opcaoSec==3){
				for(i=0, j = 0; i<ndev; i++){
					p = idev[i].lista;
					while(p!=NULL){
						if((rrn=recuperar_rrn(iprimary, p->pk, nregistros))>=0){
							if(j!=0)
								printf("\n");
							exibir_registro(rrn, 0);
							j = 1;
						}
						p = p->prox;
					}
				}
			}

			else if(opcaoSec==4){
				for(i=0, j=0; i<nregistros; i++){
					if((rrn = recuperar_rrn(iprimary, iprice[i].pk, nregistros))>=0){
						if(j!=0)
							printf("\n");
						exibir_registro(rrn, 1);
						j = 1;
					}
				}
			}

			else
				j = 1;

			if(!j)
				printf(REGISTRO_N_ENCONTRADO);
			break;
		case 6:
			limpa_arquivo(iprimary, igame, idev, icat, iprice, &nregistros, &ndev, &ncat);
		break;
		case 7:
			/* imprimir arquivo de dados*/
			printf(INICIO_ARQUIVO);
			if(nregistros==0)
				printf(ARQUIVO_VAZIO);
			else
				printf("%s\n", ARQUIVO);
			break;
		case 8:
    		/* Liberar memoria e finalizar */
			free(iprimary);
			free(igame);
			free(iprice);
			libera_idev(idev, ndev);
			libera_icat(icat, ncat);
			return (0);
			break;
		default:
			printf(OPCAO_INVALIDA);
			break;
		}
	}
	return (0);
}



/* Exibe o jogo, utilize com_desconto = 1 para listagem por preço */
int exibir_registro(int rrn, char com_desconto) {
	float preco_final;

	if(rrn < 0)
		return (0);

	float preco;
	short int desconto;
	Jogo j = recuperar_registro(rrn);
	char *cat, categorias[TAM_CATEGORIA];
	
	printf("%s\n", j.pk);
	printf("%s\n", j.nome);
	printf("%s\n", j.desenvolvedora);
	printf("%s\n", j.data);

	if(com_desconto){
		sscanf(j.preco, "%f", &preco);
		sscanf(j.desconto, "%hd", &desconto);
		preco_final = preco * (100-desconto);
		preco_final = (int) preco_final/100.0;
		printf("%07.2f\n", preco_final );
	}
	else{
		printf("%s\n", j.preco);
		printf("%s\n", j.desconto);
	}

	strncpy(categorias, j.categoria, max(strlen(j.categoria), TAM_CATEGORIA - 1));
  	for (cat = strtok (categorias, "|"); cat != NULL; cat = strtok (NULL, "|"))
    	printf("%s ", cat);
	
	printf("\n");
	return (1);
}

/* Imprime o menu para o usuário */
void print_menu(){
		printf("\n 1. Cadastro");
		printf("\n 2. Alteração");
		printf("\n 3. Remoção");
		printf("\n 4. Busca");
		printf("\n 5. Listagem");
		printf("\n 6. Liberar espaço");
		printf("\n 7. Finalizar");
		printf("\n\nEntre com uma das opções acima: ");
}

/* Carrega o arquivo de dados */
int carregar_arquivo() {
	scanf("%[^\n]\n", ARQUIVO);
	return (strlen(ARQUIVO) / TAM_REGISTRO);
}

/* (Re)faz o índice primário */
void criar_iprimary(Ip *indice_primario, int nregistros){
	int i;
	Jogo novo;

	for(i=0; i<nregistros; i++){//Percorre ARQUIVO para construir a chave
		novo = recuperar_registro(i);//Recupera o registro de rrn i do arquivo
		strcpy(indice_primario[i].pk, novo.pk);//Salva a chave primaria do mesmo
		indice_primario[i].rrn = i;//Salva o rrn
	}
	Ipsort(indice_primario, nregistros);
}

/*Dada uma certa chave, retorna o rrn dela consultando o ip*/
int recuperar_rrn(Ip* iprimary, const char* pk, int nregistros){
	Ip *aux;

	aux = bsearch(pk, iprimary, nregistros, sizeof(Ip), compStrIp);//faz busca binaria no vetor de chaves primarias
	if(aux!=NULL)//se for diferente de nulo retorna o rrn da chave encontrada
		return(aux->rrn);
	return(-1);
}

/* Recupera do arquivo o registro com o rrn informado e retorna os dados na
 * struct Jogo */
Jogo recuperar_registro(int rrn){
	Jogo novo;

	ler_entrada(ARQUIVO+(rrn*TAM_REGISTRO), &novo);
	return(novo);
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

/*Insere um registro no arquivo de dados. Se o registro ja existir imprime uma msg de erro, caso contrario reordena o vetor
de chaves e insere o registro no arquivo de dados*/
void insereReg(Ip *iprimary, Isg *igame, Ird *idev, Irc *icat, Isp *iprice, int *nregistros, int *ndev, int *ncat){
	char registro[TAM_REGISTRO+1], aux[TAM_NOME], *aux2;
	int i;
	Jogo novo;
	float preco, preco_final;
	short int desconto;

	registro[0] = '\0';
	for(i=0; i<7; i++){
		fgets(aux, TAM_NOME, stdin);//pega a string passada pelo usuario (ate \n)
		strcat(registro, aux);//concatena na string que armazena o registro como um todo
		aux2 = strchr(registro, '\n');//encontra a primeira ocorrencia de \n e troca o mesmo por @
		*aux2 = '@';
	}
	for(aux2=aux2+1; aux2<registro+TAM_REGISTRO; aux2++)
		*aux2 = '#';//preenche os espaços não utilizados com #
	*aux2 = '\0';
	ler_entrada(registro, &novo);//constroi o registro a partir da string
	i = recuperar_rrn(iprimary, novo.pk, *nregistros);//verifica se a chave ja não existe
	if(i==-1){//caso em que a chave não existe
		strcat(ARQUIVO, registro);//concatena o registro ao arquivo de dados
		strcpy(iprimary[*nregistros].pk, novo.pk);//atualiza o arquivo com indices com a nova chave e seu rrn
		iprimary[*nregistros].rrn = *nregistros;
		//Inicio da atualização do indice secundario com nome do jogo
		strcpy(igame[*nregistros].pk, novo.pk);
		strcpy(igame[*nregistros].nome, novo.nome);
		//Fim da atualização do indice secundario com nome do jogo
		//Inicio da atualização do indice secundario com preço do jogo
		strcpy(iprice[*nregistros].pk, novo.pk);
		sscanf(novo.preco, "%f", &preco);
		sscanf(novo.desconto, "%hd", &desconto);
		preco_final = preco * (100-desconto);
		preco_final = (int) preco_final/100.0;
		iprice[*nregistros].valor = preco_final;
		//Fim da atualização do indice secundario com preço do jogo
		insere_idev(idev, novo.desenvolvedora, novo.pk, ndev);//insere e organiza o arquivo de indices secundarios das devs
		insere_icat(icat, novo.categoria, novo.pk, ncat);//insere e organiza o arquivo de indices secundarios das categorias
		(*nregistros)++;
		Ipsort(iprimary, *nregistros);//ordena o arquivo de indices
		Isgsort(igame, *nregistros);//ordena o arquivo de indice secundario com nome do jogo
		Ispsort(iprice, *nregistros);//ordena o arquivo de indice secundario com preco do jogo
	}
	else{//caso em que a chave existe
		printf(ERRO_PK_REPETIDA, novo.pk);//apresenta uma msg ed erro
	}
}

// (Re)faz o indice secundário de nomes de jogos
void criar_igame(Isg *igame, int nregistros){
	int i;
	Jogo novo;

	for(i=0; i<nregistros; i++){//Percorre ARQUIVO para construir a chave
		novo = recuperar_registro(i);//Recupera o registro de rrn i do arquivo
		strcpy(igame[i].pk, novo.pk);//Salva a chave primaria do mesmo
		strcpy(igame[i].nome, novo.nome);//Salva o nome do jogo
	}
	Isgsort(igame, nregistros);
}

//Insere um novo registro no arquivo de indices secundarios de desenvolvedoras
void insere_idev(Ird *idev, char *desenvolvedora, char *pk, int *ndev){
	Ird *aux;
	ll **p, *n;

	aux = bsearch(desenvolvedora, idev, *ndev, sizeof(Ird), compStrIrd);//faz uma busca binária para ver se a dev ja esta no arquivo
	if(aux==NULL){
		strcpy(idev[*ndev].desenvolvedora, desenvolvedora);//caso a dev nao esteja ela é inserida no arquivo
		idev[*ndev].lista = NULL;
		aux = idev+(*ndev);
		(*ndev)++;
	}
	/*feita a inserção mantendo a ordem das chaves primarias*/
	p = &(aux->lista);
	while(*p!=NULL && strcmp((*p)->pk, pk)<0)
		p = &((*p)->prox);
	n = (ll *) malloc(sizeof(ll));
	strcpy(n->pk, pk);
	n->prox = *p;
	*p = n;
	//qsort(idev, *ndev, sizeof(Ird), compIrd);
	Irdsort(idev, *ndev);
}

//Insere um novo registro no arquivo de indices secundarios de categoria
void insere_icat(Irc *icat, char *categoria, char *pk, int *ncat){
	Irc *aux;
	ll **p, *n;
	char *cat, categorias[TAM_CATEGORIA];

	//strncpy(categorias, categoria, strlen(categoria)/*max(strlen(categoria), TAM_CATEGORIA - 1)*/);
	strcpy(categorias, categoria);
  	for (cat = strtok (categorias, "|"); cat != NULL; cat = strtok (NULL, "|")){
  		aux = bsearch(cat, icat, *ncat, sizeof(Irc), compStrIrc);//faz uma busca binária para ver se a categoria ja esta no arquivo
		if(aux==NULL){
			strcpy(icat[*ncat].categoria, cat);//caso a categoria nao esteja ela é inserida no arquivo
			icat[*ncat].lista = NULL;
			aux = icat+(*ncat);
			(*ncat)++;
		}
		/*feita a inserção mantendo a ordem das chaves primarias*/
		p = &(aux->lista);
		while(*p!=NULL && strcmp((*p)->pk, pk)<0)
			p = &((*p)->prox);
		n = (ll *) malloc(sizeof(ll));
		strcpy(n->pk, pk);
		n->prox = *p;
		*p = n;
		//qsort(icat, *ncat, sizeof(Irc), compIrc);
		Ircsort(icat, *ncat);
  	}
    	
}

// (Re)faz o indice secundário de nomes de desenvolvedoras
void criar_idev(Ird *idev, int *ndev, int nregistros){
	int i;
	Jogo novo;

	for(i=0; i<nregistros; i++){
		novo = recuperar_registro(i);//recupera um registro do ARQUIVO
		insere_idev(idev, novo.desenvolvedora, novo.pk, ndev);//insere o registro no arquivo com nomes da desenvolvedora
	}
}

// (Re)faz o indice secundário de categorias
void criar_icat(Irc *icat, int *ncat, int nregistros){
	int i;
	Jogo novo;

	for(i=0; i<nregistros; i++){
		novo = recuperar_registro(i);//recupera um registro do ARQUIVO
		insere_icat(icat, novo.categoria, novo.pk, ncat);//insere o registro no arquivo com as categorias
	}	
}

//Libera o arquivo de indices secundarios das devs
void libera_idev(Ird *idev, int ndev){
	ll *aux;
	int i;

	for (i=0; i<ndev; i++){
		aux = idev[i].lista;
		while(aux!=NULL){
			idev[i].lista = aux->prox;
			free(aux);
			aux = idev[i].lista;
		}
	}
	free(idev);
}

//Libera o arquivo de indices secundarios das categorias
void libera_icat(Irc *icat, int ncat){
	ll *aux;
	int i;

	for (i=0; i<ncat; i++){
		aux = icat[i].lista;
		while(aux!=NULL){
			icat[i].lista = aux->prox;
			free(aux);
			aux = icat[i].lista;
		}
	}
	free(icat);	
}

//Altera o campo desconto de um jogo. Retorna 0 caso o registro nao seja encontrado e 1 caso contrario
int alterar(Ip *iprimary, Isp *iprice, int nregistros){
	int i, rrn, flag=0;
	char desconto[TAM_DESCONTO], preco[TAM_PRECO], pk[TAM_PRIMARY_KEY], c, *aux;
	short int desconto_sh;
	float preco_f, preco_final;

	scanf("%s%*c", pk);
	rrn = recuperar_rrn(iprimary, pk, nregistros);//busca o rrn do registro procurado
	if(rrn==-1){//caso o registro nao seja encontrado
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
	for(i=0; i<4; i++)
		aux = strchr(aux+1, '@');//vai ate o @ antes do campo de desconto
	aux++;
	strncpy(preco, aux, TAM_PRECO);
	/*atualiza o campo valor no iprice*/
	for(i=0, flag=0; i<nregistros && !flag; i++){
		if(!strcmp(pk, iprice[i].pk)){
			sscanf(preco, "%f", &preco_f);
			sscanf(desconto, "%hd", &desconto_sh);
			preco_final = preco_f * (100-desconto_sh);
			preco_final = (int) preco_final/100.0;
			iprice[i].valor = preco_final;
			flag = 1;
		}
	}
	Ispsort(iprice, nregistros);
	aux = strchr(aux, '@');
	aux++;
	/*substitui o campo desconto*/
	aux[0] = desconto[0];
	aux[1] = desconto[1];
	aux[2] = desconto[2];
	return(1);
}

//Marca um registro como removido. Returna 0 caso nao encontre o registro e 1 caso contrario
int remover(Ip *iprimary, int nregistros){
	Ip *aux;
	char pk[TAM_PRIMARY_KEY], *p;

	scanf("%s%*c", pk);
	aux = bsearch(pk, iprimary, nregistros, sizeof(Ip), compStrIp);
	if(aux==NULL || aux->rrn==-1){//Caso em que a chave primaria não existe em iprimary ou ja foi removida
		printf(REGISTRO_N_ENCONTRADO);
		return(0);
	}
	p = ARQUIVO + (aux->rrn)*TAM_REGISTRO;//Coloca o apontador na posicao em que sera alterada
	p[0] = '*';
	p[1] = '|';
	aux->rrn = -1;//altera o rrn para representar que foi removido
	return(1);
}


//Reorganiza o arquivo de daodos e reconstroi os indices
void limpa_arquivo(Ip *iprimary, Isg *igame, Ird *idev, Irc *icat, Isp *iprice, int *nregistros, int *ndev, int *ncat){
	int i;
	char *p;
	ll *aux;

	/*loop irá encontrar os registros que já foram removidos e remove-los do ARQUIVO, sobreescrevendo com
	o registro posterior*/
	for(p = ARQUIVO; p-ARQUIVO<TAM_REGISTRO*(*nregistros); p = p+TAM_REGISTRO){
		if(p[0]=='*' && p[1]=='|'){
			strcpy(p, p+TAM_REGISTRO);
			(*nregistros)--;//diminui a quantidade de registros
			p = p-TAM_REGISTRO;//deve voltar para conferir o registro que esta substituindo o atual
		}
	}
	/*Libera as listas ligadas de dev*/
	for (i=0; i<*ndev; i++){
		aux = idev[i].lista;
		while(aux!=NULL){
			idev[i].lista = aux->prox;
			free(aux);
			aux = idev[i].lista;
		}
	}
	/*Libera as listas ligadas de categoria*/
	for (i=0; i<*ncat; i++){
		aux = icat[i].lista;
		while(aux!=NULL){
			icat[i].lista = aux->prox;
			free(aux);
			aux = icat[i].lista;
		}
	}
	/*Reconstroe os indices*/
	*ndev = 0;
	*ncat = 0;
	criar_iprimary(iprimary, *nregistros);
	criar_igame(igame, *nregistros);
	criar_iprice(iprice, *nregistros);
	criar_idev(idev, ndev, *nregistros);
	criar_icat(icat, ncat, *nregistros);
}

// (Re)faz o indice secundário de preços
void criar_iprice(Isp *iprice, int nregistros){
	int i;
	Jogo novo;
	float preco, preco_final;
	short int desconto;

	for(i=0; i<nregistros; i++){//Percorre ARQUIVO para construir a chave
		novo = recuperar_registro(i);//Recupera o registro de rrn i do arquivo
		strcpy(iprice[i].pk, novo.pk);//Salva a chave primaria do mesmo
		sscanf(novo.preco, "%f", &preco);
		sscanf(novo.desconto, "%hd", &desconto);
		preco_final = preco * (100-desconto);
		preco_final = (int) preco_final/100.0;
		iprice[i].valor = preco_final;
	}
	Ispsort(iprice, nregistros);
}

void Ipsort(Ip *iprimary, int nregistros){
	int i, j, menor;
	Ip aux;

	for(i=0; i<nregistros-1; i++){
		menor = i;
		for(j=i+1; j<nregistros; j++){
			if(strcmp(iprimary[menor].pk, iprimary[j].pk)>0)
				menor = j;
		}
		if(strcmp(iprimary[i].pk, iprimary[menor].pk)){
			aux = iprimary[menor];
			iprimary[menor] = iprimary[i];
			iprimary[i] = aux;
		}
	}
}

void Isgsort(Isg *igame, int nregistros){
	int i, j, menor;
	Isg aux;

	for(i=0; i<nregistros-1; i++){
		menor = i;
		for(j=i+1; j<nregistros; j++){
			if(strcmp(igame[menor].nome, igame[j].nome)>0 || 
			  (!strcmp(igame[menor].nome, igame[j].nome) && strcmp(igame[menor].pk, igame[j].pk)>0))
				menor = j;
		}
		if(strcmp(igame[i].pk, igame[menor].pk)){
			aux = igame[menor];
			igame[menor] = igame[i];
			igame[i] = aux;
		}
	}
}

void Ispsort(Isp *iprice, int nregistros){
	int i, j, menor;
	Isp aux;

	for(i=0; i<nregistros-1; i++){
		menor = i;
		for(j=i+1; j<nregistros; j++){
			if(iprice[menor].valor>iprice[j].valor || (iprice[menor].valor==iprice[j].valor && strcmp(iprice[menor].pk, iprice[j].pk)>0))
				menor = j;
		}
		if(strcmp(iprice[i].pk, iprice[menor].pk)){
			aux = iprice[menor];
			iprice[menor] = iprice[i];
			iprice[i] = aux;
		}
	}
}

void Irdsort(Ird *idev, int ndev){
	int i, j, menor;
	Ird aux;

	for(i=0; i<ndev-1; i++){
		menor = i;
		for(j=i+1; j<ndev; j++){
			if(strcmp(idev[menor].desenvolvedora, idev[j].desenvolvedora)>0)
				menor = j;
		}
		if(strcmp(idev[i].desenvolvedora, idev[menor].desenvolvedora)){
			aux = idev[menor];
			idev[menor] = idev[i];
			idev[i] = aux;
		}
	}
}

void Ircsort(Irc *icat, int ncat){
	int i, j, menor;
	Irc aux;

	for(i=0; i<ncat-1; i++){
		menor = i;
		for(j=i+1; j<ncat; j++){
			if(strcmp(icat[menor].categoria, icat[j].categoria)>0)
				menor = j;
		}
		if(strcmp(icat[i].categoria, icat[menor].categoria)){
			aux = icat[menor];
			icat[menor] = icat[i];
			icat[i] = aux;
		}
	}
}