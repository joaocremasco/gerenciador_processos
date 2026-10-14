#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tempo.h"
#include "processo.h"

struct celula
{
    int prior;
    horario *chegada;
    char descricao[MAX_DESCR];
};

celula *processo_criar(int priority, horario *tempo, char nome[MAX_DESCR])
{
    celula *processo = malloc(sizeof(*processo));
    if (processo == NULL)
        return NULL;

    processo->prior = priority;
    processo->chegada = tempo;
    strcpy(processo->descricao, nome);

    return processo;
}

void processo_apagar(celula **processo)
{
    if (processo == NULL || *processo == NULL)
        return;

    tempo_apagar(&(*processo)->chegada);
    free(*processo);
    *processo = NULL;
}

int processo_get_priority(const celula *processo)
{
    return processo->prior;
}

horario *processo_get_tempo(const celula *processo)
{
    return processo->chegada;
}

const char *processo_get_nome(const celula *processo)
{
    return processo->descricao;
}

void processo_set_priority(celula *processo, int priority) {
    processo->prior = priority;
}

void processo_set_tempo(celula *processo, horario *tempo) {
    if(processo->chegada != NULL) {
        tempo_apagar(&processo->chegada);
    }
    processo->chegada = tempo;
}

void processo_imprimir(const celula *processo) {
    printf("%02d ", processo_get_priority(processo));
    tempo_imprimir(processo_get_tempo(processo));
    printf(" %s\n", processo_get_nome(processo));
}
