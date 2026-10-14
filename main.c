#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "heap.h"
#include "tempo.h"
#include "processo.h"

void comando_add(HEAP *heap_prioridade, HEAP *heap_tempo);
void comando_exec(HEAP *heap_prioridade, HEAP *heap_tempo);
void comando_next(HEAP *heap_prioridade, HEAP *heap_tempo);
void comando_change(HEAP *heap_prioridade, HEAP *heap_tempo);
void comando_print(HEAP *heap_prioridade, HEAP *heap_tempo);

int main(void)
{

    HEAP *heap_prioridade = heap_criar(0);
    HEAP *heap_tempo = heap_criar(1);

    char comando[16];

    while(scanf(" %15s", comando))
    {

        if (!strcmp(comando, "add"))
        {
            comando_add(heap_prioridade, heap_tempo);
        }
        else if (!strcmp(comando, "exec"))
        {
            comando_exec(heap_prioridade, heap_tempo);
            // exec nao faz nada ?? wtf
        }
        else if (!strcmp(comando, "next"))
        {
            comando_next(heap_prioridade, heap_tempo);
        }
        else if (!strcmp(comando, "change"))
        {
            comando_change(heap_prioridade, heap_tempo);
        }
        else if (!strcmp(comando, "print"))
        {
            comando_print(heap_prioridade, heap_tempo);
        }
        else
        {
            break;
        }
    }

    heap_apagar(&heap_prioridade);
    heap_apagar(&heap_tempo);

    return 0;
}

void comando_add(HEAP *heap_prioridade, HEAP *heap_tempo) {
    int priority, hora, minutos, segundos;
    char nome[MAX_DESCR];

    scanf(" %d %d:%d:%d %255s", &priority, &hora, &minutos, &segundos, nome);

    PROCESSO *p = processo_criar(priority, tempo_criar(hora, minutos, segundos), nome);
    heap_inserir(heap_prioridade, p);
    heap_inserir(heap_tempo, p);
}

void comando_exec(HEAP *heap_prioridade, HEAP *heap_tempo) {
    char c;
    scanf(" -%c", &c);

    return;
}

void comando_next(HEAP *heap_prioridade, HEAP *heap_tempo) {
    char c;
    
    scanf(" -%c", &c);

    if(c == 'p') {
        heap_print_root(heap_prioridade);
    } 
    else {
        heap_print_root(heap_tempo);
    }

    printf("\n");
}

void comando_change(HEAP *heap_prioridade, HEAP *heap_tempo) {
    char c;
    
    scanf(" -%c", &c);

    if(c == 'p') {
        int ant_priority, novo_priority;
        scanf(" %d|%d", &ant_priority, &novo_priority);
        heap_modificar(heap_prioridade, 0, ant_priority, NULL, novo_priority, NULL);
        heap_modificar(heap_tempo, 0, ant_priority, NULL, novo_priority, NULL);
    } 
    else {
        int hora, minutos, segundos;
        int novo_hora, novo_minutos, novo_segundos;
        scanf(" %d:%d:%d|%d:%d:%d", &hora, &minutos, &segundos, &novo_hora, &novo_minutos, &novo_segundos);
        TEMPO *targ_tempo = tempo_criar(hora, minutos, segundos);
        TEMPO *novo_tempo = tempo_criar(novo_hora, novo_minutos, novo_segundos);
        if(!heap_modificar(heap_prioridade, 0, NULL, targ_tempo, NULL, novo_tempo)) {
            tempo_apagar(&targ_tempo);
            tempo_apagar(&novo_tempo);
        }
        if(!heap_modificar(heap_tempo, 0, NULL, targ_tempo, NULL, novo_tempo)) {
            tempo_apagar(&targ_tempo);
            tempo_apagar(&novo_tempo);
        }
    }
}

void comando_print(HEAP *heap_prioridade, HEAP *heap_tempo) {
    char c;
    
    scanf(" -%c", &c);

    if(c == 'p') {
        heap_imprimir(heap_prioridade);
    } 
    else {
        heap_imprimir(heap_tempo);
    }
}