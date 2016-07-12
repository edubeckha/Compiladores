%{
#include "ast.h"
#include "st.h"
#include <string.h>
ST::SymbolTable* symtab = new ST::SymbolTable();  /* main symbol table */
AST::Block *programRoot; /* the root node of our program AST:: */
std::vector<AST::Variable*> parametros;
std::vector<AST::Variable*> parametrosFuncao;
extern int yylex();
extern void yyerror(const char* s, ...);
static Tipos::Tipo tv = Tipos::indefinido;
bool variaveisEscopoClasse = false;
%}

%define parse.trace

/* yylval == %union
 * union informs the different ways we can store data
 */
%union {
    int integer;
    double doubler;
    const char* string;
    const char* booleano;
    AST::Node *node;
    AST::Block *block;
    AST::ConstrutorClasse* constClasse;
    Tipos::Operation operacao;
    const char *name;
    ST::SymbolTable* tabelaEscopo;
    Tipos::Tipo tipoVariavel;
}

/* token defines our terminal symbols (tokens).
 */
%token <integer> T_INT
%token <doubler> T_DOUBLE
%token <string> T_DSTRING
%token <booleano> T_BOOLTRUE T_BOOLFALSE
%token <name> T_ID
%token T_NL T_ASSIGN T_FINALEXP T_IGUAL T_DINT T_DREAL T_DBOOL  T_COMMA T_MAIOR T_MENOR T_MAIORIGUAL T_MENORIGUAL T_AND T_OR T_DIFERENTE T_UNIBOOL T_PARA T_PARAF T_ARRA T_ARRAF T_IF T_THEN T_ELSE T_END T_WHILE T_DO T_DEFI T_TYPE T_FUN T_RETO T_CHAVE T_CHAVEF T_CLASSE T_DOT T_NEW

/* type defines the type of our nonterminal symbols.
 * Types should match the names used in the union.
 * Example: %type<node> expr
 */

%type <node> expr line varlist unexpr declaracoes assignments condicionais elseIf definicoes param paramFuncao funcoesObjetos funcoesObjetosAssign declaracaoClasse possibilidadesEscopoClasse possibilidadesEscopoConstrutor
%type <block> lines program escopoClasse escopoConstrutor
%type <constClasse> construtorClasse
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
            | declaracaoClasse {$$ = $1;}
    		| assignments {$$ = $1;}
    		| condicionais {$$ = $1;}
            | definicoes {$$ = $1;}
            | funcoesObjetos {$$ = $1;}
        ;

declaracaoClasse :
            /*declaracao de classes*/
            T_CLASSE T_ID T_CHAVE novoEscopo escopoClasse construtorClasse mataEscopo T_CHAVEF {
            AST::Classe* c = symtab->newClass($2, $4, $5, $6); 
            $$ = new AST::UniOp(c, Tipos::declaracao, Tipos::indefinido); }
            ;

construtorClasse :
            T_ID T_PARA novoEscopo param T_PARAF T_CHAVE escopoConstrutor mataEscopo T_CHAVEF {$$ = new AST::ConstrutorClasse($1, parametros, $7); parametros.clear();}
            ;

possibilidadesEscopoConstrutor :
            declaracoes { $$ = $1; }
            | assignments { $$ = $1; }
            | funcoesObjetos {$$ = $1; }

escopoClasse :
            possibilidadesEscopoClasse {$$ = new AST::Block(); if($1 != NULL) $$->lines.push_back($1);} 
            | escopoClasse possibilidadesEscopoClasse {if($2 != NULL) $1->lines.push_back($2); }
            ;

escopoConstrutor :
            possibilidadesEscopoConstrutor {$$ = new AST::Block(); if($1 != NULL) $$->lines.push_back($1);} 
            | escopoConstrutor possibilidadesEscopoConstrutor {if($2 != NULL) $1->lines.push_back($2); }
            ;

possibilidadesEscopoClasse:
            declaracoes {$$ = $1;}
            | assignments {$$ = $1;}
            | condicionais {$$ = $1;}
            | definicoes {$$ = $1;}
            | funcoesObjetos {$$ = $1;}
            ;

