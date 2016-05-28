%{
#include "ast.h"
#include "st.h"
ST::SymbolTable* symtab = new ST::SymbolTable();  /* main symbol table */
std::vector<ST::Symbol*> parametros;
AST::Block *programRoot; /* the root node of our program AST:: */
extern int yylex();
extern void yyerror(const char* s, ...);
static Tipos::Tipo tv = Tipos::indefinido;
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
%token T_NL T_ASSIGN T_FINALEXP T_IGUAL T_DINT T_DREAL T_DBOOL T_DEF T_COMMA T_MAIOR T_MENOR T_MAIORIGUAL T_MENORIGUAL T_AND T_OR T_DIFERENTE T_UNIBOOL T_PARA T_PARAF T_ARRA T_ARRAF T_IF T_THEN T_ELSE T_END T_WHILE T_DO T_DECL T_FUN T_DEFI T_RETO

/* type defines the type of our nonterminal symbols.
 * Types should match the names used in the union.
 * Example: %type<node> expr
 */

%type <node> expr line varlist unexpr declaracoes assignments condicionais elseIf param //funct
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

line    : T_NL { $$ = NULL; } 
		| declaracoes {$$ = $1;}
		| assignments {$$ = $1;}
		| condicionais {$$ = $1;}
        ;

declaracoes : 
		/*declaracao de variaveis*/
		tipoVariavel T_DEF varlist T_FINALEXP { $$ = new AST::UniOp($3, Tipos::declaracao, tv);}

		/*declaracao de arranjos*/
        |tipoVariavel T_ARRA unexpr T_ARRAF T_DEF T_ID T_FINALEXP {AST::Node* var = symtab->newVariable($6, tv, NULL); $$ = new AST::UniOp(new AST::Arranjo($3 ,var), Tipos::declaracao, tv);};

////////////////////////////////////////////////////
        | T_DECL T_FUN tipoVariavel T_DEF T_ID novoEscopo T_PARA param T_PARAF mataEscopo T_FINALEXP {
        	AST::Node* node = symtab->newFunction($5, Tipos::inteiro, parametros);
        	$$ = new AST::UniOp(new AST::Funcao($5, Tipos::inteiro, node), Tipos::declaracao, tv);
        	}
////////////////////////////////////////////////////
		;

assignments : 
		/*assign em variaveis*/
		T_ID T_ASSIGN unexpr T_FINALEXP { AST::Node* node = symtab->assignVariable($1); node = AST::realizaCoercao($1, node, $3); $$ = new AST::BinOp(node,Tipos::assign,$3);}

		/*assign em arranjos*/
		|T_ID T_ARRA unexpr T_ARRAF T_ASSIGN unexpr T_FINALEXP {AST::Node* node = symtab->assignVariable($1); $$ = new AST::BinOp(new AST::Arranjo($3, node), Tipos::assign, $6);}

condicionais: 
		/*tratamento de expressoes condicionais do tipo if*/
        T_IF unexpr T_THEN novoEscopo lines mataEscopo elseIf T_END T_IF{ $$ = new AST::Condicao($2, $5, $7);}
		
		/*tratamento de lacos*/
        | T_WHILE unexpr T_DO novoEscopo lines mataEscopo T_END T_WHILE { $$ = new AST::Laco($2, $5);}
////////////////////////////////////////////////////
        | T_DEFI T_FUN T_DINT T_DEF T_ID novoEscopo T_PARA param T_PARAF lines mataEscopo T_END T_DEFI { $$ = new AST::DefineFuncao($5, $8, $10);
        	}
///////////////////////////////////////////////////
		;

elseIf : {$$ = NULL;}
		| T_ELSE novoEscopo lines mataEscopo {$$ = $3;}
		;

unexpr : expr {$$ = $1;}
		| unexpr tipoOperacao expr {$$ = new AST::BinOp($1, $2, $3);} 
		;

/*tratamento de todas as expressoes utilizadas no programa*/
expr    :
         T_INT { $$ = new AST::Integer($1); } 
        | T_DOUBLE { $$ = new AST::Doubler($1); }
        | T_BOOLTRUE { $$ = new AST::Boolean(true); }
        | T_BOOLFALSE { $$ = new AST::Boolean(false); }
        | T_ID { $$ = symtab->useVariable($1); }
        | T_SUB expr {$$ = new AST::UniOp($2, Tipos::unario, tv);}
        | T_UNIBOOL expr {$$ = new AST::UniOp($2, Tipos::unibool, tv);}
        | T_ID T_ARRA expr T_ARRAF {$$ = new AST::Arranjo($3, symtab->useVariable($1));} 
        ;

/*define todos os tipos de variaveis que possamos ter no programa*/
tipoVariavel : T_DINT { tv = Tipos::inteiro; } 
             | T_DREAL { tv = Tipos::real; }
             | T_DBOOL { tv = Tipos::booleano; }
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
varlist : T_ID { 
			$$ = symtab->newVariable($1, tv, NULL);
		}
        | varlist T_COMMA T_ID { 
        	$$ = symtab->newVariable($3, tv, $1);
        }
        ;

novoEscopo : {	ST::SymbolTable* tabelaEscopo = new ST::SymbolTable;
				tabelaEscopo->defineTabelaOrigem(symtab);
				symtab = tabelaEscopo;
				}

mataEscopo : {symtab = symtab->tabelaOrigem;}

////////////////////////////////////////////////////////////////////////////////
/*define um ou mais parametros de acordo com a vontade do usuario*/
param : tipoVariavel T_DEF T_ID T_COMMA param {
			ST::Symbol* smb = new ST::Symbol(tv, ST::variable, 0, false);
			symtab->addSymbol($3, *smb);
			AST::Variable* vari = new AST::Variable($3, Tipos::inteiro, $5);
			$$ = vari;
		}
      | 
      tipoVariavel T_DEF T_ID {
      		ST::Symbol* smb = new ST::Symbol(tv, ST::variable, 0, false);
			symtab->addSymbol($3, *smb);
			AST::Variable* vari = new AST::Variable($3, Tipos::inteiro, NULL);
			$$ = vari;
      	}
      	| {$$ = NULL;}
      ;
////////////////////////////////////////////////////////////////////////////////
%%

//decl fun int:sa(int:ab, real:bned, bool:er);
//def fun int:sa(int:wr, real:wrww, bool:etee) int:reww, refr, tew; real:worhwor, hworhwo, whohgro; end def
