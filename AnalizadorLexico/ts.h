#ifndef TS_H
#define TS_H

#include <stdio.h>

#define MAX_NOMBRE 70
#define MAX_TS     200

/* --- Estructura de un nodo (idéntica a la de ts.c) --- */
struct Nodo {
    char Nombre[MAX_NOMBRE];
    int  Ntoken;
    int  tipo;
};

/* --- Variables globales definidas en ts.c --- */
extern struct Nodo TS[MAX_TS];
extern int          Nelements;

/* --- Prototipos de las funciones que ofreces --- */
int  Alta      (int Ntoken, const char Nombre[MAX_NOMBRE], int tipo);
int  Baja      (const char Nombre[MAX_NOMBRE]);
int  Consulta  (const char Nombre[MAX_NOMBRE]);
int  Posicion  (const char Nombre[MAX_NOMBRE]);
void ImprimeTS (void);

#endif /* TS_H */
