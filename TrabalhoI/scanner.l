%{
#include <string>
#include "ast.h"
#include "parser.h"
extern int yylineno;
void yyerror(const char* s, ...);
%}

%option noyywrap nodefault yylineno

nome [a-z]+
varInteiro [0-9]+
varReal [0-9]+.[0-9]* | [0-9]*.[0-9]+

%%

[ \t]               ; //ignores spaces
"inteiro"			{RETURN T_DECLINT;}
"real"				{RETURN T_DECREAL;}
"booleano"			{RETURN T_DECBOOL;}
{varInteiro}        {yylval.integer = std::atoi(yytext); return T_INT;}
{varReal}			{yylval.doubler = std::atof(yytext); return T_REAL;}
"TRUE"				{RETURN T_BOOLTRUE;}
"FALSE"				{RETURN T_BOOLFALSE;}
"+"                 {RETURN T_PLUS;}
"-"                 {RETURN T_MENOS;}
"*"					{RETURN T_MULT;}
"/"                 {RETURN T_DIV;}
"="					{RETURN T_IGUAL;}
"~="				{RETURN T_DIFERENTE;}
">"					{RETURN T_MAIOR;}
"<"					{RETURN T_MENOR;}
">="				{RETURN T_MAIORIGUAL;}
"<="				{RETURN T_MENORIGUAL;}
"AND"				{RETURN T_AND;}
"OR"				{RETURN T_OR;}
"~"					{RETURN T_UNIBOOL;}
":="				{RETURN T_ATRIBUICAO;}
"("					{RETURN T_ABREPAR;}
")"					{RETURN T_FECHAPAR;}
";"					{RETURN T_FINALEXP;}
{nome}				{yylval.nome = (char*) strdup(yytext); return T_NOME;}
\n                  {return T_NL;}
.                   {yyerror("Unknown token! %c\n", *yytext);} /*complains about every unknown character*/

%%

void yyerror(const char *s, ...){
    va_list ap;
    va_start(ap, s);
    std::fprintf(stderr, "Line %d: error: ", yylineno);
    std::vfprintf(stderr, s, ap);
}
