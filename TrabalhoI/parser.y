%{
#include "ast.h"
#include "st.h"
ST::SymbolTable symtab;  /* main symbol table */
AST::Block *programRoot; /* the root node of our program AST:: */
extern int yylex();
extern void yyerror(const char* s, ...);
static AST::Tipo tipoVariavel = AST::indefinido;
%}

%define parse.trace

/* yylval == %union
 * union informs the different ways we can store data
 */
%union {
    int integer;
    double doubler;
    bool bolean;
    const char* booleano;
    AST::Node *node;
    AST::Block *block;
    AST::Operation operacao;
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
%type <node> expr line varlist
%type <block> lines program
%type <operacao> tipoOperacao


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

        | tipoVariavel T_DEF varlist T_FINALEXP { $$ = new AST::UniOp($3, AST::declaracao); }

        | T_ID T_ASSIGN expr T_FINALEXP { AST::Node* node = symtab.assignVariable($1); $$ = new AST::BinOp(node,AST::assign,$3);}

        | T_ID T_ASSIGN T_SUB T_INT { AST::Node* node = symtab.assignVariable($1); $$ = new AST::UniOp(node, AST::unario); }

        | T_ID T_ASSIGN T_SUB T_DOUBLE { AST::Node* node = symtab.assignVariable($1); $$ = new AST::UniOp(node, AST::unario); }

        | T_ID T_ASSIGN T_UNIBOOL T_ID { AST::Node* node = symtab.assignVariable($1); $$ = new AST::UniOp(node, AST::unibool); }
        ;

expr    : T_PARA expr T_PARAF { $$ = $2; }

        | T_INT { $$ = new AST::Integer($1); }
        
        | T_DOUBLE { $$ = new AST::Doubler($1); }
        
        | T_BOOLTRUE { $$ = new AST::Boolean(true); }

        | T_BOOLFALSE { $$ = new AST::Boolean(false); }
     	
        | T_ID { $$ = symtab.useVariable($1); }

        | expr tipoOperacao expr {$$ = new AST::BinOp($1, $2, $3);}        
        ;

tipoVariavel : T_DINT { tipoVariavel = AST::inteiro; } 
             | T_DREAL { tipoVariavel = AST::real; }
             | T_DBOOL { tipoVariavel = AST::booleano; }
             ;

tipoOperacao : T_PLUS {$$ = AST::plus;}
             | T_SUB {$$ = AST::sub;}
             | T_TIMES {$$ = AST::times;}
             | T_DIV {$$ = AST::divi;}
             | T_MAIOR  {$$ = AST::maior;}
             | T_MENOR {$$ = AST::menor;}
             | T_MAIORIGUAL {$$ = AST::maiorigual;}
             | T_MENORIGUAL {$$ = AST::menorigual;}
             | T_AND {$$ = AST::ande;}
             | T_OR {$$ = AST::ore;}
             ;

varlist : T_ID { $$ = symtab.newVariable($1, tipoVariavel, NULL); }
        | varlist T_COMMA T_ID { $$ = symtab.newVariable($3, tipoVariavel, $1); }
        ;

%%


