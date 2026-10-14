#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "processo.h"

celula *processo_criar(int priority, horario tempo, const char *nome)
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

    free(*processo);
    *processo = NULL;
}

int processo_get_priority(const celula *processo)
{
    return processo->prior;
}

horario processo_get_tempo(const celula *processo)
{
    return processo->chegada;
}

void processo_set_priority(celula *processo, int priority) {
    processo->prior = priority;
}

void processo_set_tempo(celula *processo, horario tempo) {
    processo->chegada = tempo;
}

void processo_imprimir(const celula *processo) {
    printf("%02d ", processo->prior);
    tempo_imprimir(processo->chegada);
    printf(" %s\n", processo->descricao);
}
