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
static int buscar_prioridade(const HEAP *heap, int prior);
static int buscar_tempo(const HEAP *heap, horario tempo);
static celula *remover_indice(HEAP *heap, int i);

// true se a deve ficar antes de b: maior prioridade (tipo 0) ou menor horario (tipo 1)
static bool antes(int tipo, const celula *a, const celula *b) {
    if(tipo == 0)
        return processo_get_priority(a) > processo_get_priority(b);
    return tempo_comparar(processo_get_tempo(a), processo_get_tempo(b)) < 0;
}

static void trocar(celula **a, celula **b) {
    celula *aux = *a;
    *a = *b;
    *b = aux;
}

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

// remove o item da posicao i (usado pelas duas remocoes por busca)
static celula *remover_indice(HEAP *heap, int i) {
    celula *removido = heap->vetor[i];
    heap->vetor[i] = heap->vetor[heap->tamanho - 1];
    heap->tamanho--;

    heapify_down(heap, i);
    if(i < heap->tamanho)
        heapify_up(heap, i);

    return removido;
}

celula *heap_remover_por_prioridade(HEAP *heap, int prior) {
    if(heap == NULL)
        return NULL;

    int i = buscar_prioridade(heap, prior);
    if(i == -1)
        return NULL;

    return remover_indice(heap, i);
}

celula *heap_remover_por_tempo(HEAP *heap, horario tempo) {
    if(heap == NULL)
        return NULL;

    int i = buscar_tempo(heap, tempo);
    if(i == -1)
        return NULL;

    return remover_indice(heap, i);
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

        trocar(&v[i], &v[j]);
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

// busca linear: retorna o indice ou -1 se nao existir (prioridades e horarios sao unicos)
static int buscar_prioridade(const HEAP *heap, int prior) {
    for(int i = 0; i < heap->tamanho; i++) {
        if(processo_get_priority(heap->vetor[i]) == prior)
            return i;
    }

    return -1;
}

static int buscar_tempo(const HEAP *heap, horario tempo) {
    for(int i = 0; i < heap->tamanho; i++) {
        if(tempo_comparar(processo_get_tempo(heap->vetor[i]), tempo) == 0)
            return i;
    }

    return -1;
}

// depois de alterar o campo, so um dos dois heapify chega a mexer no item
bool heap_alterar_prioridade(HEAP *heap, int anterior, int novo) {
    if(heap == NULL)
        return false;

    int i = buscar_prioridade(heap, anterior);
    if(i == -1)
        return false;

    processo_set_priority(heap->vetor[i], novo);
    heapify_up(heap, i);
    heapify_down(heap, i);

    return true;
}

bool heap_alterar_tempo(HEAP *heap, horario anterior, horario novo) {
    if(heap == NULL)
        return false;

    int i = buscar_tempo(heap, anterior);
    if(i == -1)
        return false;

    processo_set_tempo(heap->vetor[i], novo);
    heapify_up(heap, i);
    heapify_down(heap, i);

    return true;
}

static void heapify_up(HEAP *heap, int i)
{
    while(i > 0)
    {
        int pai = (i - 1) / 2;

        if(!antes(heap->tipo, heap->vetor[i], heap->vetor[pai]))
            break;

        trocar(&heap->vetor[i], &heap->vetor[pai]);
        i = pai;
    }
}

static void heapify_down(HEAP *heap, int i)
{
    while(2 * i + 1 < heap->tamanho)
    {
        int esq = 2 * i + 1;
        int dir = 2 * i + 2;
        int melhor = esq;

        if(dir < heap->tamanho && antes(heap->tipo, heap->vetor[dir], heap->vetor[esq]))
            melhor = dir;

        if(!antes(heap->tipo, heap->vetor[melhor], heap->vetor[i]))
            break;

        trocar(&heap->vetor[i], &heap->vetor[melhor]);
        i = melhor;
    }
}