#ifndef celula_H
#define celula_H
#include "tempo.h"

#define MAX_DESCR 51

typedef struct celula celula;

celula *processo_criar(int priority, horario *tempo, char nome[MAX_DESCR]);
void processo_apagar(celula **processo);
int processo_get_priority(const celula *processo);
const char *processo_get_nome(const celula *processo);
horario *processo_get_tempo(const celula *processo);
void processo_imprimir(const celula *processo);
void processo_set_priority(celula *processo, int priority);
void processo_set_tempo(celula *processo, horario *tempo);

#endif