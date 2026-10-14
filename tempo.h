#ifndef TEMPO_H
#define TEMPO_H

typedef struct tempo_ TEMPO;

TEMPO *tempo_criar(int hora, int minutos, int segundos);
void tempo_apagar(TEMPO **tempo);
int tempo_get_hora(const TEMPO *tempo);
int tempo_get_minutos(const TEMPO *tempo);
int tempo_get_segundos(const TEMPO *tempo);
void tempo_imprimir(const TEMPO *tempo);
int tempo_comparar(const TEMPO *a, const TEMPO *b);

#endif