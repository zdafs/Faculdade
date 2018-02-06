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
	struct Celula *prox;
}Celula;

typedef struct{
	Celula *inicio; /*fim*/
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
Celula *procuraTitulo(Lista *lista, char *titulo);
boolean retornaValidade(Celula *temp);
int retornaEntradaSaida(Celula *temp, char *placa, Horario *entrada, Horario *saida);
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
			if(procuraTitulo(lista, aux)==NULL){
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
					entrada.horas = (char) j;
					scanf("%d ", &j);
					entrada.minutos = (char) j;
					scanf("%dh", &j);
					saida.horas = (char) j;
					scanf("%d", &j);
					saida.minutos = (char) j;
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
			temp = procuraTitulo(lista, aux);
			if(temp!=NULL){
				if(retornaValidade(temp))
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
			temp = procuraTitulo(lista, aux);
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
			if(temp!=NULL){
				if(retornaEntradaSaida(temp, aux, &entrada, &saida))
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
}

int listaVazia(Lista *lista){
	return(lista->inicio==NULL);
}

int adicionaNaLista(Lista *lista, char *titulo){
	Celula *aux;
	aux = (Celula *) malloc(sizeof(Celula));
	if(aux==NULL)
		return(0);
	aux->titulo = titulo;
	aux->veiculos = NULL;
	aux->validade = 1;
	aux->tam = 0;
	//aux->capacidade = k;
	aux->prox = lista->inicio;
	lista->inicio = aux;
	return(1);
}

int adicionaVeiculo(Lista *lista, char *placa, Horario entrada, Horario saida){
	if(lista->inicio->tam==0){
		lista->inicio->veiculos = (Veiculo *) malloc(5*sizeof(Veiculo));
		if(lista->inicio->veiculos==NULL)
			return(0);
	}
	else if(lista->inicio->tam%5==0){
		lista->inicio->veiculos = (Veiculo *) realloc(lista->inicio->veiculos,(lista->inicio->tam+5)*sizeof(Veiculo));
		if(lista->inicio->veiculos==NULL)
			return(0);
	}
	lista->inicio->veiculos[lista->inicio->tam].placa = placa;
	lista->inicio->veiculos[lista->inicio->tam].entrada = entrada;
	lista->inicio->veiculos[lista->inicio->tam].saida = saida;
	lista->inicio->tam++;
	return(1);
}

int verificaValidade(Lista *lista, int k){
	Horario *pilha;
	int topo, i;
	pilha = (Horario *) malloc(k*sizeof(Horario));
	if(pilha==NULL)
		return(0);
	for(i=0, topo=-1; lista->inicio->validade && i<lista->inicio->tam; i++){
		if(lista->inicio->veiculos[i].entrada.horas<lista->inicio->veiculos[i].saida.horas || 
			(lista->inicio->veiculos[i].entrada.horas==lista->inicio->veiculos[i].saida.horas && 
				lista->inicio->veiculos[i].entrada.minutos<lista->inicio->veiculos[i].saida.minutos)){
			if(lista->inicio->veiculos[i].entrada.horas>=6 && lista->inicio->veiculos[i].saida.horas>=6){
				if(lista->inicio->veiculos[i].entrada.horas<22 && (lista->inicio->veiculos[i].saida.horas<22 || 
					(lista->inicio->veiculos[i].saida.horas==22 && lista->inicio->veiculos[i].saida.minutos==0))){
					if(topo==-1 ||
						((pilha[topo].horas!=lista->inicio->veiculos[i].entrada.horas || pilha[topo].minutos!=lista->inicio->veiculos[i].entrada.minutos)
						&& (pilha[topo].horas!=lista->inicio->veiculos[i].saida.horas || pilha[topo].minutos!=lista->inicio->veiculos[i].saida.minutos))){
						while(topo!=-1 && (lista->inicio->veiculos[i].entrada.horas>pilha[topo].horas || 
							(lista->inicio->veiculos[i].entrada.horas==pilha[topo].horas &&
							 lista->inicio->veiculos[i].entrada.minutos>pilha[topo].minutos))){
							topo--;
						}
						if(topo==-1 || topo<k-1 && (lista->inicio->veiculos[i].saida.horas<pilha[topo].horas || 
							(lista->inicio->veiculos[i].saida.horas==pilha[topo].horas &&
							lista->inicio->veiculos[i].saida.minutos<pilha[topo].minutos)))
						{
							topo++;
							pilha[topo] = lista->inicio->veiculos[i].saida;
						}
						else
							lista->inicio->validade = 0;
					}
					else
						lista->inicio->validade = 0;
				}
				else
					lista->inicio->validade = 0;
			}
			else
				lista->inicio->validade = 0;
		}
		else
			lista->inicio->validade = 0;
	}
	free(pilha);
	return(1);
}

Celula *procuraTitulo(Lista *lista, char *titulo){
	Celula *aux;
	for(aux=lista->inicio; aux!=NULL; aux=aux->prox){
		if(strcmp(titulo, aux->titulo)==0)
			return(aux);
	}
	return(NULL);
}

int retornaEntradaSaida(Celula *temp, char *placa, Horario *entrada, Horario *saida){
	int i;
	for(i=0; i<temp->tam; i++){
		if(strcmp(temp->veiculos[i].placa, placa)==0){
			*entrada = temp->veiculos[i].entrada;
			*saida = temp->veiculos[i].saida;
			return(1);
		}
	}
	return(0);
}

void liberaMemoria(Lista *lista){
	Celula *aux;
	int i;

	for(aux=lista->inicio; aux!=NULL; aux=lista->inicio){
		lista->inicio = lista->inicio->prox;
		for(i=0; i<aux->tam; i++)
			free(aux->veiculos[i].placa);
		free(aux->titulo);
		free(aux->veiculos);
		free(aux);
	}
}

boolean retornaValidade(Celula *temp){
	return(temp->validade);
}