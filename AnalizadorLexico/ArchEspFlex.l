%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "token.h"
#include "ts.h"

extern int yylineno;    
extern FILE *yyin;      
extern FILE *errores;   
%}

%option noyywrap        
%option yylineno        


DIGITO      [0-9]
LETRA       [A-Za-z]
ID          {LETRA}({LETRA}|{DIGITO})*
CADENA      \"([^\"\\]|\\.)*\"



%%
"rutina"        { return TOK_RUTINA; }
"principal"     { return TOK_PRINCIPAL; }
"si"            { return TOK_SI; }
"entonces"      { return TOK_ENTONCES; }
"otro"          { return TOK_OTRO; }
"mientras"      { return TOK_MIENTRAS; }
"haz"           { return TOK_HAZ; }
"regresa"       { return TOK_REGRESA; }

{ID}            {
                    insertar_en_ts(yytext);
                    return TOK_IDENTIFICADOR;
                }
{DIGITO}+       {
                    yylval.valor_entero = atoi(yytext);
                    return TOK_NUMERO;
                }
{CADENA}        {
                    insertar_en_tc(yytext);
                    return TOK_CADENA;
                }

"/*"([^*]|\*+[^*/])*\*+"/"    { /* ignora comentario de bloque */ }
"//".*                        { /* ignora comentario de línea */ }

">="            { return TOK_MAYOR_IGUAL; }
"<="            { return TOK_MENOR_IGUAL; }
"=="            { return TOK_IGUAL_IGUAL; }
"!="            { return TOK_DIFERENTE; }

"+"             { return TOK_SUMA; }
"-"             { return TOK_RESTA; }
"*"             { return TOK_MULTIPLICACION; }
"/"             { return TOK_DIVISION; }

";"             { return ';'; }
","             { return ','; }
"("             { return '('; }
")"             { return ')'; }
"{"             { return '{'; }
"}"             { return '}'; }
"["             { return '['; }
"]"             { return ']'; }
"="             { return '='; }
"<"             { return '<'; }
">"             { return '>'; }

[ \t\r]+        { /* ignóralos */ }
\n              { /* Flex suma automáticamente yylineno */ }

.               {
                    fprintf(errores,
                            "%d\t%s\tToken inválido\n",
                            yylineno,
                            yytext);
                }
%%

