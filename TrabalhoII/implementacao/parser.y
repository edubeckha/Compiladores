%{
#include "ast.h"
#include "st.h"
ST::SymbolTable* symtab = new ST::SymbolTable();  /* main symbol table */
AST::Block *programRoot; /* the root node of our program AST:: */
std::vector<AST::Variable*> teste;
std::vector<ST::Symbol*> parametros;
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
    const char* String;
    const char* booleano;
    AST::Node *node;
    AST::Block *block;
    Tipos::Operation operacao;
    const char *name;
    ST::SymbolTable* tabelaEscopo;
    Tipos::Tipo tipoVariavel;
}

/* token defines our terminal symbols (tokens).
 */
%token <integer> T_INT
%token <doubler> T_DOUBLE
%token <booleano> T_BOOLTRUE T_BOOLFALSE
%token <name> T_ID
%token <String> T_STRING
%token T_NL T_ASSIGN T_FINALEXP T_IGUAL T_DINT T_DREAL T_DBOOL  T_COMMA T_MAIOR T_MENOR T_MAIORIGUAL T_MENORIGUAL T_AND T_OR T_DIFERENTE T_UNIBOOL T_PARA T_PARAF T_ARRA T_ARRAF T_IF T_THEN T_ELSE T_END T_WHILE T_DO  T_TYPE T_FUN T_RETO T_CHAVE T_CHAVEF T_DSTRING T_SUBSTRG T_TAMANHO

/* type defines the type of our nonterminal symbols.
 * Types should match the names used in the union.
 * Example: %type<node> expr
 */

%type <node> expr line varlist unexpr declaracoes assignments condicionais elseIf definicoes param concString
%type <block> lines program corpoComplexo
%type <operacao> tipoOperacao
%type<tabelaEscopo> novoEscopo
%type<tipoVariavel> tipoVariavel

/* Operator precedence for mathematical operators
 * The latest it is listed, the highest the precedence
 */
%left T_PLUS T_SUB
%left T_TIMES T_DIV
%left T_UNIBOOL
%left T_MAIOR T_MAIORIGUAL T_MENOR T_MENORIGUAL 



%nonassoc error

/* Starting rule 
 */
%start program

%%

program : lines {programRoot = $1; }
        ;

lines   : line {$$ = new AST::Block(); if($1 != NULL) $$->lines.push_back($1); }
        | lines line {if($2 != NULL) $1->lines.push_back($2); }
        | lines error T_NL { yyerrok; }
        ;

line    : T_NL {$$ = NULL; } 
    		| declaracoes {$$ = $1;}
    		| assignments {$$ = $1;}
    		| condicionais {$$ = $1;}
        | definicoes {$$ = $1;}
        ;


declaracoes : 
    	/*declaracao de variaveis*/
    	tipoVariavel  varlist T_FINALEXP {$$ = new AST::UniOp($2, Tipos::declaracao, tv);}

		/*declaracao de arranjos*/
        |tipoVariavel T_ID T_ARRA unexpr T_ARRAF T_FINALEXP {AST::Node* var = symtab->newVariable($2, tv, NULL); $$ = new AST::UniOp(new AST::Arranjo($4 ,var), Tipos::declaracao, tv);};
		
        /*declaracao de arranjos do tipo complexo*/
        |T_ID T_ARRA unexpr T_ARRAF T_ID T_FINALEXP {AST::Node* complexo = symtab->useVariable($1);};

        /*declaracao de funcoes*/
        | T_FUN tipoVariavel  T_ID novoEscopo T_PARA param T_PARAF mataEscopo T_FINALEXP {
          AST::Node* node = symtab->newFunction($3, $2, parametros);
          $$ = new AST::Funcao($3, $2, teste);
          parametros.clear();
          teste.clear();
        }
        | T_ID T_SUBSTRG T_PARA T_INT T_COMMA T_INT T_PARAF T_FINALEXP {AST::Node* node = symtab->useVariable($1); $$ = new AST::Substring($1, node, $4, $6);}

        | T_ID T_TAMANHO T_PARA T_PARAF T_FINALEXP {AST::Node* node = symtab->useVariable($1); $$ = new AST::Tamanho($1, node); }
        ;

assignments : 
    		/*assign em variaveis*/
    		T_ID T_ASSIGN unexpr T_FINALEXP { AST::Node* node = symtab->assignVariable($1); node = AST::realizaCoercao($1, node, $3, symtab); $$ = new AST::BinOp(node,Tipos::assign,$3);}

    		/*assign em arranjos*/
    		|T_ID T_ARRA unexpr T_ARRAF T_ASSIGN unexpr T_FINALEXP {AST::Node* node = symtab->assignVariable($1); $$ = new AST::BinOp(new AST::Arranjo($3, node), Tipos::assign, $6);}

/////////////////////////////////
    		/*Assign em string*/
            |T_ID T_ASSIGN concString T_FINALEXP  { AST::Node* node = symtab->assignVariable($1); $$ = new AST::BinOp(node, Tipos::assign, $3); }

            /*Concatenação de duas strings.*/
           | T_ID T_ASSIGN concString {AST::Node* node = symtab->assignVariable($1); $$ = new AST::BinOp(node, Tipos::assign, $3); }
////////////////////////////////
        /*Reconhece uma ou mais declarações de retorno de uma função.*/
        | T_RETO unexpr T_FINALEXP { $$ = new AST::Retorno($2); }
        ;


