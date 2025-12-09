%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ts.h"
#include "AS.tab.h"

extern FILE *yyin;

FILE *error_file = NULL;
int num_errores = 0;

extern int Valor_num;
extern NodoPointer ap_id;
extern int indice_cadena_actual;

extern int tipo_actual;

void inicializarErrores();
void reportarError(const char *mensaje, const char *token);
void finalizarErrores();
%}

%option yylineno
%option noyywrap   

DIGITO    [0-9]
LETRA     [a-zA-Z]
ID        {LETRA}({LETRA}|{DIGITO})*
CAD       \"([^\\\"]*)\"

%%
[ \t\r]+            ;                   
\n                  ;                   

"//".*              ;                   
"entero"            { return TOK_ENTERO; }
"rutina"            { return TOK_RUTINA; }
"principal"         { return TOK_PRINCIPAL; }
"si"                { return TOK_SI; }
"entonces"          { return TOK_ENTONCES; }
"otro"              { return TOK_OTRO; }
"mientras"          { return TOK_MIENTRAS; }
"haz"               { return TOK_HAZ; }
"regresa"           { return TOK_REGRESA; }
"caracter"          { return TOK_CARACTER; }
"comienza"          { return TOK_COMIENZA; }
"termina"           { return TOK_TERMINA; }


{DIGITO}+           {
                      yylval.entero = atoi(yytext);
                      Valor_num = atoi(yytext);  
                      return TOK_NUMERO;
                    }

{CAD}               {
                      yylval.pos_cad = insertarCadena(yytext);
                      indice_cadena_actual = insertarCadena(yytext);
                      return TOK_CADENA;
                    }

{ID}                {
                      ap_id = insertarID(yytext);
                      yylval.ap_id = ap_id;
                      return TOK_IDENTIFICADOR;
                    }

">="                { return TOK_MAYOR_IGUAL; }
"<="                { return TOK_MENOR_IGUAL; }
"=="                { return TOK_IGUAL_IGUAL; }
"!="                { return TOK_DIFERENTE; }

";"                 { return TOK_PUNTO_Y_COMA; }
","                 { return TOK_COMA; }
"("                 { return TOK_PARENTESIS_ABRE; }
")"                 { return TOK_PARENTESIS_CIERRA; }
"{"                 { return TOK_LLAVE_ABRE; }
"}"                 { return TOK_LLAVE_CIERRA; }
"["                 { return TOK_CORCHETE_ABRE; }
"]"                 { return TOK_CORCHETE_CIERRA; }
">"                 { return TOK_MAYOR; }
"<"                 { return TOK_MENOR; }
"="                 { return TOK_ASIGNACION; }
"+"                 { return TOK_SUMA; }
"-"                 { return TOK_RESTA; }
"*"                 { return TOK_MULTIPLICACION; }
"/"                 { return TOK_DIVISION; }

<<EOF>>              { return TOK_EOF; }

.                   {
                      // Manejar caracteres no reconocidos
                      reportarError("Carácter no válido", yytext);
                      return TOK_ERROR;
                    }
%%


void inicializarErrores() {
    error_file = fopen("errores.txt", "w");
    if (error_file) {
        fprintf(error_file, "# Errores Léxicos\n\n");
        fprintf(error_file, "| Línea | Token Inválido | Mensaje de Error |\n");
        fprintf(error_file, "|-------|----------------|------------------|\n");
        num_errores = 0;
    } else {
        fprintf(stderr, "Error: No se pudo crear archivo de errores\n");
    }
}

void reportarError(const char *mensaje, const char *token) {
    if (error_file) {
        fprintf(error_file, "| %5d | %-14s | %s |\n", 
                yylineno, token, mensaje);
        num_errores++;
    }
    fprintf(stderr, "Error línea %d: %s '%s'\n", yylineno, mensaje, token);
}

void finalizarErrores() {
    if (error_file) {
        fprintf(error_file, "\n**Total de errores:** %d\n", num_errores);
        fclose(error_file);
        error_file = NULL;
    }
}

