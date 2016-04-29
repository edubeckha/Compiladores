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
varReal [0-9]+.[0-9]*|[0-9]*.[0-9]+

%%

[ \t]               ; //ignores spaces
"inteiro"			{return T_DECLINT;}
":"					{return T_DECLNOME;}
":="				{return T_ATRIBUICAO;}
";"					{return T_FINALEXP;}
{nome}				{yylval.nome = (char*) strdup(yytext); return T_NOME;}
.                   {yyerror("Unknown token! %c\n", *yytext);} /*complains about every unknown character*/

%%

void yyerror(const char *s, ...){
    va_list ap;
    va_start(ap, s);
    std::fprintf(stderr, "Line %d: error: ", yylineno);
    std::vfprintf(stderr, s, ap);
}
