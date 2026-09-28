#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "heap.h"
#include "tempo.h"
#include "processo.h"

void comando_add(const char *linha, HEAP *heap_prioridade, HEAP *heap_tempo);
void comando_exec(const char *linha, HEAP *heap_prioridade, HEAP *heap_tempo);
void comando_next(const char *linha, HEAP *heap_prioridade, HEAP *heap_tempo);
void comando_change(const char *linha, HEAP *heap_prioridade, HEAP *heap_tempo);
void comando_print(const char *linha, HEAP *heap_prioridade, HEAP *heap_tempo);

int main(void)
{
    char linha[100];

    HEAP *heap_prioridade = heap_criar();
    HEAP *heap_tempo = heap_criar();

    while (fgets(linha, sizeof(linha), stdin) != NULL)
    {
        char comando[10];

        sscanf(linha, "%9s", comando);

        if (!strcmp(comando, "add"))
        {
            comando_add(linha, heap_prioridade, heap_tempo);
        }
        else if (!strcmp(comando, "exec"))
        {
            comando_exec(linha, heap_prioridade, heap_tempo);
        }
        else if (!strcmp(comando, "next"))
        {
            comando_next(linha, heap_prioridade, heap_tempo);
        }
        else if (!strcmp(comando, "change"))
        {
            comando_change(linha, heap_prioridade, heap_tempo);
        }
        else if (!strcmp(comando, "print"))
        {
            comando_print(linha, heap_prioridade, heap_tempo);
        }
        else if (!strcmp(comando, "quit"))
        {
            break;
        }
    }

    heap_apagar(&heap_prioridade);
    heap_apagar(&heap_tempo);

    return 0;
}

void comando_add(const char *linha, HEAP *heap_prioridade, HEAP *heap_tempo)
{
    
}

void comando_exec(const char *linha, HEAP *heap_prioridade, HEAP *heap_tempo)
{
}

void comando_next(const char *linha, HEAP *heap_prioridade, HEAP *heap_tempo)
{
}

void comando_change(const char *linha, HEAP *heap_prioridade, HEAP *heap_tempo)
{
    char parametro[3];
    char valores[30];

    sscanf(linha, "%*s %2s %29s", parametro, valores);

    // interpretar parametro e valores...
}

void comando_print(const char *linha, HEAP *heap_prioridade, HEAP *heap_tempo)
{
}

//OPTEI POR FAZER PARSING NA FUNÇÃO, FICA MENOS CARREGADA E PASSAR UM CONST *CHAR PARA LEITURA