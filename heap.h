#ifndef HEAP_H
#define HEAP_H
#include "tempo.h"
#include "processo.h"
#include <stdbool.h>

typedef struct heap_ HEAP;

HEAP *heap_criar(int tipo);
void heap_apagar(HEAP **heap);
bool heap_inserir(HEAP *heap, celula *item);
celula *heap_remover_raiz(HEAP *heap);
bool heap_vazia(const HEAP *heap);
int heap_tamanho(const HEAP *heap);
bool heap_modificar(HEAP *heap, int targ_priority, horario *targ_tempo, int novo_priority, horario *novo_tempo);
void heap_imprimir(const HEAP *heap); //implementação deve ser feita com mergesort // merge sort??
void heap_print_root(const HEAP *heap);
void heap_apagar_processos(HEAP *heap);
celula *heap_remover_item(HEAP *heap, int targ_priority, horario *targ_tempo);

#endif