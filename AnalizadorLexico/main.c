#include <stdio.h>
#include <stdlib.h>
#include "token.h"   /* Definición de TOK_* */
#include "ts.h"      /* Alta(), ImprimeTS() */

extern FILE *yyin;
extern int yylex(void);
extern char *yytext;
extern int yylineno;

// Variables del analizador
extern int Valor_num;
extern NodoPointer ap_id;
extern IndexTablaCadenas pos_cad;
extern int indice_cadena_actual;

// Funciones de manejo de errores
extern void inicializarErrores();
extern void finalizarErrores();
extern int num_errores;

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <archivo_entrada>\n", argv[0]);
        return 1;
    }

    /* Abrir archivo de entrada */
    yyin = fopen(argv[1], "r");
    if (!yyin) {
        perror("Error al abrir archivo de entrada");
        return 1;
    }

    /* Inicializar estructuras */
    inicializarTablaCadenas();
    inicializarErrores();

    printf("=== ANÁLISIS LÉXICO ===\n");
    printf("Archivo: %s\n\n", argv[1]);
    printf("Línea\tCódigo\tLexema\t\tAtributo\n");
    printf("-----\t------\t------\t\t--------\n");

    /* Bucle de análisis */
    int token;
    while ((token = yylex()) != 0) {
        if (token == TOK_ERROR) {
            continue; // Error ya reportado
        }
        
        printf("%3d\t%d\t%-15s\t", yylineno, token, yytext);
        
        switch (token) {
            case TOK_NUMERO:
                printf("%d", Valor_num);
                break;
            case TOK_IDENTIFICADOR:
                if (ap_id != NULL) {
                    printf("pos: %ld", ap_id - TS);
                } else {
                    printf("ERROR");
                }
                break;
            case TOK_CADENA:
                printf("pos: %d", indice_cadena_actual);
                break;
            default:
                printf("—");
                break;
        }
        printf("\n");
    }

    /* Cerrar archivo de entrada */
    fclose(yyin);

    /* Generar archivos de salida */
    printf("\n=== GENERANDO REPORTES ===\n");
    
    // Tabla de símbolos
    FILE *salida_ts = fopen("tabla_salida.md", "w");
    if (salida_ts) {
        ImprimeTS(salida_ts);
        fclose(salida_ts);
        printf("✓ Tabla de símbolos: tabla_salida.md\n");
    }
    
    // Tabla de cadenas
    FILE *salida_cad = fopen("tabla_cadenas.md", "w");
    if (salida_cad) {
        imprimirTablaCadenas(salida_cad);
        fclose(salida_cad);
        printf("✓ Tabla de cadenas: tabla_cadenas.md\n");
    }

    // También imprimir en consola
    printf("\n=== TABLA DE SÍMBOLOS ===\n");
    ImprimeTS(stdout);
    
    printf("\n=== TABLA DE CADENAS ===\n");
    imprimirTablaCadenas(stdout);

    /* Finalizar manejo de errores */
    finalizarErrores();

    /* Reporte final */
    printf("\n=== RESUMEN ===\n");
    printf("Símbolos encontrados: %d\n", Nelements);
    printf("Cadenas encontradas: %d\n", pos_cad);
    
    if (num_errores > 0) {
        printf("⚠️  Errores encontrados: %d\n", num_errores);
        printf("   Ver detalles en: errores.txt\n");
        return 1;
    } else {
        printf("✅ Análisis completado sin errores\n");
        return 0;
    }
}
