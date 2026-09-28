#ifndef HEAP_H
#define HEAP_H
#include "tempo.h"
#include "processo.h"

typedef struct heap_ HEAP;

HEAP *heap_criar(int tipo);
void heap_apagar(HEAP **heap);
int heap_inserir(HEAP *heap, PROCESSO *item);
PROCESSO *heap_remover(HEAP *heap);
int heap_vazia(const HEAP *heap);
int heap_tamanho(const HEAP *heap);
void heap_imprimir(const HEAP *heap); //implementação deve ser feita com mergesort

#endif