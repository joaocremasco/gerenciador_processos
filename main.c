#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "heap.h"

void comando_add(HEAP *heap_prioridade, HEAP *heap_tempo);
void comando_exec(HEAP *heap_prioridade, HEAP *heap_tempo);
void comando_next(HEAP *heap_prioridade, HEAP *heap_tempo);
void comando_change(HEAP *heap_prioridade, HEAP *heap_tempo);
void comando_print(HEAP *heap_prioridade, HEAP *heap_tempo);

int main(void)
{

    HEAP *heap_prioridade = heap_criar(0);
    if(heap_prioridade == NULL) {
        return EXIT_FAILURE;
    }

    HEAP *heap_tempo = heap_criar(1);
    if(heap_tempo == NULL) {
        heap_apagar(&heap_prioridade);
        return EXIT_FAILURE;
    }

    char comando[16];

    while(scanf(" %15s", comando) == 1)
    {

        if (!strcmp(comando, "add"))
        {
            comando_add(heap_prioridade, heap_tempo);
        }
        else if (!strcmp(comando, "exec"))
        {
            comando_exec(heap_prioridade, heap_tempo);
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

    heap_apagar_processos(heap_prioridade);
    heap_apagar_processos(heap_tempo);
    heap_apagar(&heap_prioridade);
    heap_apagar(&heap_tempo);

    return 0;
}

void comando_add(HEAP *heap_prioridade, HEAP *heap_tempo) {
    int priority, hora, minutos, segundos;
    char nome[MAX_DESCR];

    scanf(" %d %d:%d:%d %50[^\r\n]", &priority, &hora, &minutos, &segundos, nome);

    horario t = {hora, minutos, segundos};

    // assumimos aqui que inserir nao vai falhar
    heap_inserir(heap_prioridade, processo_criar(priority, t, nome));
    heap_inserir(heap_tempo, processo_criar(priority, t, nome));
}

void comando_exec(HEAP *heap_prioridade, HEAP *heap_tempo) {
    char c;
    scanf(" -%c", &c);

    celula *p, *outro;

    if(c == 'p') {
        p = heap_remover_raiz(heap_prioridade);
        if(p == NULL)
            return;
        outro = heap_remover_item(heap_tempo, processo_get_priority(p), NULL);
    } 
    else {
        p = heap_remover_raiz(heap_tempo);
        if(p == NULL) 
            return;
        horario t = processo_get_tempo(p);
        outro = heap_remover_item(heap_prioridade, -1, &t);
    }
    processo_apagar(&p);
    processo_apagar(&outro);
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

        heap_modificar(heap_prioridade, ant_priority, NULL, novo_priority, NULL);
        heap_modificar(heap_tempo, ant_priority, NULL, novo_priority, NULL);
    } 
    else {
        int hora, minutos, segundos;
        int novo_hora, novo_minutos, novo_segundos;

        scanf(" %d:%d:%d|%d:%d:%d", &hora, &minutos, &segundos, &novo_hora, &novo_minutos, &novo_segundos);

        horario targ_tempo = {hora, minutos, segundos};
        horario novo_tempo = {novo_hora, novo_minutos, novo_segundos};

        heap_modificar(heap_prioridade, -1, &targ_tempo, -1, &novo_tempo);
        heap_modificar(heap_tempo, -1, &targ_tempo, -1, &novo_tempo);
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

    printf("\n");
}