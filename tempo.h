#ifndef TEMPO_H
#define TEMPO_H

typedef struct {
    int hh;
    int mm;
    int ss;
} horario;

void tempo_imprimir(horario tempo);
int tempo_comparar(horario a, horario b);

#endif
