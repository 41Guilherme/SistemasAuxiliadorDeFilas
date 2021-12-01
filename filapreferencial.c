/*********************************************************************/
/**   ACH2023 - Algoritmos e Estruturas de Dados I                  **/
/**   EACH-USP - Segundo Semestre de 2021                           **/
/**   Turma 04 - Prof. Luciano Antonio Digiampietri                 **/
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

	PONT x = buscarID(f,id);  // Verificação inicial para saber se 
	if (x != NULL || id < 0){ // o id já esta cadastrado ou se é negativo
		return false;
	}
	
	//Alocação de memoria para o novo membro da fila
	PONT novoElemento = (PONT) malloc(sizeof(ELEMENTO));
	
	novoElemento->id = id;                         // Id do membro da fila
	novoElemento->ehPreferencial = ehPreferencial; // Preferencialidade do membro da fila
	
	PONT aux = f->cabeca; // Variavel auxiliar para inserir na fila

    if (ehPreferencial == true){
		//Inserção do preferencial 
        while(aux){

            if(aux->prox == f->cabeca || aux->prox->ehPreferencial == false){

                novoElemento->prox = aux->prox; // arrumando os ponteiros do elemento inserido
                novoElemento->ant = aux;

                aux->prox->ant = novoElemento; // arrumando os ponteiros dos elementos que já estão na fila
                aux->prox = novoElemento;
                
                return true;

            }else{
                aux = aux->prox; // Muda o auxiliar
            }
        }
    }else{
        //Inserção do não preferencial 
        while (aux){
            
            if(aux->prox == f->cabeca){

                novoElemento->prox = f->cabeca; // arrumando os ponteiros do elemento inserido
                novoElemento->ant = aux;

                aux->prox = novoElemento;   // arrumando os ponteiros dos elementos que já estão na fila
                f->cabeca->ant = novoElemento;

				// Ponteiro que identifica o começo dos não preferenciais
                if(f->inicioNaoPref->prox == f->cabeca) {
                    f->inicioNaoPref->prox = novoElemento; 
                }

                return true;

            }else{
                aux = aux->prox; // Muda o auxiliar
            }
        }
        
    }

	

}

bool atenderPrimeiraDaFila(PFILA f, int* id){

	// Verifica se a fila já esta vazia
    int tam = tamanho(f);
	if (tam <= 0){
		return false; // retorna false caso não tenha ninguem
	}

	*id = f->cabeca->prox->id; // Aloca o ID da pessoa a ser atendida
	PONT aux;
	aux = f->cabeca->prox;
	if(aux->prox->ehPreferencial == false ){
		f->inicioNaoPref->prox = aux->prox; // Muda o ponteiro do
	}										// inicioNaoPref se necessário 
	f->cabeca->prox = aux->prox;
	aux->prox->ant = f->cabeca;
	aux = NULL;  // Libera memoria 
	
	return true;

}


bool desistirDaFila(PFILA f, int id){
	// Verifica se o id existe na Fila
    PONT verifica = buscarID(f,id);
	if (verifica == NULL) return false;

    PONT aux = buscarID(f,id); 

    PONT antecessor = aux->ant; // PONT de quem esta antes do desistente
    PONT sucessor = aux->prox;  // PONT de quem esta depois do desistente

	if(f->inicioNaoPref->prox == aux){
		f->inicioNaoPref->prox = sucessor; // Muda o inicioNaoPref se necessário
	}
	// Fazemos os ponteiros 'pularem' o desistente 
    antecessor->prox = sucessor;
    sucessor->ant = antecessor;

    aux = NULL; // Libera memoria
	return true;
}


