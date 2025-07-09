// Implementación de la tabla de símbolos
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ts.h"


// Tabla de símbolos: arreglo estático de hasta 200 nodos
struct Nodo TS[MAX_TS];


// Número de elementos actualmente en la tabla
int Nelements = 0;


// Inserta un nuevo símbolo en la tabla
int Alta(int Ntoken, const char *Nombre, int tipo) {
    // Si el token ya exite, evitamos crear un duplicado
    int pos = Consulta(Nombre);
    if (pos >= 0) {
        // Si sí, devolvemos la posición que ya había
        return pos;
    }
    // Si la tabla está llena, no se puede insertar
    if (Nelements >= MAX_TS) {
        printf("Tabla de símbolos llena\n");
        return -1;
    }
    // Copia el nombre al nodo
    strcpy(TS[Nelements].Nombre, Nombre);
    // Asigna el número de token
    TS[Nelements].Ntoken = Ntoken;
    // Asigna el tipo
    TS[Nelements].tipo   = tipo;
    // Incrementa el contador de elementos
    int posicion = Nelements;
    Nelements++;
    return posicion;  // Devuelve la posición del nuevo símbolo
}

// Elimina un símbolo de la tabla
int Baja(const char *Nombre) {
    int pos;
    // Si no hay elementos, no se puede eliminar
    if (Nelements == 0) {
        printf("La tabla está vacía\n");
        return -1;
    }
    // Busca la posición del símbolo
    pos = Consulta(Nombre);
    // Si no se encontró, informa y sale
    if (pos == -1) {
        printf("%s: símbolo no encontrado\n", Nombre);
        return -1;
    }
    // Desplaza todos los elementos posteriores una posición hacia atrás
    for (int i = pos; i < Nelements - 1; i++) {
        TS[i] = TS[i + 1];
    }
    // Decrementa el contador de elementos
    Nelements--;
    // Devuelve la posición donde estaba el símbolo eliminado
    return pos;
}

// Devuelve la posición de un símbolo (o -1 si no existe)
int Consulta(const char *Nombre) {
    // Recorre todos los elementos actuales
    for (int i = 0; i < Nelements; i++) {
        // Compara cadenas; strcmp == 0 significa coincidencia
        if (strcmp(TS[i].Nombre, Nombre) == 0) {
            return i;   // Retorna el índice si coincide
        }
    }
    // No encontró el símbolo
    return -1;
}

// (alternativa interna) Mismo comportamiento que Consulta
int Posicion(const char *Nombre) {
    return Consulta(Nombre);
}

// Imprime el contenido de la tabla de símbolos
void ImprimeTS(FILE *f) {
    fprintf(f, "Tabla de Símbolos:\n");
    fprintf(f, "Índice  Nombre                          Ntoken  Tipo\n");
    for (int i = 0; i < Nelements; i++) {
        fprintf(f, "%3d  %-*s  %3d  %3d\n",
                i,
                MAX_NOMBRE, TS[i].Nombre,
                TS[i].Ntoken,
                TS[i].tipo);
    }
}

