#ifndef HEAP_H
#define HEAP_H
#include "tempo.h"
#include "processo.h"
#include <stdbool.h>

typedef struct heap_ HEAP;

HEAP *heap_criar(int tipo);
void heap_apagar(HEAP **heap);
bool heap_inserir(HEAP *heap, PROCESSO *item);
// PROCESSO *heap_remover(HEAP *heap); precisamos disso?
bool heap_vazia(const HEAP *heap);
int heap_tamanho(const HEAP *heap);
bool heap_modificar(HEAP *heap, int i, int targ_priority, TEMPO *targ_tempo, int novo_priority, TEMPO *novo_tempo);
void heap_imprimir(const HEAP *heap); //implementação deve ser feita com mergesort

#endif