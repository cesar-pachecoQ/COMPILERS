// main.c
#include <stdio.h>
#include <stdlib.h>
#include "token.h"
#include "ts.h"

// Prototipos y variables del scanner (definidos en lex.yy.c)
int yylex(void);
extern FILE *yyin;        // archivo de entrada
extern char *yytext;      // texto del token actual
extern int yylineno;      // número de línea
extern int Valor_num;     // atributo numérico
extern int ap_id;         // posición en tabla de símbolos
extern int ap_cad;        // posición en tabla de cadenas (TS)
extern FILE *errores;     // fichero para errores léxicos

// Código principal
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <archivo_prueba.txt>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // 1) Abrir archivo de prueba
    yyin = fopen(argv[1], "r");
    if (!yyin) {
        perror("Error abriendo archivo de prueba");
        return EXIT_FAILURE;
    }

    // 2) Preparar ficheros de salida
    errores = fopen("errores.txt", "w");
    if (!errores) {
        perror("Error abriendo errores.txt");
        return EXIT_FAILURE;
    }
    FILE *f_tabla = fopen("tabla.txt", "w");
    if (!f_tabla) {
        perror("Error abriendo tabla.txt");
        return EXIT_FAILURE;
    }

    // 3) Bucle de tokenización
    int tok;
    while ((tok = yylex()) != TOK_EOF) {
        int attr = 0;
        switch (tok) {
            case TOK_NUMERO:
                attr = Valor_num;       // el valor numérico
                break;
            case TOK_IDENTIFICADOR:
                attr = ap_id;           // posición en TS
                break;
            case TOK_CADENA:
                attr = ap_cad;          // posición en TS (cadenas)
                break;
            default:
                attr = 0;               // sin atributo
        }
        // Formato: código_token    yytext    atributo
        fprintf(f_tabla, "%d\t%s\t%d\n", tok, yytext, attr);
    }

    // 4) Cerrar flujos de análisis
    fclose(yyin);
    fclose(errores);
    fclose(f_tabla);

    // 5) Volcar tabla de símbolos (e incluso cadenas) 
    FILE *f_ts = fopen("tabla_simbolos.txt", "w");
    if (!f_ts) {
        perror("Error abriendo tabla_simbolos.txt");
        return EXIT_FAILURE;
    }
    ImprimeTS(f_ts);
    fclose(f_ts);

    return EXIT_SUCCESS;
}