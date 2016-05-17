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

%token T_DINT T_DREAL T_DBOOL T_PLUS T_SUB T_TIMES T_DIV T_DEF T_COMMA T_ASSIGN T_DIFERENTE T_MAIOR T_MENOR T_MAIORIGUAL T_MENORIGUAL T_AND T_OR T_UNIBOOL T_ATRI T_PARA T_PARAF T_FINALEXP T_NL T_IGUAL T_ARRA T_ARRAF

/* type defines the type of our nonterminal symbols.
 * Types should match the names used in the union.
 * Example: %type<node> expr
 */

%type <node> expr line varlist indiceArranjo tesIgual tesDif
%type <block> lines program
%type <operacao> tipoOperacao operacaoArranjo
%type <boolean> bool //verificar a possivel remocao deste type


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
        | tipoVariavel T_DEF varlist T_FINALEXP { $$ = new AST::UniOp($3, AST::declaracao); }

        /*assign em variaveis*/
        | T_ID T_ASSIGN expr T_FINALEXP { AST::Node* node = symtab.assignVariable($1); $$ = new AST::BinOp(node,AST::assign,$3);}

        /*expressoes unarias para inteiro e booleano*/
        | T_ID T_ASSIGN T_SUB expr T_FINALEXP { AST::Node* node = symtab.assignVariable($1); $$ = new AST::BinOp(node, AST::unario,$4); }
        | T_ID T_ASSIGN tesIgual { AST::Node* node = symtab.assignVariable($1); $$ = new AST::BinOp(node, AST::igual, $3 ); }
        | T_ID T_ASSIGN tesDif { AST::Node* node = symtab.assignVariable($1); $$ = new AST::BinOp(node, AST::diferente, $3 ); }
        | T_ID T_ASSIGN T_UNIBOOL expr T_FINALEXP { AST::Node* node = symtab.assignVariable($1); $$ = new AST::BinOp(node, AST::unibool,$4); }
        | T_ID T_ASSIGN T_SUB T_INT T_FINALEXP { AST::Node* node = symtab.assignVariable($1); $$ = new AST::BinOp(node, AST::unario, new AST::Integer(-$4) ); }
        | T_ID T_ASSIGN T_SUB T_DOUBLE T_FINALEXP { AST::Node* node = symtab.assignVariable($1); $$ = new AST::BinOp(node, AST::unario, new AST::Doubler(-$4) ); }
        | T_ID T_ASSIGN T_UNIBOOL bool T_FINALEXP { AST::Node* node = symtab.assignVariable($1); $$ = new AST::BinOp(node, AST::unibool, new AST::Boolean(!$4)); }

        /*declaracao de arranjos*/
        | tipoVariavel T_ARRA indiceArranjo T_ARRAF T_DEF T_ID T_FINALEXP {AST::Node* var = symtab.newVariable($6, tipoVariavel, NULL); $$ = new AST::UniOp( new AST::Arranjo($3 ,var), AST::declaracao);};
        
        /*assign em arranjos*/
        |T_ID T_ARRA indiceArranjo T_ARRAF T_ASSIGN expr T_FINALEXP {AST::Node* node = symtab.assignVariable($1); $$ = new AST::BinOp(new AST::Arranjo($3, node), AST::assign, $6);}

        /*definicao de tipos complexos*/
        ;

/*trata indices de arranjo como inteiros, expressoes ou simplesmente variaveis ja atribuidas*/
indiceArranjo : T_INT operacaoArranjo indiceArranjo {$$ = new AST::BinOp(new AST::Integer($1), $2, $3);}
              | T_ID operacaoArranjo indiceArranjo { AST::Node* node = symtab.useVariable($1);  $$ = new AST::BinOp(node, $2, $3);}
              | T_ID {$$ = symtab.useVariable($1);}
              | T_INT {$$ = new AST::Integer($1);}
              ;

/*define operacoes permitidas no indice do arranjo*/
operacaoArranjo : T_PLUS {$$ = AST::plus;}| T_SUB {$$ = AST::sub;}| T_TIMES {$$ = AST::times;}

/*define booleanos*/
bool    : T_BOOLTRUE {$$ = new AST::Boolean(true);}
        | T_BOOLFALSE {$$ = new AST::Boolean(false);}
        ;  
/*define igualdade de expressoes*/
tesIgual : expr T_IGUAL expr T_FINALEXP

/*define diferenca em expressoes*/
tesDif : expr T_DIFERENTE expr T_FINALEXP

/*tratamento de todas as expressoes utilizadas no programa*/
expr    : T_PARA expr T_PARAF { $$ = $2; }
        | T_INT { $$ = new AST::Integer($1); } 
        | T_DOUBLE { $$ = new AST::Doubler($1); }
        | T_BOOLTRUE { $$ = new AST::Boolean(true); }
        | T_BOOLFALSE { $$ = new AST::Boolean(false); }
        | T_ID { $$ = symtab.useVariable($1); }
        | expr tipoOperacao expr {$$ = new AST::BinOp($1, $2, $3);}  
        | T_ID T_ARRA indiceArranjo T_ARRAF {$$ = new AST::Arranjo($3, symtab.useVariable($1));}      
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

%%


