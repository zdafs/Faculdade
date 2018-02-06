/* ================================================================== *
	Universidade Federal de Sao Carlos - UFSCar, Sorocaba

	Disciplina: Estruturas de Dados 1
	Prof. Tiago A. Almeida

	Exercício 07 - Gestão de Estacionamentos

	Instrucoes
	----------

	Este arquivo contem o codigo que auxiliara no desenvolvimento do
	exercicio. Voce precisara completar as funcoes requisitadas.

	Voce nao podera criar nenhuma outra funcao. Complete apenas as
	rotinas	fornecidas.
 * ==================================================================
    Dados do aluno:

   RA: 726563
   Nome: Lucca La Fonte Albuquerque Carvalho

* ================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Frases pre-definidas
#define MSG_ERRO_ALOC 		"Erro de alocacao!\n"
#define MSG_JA_EXISTE		"O título de relatório informado já está cadastrado!\n"
#define MSG_NAO_EXISTE_REL	"O relatório requisitado não está cadastrado!\n"
#define MSG_NAO_EXISTE_PLC	"A placa informada não está presente no relatório!\n"
#define MSG_OPCAO_INV 		"Opcao invalida!\n"
#define MSG_EXIBE_HORARIO	"E: %02dh%02d | S: %02dh%02d\n"


// === TAD E DEMAIS REGISTROS ===

typedef char boolean;

typedef struct{
	char horas, minutos;
}Horario;

typedef struct{
	char *placa;
	Horario entrada, saida;
}Veiculo;

typedef struct Celula{
	char *titulo;
	Veiculo *veiculos;
	int tam;
	boolean validade;
}Celula;

typedef struct{
	Celula *inicio;
	int tamanho;
}Lista;

/*typedef struct{
	Horario entrada, saida;
}Pilha;*/

/* ================================================================== */
/* ===================== PREAMBULO DAS FUNCOES ====================== */
/* ================================================================== */

void iniciaLista(Lista *lista);
int listaVazia(Lista *lista);
int adicionaNaLista(Lista *lista, char *titulo);
int adicionaVeiculo(Lista *lista, char *placa, Horario entrada, Horario saida);
int verificaValidade(Lista *lista, int k);
int procuraTitulo(Lista *lista, char *titulo);
boolean retornaValidade(Lista *lista, int k);
int retornaEntradaSaida(Lista *lista, char *placa, Horario *entrada, Horario *saida, int k);
void liberaMemoria(Lista *lista);



/* ================================================================== */
/* ======================== ROTINA PRINCIPAL ======================== */
/* ================================================================== */

