#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
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
int heap_buscar(HEAP *heap, int targ_priority, TEMPO *targ_tempo);

HEAP *heap_criar(int tipo){
    HEAP *heap = malloc(sizeof(*heap));
    if (heap == NULL) return NULL;
    
    heap->vetor = NULL;
    heap->tamanho = 0;
    heap->capacidade = 0;
    heap->tipo = tipo;

    return heap;
}

// nao apaga os processos tem q liberar dps
void heap_apagar(HEAP **heap){
    if (heap == NULL || *heap == NULL)
        return;

    free((*heap)->vetor);
    free(*heap);
    *heap = NULL;
}

void heap_apagar_processos(HEAP *heap) {
    if(heap == NULL)
        return;

    for(int i = 0; i < (heap)->tamanho; i++) {
        processo_apagar(&((heap)->vetor[i]));
    }

    heap->tamanho = 0;
}

int heap_tamanho(const HEAP *heap) {
    return heap->tamanho;
}

bool heap_vazia(const HEAP *heap) {
    return heap->tamanho == 0;
}

PROCESSO *heap_remover_raiz(HEAP *heap) {
    if(heap == NULL || heap->tamanho == 0)
        return NULL;

    PROCESSO *removido = heap->vetor[0];
    heap->vetor[0] = heap->vetor[heap->tamanho - 1];
    heap->tamanho--;

    heapify_down(heap, 0);

    return removido;
}

PROCESSO *heap_remover_item(HEAP *heap, int targ_priority, TEMPO *targ_tempo) {
    if(heap == NULL)
        return NULL;

    int i = heap_buscar(heap, targ_priority, targ_tempo);

    if(i == -1)
        return NULL;

    PROCESSO *removido = heap->vetor[i];
    heap->vetor[i] = heap->vetor[heap->tamanho - 1];
    heap->tamanho--;

    heapify_down(heap, i);
    heapify_up(heap, i);

    return removido;
}

bool heap_inserir(HEAP *heap, PROCESSO *item) {
    if(heap == NULL || item == NULL)
        return false;
    
    if(heap->tamanho == heap->capacidade) {
        int nova_capacidade = (heap->capacidade == 0) ? 16 : heap->capacidade * 2; // 16 processos iniciais
        PROCESSO **novo_vetor = realloc(heap->vetor, nova_capacidade * sizeof(*novo_vetor));
        if(novo_vetor == NULL)
            return false;
        heap->vetor = novo_vetor;
        heap->capacidade = nova_capacidade;
    }

    heap->vetor[heap->tamanho] = item;
    heap->tamanho++;

    heapify_up(heap, heap->tamanho - 1);

    return true;
}

void heap_print_root(const HEAP *heap) {
    if(heap == NULL || heap->tamanho == 0)
        return;

    printf("%02d ", processo_get_priority(heap->vetor[0]));
    tempo_imprimir(processo_get_tempo(heap->vetor[0]));
    printf(" %s\n", processo_get_nome(heap->vetor[0]));
}

void heap_imprimir(const HEAP *heap) {
    if(heap == NULL || heap->tamanho == 0)
        return;

    HEAP *heap2 = malloc(sizeof(*heap));

    if(heap2 == NULL)
        return;

    heap2->tamanho = heap->tamanho;
    heap2->capacidade = heap->capacidade;
    heap2->tipo = heap->tipo;

    heap2->vetor = malloc(heap->tamanho * sizeof(*(heap->vetor)));
    
    if(heap2->vetor == NULL) {
        free(heap2);
        return;
    }

    memcpy(heap2->vetor, heap->vetor, heap->tamanho * sizeof(*(heap->vetor)));
    
    for(int i = heap2->tamanho - 1; i >= 0; i--) {
        printf("%02d ", processo_get_priority(heap2->vetor[0]));
        tempo_imprimir(processo_get_tempo(heap2->vetor[0]));
        printf(" %s\n", processo_get_nome(heap2->vetor[0]));

        heap2->vetor[0] = heap2->vetor[i];
        heap2->tamanho--;
        heapify_down(heap2, 0);
    }

    heap_apagar(&heap2);
}

int heap_buscar(HEAP *heap, int targ_priority, TEMPO *targ_tempo) {
    if(heap == NULL)
        return -1;
    
    for(int i = 0; i < heap->tamanho; i++) {

        int priority_atual = processo_get_priority(heap->vetor[i]);
        TEMPO* tempo_atual = processo_get_tempo(heap->vetor[i]);
        
        if((targ_priority != -1 && priority_atual == targ_priority)) {
            return i;
        }

        if((targ_tempo != NULL && tempo_comparar(tempo_atual, targ_tempo) == 0)) {
            return i;
        }
    }

    return -1;
}

bool heap_modificar(HEAP *heap, int targ_priority, TEMPO *targ_tempo, int novo_priority, TEMPO *novo_tempo) {
    if(heap == NULL)
        return false;

    int i = heap_buscar(heap, targ_priority, targ_tempo);

    if(i == -1)
        return false;
    
    int priority_atual = processo_get_priority(heap->vetor[i]);
    TEMPO* tempo_atual = processo_get_tempo(heap->vetor[i]);
    
    if((targ_priority != -1 && priority_atual == targ_priority)) {
        if(novo_priority != -1) {
            processo_set_priority(heap->vetor[i], novo_priority);
            
            if(novo_priority > priority_atual)
                heapify_up(heap, i);
            else
                heapify_down(heap, i);
            
            return true;
        }
    }

    if((targ_tempo != NULL && tempo_comparar(tempo_atual, targ_tempo) == 0)) {
        if(novo_tempo != NULL)  {
            if(tempo_comparar(novo_tempo, tempo_atual) < 0) {
                processo_set_tempo(heap->vetor[i], novo_tempo);
                heapify_up(heap, i);
            }
            else {
                processo_set_tempo(heap->vetor[i], novo_tempo);
                heapify_down(heap, i);
            }

            return true;
        }
    }

    return false;
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