funcoesObjetos: 
        T_ID T_DOT T_ID T_PARA paramFuncao T_PARAF T_FINALEXP {
        AST::Classe* c = symtab->useObjeto($1)->classePertencente; 
        symtab->useObjeto($1)->verificaParametros($3, parametrosFuncao); 
        $$ = new AST::BinOp(c->tabelaSimbolos->useFunction($3), Tipos::chamadaFuncao, symtab->useObjeto($1));
        parametrosFuncao.clear();}
        ;

funcoesObjetosAssign : 
        T_ID T_DOT T_ID T_PARA paramFuncao T_PARAF {
        AST::Classe* c = symtab->useObjeto($1)->classePertencente; 
        symtab->useObjeto($1)->verificaParametros($3, parametrosFuncao); 
        $$ = new AST::BinOp(c->tabelaSimbolos->useFunction($3), Tipos::chamadaFuncao, symtab->useObjeto($1));
        std::cout << Tipos::tipoParaString(c->tabelaSimbolos->useFunction($3)->tipo, true);
        parametrosFuncao.clear();}
        ;

declaracoes : 
    	/*declaracao de variaveis*/
    	tipoVariavel  varlist T_FINALEXP { $$ = new AST::UniOp($2, Tipos::declaracao, $1);}

		/*declaracao de arranjos*/
        |tipoVariavel T_ID T_ARRA unexpr T_ARRAF T_FINALEXP {AST::Node* var = symtab->newVariable($2, $1, NULL, false); $$ = new AST::UniOp(new AST::Arranjo($4 ,var), Tipos::declaracao, $1);};

        /*declaracao de funcoes*/
        | tipoVariavel T_ID novoEscopo T_PARA param T_PARAF mataEscopo T_FINALEXP {
          AST::Node* node = symtab->newFunction($2, $1, parametros);
          $$ = node;
          parametros.clear();
        }

         /*declaracao de objetos de uma classe*/
        | T_ID T_ID T_ASSIGN T_NEW T_ID T_PARA paramFuncao T_PARAF T_FINALEXP { 
        std::string pri = $1; std::string seg = $5; if(pri != seg) { std::cout << "Erro na declaracao do objeto: classe deve ser compativel com o tipo de objeto declarado." << std::endl; } 
        AST::Objeto* obj = symtab->newObjeto($2, symtab->useClass($1));
        obj->verificaParametrosConstrutor(parametrosFuncao);
        $$ = new AST::UniOp(obj, Tipos::declaracao, Tipos::indefinido );
        parametrosFuncao.clear();}
        ;

assignments : 
    	/*assign em variaveis*/
    	T_ID T_ASSIGN unexpr T_FINALEXP {AST::Node* node = symtab->assignVariable($1); node = AST::realizaCoercao($1, node, $3, symtab); $$ = new AST::BinOp(node,Tipos::assign,$3);}

    	/*assign em arranjos*/
    	|T_ID T_ARRA unexpr T_ARRAF T_ASSIGN unexpr T_FINALEXP {AST::Node* node = symtab->assignVariable($1); $$ = new AST::BinOp(new AST::Arranjo($3, node), Tipos::assign, $6);}

        /*assign em atributos de objetos*/
        |T_ID T_DOT T_ID T_ASSIGN unexpr T_FINALEXP { AST::Classe* c = symtab->useObjeto($1)->classePertencente; AST::Atributo* atri = c->tabelaSimbolos->assignAtributo((AST::Variable*) c->tabelaSimbolos->assignVariable($3), symtab->useObjeto($1)->classePertencente); 
        $$ = new AST::BinOp(atri, Tipos::assign, $5); }

        /*Reconhece uma ou mais declarações de retorno de uma função.*/
        | T_RETO unexpr T_FINALEXP {
            $$ = new AST::Retorno($2);
        }
        ;

condicionais: 
		/*tratamento de expressoes condicionais do tipo if*/
        T_IF T_PARA unexpr T_PARAF T_CHAVE novoEscopo lines mataEscopo T_CHAVEF elseIf { $$ = new AST::Condicao($3, $7, $10);}

		/*tratamento de lacos*/
        | T_WHILE T_PARA unexpr T_PARAF T_CHAVE novoEscopo lines mataEscopo T_CHAVEF { $$ = new AST::Laco($3, $7);}
		;