int main(){

	char *aux, c;
	int op, k, j;
	Horario entrada, saida;
	Lista *lista;
	Celula *temp;

	lista = (Lista *) malloc(sizeof(Lista));
	if(lista==NULL){
		printf(MSG_ERRO_ALOC);
		return(0);
	}
	iniciaLista(lista);
	scanf("%d", &op);
	while(op!=4){
		if(op==1){
			getchar();
			k = 0;
			aux = (char *) malloc(1);
			while((c = getchar())!='\n'){
				aux[k] = c;
				k++;
				aux = (char *) realloc(aux, k+1);
			}
			aux[k] = '\0';
			scanf("%d", &k);
			if(procuraTitulo(lista, aux)==-1){
				if(adicionaNaLista(lista, aux)==0){
					printf(MSG_ERRO_ALOC);
					return(0);
				}
				getchar();
				aux = (char *) malloc(8);
				j = 0;
				while(j<7){
					if((c = getchar())!='-'){
						aux[j] = c;
						j++;
					}
				}
				aux[j] = '\0';
				while(strcmp(aux, "END0000")){
					scanf("%dh", &j);
					entrada.horas = (int) j;
					scanf("%d ", &j);
					entrada.minutos = (int) j;
					scanf("%dh", &j);
					saida.horas = (int) j;
					scanf("%d", &j);
					saida.minutos = (int) j;
					if(adicionaVeiculo(lista, aux, entrada, saida)==0){
						printf(MSG_ERRO_ALOC);
						return(0);
					}
					getchar();
					aux = (char *) malloc(8);
					j = 0;
					while(j<7){
						if((c = getchar())!='-'){
							aux[j] = c;
							j++;
						}
					}
					aux[j] = '\0';
				}
				if(verificaValidade(lista, k)==0){
					printf(MSG_ERRO_ALOC);
					return(0);
				}
			}
			else
				printf(MSG_JA_EXISTE);
			free(aux);
		}

		else if(op==2){
			getchar();
			k=0;
			aux = (char *) malloc(1);
			while((c = getchar())!='\n'){
				aux[k] = c;
				k++;
				aux = (char *) realloc(aux, k+1);
			}
			aux[k] = '\0';
			k = procuraTitulo(lista, aux);
			if(k!=-1){
				if(retornaValidade(lista, k))
					printf("Válido\n");
				else
					printf("Inválido\n");
			}
			else
				printf(MSG_NAO_EXISTE_REL);
			free(aux);
		}

		else if(op==3){
			getchar();
			k=0;
			aux = (char *) malloc(1);
			while((c = getchar())!='\n'){
				aux[k] = c;
				k++;
				aux = (char *) realloc(aux, k+1);
			}
			aux[k] = '\0';
			k = procuraTitulo(lista, aux);
			free(aux);
			aux = (char *) malloc(8);
			j = 0;
			while(j<7){
				if((c = getchar())!='-'){
					aux[j] = c;
					j++;
				}
			}
			aux[j] = '\0';
			if(k!=-1){
				if(retornaEntradaSaida(lista, aux, &entrada, &saida, k))
					printf(MSG_EXIBE_HORARIO, entrada.horas, entrada.minutos, saida.horas, saida.minutos);
				else
					printf(MSG_NAO_EXISTE_PLC);
			}
			else
				printf(MSG_NAO_EXISTE_REL);
			free(aux);
		}

		else if(op!=4)
			printf(MSG_OPCAO_INV);
		scanf("%d", &op);
	}
	liberaMemoria(lista);
	free(lista);

	return (0);
}



/* ================================================================== */
/* ========== FUNCOES QUE DETERMINAM AS OPERACOES POSSIVEIS ========= */
/* ================================================================== */

void iniciaLista(Lista *lista){
	lista->inicio = NULL;
	lista->tamanho = 0;
}

int listaVazia(Lista *lista){
	return(lista->inicio==NULL);
}

int adicionaNaLista(Lista *lista, char *titulo){
	if(lista->tamanho==0){
		lista->inicio = (Celula *) malloc(sizeof(Celula));
		if(lista->inicio==NULL)
			return(0);
	}
	else{
		lista->inicio = (Celula *) realloc(lista->inicio, (lista->tamanho+1)*sizeof(Celula));
		if(lista->inicio==NULL)
			return(0);
	}
	lista->inicio[lista->tamanho].titulo = titulo;
	lista->inicio[lista->tamanho].veiculos = NULL;
	lista->inicio[lista->tamanho].tam = 0;
	lista->inicio[lista->tamanho].validade = 1;
	lista->tamanho++;
	return(1);
}

int adicionaVeiculo(Lista *lista, char *placa, Horario entrada, Horario saida){
	if(lista->inicio[lista->tamanho-1].tam==0){
		lista->inicio[lista->tamanho-1].veiculos = (Veiculo *) malloc(5*sizeof(Veiculo));
		if(lista->inicio[lista->tamanho-1].veiculos==NULL)
			return(0);
	}
	else if(lista->inicio[lista->tamanho-1].tam%5==0){
		lista->inicio[lista->tamanho-1].veiculos = (Veiculo *) realloc(lista->inicio[lista->tamanho-1].veiculos,(lista->inicio[lista->tamanho-1].tam+5)*sizeof(Veiculo));
		if(lista->inicio[lista->tamanho-1].veiculos==NULL)
			return(0);
	}
	lista->inicio[lista->tamanho-1].veiculos[lista->inicio[lista->tamanho-1].tam].placa = placa;
	lista->inicio[lista->tamanho-1].veiculos[lista->inicio[lista->tamanho-1].tam].entrada = entrada;
	lista->inicio[lista->tamanho-1].veiculos[lista->inicio[lista->tamanho-1].tam].saida = saida;
	lista->inicio[lista->tamanho-1].tam++;
	return(1);
}

