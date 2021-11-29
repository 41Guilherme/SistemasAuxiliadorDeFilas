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
	int tam = tamanho(f);
	PONT novoElemento = (PONT) malloc(sizeof(ELEMENTO));
	
	novoElemento->id = id;
	novoElemento->ehPreferencial = ehPreferencial;
	
	PONT aux = f->cabeca;

    if (ehPreferencial == true){

        if (tam == 0) f->inicioNaoPref->prox = f->cabeca;
        while(aux){

            if(aux->prox == f->cabeca || aux->prox->ehPreferencial == false){

                novoElemento->prox = aux->prox;
                novoElemento->ant = aux;

                aux->prox->ant = novoElemento;
                aux->prox = novoElemento;
                
                if (aux->prox == f->cabeca){
                    f->cabeca->ant = novoElemento;
                    f->cabeca->prox = novoElemento;
                    
                }
                return true;

            }else{
                aux = aux->prox;
            }
        }
    }else{
        
        while (aux){
            
            if(aux->prox == f->cabeca){

                novoElemento->prox = f->cabeca;
                novoElemento->ant = aux;

                aux->prox = novoElemento;
                f->cabeca->ant = novoElemento;
                if(f->inicioNaoPref->prox == f->cabeca) {
                    f->inicioNaoPref->prox = novoElemento;
                }
                return true;
            }else{
                aux = aux->prox;
            }
        }
        
    }

	

}

bool atenderPrimeiraDaFila(PFILA f, int* id){

	
    int tam = tamanho(f);
	if (tam <= 0){
		return false;
	}

	*id = f->cabeca->prox->id;
	PONT aux;
	aux = f->cabeca->prox;

	f->cabeca->prox = aux->prox;
	aux->prox->ant = f->cabeca;
	aux = NULL;

	return true;

}


bool desistirDaFila(PFILA f, int id){
	
    PONT verifica = buscarID(f,id);
	if (verifica == NULL) return false;

    PONT aux = buscarID(f,id);

    PONT antecessor = aux->ant;
    PONT sucessor = aux->prox;

    antecessor->prox = sucessor;
    sucessor->ant = antecessor;
    aux = NULL;
	return true;
}


