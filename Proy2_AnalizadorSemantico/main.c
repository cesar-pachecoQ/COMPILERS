#include <stdio.h>
#include <stdlib.h>
#include "ts.h"

extern FILE *yyin;
extern int yyparse();
extern int yylineno;
extern int num_errores;

void inicializarErrores();
void finalizarErrores();

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

    printf("=== ANÁLISIS SINTÁCTICO Y SEMÁNTICO ===\n");
    printf("Archivo: %s\n\n", argv[1]);

    /* Ejecutar el parser */
    int resultado = yyparse();

    /* Cerrar archivo */
    fclose(yyin);

    /* Generar reportes */
    printf("\n=== GENERANDO REPORTES ===\n");
    
    FILE *salida_ts = fopen("tabla_simbolos_parser.md", "w");
    if (salida_ts) {
        ImprimeTS(salida_ts);
        fclose(salida_ts);
        printf("✓ Tabla de símbolos: tabla_simbolos_parser.md\n");
    }

    FILE *salida_cad = fopen("tabla_cadenas_parser.md", "w");
    if (salida_cad) {
        imprimirTablaCadenas(salida_cad);
        fclose(salida_cad);
        printf("✓ Tabla de cadenas: tabla_cadenas_parser.md\n");
    }

    printf("\n=== TABLA DE SÍMBOLOS FINAL ===\n");
    ImprimeTS(stdout);

    printf("\n=== TABLA DE CADENAS FINAL ===\n");
    imprimirTablaCadenas(stdout);

    finalizarErrores();

    printf("\n=== RESUMEN FINAL ===\n");
    printf("Símbolos en tabla: %d\n", Nelements);
    printf("Cadenas en tabla: %d\n", pos_cad);

    if (resultado == 0 && num_errores == 0) {
        printf(" Análisis sintáctico y semántico completado exitosamente\n");
        return 0;
    } else {
        printf(" Análisis terminado con errores\n");
        printf("   Errores de sintaxis: %s\n", (resultado != 0) ? "Sí" : "No");
        printf("   Errores léxicos: %d\n", num_errores);
        return 1;
    }
}