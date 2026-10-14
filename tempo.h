#ifndef horario_H
#define horario_H

typedef struct horario horario;

horario *tempo_criar(int hora, int minutos, int segundos);
void tempo_apagar(horario **tempo);
int tempo_get_hora(const horario *tempo);
int tempo_get_minutos(const horario *tempo);
int tempo_get_segundos(const horario *tempo);
void tempo_imprimir(const horario *tempo);
int tempo_comparar(const horario *a, const horario *b);

#endif