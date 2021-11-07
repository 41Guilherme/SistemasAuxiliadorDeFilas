#include "filapreferencial.c"

void main() {
	PFILA f = criarFila();
	int id;
	bool ehPreferencial;
	bool res;
    exibirLog(f);
	res = inserirPessoaNaFila(f, 1, true);
	if(res) printf("Insercao retornou true (0).\n");
	else printf("Insercao retornou false (0). [OK]\n");
	exibirLog(f);
    
}  