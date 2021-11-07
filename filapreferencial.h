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
