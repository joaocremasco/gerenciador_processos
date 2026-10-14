#include <stdlib.h>
#include <string.h>
#include "heap.h"

struct heap_
{
    celula **vetor;
    int tamanho;
    int capacidade;
    int tipo; // 0 e max heap (prioridade) e 1 min heap (tempo)
};

static void heapify_up(HEAP *heap, int i);
static void heapify_down(HEAP *heap, int i);
static int heap_buscar(HEAP *heap, int targ_priority, const horario *targ_tempo);

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

celula *heap_remover_raiz(HEAP *heap) {
    if(heap == NULL || heap->tamanho == 0)
        return NULL;

    celula *removido = heap->vetor[0];
    heap->vetor[0] = heap->vetor[heap->tamanho - 1];
    heap->tamanho--;

    heapify_down(heap, 0);

    return removido;
}

celula *heap_remover_item(HEAP *heap, int targ_priority, const horario *targ_tempo) {
    if(heap == NULL)
        return NULL;

    int i = heap_buscar(heap, targ_priority, targ_tempo);

    if(i == -1)
        return NULL;

    celula *removido = heap->vetor[i];
    heap->vetor[i] = heap->vetor[heap->tamanho - 1];
    heap->tamanho--;

    heapify_down(heap, i);
    if(i < heap->tamanho)
        heapify_up(heap, i);

    return removido;
}

bool heap_inserir(HEAP *heap, celula *item) {
    if(heap == NULL || item == NULL)
        return false;
    
    if(heap->tamanho == heap->capacidade) {
        int nova_capacidade = (heap->capacidade == 0) ? 16 : heap->capacidade * 2; // 16 processos iniciais
        celula **novo_vetor = realloc(heap->vetor, nova_capacidade * sizeof(*novo_vetor));
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

    processo_imprimir(heap->vetor[0]);
}

static int comparar_impressao(int tipo, celula *a, celula *b) {
    if(tipo == 0)
        return processo_get_priority(b) - processo_get_priority(a);
    return tempo_comparar(processo_get_tempo(a), processo_get_tempo(b));
}

static int quick_sort_partition(celula **v, int low, int high, int tipo) {
    celula *pivot = v[low + (high - low) / 2];
    int i = low - 1;
    int j = high + 1;

    while(1) {
        do i++; 
        while(comparar_impressao(tipo, v[i], pivot) < 0);
        do j--; 
        while(comparar_impressao(tipo, v[j], pivot) > 0);

        if(i >= j)
            return j;

        celula *tmp = v[i];
        v[i] = v[j];
        v[j] = tmp;
    }
}

static void quick_sort(celula **v, int low, int high, int tipo) {
    if(low >= high)
        return;

    int p = quick_sort_partition(v, low, high, tipo);
    quick_sort(v, low, p, tipo);
    quick_sort(v, p + 1, high, tipo);
}

void heap_imprimir(const HEAP *heap) {
    if(heap == NULL || heap->tamanho == 0)
        return;

    celula **copia = malloc(heap->tamanho * sizeof(*copia));
    if(copia == NULL)
        return;

    memcpy(copia, heap->vetor, heap->tamanho * sizeof(*copia));
    quick_sort(copia, 0, heap->tamanho - 1, heap->tipo);

    for(int i = 0; i < heap->tamanho; i++)
        processo_imprimir(copia[i]);

    free(copia);
}

static int heap_buscar(HEAP *heap, int targ_priority, const horario *targ_tempo) {
    if(heap == NULL)
        return -1;
    
    for(int i = 0; i < heap->tamanho; i++) {

        int priority_atual = processo_get_priority(heap->vetor[i]);
        horario tempo_atual = processo_get_tempo(heap->vetor[i]);

        if(targ_priority != -1 && priority_atual == targ_priority)
            return i;

        if(targ_tempo != NULL && tempo_comparar(tempo_atual, *targ_tempo) == 0)
            return i;
    }

    return -1;
}

bool heap_modificar(HEAP *heap, int targ_priority, const horario *targ_tempo, int novo_priority, const horario *novo_tempo) {
    if(heap == NULL)
        return false;

    int i = heap_buscar(heap, targ_priority, targ_tempo);

    if(i == -1)
        return false;

    if(targ_priority != -1 && novo_priority != -1) {
        int priority_atual = processo_get_priority(heap->vetor[i]);
        processo_set_priority(heap->vetor[i], novo_priority);

        if(novo_priority > priority_atual)
            heapify_up(heap, i);
        else
            heapify_down(heap, i);

        return true;
    }

    if(targ_tempo != NULL && novo_tempo != NULL) {
        horario tempo_atual = processo_get_tempo(heap->vetor[i]);
        processo_set_tempo(heap->vetor[i], *novo_tempo);

        if(tempo_comparar(*novo_tempo, tempo_atual) < 0)
            heapify_up(heap, i);
        else
            heapify_down(heap, i);

        return true;
    }

    return false;
}

static void heapify_up(HEAP *heap, int i)
{
    if(heap->tipo == 0) {
        while(i > 0)
        {
            int pai = (i - 1) / 2;

            if(processo_get_priority(heap->vetor[i]) <= processo_get_priority(heap->vetor[pai]))
                break;

            celula *aux = heap->vetor[i];
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

            celula *aux = heap->vetor[i];
            heap->vetor[i] = heap->vetor[pai];
            heap->vetor[pai] = aux;

            i = pai;
        }
    }
}

static void heapify_down(HEAP *heap, int i)
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

            celula *aux = heap->vetor[i];
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

            celula *aux = heap->vetor[i];
            heap->vetor[i] = heap->vetor[menor];
            heap->vetor[menor] = aux;

            i = menor;
        }
    }
}
