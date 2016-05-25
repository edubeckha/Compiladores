%{
#include "ast.h"
#include "st.h"

ST::SymbolTable symtab;  /* main symbol table */
std::vector<AST::Variable*> parametros;

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
    bool boolean;
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
%token T_DINT T_DREAL T_DBOOL T_PLUS T_SUB T_TIMES T_DIV T_DEF T_COMMA T_ASSIGN T_DIFERENTE T_MAIOR T_MENOR T_MAIORIGUAL T_MENORIGUAL T_AND T_OR T_UNIBOOL T_ATRI T_PARA T_PARAF T_FINALEXP T_NL T_END T_DEFI T_RETO T_DECL T_FUN

/* type defines the type of our nonterminal symbols.
 * Types should match the names used in the union.
 * Example: %type<node> expr
 */
%type <node> expr line varlist param funct teste //retorna
%type <block> lines program
%type <operacao> tipoOperacao 
%type <boolean> bool


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

line    : teste
		| funct
		;

        /*declara função com e sem parametros (inteiro somente)*/
funct   : T_DECL T_FUN tipoVariavel T_DEF T_ID T_PARA param T_PARAF T_FINALEXP { AST::Node* node = symtab.newFunction($5,AST::inteiro,parametros); $$ = new AST::Funcao($5, AST::inteiro, parametros); parametros.clear();}
        | T_DECL T_FUN tipoVariavel T_DEF T_ID T_PARA T_PARAF T_FINALEXP { AST::Node* node = symtab.newFunction($5,AST::inteiro,parametros); $$ = new AST::Funcao($5, AST::inteiro, parametros); }

        /*define a funcao*/
        | T_DEFI T_FUN T_DINT T_DEF T_ID T_PARA param T_PARAF teste T_END T_DEFI { AST::Node* node = symtab.assignFunction($5,parametros,$9); $$ = new AST::DefineFuncao($5,parametros, $9);}
        | T_DEFI T_FUN T_DINT T_DEF T_ID T_PARA T_PARAF teste T_END T_DEFI { AST::Node* node = symtab.assignFunction($5,parametros,$8);  $$ = new AST::DefineFuncao($5,parametros,$8);}
        ;

teste	: T_NL {$$ = NULL; } /*nothing here to be used */

        | expr T_FINALEXP {$$ = $1; } /*$$ = $1 when nothing is said*/

        | tipoVariavel T_DEF varlist T_FINALEXP {$$ = new AST::UniOp($3, AST::declaracao); }

        | T_ID T_ASSIGN expr T_FINALEXP { AST::Node* node = symtab.assignVariable($1); $$ = new AST::BinOp(node,AST::assign,$3);}

        | T_ID T_ASSIGN T_SUB T_INT T_FINALEXP { AST::Node* node = symtab.assignVariable($1); $$ = new AST::BinOp(node, AST::unario, new AST::Integer(-$4)); }
        | T_ID T_ASSIGN T_SUB T_DOUBLE T_FINALEXP { AST::Node* node = symtab.assignVariable($1); $$ = new AST::BinOp(node, AST::unario, new AST::Doubler(-$4)); }

        | T_ID T_ASSIGN T_UNIBOOL bool T_FINALEXP { AST::Node* node = symtab.assignVariable($1); $$ = new AST::BinOp(node, AST::unibool, new AST::Boolean(!$4)); }
        ;

//retorna : T_RETO expr T_FINALEXP {$$ = $2;}
//		;

/*define booleanos*/
bool    : T_BOOLTRUE {$$ = new AST::Boolean(true);}
        | T_BOOLFALSE {$$ = new AST::Boolean(false);}
        ;

/*tratamento de todas as expressoes utilizadas no programa*/
expr    : T_PARA expr T_PARAF { $$ = $2; }
        | T_INT { $$ = new AST::Integer($1); } 
        | T_DOUBLE { $$ = new AST::Doubler($1); }
        | T_BOOLTRUE { $$ = new AST::Boolean(true); }
        | T_BOOLFALSE { $$ = new AST::Boolean(false); }
        | T_ID { $$ = symtab.useVariable($1); }
        | expr tipoOperacao expr {$$ = new AST::BinOp($1, $2, $3);}        
        ;

/*define todos os tipos de variaveis que possamos ter no programa*/
tipoVariavel : T_DINT { tipoVariavel = AST::inteiro; } 
             | T_DREAL { tipoVariavel = AST::real; }
             | T_DBOOL { tipoVariavel = AST::booleano; }
             ;

/*define todos os tipos de operacoes que possamos ter no programa*/
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

/*define uma ou mais variaveis de acordo com a vontade do usuario*/
varlist : T_ID { $$ = symtab.newVariable($1, tipoVariavel, NULL); }
        | varlist T_COMMA T_ID { $$ = symtab.newVariable($3, tipoVariavel, $1); }
        ;

/*define um ou mais parametros de acordo com a vontade do usuario*/
param : tipoVariavel T_DEF T_ID T_COMMA param {AST::Variable* var = new AST::Variable($3,AST::inteiro,NULL); parametros.push_back(var);}
      | tipoVariavel T_DEF T_ID {AST::Variable* var = new AST::Variable($3,AST::inteiro,NULL); parametros.push_back(var); }
      ; 

%%