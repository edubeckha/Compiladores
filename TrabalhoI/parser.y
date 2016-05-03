%{
#include "ast.h"
#include "st.h"
ST::SymbolTable symtab;  /* main symbol table */
AST::Block *programRoot; /* the root node of our program AST:: */
extern int yylex();
extern void yyerror(const char* s, ...);
%}

%define parse.trace

/* yylval == %union
 * union informs the different ways we can store data
 */
%union {
    int integer;
    double doubler;
    const char* booleano;
    AST::Node *node;
    AST::Block *block;
    const char *name;
}

/* token defines our terminal symbols (tokens).
 */
%token <integer> T_INT
%token <doubler> T_DOUBLE
%token <booleano> T_BOOLTRUE T_BOOLFALSE
%token <name> T_ID
%token T_DINT T_DREAL T_DBOOL T_PLUS T_SUB T_TIMES T_DIV T_DEF T_COMMA T_ASSIGN T_DIFERENTE T_MAIOR T_MENOR T_MAIORIGUAL T_MENORIGUAL T_AND T_OR T_UNIBOOL T_ATRI T_PARA T_PARAF T_FINALEXP T_NL 




/* type defines the type of our nonterminal symbols.
 * Types should match the names used in the union.
 * Example: %type<node> expr
 */
%type <node> expr line varlist tipoVariavel
%type <block> lines program




/* Operator precedence for mathematical operators
 * The latest it is listed, the highest the precedence
 */
%left T_PLUS T_SUB
%left T_TIMES T_DIV
%nonassoc error

/* Starting rule 
 */
%start program

%%

program : lines { programRoot = $1; }
        ;

lines   : line { $$ = new AST::Block(); if($1 != NULL) $$->lines.push_back($1); }
        | lines line { if($2 != NULL) $1->lines.push_back($2); }
        | lines error T_NL { yyerrok; }
        ;

line    : T_NL { $$ = NULL; } /*nothing here to be used */
        | expr T_FINALEXP /*$$ = $1 when nothing is said*/
        | tipoVariavel T_DEF varlist T_FINALEXP { $$ = $1; }
        | T_ID T_ASSIGN expr {  AST::Node* node = symtab.assignVariable($1); $$ = new AST::BinOp(node,AST::assign,$3); }
        ;

expr    : T_INT { $$ = new AST::Integer($1); }
        | T_DOUBLE { $$ = new AST::Doubler($1); }
        | T_ID { $$ = symtab.useVariable($1); }
        | expr T_PLUS expr { $$ = new AST::BinOp($1,AST::plus,$3); }
        | expr T_TIMES expr { $$ = new AST::BinOp($1,AST::times,$3); }
        ;

tipoVariavel : T_DINT { $$ = new AST::TipoVariavel(AST::inteiro); } 
             | T_DREAL { $$ = new AST::TipoVariavel(AST::real); }
             | T_DBOOL { $$ = new AST::TipoVariavel(AST::booleano); }
             ;

varlist : T_ID { $$ = symtab.newVariable($1, NULL); }
        | varlist T_COMMA T_ID { $$ = symtab.newVariable($3, $1); }
        ;

%%


