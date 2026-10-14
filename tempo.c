#include <stdio.h>
#include <stdlib.h>
#include "tempo.h"

struct horario
{
    int hh;
    int mm;
    int ss;
};

horario *tempo_criar(int hora, int minutos, int segundos){
    horario *tempo = malloc(sizeof(*tempo));
    if(tempo == NULL)
        return NULL;

    tempo->hh = hora;
    tempo->mm = minutos;
    tempo->ss = segundos;
    return tempo;
}

void tempo_apagar(horario **tempo){
    if(tempo == NULL || *tempo == NULL)
        return;

    free(*tempo);
    *tempo = NULL;
}

int tempo_get_hora(const horario *tempo){
    return tempo->hh;
}

int tempo_get_minutos(const horario *tempo){
    return tempo->mm;
}

int tempo_get_segundos(const horario *tempo){
    return tempo->ss;
}

void tempo_imprimir(const horario *tempo){
    printf("%02d:%02d:%02d", 
        tempo_get_hora(tempo), 
        tempo_get_minutos(tempo),
        tempo_get_segundos(tempo));
}

int tempo_comparar(const horario *a, const horario *b) {
    if(tempo_get_hora(a) != tempo_get_hora(b))
        return tempo_get_hora(a) - tempo_get_hora(b);
    if(tempo_get_minutos(a) != tempo_get_minutos(b))
        return tempo_get_minutos(a) - tempo_get_minutos(b);
    return tempo_get_segundos(a) - tempo_get_segundos(b);
}