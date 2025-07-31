// Implementación de la tabla de símbolos
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ts.h"
#include "token.h"


// Tabla de símbolos: arreglo estático de hasta 200 nodos
struct Nodo TS[MAX_TS];


// Número de elementos actualmente en la tabla
int Nelements = 0;

// Tabla de cadenas
char TablaCadenas[MAX_TS][MAX_NOMBRE];

typedef int IndexTablaCadenas;

NodoPointer ap_id = NULL;  // Apuntador a nodo actual (para identificadores)
IndexTablaCadenas pos_cad = 0;  // Posición actual en la tabla de cadenas

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



NodoPointer insertarID(const char *lexema) { 
    int pos = Consulta(lexema);
    if (pos >= 0) {
        // Si ya existe, devuelve el apuntador al nodo
        return &TS[pos];
    } else {
        int nuevo_indice = Alta(TOK_IDENTIFICADOR, lexema, 0);
        if (nuevo_indice >= 0) {
            // Si se insertó correctamente, devuelve el apuntador al nuevo nodo
            fprintf(stderr, "Insertando ID: %s en la posición %d\n", lexema, nuevo_indice);
            return &TS[nuevo_indice];

        } else {
            // Si hubo un error al insertar, devuelve NULL
            fprintf(stderr, "Error al insertar ID: %s\n", lexema);
            return NULL;
        }

    }

}
// Al inicio del archivo, después de las variables globales:
void inicializarTablaCadenas() {
    for (int i = 0; i < MAX_TS; i++) {
        TablaCadenas[i][0] = '\0';
    }
}
IndexTablaCadenas insertarCadena(const char *lexema) {
  char lexema_temp[MAX_NOMBRE];
  int longitud = strlen(lexema);

  if (longitud > 1 && lexema[0] == '"' && lexema[longitud - 1] == '"') {
    // Elimina las comillas al inicio y al final
    strncpy(lexema_temp, lexema + 1, longitud - 2);
    lexema_temp[longitud - 2] = '\0'; // Asegura que la cadena esté terminada en nulo
  } else {
    strncpy(lexema_temp, lexema, longitud);
    lexema_temp[longitud] = '\0'; // Asegura que la cadena esté terminada en nulo
  }

  for (int i = 0; i < pos_cad; i++) {
    if (strcmp(TablaCadenas[i], lexema_temp) == 0) {
      // Si la cadena ya existe, devuelve su índice
      return i;
    }
  }
  // Si no existe, la inserta
  if (pos_cad < MAX_TS) {
    strncpy(TablaCadenas[pos_cad], lexema_temp, MAX_NOMBRE - 1);
    TablaCadenas[pos_cad][MAX_NOMBRE - 1] = '\0';  // Asegura terminación nula
    pos_cad++;
    return pos_cad - 1;  // Retorna el índice de la cadena insertada
  }
  printf("Error: Tabla de cadenas llena al intentar insertar '%s'\n", lexema_temp);
  return -1;  // Error si la tabla está llena
}

void imprimirTablaCadenas(FILE *f) {
    fprintf(f, "# Tabla de Cadenas\n\n");
    fprintf(f, "| Índice | Cadena |\n");
    fprintf(f, "|--------|--------|\n");
    
    for (int i = 0; i < pos_cad; i++) {
        fprintf(f, "| %3d | %-*s |\n", 
                i, 
                MAX_NOMBRE, TablaCadenas[i]);
    }
    fprintf(f, "\n");
}
// Imprime el contenido de la tabla de símbolos
void ImprimeTS(FILE *f) {
    fprintf(f, "# Tabla de Símbolos\n\n");
    fprintf(f, "| Índice | Nombre | Ntoken | Tipo |\n");
    fprintf(f, "|--------|--------|--------|------|\n");
    for (int i = 0; i < Nelements; i++) {
        fprintf(f, "| %3d | %-*s | %3d | %3d |\n",
                i,
                MAX_NOMBRE, TS[i].Nombre,
                TS[i].Ntoken,
                TS[i].tipo);
    }
    fprintf(f, "\n");
}
