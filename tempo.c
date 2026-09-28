#include <stdio.h>
#include "tempo.h"

struct tempo_
{
    int hora;
    int minutos;
    int segundos;
};

TEMPO *tempo_criar(int hora, int minutos, int segundos){
    TEMPO *tempo = malloc(sizeof(*tempo));
    if(tempo == NULL)
        return NULL;

    tempo->hora = hora;
    tempo->minutos = minutos;
    tempo->segundos = segundos;
    return tempo;
}

void tempo_apagar(TEMPO **tempo){
    if(tempo == NULL || *tempo == NULL)
        return;

    free(*tempo);
    *tempo = NULL;
}

int tempo_get_hora(const TEMPO *tempo){
    return tempo->hora;
}

int tempo_get_minutos(const TEMPO *tempo){
    return tempo->minutos;
}

int tempo_get_segundos(const TEMPO *tempo){
    return tempo->segundos;
}

void tempo_imprimir(const TEMPO *tempo){
    printf("%02d:%02d:%02d", 
        tempo_get_hora(tempo), 
        tempo_get_minutos(tempo),
        tempo_get_segundos(tempo));
}

int tempo_em_segundos(const TEMPO *tempo)
{
    return tempo->hora * 3600
         + tempo->minutos * 60
         + tempo->segundos;
}

int tempo_comparar(const TEMPO *a, const TEMPO *b){
    return tempo_em_segundos(a) - tempo_em_segundos(b);
}



