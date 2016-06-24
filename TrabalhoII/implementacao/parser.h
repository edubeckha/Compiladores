/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    T_INT = 258,
    T_DOUBLE = 259,
    T_BOOLTRUE = 260,
    T_BOOLFALSE = 261,
    T_ID = 262,
    T_NL = 263,
    T_ASSIGN = 264,
    T_FINALEXP = 265,
    T_IGUAL = 266,
    T_DINT = 267,
    T_DREAL = 268,
    T_DBOOL = 269,
    T_DEF = 270,
    T_COMMA = 271,
    T_MAIOR = 272,
    T_MENOR = 273,
    T_MAIORIGUAL = 274,
    T_MENORIGUAL = 275,
    T_AND = 276,
    T_OR = 277,
    T_DIFERENTE = 278,
    T_UNIBOOL = 279,
    T_PARA = 280,
    T_PARAF = 281,
    T_ARRA = 282,
    T_ARRAF = 283,
    T_IF = 284,
    T_THEN = 285,
    T_ELSE = 286,
    T_END = 287,
    T_WHILE = 288,
    T_DO = 289,
    T_DEFI = 290,
    T_TYPE = 291,
    T_FUN = 292,
    T_RETO = 293,
    T_DECL = 294,
    T_PLUS = 295,
    T_SUB = 296,
    T_TIMES = 297,
    T_DIV = 298
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 21 "parser.y" /* yacc.c:1909  */

    int integer;
    double doubler;
    const char* booleano;
    AST::Node *node;
    AST::Block *block;
    Tipos::Operation operacao;
    const char *name;
    ST::SymbolTable* tabelaEscopo;
    Tipos::Tipo tipoVariavel;

#line 110 "parser.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
