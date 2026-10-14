#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tempo.h"
#include "processo.h"

struct processo_
{
    int priority;
    TEMPO *tempo;
    char nome[MAX_DESCR];
};

PROCESSO *processo_criar(int priority, TEMPO *tempo, char nome[MAX_DESCR])
{
    PROCESSO *processo = malloc(sizeof(*processo));
    if (processo == NULL)
        return NULL;

    processo->priority = priority;
    processo->tempo = tempo;
    strcpy(processo->nome, nome); // temos que garantir que char nome tem no max MAX_DESCR - 1 caracteres

    return processo;
}

void processo_apagar(PROCESSO **processo)
{
    if (processo == NULL || *processo == NULL)
        return;

    tempo_apagar(&(*processo)->tempo);
    free(*processo);
    *processo = NULL;
}

int processo_get_priority(const PROCESSO *processo)
{
    return processo->priority;
}

TEMPO *processo_get_tempo(const PROCESSO *processo)
{
    return processo->tempo;
}

const char *processo_get_nome(const PROCESSO *processo)
{
    return processo->nome;
}

void processo_imprimir(const PROCESSO *processo) {
    printf("%d ", processo_get_priority(processo));
    tempo_imprimir(processo_get_tempo(processo));
    printf(" %s\n", processo_get_nome(processo));
}
