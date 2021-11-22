/*********************************************************************/
/**   ACH2023 - Algoritmos e Estruturas de Dados I                  **/
/**   EACH-USP - Segundo Semestre de 2021                           **/
/**   <turma> - Prof. Luciano Antonio Digiampietri                  **/
/**                                                                 **/
/**   EP 2 - Fila Preferencial                                      **/
/**                                                                 **/
/**   Guilherme José da Silva Nascimento      NUSP - 12543252       **/
/**                                                                 **/
/*********************************************************************/

#include "filapreferencial.h"

PFILA criarFila(){
    PFILA res = (PFILA) malloc(sizeof(FILAPREFERENCIAL));
    res->cabeca = (PONT) malloc(sizeof(ELEMENTO));
    res->inicioNaoPref = res->cabeca;
    res->cabeca->id = -1;
    res->cabeca->ehPreferencial = false;
    res->cabeca->ant = res->cabeca;
    res->cabeca->prox = res->cabeca;
    return res;
}

int tamanho(PFILA f){
	PONT atual = f->cabeca->prox;
	int tam = 0;
	while (atual != f->cabeca) {
		atual = atual->prox;
		tam++;
	}
	return tam;
}

PONT buscarID(PFILA f, int id){
	PONT atual = f->cabeca->prox;
	while (atual != f->cabeca) {
		if (atual->id == id) return atual;
		atual = atual->prox;
	}
	return NULL;
}

void exibirLog(PFILA f){
	int numElementos = tamanho(f);
	printf("\nLog fila [elementos: %i]\t- Inicio:", numElementos);
	PONT atual = f->cabeca->prox;
	while (atual != f->cabeca) {
		printf(" [%i;%i]", atual->id, atual->ehPreferencial);
		atual = atual->prox;
	}
	printf("\n                       \t-    Fim:");
	atual = f->cabeca->ant;
	while (atual != f->cabeca) {
		printf(" [%i;%i]", atual->id, atual->ehPreferencial);
		atual = atual->ant;
	}
	printf("\n\n");
}


bool consultarPreferencial(PFILA f, int id){
	PONT atual = f->cabeca->prox;
	while (atual != f->cabeca) {
		if (atual->id == id) return atual->ehPreferencial;
		atual = atual->prox;
	}
	return -1;
}



bool inserirPessoaNaFila(PFILA f, int id, bool ehPreferencial){
	PONT x = buscarID(f,id);
	if (x != NULL || id < 0){
		return false;
	}
	
	PONT novoElemento = (PONT) malloc(sizeof(ELEMENTO));
	
	novoElemento->id = id;
	novoElemento->ehPreferencial = ehPreferencial;
	
	PONT aux = f->cabeca;
	if (ehPreferencial == true){
		
		while(aux){

			if(aux->prox == f->cabeca){
				novoElemento->prox = f->cabeca;
				novoElemento->ant = aux;
				
				aux->prox = novoElemento;
				f->cabeca->ant = novoElemento;
				return true;
			}else{
				aux = aux->prox;
			}

		}

	}else{
		
		while(aux){

			if(aux->prox == f->cabeca){
				novoElemento->prox = f->cabeca;
				novoElemento->ant = aux;
				
				aux->prox = novoElemento;
				f->cabeca->ant = novoElemento;
				return true;
			}else{
				aux = aux->prox;
			}

		}
		
	}
	
	
}

bool atenderPrimeiraDaFila(PFILA f, int* id){

	/* COMPLETE */


	return false;
}


bool desistirDaFila(PFILA f, int id){

	/* COMPLETE */


	return false;
}

