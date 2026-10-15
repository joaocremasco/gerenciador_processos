#ifndef HEAP_H
#define HEAP_H
#include "processo.h"
#include <stdbool.h>

typedef struct heap_ HEAP;

HEAP *heap_criar(int tipo);
void heap_apagar(HEAP **heap);
bool heap_inserir(HEAP *heap, celula *item);
celula *heap_remover_raiz(HEAP *heap);
celula *heap_remover_por_prioridade(HEAP *heap, int prior);
celula *heap_remover_por_tempo(HEAP *heap, horario tempo);
bool heap_alterar_prioridade(HEAP *heap, int anterior, int novo);
bool heap_alterar_tempo(HEAP *heap, horario anterior, horario novo);
void heap_imprimir(const HEAP *heap);
void heap_print_root(const HEAP *heap);
void heap_apagar_processos(HEAP *heap);

#endif