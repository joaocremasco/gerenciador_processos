#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "heap.h"
#include "processo.h"
#include "tempo.h"

struct heap_
{
    PROCESSO **vetor;
    int tamanho;
    int capacidade;
    int tipo; // 0 e max heap (prioridade) e 1 min heap (tempo)
};

void heapify_up(HEAP *heap, int i);
void heapify_down(HEAP *heap, int i);

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
    
    for(int i = 0; i < (*heap)->tamanho; i++) {
        processo_apagar(&(*heap)->vetor[i]);
    }

    free((*heap)->vetor);
    free(*heap);
    *heap = NULL;
}

int heap_tamanho(const HEAP *heap) {
    return heap->tamanho;
}

bool heap_vazia(const HEAP *heap) {
    return heap->tamanho == 0;
}

bool heap_inserir(HEAP *heap, PROCESSO *item) {
    if(heap == NULL || item == NULL)
        return false;
    
    if(heap->tamanho == heap->capacidade) {
        int nova_capacidade = (heap->capacidade == 0) ? 1 : heap->capacidade * 2;
        PROCESSO **novo_vetor = realloc(heap->vetor, nova_capacidade * sizeof(*novo_vetor));
        if(novo_vetor == NULL)
            return 0;
        heap->vetor = novo_vetor;
        heap->capacidade = nova_capacidade;
    }

    heap->vetor[heap->tamanho] = item;
    heap->tamanho++;

    heapify_up(heap, heap->tamanho - 1);

    return true;
}
    
void heapify_up(HEAP *heap, int i)
{
    if(heap->tipo == 0) {
        while(i > 0)
        {
            int pai = (i - 1) / 2;

            if(processo_get_priority(heap->vetor[i]) <= processo_get_priority(heap->vetor[pai]))
                break;

            PROCESSO *aux = heap->vetor[i];
            heap->vetor[i] = heap->vetor[pai];
            heap->vetor[pai] = aux;

            i = pai;
        }
    } 
    else {
        while(i > 0)
        {
            int pai = (i - 1) / 2;

            if(tempo_comparar(processo_get_tempo(heap->vetor[i]), processo_get_tempo(heap->vetor[pai])) >= 0)
                break;

            PROCESSO *aux = heap->vetor[i];
            heap->vetor[i] = heap->vetor[pai];
            heap->vetor[pai] = aux;

            i = pai;
        }
    }
}

void heapify_down(HEAP *heap, int i)
{
    if(heap->tipo == 0) {
        while (2 * i + 1 < heap->tamanho)
        {
            int esq = 2 * i + 1;
            int dir = 2 * i + 2;
            int maior = esq;

            if (dir < heap->tamanho &&
                processo_get_priority(heap->vetor[dir]) > processo_get_priority(heap->vetor[esq]))
            {
                maior = dir;
            }

            if (processo_get_priority(heap->vetor[i]) >= processo_get_priority(heap->vetor[maior]))
                break;

            PROCESSO *aux = heap->vetor[i];
            heap->vetor[i] = heap->vetor[maior];
            heap->vetor[maior] = aux;

            i = maior;
        }
    } 
    else {
        while (2 * i + 1 < heap->tamanho)
        {
            int esq = 2 * i + 1;
            int dir = 2 * i + 2;
            int menor = esq;

            if (dir < heap->tamanho &&
                tempo_comparar(processo_get_tempo(heap->vetor[dir]), processo_get_tempo(heap->vetor[esq])) < 0)
            {
                menor = dir;
            }

            if (tempo_comparar(processo_get_tempo(heap->vetor[i]), processo_get_tempo(heap->vetor[menor])) <= 0)
                break;

            PROCESSO *aux = heap->vetor[i];
            heap->vetor[i] = heap->vetor[menor];
            heap->vetor[menor] = aux;

            i = menor;
        }
    }
}