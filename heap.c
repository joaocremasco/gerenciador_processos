#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include "processo.h"
#include "tempo.h"

struct heap_
{
    PROCESSO **vetor;
    int tamanho;
    int capacidade;
    int tipo;
};

HEAP *heap_criar(int tipo){
    HEAP *heap = malloc(sizeof(*heap));
    if (heap == NULL) return NULL;
    
    heap->vetor = NULL;
    heap->tamanho = 0;
    heap->capacidade = 0;
    heap->tipo = tipo;

    return heap;
}

void heap_apagar(HEAP **heap){
    if (heap == NULL || *heap == NULL)
        return;



}
    
void heapify_up(HEAP *heap, int i)
{
    while (i > 0)
    {
        int pai = (i - 1) / 2;

        if (heap->vetor[i] <= heap->vetor[pai])
            break;

        int aux = heap->vetor[i];
        heap->vetor[i] = heap->vetor[pai];
        heap->vetor[pai] = aux;

        i = pai;
    }
}

void heapify_down(HEAP *heap, int i)
{
    while (2 * i + 1 < heap->tamanho)
    {
        int esq = 2 * i + 1;
        int dir = 2 * i + 2;
        int maior = esq;

        if (dir < heap->tamanho &&
            heap->vetor[dir] > heap->vetor[esq])
        {
            maior = dir;
        }

        if (heap->vetor[i] >= heap->vetor[maior])
            break;

        int aux = heap->vetor[i];
        heap->vetor[i] = heap->vetor[maior];
        heap->vetor[maior] = aux;

        i = maior;
    }
}