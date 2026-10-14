#ifndef PROCESSO_H
#define PROCESSO_H
#include "tempo.h"

#define MAX_DESCR 51

typedef struct processo_ PROCESSO;

PROCESSO *processo_criar(int priority, TEMPO *tempo, char nome[MAX_DESCR]);
void processo_apagar(PROCESSO **processo);
int processo_get_priority(const PROCESSO *processo);
const char *processo_nome(const PROCESSO *processo);
void processo_imprimir(const PROCESSO *processo);
void processo_set_priority(PROCESSO *processo, int priority);
void processo_set_tempo(PROCESSO *processo, TEMPO *tempo);

#endif