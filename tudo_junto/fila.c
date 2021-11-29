#include <stdlib.h>
#include <stdio.h>
#define true 1
#define false 0

typedef int bool;

typedef struct aux {
  int id;
  bool ehPreferencial;
  struct aux* ant;
  struct aux* prox;
} ELEMENTO, * PONT;


typedef struct {
  PONT cabeca;
  PONT inicioNaoPref;
} FILAPREFERENCIAL, * PFILA;


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

int main() {
	PFILA f = criarFila();
	int id;
	bool ehPreferencial;
	bool res;
    
	printf("################# INSERINDO #######################\n");

	exibirLog(f);
	res = inserirPessoaNaFila(f, -1, false);
	if(res) printf("Insercao retornou true (0).\n");
	else printf("Insercao retornou false (0). [OK]\n");
	exibirLog(f);
	res = inserirPessoaNaFila(f, 1, false);
	if(res) printf("Insercao retornou true (1). [OK]\n");
	else printf("Insercao retornou false (1).\n");
	exibirLog(f);
	res = inserirPessoaNaFila(f, 2, false);
	if(res) printf("Insercao retornou true (2). [OK]\n");
	else printf("Insercao retornou false (2).\n");
	exibirLog(f);
	res = inserirPessoaNaFila(f, 3, false);
	if(res) printf("Insercao retornou true (3). [OK]\n");
	else printf("Insercao retornou false (3).\n");
	exibirLog(f);
	res = inserirPessoaNaFila(f, 4, true);
	if(res) printf("Insercao retornou true (4). [OK]\n");
	else printf("Insercao retornou false (4).\n");
	exibirLog(f);
	res = inserirPessoaNaFila(f, 5, true);
	if(res) printf("Insercao retornou true (5). [OK]\n");
	else printf("Insercao retornou false (5).\n");
	exibirLog(f);
	res = inserirPessoaNaFila(f, 6, true);
	if(res) printf("Insercao retornou true (6). [OK]\n");
	else printf("Insercao retornou false (6).\n");
	exibirLog(f);

    
	printf("################# ATENDENDO #######################\n");
	exibirLog(f);
	res = atenderPrimeiraDaFila(f, &id);
	if(res) printf("Atendimento retornou true (7), id=%i. [OK]\n",id);
	else printf("Atendimento retornou false (7).\n");

	exibirLog(f);
	res = atenderPrimeiraDaFila(f, &id);
	if(res) printf("Atendimento retornou true (8), id=%i. [OK]\n",id);
	else printf("Atendimento retornou false (8).\n");

	exibirLog(f);
	res = atenderPrimeiraDaFila(f, &id);
	if(res) printf("Atendimento retornou true (9), id=%i. [OK]\n",id);
	else printf("Atendimento retornou false (9).\n");

	exibirLog(f);
	res = atenderPrimeiraDaFila(f, &id);
	if(res) printf("Atendimento retornou true (10), id=%i. [OK]\n",id);
	else printf("Atendimento retornou false (10).\n");

	exibirLog(f);
	res = atenderPrimeiraDaFila(f, &id);
	if(res) printf("Atendimento retornou true (11), id=%i. [OK]\n",id);
	else printf("Atendimento retornou false (11).\n");

	exibirLog(f);
	res = atenderPrimeiraDaFila(f, &id);
	if(res) printf("Atendimento retornou true (12), id=%i. [OK]\n",id);
	else printf("Atendimento retornou false (12).\n");

	exibirLog(f);
	res = atenderPrimeiraDaFila(f, &id);
	if(res) printf("Atendimento retornou true (13), id=%i.\n",id);
	else printf("Atendimento retornou false (13). [OK]\n");
	exibirLog(f);


	printf("################# INSERINDO PARTE 2 ###############\n");

	exibirLog(f);
	res = inserirPessoaNaFila(f, 7, true);
	if(res) printf("Insercao retornou true (14). [OK]\n");
	else printf("Insercao retornou false (14).\n");
	exibirLog(f);
	res = inserirPessoaNaFila(f, 8, false);
	if(res) printf("Insercao retornou true (15). [OK]\n");
	else printf("Insercao retornou false (15).\n");
	exibirLog(f);
	res = inserirPessoaNaFila(f, 9, true);
	if(res) printf("Insercao retornou true (16). [OK]\n");
	else printf("Insercao retornou false (16).\n");
	exibirLog(f);
	res = inserirPessoaNaFila(f, 10, false);
	if(res) printf("Insercao retornou true (17). [OK]\n");
	else printf("Insercao retornou false (17).\n");
	exibirLog(f);


	printf("################# SAINDO DA FILA ##################\n");

	exibirLog(f);
	res = desistirDaFila(f, 6);
	if(res) printf("Desistindo da fila retornou true (18).\n");
	else printf("Desistindo da fila retornou false (18). [OK]\n");
	exibirLog(f);
	res = desistirDaFila(f, 7);
	if(res) printf("Desistindo da fila retornou true (19). [OK]\n");
	else printf("Desistindo da fila retornou false (19).\n");
	exibirLog(f);
	res = desistirDaFila(f, 8);
	if(res) printf("Desistindo da fila retornou true (20). [OK]\n");
	else printf("Desistindo da fila retornou false (20).\n");
	exibirLog(f);
	res = desistirDaFila(f, 9);
	if(res) printf("Desistindo da fila retornou true (21). [OK]\n");
	else printf("Desistindo da fila retornou false (21).\n");
	exibirLog(f);
	res = desistirDaFila(f, 10);
	if(res) printf("Desistindo da fila retornou true (22). [OK]\n");
	else printf("Desistindo da fila retornou false (22).\n");
	exibirLog(f);
    
	return 0;
}



