#ifndef PROCESSO_H
#define PROCESSO_H
#include "tempo.h"

#define MAX_DESCR 51

typedef struct {
    int prior;
    horario chegada;
    char descricao[MAX_DESCR];
} celula;

celula *processo_criar(int priority, horario tempo, const char *nome);
void processo_apagar(celula **processo);
int processo_get_priority(const celula *processo);
horario processo_get_tempo(const celula *processo);
void processo_set_priority(celula *processo, int priority);
void processo_set_tempo(celula *processo, horario tempo);
void processo_imprimir(const celula *processo);

#endif
