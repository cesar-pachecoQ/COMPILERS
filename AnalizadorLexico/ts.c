// Implementación de la tabla de símbolos
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ts.h"

// Definición de un nodo de la tabla de símbolos
struct Nodo {
    char Nombre[70];   // Nombre del símbolo
    int Ntoken;        // Número de token asociado
    int tipo;          // Tipo del símbolo (p.ej. variable, función, etc.)
};

// Tabla de símbolos: arreglo estático de hasta 200 nodos
struct Nodo TS[200];

// Número de elementos actualmente en la tabla
int Nelements = 0;

// Prototipos de funciones
int Alta(int Ntoken, char Nombre[70], int tipo);
int Baja(char Nombre[70]);
int Consulta(char Nombre[70]);
void ImprimeTS(void);
int Posicion(char Nombre[70]);

// Inserta un nuevo símbolo en la tabla
int Alta(int Ntoken, char Nombre[70], int tipo) {
    // Si la tabla está llena, no se puede insertar
    if (Nelements == 200) {
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
    Nelements++;
    // Éxito
    return 1;
}

// Elimina un símbolo de la tabla
int Baja(char Nombre[70]) {
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
int Consulta(char Nombre[70]) {
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
int Posicion(char Nombre[70]) {
    return Consulta(Nombre);
}

// Imprime el contenido de la tabla de símbolos
void ImprimeTS(void) {
    // Recorre todos los elementos actuales
    for (int i = 0; i < Nelements; i++) {
        // Imprime índice y datos de cada nodo
        printf("Posición: %d\n", i);
        printf("  Nombre del símbolo: %s\n", TS[i].Nombre);
        printf("  Número de token:    %d\n", TS[i].Ntoken);
        printf("  Tipo:               %d\n", TS[i].tipo);
    }
}