/*Regras para reconhece o conteudo atribuido a uma variavel do tipo string e fazer a concatenação de strings.*/
concString : 
        //////////////////////////////////////
        T_STRING T_PLUS concString {AST::Node* n1 = new AST::String($1); $$ = new AST::BinOp(n1, Tipos::plus, $3); }

        | T_STRING T_FINALEXP {$$ =  new AST::String($1); }
        ;
       ///////////////////////////////////////

condicionais: 
		/*tratamento de expressoes condicionais do tipo if*/
        T_IF T_PARA unexpr T_PARAF T_CHAVE novoEscopo lines mataEscopo T_CHAVEF elseIf { $$ = new AST::Condicao($3, $7, $10);}

		/*tratamento de lacos*/
        | T_WHILE T_PARA unexpr T_PARAF T_CHAVE novoEscopo lines mataEscopo T_CHAVEF { $$ = new AST::Laco($3, $7);}
		;

definicoes:
        /*Definicao de tipos complexos*/
         T_TYPE  T_ID novoEscopo corpoComplexo mataEscopo T_END  {AST::Node* var = symtab->newVariable($2, Tipos::complexo, NULL); $$ = new AST::Complexo(var, $4, $3);}

        /*definição da função previamente declarada.*/
        | T_FUN tipoVariavel  T_ID novoEscopo T_PARA param T_PARAF lines mataEscopo T_END  {
          AST::Node* var = symtab->assignFunction($3, $2, parametros, $8);
          $$ = new AST::DefineFuncao($3, $2, teste, $8);
        }
        ;
        

/*Trata do que pode ser aceito no corpo de uma estrutura complexa. Tratado como um bloco a parte do programa*/
corpoComplexo  : 
        declaracoes {$$ = new AST::Block(); if($1 != NULL) $$->lines.push_back($1); }
        | corpoComplexo declaracoes { if($2 != NULL) $1->lines.push_back($2); }
        ;

/*Trata da parte do else no laco if*/
elseIf : {$$ = NULL;}
    		| T_ELSE T_CHAVE novoEscopo lines mataEscopo T_CHAVEF {$$ = $4;}
    		;

/*Trata da parte de expressoes*/
unexpr : 
        unexpr tipoOperacao expr {$$ = new AST::BinOp($1, $2, $3);}
        | expr {$$ = $1;}
        ///////////////////////////////////////
        | T_STRING T_IGUAL T_STRING {AST::Node* n1 = new AST::String($1); AST::Node* n2 = new AST::String($1); $$ = new AST::BinOp(n1, Tipos::igual, n2);}
        ///////////////////////////////////////
		;

/*tratamento de todas as expressoes utilizadas no programa*/
expr    : T_PARA unexpr T_PARAF {$$ = $2;}
        | T_INT { $$ = new AST::Integer($1); } 
        | T_DOUBLE { $$ = new AST::Doubler($1); }
        | T_BOOLTRUE { $$ = new AST::Boolean(true); }
        | T_BOOLFALSE { $$ = new AST::Boolean(false); }
        | T_ID { $$ = symtab->useVariable($1); }
        | T_SUB expr {$$ = new AST::UniOp($2, Tipos::unario, $2->tipo);}
        | T_UNIBOOL expr {$$ = new AST::UniOp($2, Tipos::unibool, Tipos::booleano);}
        | T_ID T_ARRA expr T_ARRAF {$$ = new AST::Arranjo($3, symtab->useVariable($1));} 
        ;

/*define todos os tipos de variaveis que possamos ter no programa*/
tipoVariavel : 
        T_DINT { tv = Tipos::inteiro; } 
        | T_DREAL { tv = Tipos::real; }
        | T_DBOOL { tv = Tipos::booleano; }
        ////////////////////////////
        | T_DSTRING { tv = Tipos::string; }
        ////////////////////////////
        ;
/*define todos os tipos de operacoes que possamos ter no programa*/
tipoOperacao : 
        T_PLUS {$$ = Tipos::plus;}
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
varlist : 
        T_ID { $$ = symtab->newVariable($1, tv, NULL); }
        | varlist T_COMMA T_ID { $$ = symtab->newVariable($3, tv, $1); }
        ;

/*define um novo escopo para as mais diferentes estruturas, como lacos condicionais, funcoes, etc. Para isso, a mesma cria uma nova
tabela de escopo e seta a tabela de origem da mesma como a tabela atual do sistema. Depois disso, torna a tabela criada como a padrao
para ser utilizada no momento*/
novoEscopo : {ST::SymbolTable* tabelaEscopo = new ST::SymbolTable; tabelaEscopo->defineTabelaOrigem(symtab); symtab = tabelaEscopo; $$ = symtab;}

/*Encerra o escopo de uma tabela de simbolos, dando a autoridade para a tabela que deu origem a tabela encerrada*/
mataEscopo : {symtab = symtab->tabelaOrigem;}

/*define um ou mais parametros de acordo com a vontade do usuario*/
param : 
      tipoVariavel  T_ID T_COMMA param {
        ST::Symbol* smb = new ST::Symbol(tv, ST::variable, 0, false);
        symtab->addSymbol($2, *smb);
        parametros.push_back(smb);
        AST::Variable* vari = new AST::Variable($2, tv, $4);
        teste.push_back(vari);
        $$ = vari;
      }
      |tipoVariavel  T_ID {
        ST::Symbol* smb = new ST::Symbol(tv, ST::variable, 0, false);
        symtab->addSymbol($2, *smb);
        parametros.push_back(smb);
        AST::Variable* vari = new AST::Variable($2, tv, NULL);
        teste.push_back(vari);
        $$ = vari;
      }
      | {$$ = NULL;}
      ;
%%
