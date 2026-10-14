#ifndef HEAP_H
#define HEAP_H
#include "processo.h"
#include <stdbool.h>

typedef struct heap_ HEAP;

HEAP *heap_criar(int tipo);
void heap_apagar(HEAP **heap);
bool heap_inserir(HEAP *heap, celula *item);
celula *heap_remover_raiz(HEAP *heap);
celula *heap_remover_item(HEAP *heap, int targ_priority, const horario *targ_tempo);
bool heap_modificar(HEAP *heap, int targ_priority, const horario *targ_tempo, int novo_priority, const horario *novo_tempo);
void heap_imprimir(const HEAP *heap);
void heap_print_root(const HEAP *heap);
void heap_apagar_processos(HEAP *heap);

#endif
