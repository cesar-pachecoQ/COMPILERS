#ifndef TS_H
#define TS_H

#include <stdio.h>

#define MAX_NOMBRE 70
#define MAX_TS     200

struct Nodo {
    char Nombre[MAX_NOMBRE];
    int  Ntoken;
    int  tipo;
};

extern struct Nodo TS[MAX_TS];
extern int          Nelements;

// Corregir prototipos para usar const char*
int  Alta      (int Ntoken, const char *Nombre, int tipo);
int  Baja      (const char *Nombre);
int  Consulta  (const char *Nombre);
int  Posicion  (const char *Nombre);
void ImprimeTS (FILE *f);

#endif /* TS_H */