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
    char* tipo;
    char* nome;
    AST::Node *node;
    AST::Block *block;
}

/* token defines our terminal symbols (tokens).
 */

%token T_ATRIBUICAO T_DECLNOME T_FINALEXP

%token <tipo> T_DECLINT T_DECLREAL T_DECLBOOL
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

expr    : T_DECLINT T_NOME { std::cout << $1 << " - " << $2 << std::endl; $$ = new AST::Variavel($1, $2); } 
        | T_DECLREAL T_NOME { std::cout << $1 << " - " << $2 << std::endl; $$ = new AST::Variavel($1, $2); }
        | T_DECLBOOL T_NOME { std::cout << $1 << " - " << $2 << std::endl; $$ = new AST::Variavel($1, $2); }
    //  | expr error { yyerrok; $$ = $1; } 
        ;

%%

