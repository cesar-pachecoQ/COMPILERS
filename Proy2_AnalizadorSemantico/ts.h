#ifndef TS_H
#define TS_H

#include <stdio.h>

#define MAX_NOMBRE 70
#define MAX_TS     200

#define TIPO_ENTERO 1
#define TIPO_CARACTER 2
#define TIPO_NO_DEFINIDO 0

struct Nodo {
    char Nombre[MAX_NOMBRE];
    int  Ntoken;
    int  tipo;
    int  valor;
    char *lexema;  // Apuntador al lexema asociado
};

typedef struct Nodo* NodoPointer;
typedef int IndexTablaCadenas;
extern struct Nodo TS[MAX_TS];
extern int Nelements;
extern char TablaCadenas[MAX_TS][MAX_NOMBRE];
//indices
extern IndexTablaCadenas pos_cad;
extern NodoPointer ap_id;
extern int indice_cadena_actual;


// Corregir prototipos para usar const char*
int  Alta      (int Ntoken, const char *Nombre, int tipo);
int  Baja      (const char *Nombre);
int  Consulta  (const char *Nombre);
int  Posicion  (const char *Nombre);
void ImprimeTS (FILE *f);


NodoPointer insertarID(const char *lexema);
IndexTablaCadenas insertarCadena(const char *lexema);
void inicializarTablaCadenas();
void imprimirTablaCadenas(FILE *f);

// Declaraciones para manejo de errores
extern FILE *error_file;
extern int num_errores;
void inicializarErrores();
void finalizarErrores();
void reportarError(const char *mensaje, const char *token);


#endif /* TS_H */