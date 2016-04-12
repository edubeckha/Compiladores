%{
#include <string>
#include "ast.h"
#include "parser.h"
extern int yylineno;
void yyerror(const char* s, ...);
%}

%option noyywrap nodefault yylineno

digsInt [0-9]+
digsDouble [0-9]+\.[0-9]* 
variavel [a-z][a-z0-9]*
reservado def

%%

[ \t]               ; //ignores spaces
{reservado}			{return T_DEF;}
{digsInt}           {yylval.integer = std::atoi(yytext); return T_INT;}
{digsDouble}		{std::cout<<yytext<<std::endl;yylval.doubler = std::atof(yytext); std::cout<<T_DOUBLE<<std::endl; return T_DOUBLE;}
"+"                 {return T_PLUS;}
"*"					{return T_MULT;}
{variavel}			{yylval.variavel = (char*) strdup(yytext); return T_VARIAVEL;}
\n                  {return T_NL;}
.                   {yyerror("Unknown token! %c\n", *yytext);} /*complains about every unknown character*/

%%

void yyerror(const char *s, ...){
    va_list ap;
    va_start(ap, s);
    std::fprintf(stderr, "Line %d: error: ", yylineno);
    std::vfprintf(stderr, s, ap);
}
