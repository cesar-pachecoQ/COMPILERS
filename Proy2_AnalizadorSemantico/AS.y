%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ts.h"

int tipo_actual = TIPO_NO_DEFINIDO;  // Tipo actual para declaraciones

void yyerror(const char *s);
extern int yylex();
extern FILE *yyin;
extern int yyparse();
extern int yylineno;
%}

%union {
    int entero;
    NodoPointer ap_id;
    IndexTablaCadenas pos_cad;
    int tipo;
}

%token TOK_ENTERO TOK_RUTINA TOK_PRINCIPAL TOK_SI TOK_ENTONCES TOK_OTRO
%token TOK_MIENTRAS TOK_HAZ TOK_REGRESA TOK_PUNTO_Y_COMA TOK_COMA 
%token TOK_PARENTESIS_ABRE TOK_PARENTESIS_CIERRA
%token TOK_LLAVE_ABRE TOK_LLAVE_CIERRA TOK_CORCHETE_ABRE TOK_CORCHETE_CIERRA
%token TOK_MAYOR TOK_MENOR TOK_ASIGNACION TOK_SUMA TOK_RESTA TOK_MULTIPLICACION
%token TOK_DIVISION TOK_MAYOR_IGUAL TOK_MENOR_IGUAL TOK_DIFERENTE TOK_IGUAL_IGUAL
%token TOK_EOF TOK_ERROR TOK_UNKNOWN TOK_COMIENZA TOK_TERMINA

%token <entero> TOK_NUMERO TOK_CARACTER
%token <popo> DECLs_cad> TOK_CADENA
%token <ap_id> TOK_IDENTIFICADOR

//Estos son los no terminales

%type <entero> EXPRESION TERMINO FACTOR
%type <tipo> DECLARACION

%start PROGRAMA

%%

PROGRAMA: DECLARACIONES BLOQUE
    {
        printf("Programa analizado correctamente\n");
    }

DECLARACIONES: DECLARACION TOK_PUNTO_Y_COMA DECLARACIONES
    {
        printf("Procesando declaraciones múltiples\n");
    }
    | DECLARACION TOK_PUNTO_Y_COMA
    {
        printf("Última declaración procesada\n");
    }

DECLARACION: TOK_ENTERO { tipo_actual = TIPO_ENTERO; } LISTA_ID
    {
        $$ = TIPO_ENTERO;
        printf("Declaración de variables enteras\n");
    }
    | TOK_CARACTER { tipo_actual = TIPO_CARACTER; } LISTA_ID
    {
        $$ = TIPO_CARACTER;
        printf("Declaración de variables carácter\n");
    }

LISTA_ID: TOK_IDENTIFICADOR TOK_COMA LISTA_ID
    {
        // Insertar identificador en la tabla de símbolos
        if ($1 != NULL) {
            $1->tipo = tipo_actual;
            printf("Declarando identificador: %s\n", $1->lexema);
        }
    }
    | TOK_IDENTIFICADOR
    {
        // Insertar último identificador en la tabla de símbolos
        if ($1 != NULL) {
            $1->tipo = tipo_actual;
            printf("Declarando último identificador: %s\n", $1->lexema);
        }
    }

BLOQUE: TOK_COMIENZA SENTENCIAS TOK_TERMINA
    {
        printf("Bloque procesado correctamente\n");
    }

SENTENCIAS: SENTENCIA TOK_PUNTO_Y_COMA SENTENCIAS
    {
        printf("Procesando múltiples sentencias\n");
    }
    | SENTENCIA
    {
        printf("Última sentencia procesada\n");
    }

SENTENCIA: ASIGNACION
    {
        printf("Sentencia de asignación procesada\n");
    }
    | IF
    {
        printf("Sentencia IF procesada\n");
    }
    | WHILE
    {
        printf("Sentencia WHILE procesada\n");
    }
    | BLOQUE
    {
        printf("Bloque anidado procesado\n");
    }

ASIGNACION: TOK_IDENTIFICADOR TOK_ASIGNACION EXPRESION
    {
        // Verificar que el identificador esté declarado
        if ($1 != NULL) {
            if ($1->tipo == TIPO_NO_DEFINIDO) {
                yyerror("Identificador no inicializado en asignación");
                YYABORT;
            }
            $1->valor = $3;
            printf("Asignación a %s = %d\n", $1->lexema, $3);
        } else {
            yyerror("Identificador no declarado en asignación");
            YYABORT;
        }
    }

IF: TOK_SI TOK_PARENTESIS_ABRE EXPRESION TOK_PARENTESIS_CIERRA TOK_PUNTO_Y_COMA TOK_ENTONCES SENTENCIA TOK_OTRO SENTENCIA
    {
        printf("Estructura IF-ELSE con condición: %d\n", $3);
    }

WHILE: TOK_MIENTRAS TOK_PARENTESIS_ABRE EXPRESION TOK_PARENTESIS_CIERRA TOK_HAZ SENTENCIA TOK_PUNTO_Y_COMA
    {
        printf("Estructura WHILE con condición: %d\n", $3);
    }

EXPRESION: EXPRESION TOK_SUMA TERMINO
    {
        $$ = $1 + $3;
        printf("Suma: %d + %d = %d\n", $1, $3, $$);
    }
    | EXPRESION TOK_RESTA TERMINO
    {
        $$ = $1 - $3;
        printf("Resta: %d - %d = %d\n", $1, $3, $$);
    }
    | TERMINO
    {
        $$ = $1;
    }

TERMINO: TERMINO TOK_MULTIPLICACION FACTOR
    {
        $$ = $1 * $3;
        printf("Multiplicación: %d * %d = %d\n", $1, $3, $$);
    }
    | TERMINO TOK_DIVISION FACTOR
    {
        if ($3 == 0) {
            yyerror("División por cero detectada");
            YYABORT;
        }
        $$ = $1 / $3;
        printf("División: %d / %d = %d\n", $1, $3, $$);
    }
    | FACTOR
    {
        $$ = $1;
    }

FACTOR: TOK_PARENTESIS_ABRE EXPRESION TOK_PARENTESIS_CIERRA
    {
        $$ = $2;
        printf("Expresión entre paréntesis: %d\n", $$);
    }
    | TOK_IDENTIFICADOR
    {
        if ($1 != NULL) {
            // Verificar que el identificador esté declarado
            if ($1->tipo == TIPO_NO_DEFINIDO) {
                yyerror("Identificador no inicializado");
                $$ = 0;
            } else {
                $$ = $1->valor;
                printf("Usando identificador %s con valor %d\n", $1->lexema, $$);
            }
        } else {
            yyerror("Identificador no declarado");
            $$ = 0;
        }
    }
    | TOK_NUMERO
    {
        $$ = $1;
        printf("Número: %d\n", $$);
    }
    | TOK_CARACTER
    {
        $$ = $1;
        printf("Carácter: %d\n", $$);
    }

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error de sintaxis: %s en la línea %d\n", s, yylineno);
}