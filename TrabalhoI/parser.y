%{
#include "ast.h"
#include "st.h"
ST::SymbolTable symtab;  /* main symbol table */
AST::Block *programRoot; /* the root node of our program AST:: */
extern int yylex();
extern void yyerror(const char* s, ...);
static Tipos::Tipo tipoVariavel = Tipos::indefinido;
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
    Tipos::Operation operacao;
    const char *name;
}

/* token defines our terminal symbols (tokens).
 */
%token <integer> T_INT
%token <doubler> T_DOUBLE
%token <booleano> T_BOOLTRUE T_BOOLFALSE
%token <name> T_ID

%token T_DINT T_DREAL T_DBOOL T_PLUS T_SUB T_TIMES T_DIV T_DEF T_COMMA T_ASSIGN T_DIFERENTE T_MAIOR T_MENOR T_MAIORIGUAL T_MENORIGUAL T_AND T_OR T_UNIBOOL T_ATRI T_PARA T_PARAF T_FINALEXP T_NL T_IGUAL T_ARRA T_ARRAF

/* type defines the type of our nonterminal symbols.
 * Types should match the names used in the union.
 * Example: %type<node> expr
 */

%type <node> expr line varlist indiceArranjo
%type <block> lines program
%type <operacao> tipoOperacao operacaoArranjo

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
        
        /*declaracao de variaveis*/
        | tipoVariavel T_DEF varlist T_FINALEXP { $$ = new AST::UniOp($3, Tipos::declaracao, tipoVariavel); }

        /*assign em variaveis*/
        | T_ID T_ASSIGN expr T_FINALEXP { AST::Node* node = symtab.assignVariable($1); 
        node = AST::realizaCoercao($1, node, $3); 
        $$ = new AST::BinOp(node,Tipos::assign,$3);}

        /*declaracao de arranjos*/
        | tipoVariavel T_ARRA indiceArranjo T_ARRAF T_DEF T_ID T_FINALEXP {AST::Node* var = symtab.newVariable($6, tipoVariavel, NULL); $$ = new AST::UniOp( new AST::Arranjo($3 ,var), Tipos::declaracao, tipoVariavel);};
        
        /*assign em arranjos*/
        |T_ID T_ARRA indiceArranjo T_ARRAF T_ASSIGN expr T_FINALEXP {AST::Node* node = symtab.assignVariable($1); $$ = new AST::BinOp(new AST::Arranjo($3, node), Tipos::assign, $6);}
        ;

        /*tratamento de todas as expressoes utilizadas no programa*/
expr    : T_PARA expr T_PARAF { $$ = $2; }
        | T_INT { $$ = new AST::Integer($1); } 
        | T_DOUBLE { $$ = new AST::Doubler($1); }
        | T_BOOLTRUE { $$ = new AST::Boolean(true); }
        | T_BOOLFALSE { $$ = new AST::Boolean(false); }
        | T_ID { $$ = symtab.useVariable($1); }
        | expr tipoOperacao expr {$$ = new AST::BinOp($1, $2, $3);}  
        | T_ID T_ARRA indiceArranjo T_ARRAF {$$ = new AST::Arranjo($3, symtab.useVariable($1));} 
        | T_SUB expr {$$ = new AST::UniOp($2, Tipos::unario, tipoVariavel);}
        | T_UNIBOOL expr {$$ = new AST::UniOp($2, Tipos::unibool, tipoVariavel);}
        ;

/*trata indices de arranjo como inteiros, expressoes ou simplesmente variaveis ja atribuidas*/
indiceArranjo : T_INT operacaoArranjo indiceArranjo {$$ = new AST::BinOp(new AST::Integer($1), $2, $3);}
              | T_ID operacaoArranjo indiceArranjo { AST::Node* node = symtab.useVariable($1);  $$ = new AST::BinOp(node, $2, $3);}
              | T_ID {$$ = symtab.useVariable($1);}
              | T_INT {$$ = new AST::Integer($1);}
              ;

/*define operacoes permitidas no indice do arranjo*/
operacaoArranjo : T_PLUS {$$ = Tipos::plus;}
                | T_SUB {$$ = Tipos::sub;}
                | T_TIMES {$$ = Tipos::times;}
                ;

/*define todos os tipos de variaveis que possamos ter no programa*/
tipoVariavel : T_DINT { tipoVariavel = Tipos::inteiro; } 
             | T_DREAL { tipoVariavel = Tipos::real; }
             | T_DBOOL { tipoVariavel = Tipos::booleano; }
             ;
/*define todos os tipos de operacoes que possamos ter no programa*/
tipoOperacao : T_PLUS {$$ = Tipos::plus;}
             | T_SUB {$$ = Tipos::sub;}
             | T_TIMES {$$ = Tipos::times;}
             | T_DIV {$$ = Tipos::divi;}
             | T_MAIOR  {$$ = Tipos::maior;}
             | T_MENOR {$$ = Tipos::menor;}
             | T_MAIORIGUAL {$$ = Tipos::maiorigual;}
             | T_MENORIGUAL {$$ = Tipos::menorigual;}
             | T_AND {$$ = Tipos::ande;}
             | T_OR {$$ = Tipos::ore;}
             | T_IGUAL {$$ = Tipos::igual;}
             | T_DIFERENTE {$$ = Tipos::diferente;}
             ;
/*define uma ou mais variaveis de acordo com a vontade do usuario*/
varlist : T_ID { $$ = symtab.newVariable($1, tipoVariavel, NULL); }
        | varlist T_COMMA T_ID { $$ = symtab.newVariable($3, tipoVariavel, $1); }
        ;

%%


