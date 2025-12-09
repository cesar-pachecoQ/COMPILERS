/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_AS_TAB_H_INCLUDED
# define YY_YY_AS_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    TOK_ENTERO = 258,              /* TOK_ENTERO  */
    TOK_RUTINA = 259,              /* TOK_RUTINA  */
    TOK_PRINCIPAL = 260,           /* TOK_PRINCIPAL  */
    TOK_SI = 261,                  /* TOK_SI  */
    TOK_ENTONCES = 262,            /* TOK_ENTONCES  */
    TOK_OTRO = 263,                /* TOK_OTRO  */
    TOK_MIENTRAS = 264,            /* TOK_MIENTRAS  */
    TOK_HAZ = 265,                 /* TOK_HAZ  */
    TOK_REGRESA = 266,             /* TOK_REGRESA  */
    TOK_PUNTO_Y_COMA = 267,        /* TOK_PUNTO_Y_COMA  */
    TOK_COMA = 268,                /* TOK_COMA  */
    TOK_PARENTESIS_ABRE = 269,     /* TOK_PARENTESIS_ABRE  */
    TOK_PARENTESIS_CIERRA = 270,   /* TOK_PARENTESIS_CIERRA  */
    TOK_LLAVE_ABRE = 271,          /* TOK_LLAVE_ABRE  */
    TOK_LLAVE_CIERRA = 272,        /* TOK_LLAVE_CIERRA  */
    TOK_CORCHETE_ABRE = 273,       /* TOK_CORCHETE_ABRE  */
    TOK_CORCHETE_CIERRA = 274,     /* TOK_CORCHETE_CIERRA  */
    TOK_MAYOR = 275,               /* TOK_MAYOR  */
    TOK_MENOR = 276,               /* TOK_MENOR  */
    TOK_ASIGNACION = 277,          /* TOK_ASIGNACION  */
    TOK_SUMA = 278,                /* TOK_SUMA  */
    TOK_RESTA = 279,               /* TOK_RESTA  */
    TOK_MULTIPLICACION = 280,      /* TOK_MULTIPLICACION  */
    TOK_DIVISION = 281,            /* TOK_DIVISION  */
    TOK_MAYOR_IGUAL = 282,         /* TOK_MAYOR_IGUAL  */
    TOK_MENOR_IGUAL = 283,         /* TOK_MENOR_IGUAL  */
    TOK_DIFERENTE = 284,           /* TOK_DIFERENTE  */
    TOK_IGUAL_IGUAL = 285,         /* TOK_IGUAL_IGUAL  */
    TOK_EOF = 286,                 /* TOK_EOF  */
    TOK_ERROR = 287,               /* TOK_ERROR  */
    TOK_UNKNOWN = 288,             /* TOK_UNKNOWN  */
    TOK_COMIENZA = 289,            /* TOK_COMIENZA  */
    TOK_TERMINA = 290,             /* TOK_TERMINA  */
    TOK_NUMERO = 291,              /* TOK_NUMERO  */
    TOK_CARACTER = 292,            /* TOK_CARACTER  */
    TOK_CADENA = 293,              /* TOK_CADENA  */
    TOK_IDENTIFICADOR = 294        /* TOK_IDENTIFICADOR  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 16 "AS.y"

    int entero;
    NodoPointer ap_id;
    IndexTablaCadenas pos_cad;
    int tipo;

#line 110 "AS.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_AS_TAB_H_INCLUDED  */
