#ifndef PROCESSO_H
#define PROCESSO_H
#include "tempo.h"

typedef struct processo_ PROCESSO;

PROCESSO *processo_criar(int priority, TEMPO tempo, char *nome);
void processo_apagar(PROCESSO **processo);
int processo_get_priority(const PROCESSO *processo);
const char *processo_nome(const PROCESSO *processo);
void processo_imprimir(const PROCESSO *processo);

#endif

