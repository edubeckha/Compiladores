%{
#include "ast.h"
AST::Block *programRoot; /* the root node of our program AST:: */
extern int yylex();
extern void yyerror(const char* s, ...);
%}

/* yylval == %union
 * union informs the different ways we can store data
 */
%union {
    const char* variavel;
    int integer;
    double doubler;
    AST::Node *node;
    AST::Block *block;
}

/* token defines our terminal symbols (tokens).
 */
%token <reservado> T_DEF
%token <variavel> T_VARIAVEL
%token <integer> T_INT
%token <doubler> T_DOUBLE
%token T_PLUS T_NL T_MULT


/* type defines the type of our nonterminal symbols.
 * Types should match the names used in the union.
 * Example: %type<node> expr
 */
%type <node> expr line
%type <block> lines program
/*%type <node> 
*/

/* Operator precedence for mathematical operators
 * The latest it is listed, the highest the precedence
 */
%left T_PLUS
%left T_MULT
%nonassoc error

/* Starting rule 
 */
%start program

%%

program : lines { programRoot = $1; }
        ;
        

lines   : line { $$ = new AST::Block(); $$->lines.push_back($1); }
        | lines line { if($2 != NULL) $1->lines.push_back($2); }
        ;

line    : T_NL { $$ = NULL; } /*nothing here to be used */
        | expr T_NL /*$$ = $1 when nothing is said*/
        ;

expr    : T_INT { $$ = new AST::Integer($1); }
        | expr T_PLUS expr { $$ = new AST::BinOp($1,AST::plus,$3); }
        | expr T_MULT expr { $$ = new AST::BinOp($1, AST::mult, $3); }
    //    | expr error { yyerrok; $$ = $1; } /*just a point for error recovery*/
        | T_DOUBLE { $$ = new AST::Double($1); }
        ;

%%