int verificaValidade(Lista *lista, int k){
	Horario *pilha;
	int topo, i;
	pilha = (Horario *) malloc(k*sizeof(Horario));
	if(pilha==NULL)
		return(0);
	for(i=0, topo=-1; lista->inicio[lista->tamanho-1].validade && i<lista->inicio[lista->tamanho-1].tam; i++){
		if(lista->inicio[lista->tamanho-1].veiculos[i].entrada.horas<lista->inicio[lista->tamanho-1].veiculos[i].saida.horas || 
			(lista->inicio[lista->tamanho-1].veiculos[i].entrada.horas==lista->inicio[lista->tamanho-1].veiculos[i].saida.horas && 
				lista->inicio[lista->tamanho-1].veiculos[i].entrada.minutos<lista->inicio[lista->tamanho-1].veiculos[i].saida.minutos)){
			if(lista->inicio[lista->tamanho-1].veiculos[i].entrada.horas>=6 && lista->inicio[lista->tamanho-1].veiculos[i].saida.horas>=6){
				if(lista->inicio[lista->tamanho-1].veiculos[i].entrada.horas<22 && (lista->inicio[lista->tamanho-1].veiculos[i].saida.horas<22 || 
					(lista->inicio[lista->tamanho-1].veiculos[i].saida.horas==22 && lista->inicio[lista->tamanho-1].veiculos[i].saida.minutos==0))){
					if(topo==-1 ||
						((pilha[topo].horas!=lista->inicio[lista->tamanho-1].veiculos[i].entrada.horas || pilha[topo].minutos!=lista->inicio[lista->tamanho-1].veiculos[i].entrada.minutos)
						&& (pilha[topo].horas!=lista->inicio[lista->tamanho-1].veiculos[i].saida.horas || pilha[topo].minutos!=lista->inicio[lista->tamanho-1].veiculos[i].saida.minutos))){
						while(topo!=-1 && (lista->inicio[lista->tamanho-1].veiculos[i].entrada.horas>pilha[topo].horas || 
							(lista->inicio[lista->tamanho-1].veiculos[i].entrada.horas==pilha[topo].horas &&
							 lista->inicio[lista->tamanho-1].veiculos[i].entrada.minutos>pilha[topo].minutos))){
							topo--;
						}
						if(topo==-1 || topo<k-1 && (lista->inicio[lista->tamanho-1].veiculos[i].saida.horas<pilha[topo].horas || 
							(lista->inicio[lista->tamanho-1].veiculos[i].saida.horas==pilha[topo].horas &&
							lista->inicio[lista->tamanho-1].veiculos[i].saida.minutos<pilha[topo].minutos)))
						{
							topo++;
							pilha[topo] = lista->inicio[lista->tamanho-1].veiculos[i].saida;
						}
						else
							lista->inicio[lista->tamanho-1].validade = 0;
					}
					else
						lista->inicio[lista->tamanho-1].validade = 0;
				}
				else
					lista->inicio[lista->tamanho-1].validade = 0;
			}
			else
				lista->inicio[lista->tamanho-1].validade = 0;
		}
		else
			lista->inicio[lista->tamanho-1].validade = 0;
	}
	free(pilha);
	return(1);
}

int procuraTitulo(Lista *lista, char *titulo){
	int i;
	for(i=0; i<lista->tamanho; i++){
		if(strcmp(titulo, lista->inicio[i].titulo)==0)
			return(i);
	}
	return(-1);
}

int retornaEntradaSaida(Lista *lista, char *placa, Horario *entrada, Horario *saida, int k){
	int i;
	for(i=0; i<lista->inicio[k].tam; i++){
		if(strcmp(lista->inicio[k].veiculos[i].placa, placa)==0){
			*entrada = lista->inicio[k].veiculos[i].entrada;
			*saida = lista->inicio[k].veiculos[i].saida;
			return(1);
		}
	}
	return(0);
}

void liberaMemoria(Lista *lista){
	Celula *aux;
	int i, j;

	for(i=0; i<lista->tamanho; i++){
		for(j=0; j<lista->inicio[i].tam; j++)
			free(lista->inicio[i].veiculos[j].placa);
		free(lista->inicio[i].titulo);
		free(lista->inicio[i].veiculos);
	}
	free(lista->inicio);
}

boolean retornaValidade(Lista *lista, int k){
	return(lista->inicio[k].validade);
}