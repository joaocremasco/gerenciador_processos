#include <stdio.h>
#include "tempo.h"

void tempo_imprimir(horario tempo){
    printf("%02d:%02d:%02d", tempo.hh, tempo.mm, tempo.ss);
}

int tempo_comparar(horario a, horario b) {
    if(a.hh != b.hh)
        return a.hh - b.hh;
    if(a.mm != b.mm)
        return a.mm - b.mm;
    return a.ss - b.ss;
}