definicoes:
        /*definição da função previamente declarada.*/
        tipoVariavel T_ID novoEscopo T_PARA param T_PARAF T_CHAVE lines mataEscopo T_CHAVEF {
          AST::Node* var = symtab->assignFunction($2, $1, parametros, $8);
          $$ = new AST::DefineFuncao($2, $1, parametros, $8);
          parametros.clear();
        }
        ;
        
/*Trata da parte do else no laco if*/
elseIf : {$$ = NULL;}
    		| T_ELSE T_CHAVE novoEscopo lines mataEscopo T_CHAVEF {$$ = $4;}
    		;

/*Trata da parte de expressoes*/
unexpr : 
        unexpr tipoOperacao expr {$$ = new AST::BinOp($1, $2, $3);}
        | expr {$$ = $1;}
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
        | funcoesObjetosAssign {$$ = $1;}
        ;

/*define todos os tipos de variaveis que possamos ter no programa*/
tipoVariavel : 
        T_DINT { tv = Tipos::inteiro; $$ = Tipos::inteiro; } 
        | T_DREAL { tv = Tipos::real;  $$ = Tipos::real; }
        | T_DBOOL { tv = Tipos::booleano; $$ = Tipos::booleano; }
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
        T_ID {$$ = symtab->newVariable($1, tv, NULL, false); }
        | varlist T_COMMA T_ID { $$ = symtab->newVariable($3, tv, $1, false); }
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
        AST::Variable* vari = new AST::Variable($2, $1, $4);
        symtab->newVariable($2, $1, NULL, true);
        parametros.push_back(vari);
        $$ = vari;
      }
      |tipoVariavel  T_ID {
        AST::Variable* vari = new AST::Variable($2, $1, NULL);
        parametros.push_back(vari);
        symtab->newVariable($2, $1, NULL, true);
        $$ = vari;
      }
      | {$$ = NULL;}
      ;


/*recebe os parametros da funcao e da inicializacao de objetos*/
paramFuncao :
    T_INT T_COMMA paramFuncao {
        AST::Variable* vari = new AST::Variable(std::to_string($1), Tipos::inteiro, $3);
        parametrosFuncao.push_back(vari);
    }
    | T_DOUBLE T_COMMA paramFuncao {
        AST::Variable* vari = new AST::Variable(std::to_string($1), Tipos::real, $3);
        parametrosFuncao.push_back(vari);
    }
    | T_BOOLTRUE T_COMMA paramFuncao {
        AST::Variable* vari = new AST::Variable("true", Tipos::booleano, $3);
        parametrosFuncao.push_back(vari);
    }
    | T_BOOLFALSE T_COMMA paramFuncao {
        AST::Variable* vari = new AST::Variable("false", Tipos::booleano, $3);
        parametrosFuncao.push_back(vari);
    }
    | T_ID T_COMMA paramFuncao {
        AST::Variable* vari = new AST::Variable(dynamic_cast<AST::Variable*> (symtab->useVariable($1))->id, dynamic_cast<AST::Variable*> (symtab->useVariable($1))->tipo, $3);
        parametrosFuncao.push_back(vari);
    }
     | T_INT {
        AST::Variable* vari = new AST::Variable(std::to_string($1), Tipos::inteiro, NULL);
        parametrosFuncao.push_back(vari);
    }
    | T_DOUBLE {
        AST::Variable* vari = new AST::Variable(std::to_string($1), Tipos::real, NULL);
        parametrosFuncao.push_back(vari);
    }
    | T_BOOLTRUE {
        AST::Variable* vari = new AST::Variable("true", Tipos::booleano, NULL);
        parametrosFuncao.push_back(vari);
    }
    | T_BOOLFALSE {
        AST::Variable* vari = new AST::Variable("false", Tipos::booleano, NULL);
        parametrosFuncao.push_back(vari);
    }
    | T_ID {
        AST::Variable* vari = new AST::Variable(dynamic_cast<AST::Variable*> (symtab->useVariable($1))->id, dynamic_cast<AST::Variable*> (symtab->useVariable($1))->tipo, NULL);
        parametrosFuncao.push_back(vari);
    }
    ;

%%


