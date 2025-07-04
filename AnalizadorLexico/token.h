#ifndef TOKENS_H
#define TOKENS_H

typedef enum {
    // — Palabras reservadas (solo nombre) —
    TOK_RUTINA,
    TOK_PRINCIPAL,
    TOK_SI,
    TOK_ENTONCES,
    TOK_OTRO,
    TOK_MIENTRAS,
    TOK_HAZ,
    TOK_REGRESA,
    TOK_NUMERO,          // Número entero

    // — Identificadores y literales (solo nombre) —
    TOK_IDENTIFICADOR,      // ((l | d))*
    TOK_ENTERO,             // d+
    TOK_CADENA,             // "C*"

    // — Símbolos ASCII (asignados al carácter) —
    TOK_PUNTO_Y_COMA        = ';',
    TOK_COMA                = ',',
    TOK_PARENTESIS_ABRE     = '(',
    TOK_PARENTESIS_CIERRA   = ')',
    TOK_LLAVE_ABRE          = '{',
    TOK_LLAVE_CIERRA        = '}',
    TOK_CORCHETE_ABRE       = '[',
    TOK_CORCHETE_CIERRA     = ']',
    TOK_MAYOR               = '>',
    TOK_MENOR               = '<',
    TOK_ASIGNACION          = '=',
    TOK_SUMA                = '+',
    TOK_RESTA               = '-',
    TOK_MULTIPLICACION      = '*',
    TOK_DIVISION            = '/',

    // — Operadores de dos caracteres (solo nombre) —
    TOK_MAYOR_IGUAL,        // >=
    TOK_MENOR_IGUAL,        // <=
    TOK_DIFERENTE,          // !=
    TOK_IGUAL_IGUAL,        // ==

    // Token especial de fin de archivo
    TOK_EOF
} Token;

#endif // TOKENS_H
