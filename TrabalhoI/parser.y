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
    char* nome;
    AST::Node *node;
    AST::Block *block;
}

/* token defines our terminal symbols (tokens).
 */

%token T_ATRIBUICAO T_DECLNOME T_FINALEXP


%token <nome> T_NOME 

%token T_NL


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


/* %left T_PLUS
%left T_NOME
%left T_MULT
%left T_DECLINT
%left T_DECREAL
%left T_DECBOOL
%left T_INT
%left T_REAL
%left T_BOOLTRUE
%left T_BOOLFALSE
%left T_PLUS
%left T_MENOS
%left T_MULT
%left T_DIV
%left T_IGUAL
%left T_DIFERENTE
%left T_MAIOR
%left T_MENOR
%left T_MAIORIGUAL
%left T_MENORIGUAL
%left T_AND
%left T_OR
%left T_UNIBOOL
%left T_ATRIBUICAO
%left T_ABREPAR
%left T_FECHAPAR
%left T_FINALEXP
%left T_NL
*/

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

expr    : T_NOME { std::cout << $1 << std::endl; $$ = new AST::Nome($1); } 


    //  | expr error { yyerrok; $$ = $1; } 
        ;

%%

