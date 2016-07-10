/*Ja previamente definido por Laércio Lima Pilla e ampliado para aceitar funcoes e outros tipos de estruturas*/
#pragma once
//Global Includes
#include <map>
#include <cassert>
//Local Includes
#include "ast.h"


extern void yyerror ( const char * s, ... );
namespace AST {class Node; class Variable; class Classe; class Objeto; class ConstrutorClasse; class Block; class Atributo; class Funcao;}
namespace ST {

	class Symbol;
	class SymbolTable;
	enum Kind { variable, arranjo,  funcao , classe, objeto, atributo };

	typedef std::map<std::string, Symbol> SymbolList; //Set of Symbols

	class Symbol {
	public:
		Tipos::Tipo type = Tipos::indefinido;              /*[Return] type of Symbol: integer, double.*/
		Kind kind;              /*Kind of symbol: variable, function, etc.*/
		int64_t value;        /*Space to store a value while we are doing interpretation.*/
		bool initialized;       /*Defines if symbol has been initialized or not.*/
		std::vector<AST::Variable *> parametros; /*Stores the parameters of function*/
		SymbolTable* tabelaClasse;
		AST::ConstrutorClasse* construtor;
		AST::Classe* classePertencente;
		AST::Variable* var;

		/*Construtor de simbolos para variaveis*/
		Symbol ( Tipos::Tipo type, Kind kind, int64_t value, bool initialized ) :
			type ( type ), kind ( kind ), value ( value ), initialized ( initialized ) {  }
			
		Symbol() {type = Tipos::indefinido; kind = variable; value = 0; initialized = false;}

		/*Construtor de simbolos para funcoes*/
		Symbol ( Tipos::Tipo type, Kind kind, std::vector<AST::Variable *> parametros, bool initialized ) :
			type ( type ), kind ( kind ), parametros ( parametros ), initialized ( initialized ) { }

		/*Construtor de simbolos para classes*/
		Symbol(SymbolTable* tabelaClasse, AST::ConstrutorClasse* construtor) : tabelaClasse(tabelaClasse), construtor(construtor) {kind = classe; initialized = true;}

		/*Construtor de simbolos para objetos*/
		Symbol(AST::Classe* classePertencente) : classePertencente(classePertencente) {kind = objeto; initialized = true;}

		/*Construtor de simbolos para atributos de classes*/
		Symbol(AST::Variable* var, AST::Classe* classePertencente) : var(var), classePertencente(classePertencente) {kind = atributo; initialized = false;}
	};

	class SymbolTable {
	public:
		SymbolList entryList;
		SymbolTable() {}

		/*Verifica se o identificador esta na tabela*/
		bool checkId ( std::string id ) {return entryList.find ( id ) != entryList.end();}

		/*Retorna o simbolo associado ao id*/
		ST::Symbol getSymbol ( std::string id );

		/*Adiciona o simbolo na tabela*/
		void addSymbol ( std::string id, Symbol newsymbol ) {entryList[id] = newsymbol;}

		/*Cria uma nova variavel*/
		AST::Node * newVariable ( std::string id, Tipos::Tipo tipo,  AST::Node * next );

		/*Atribui variavel*/
		AST::Node * assignVariable ( std::string id );

		/*Atribui variavel a um atributo de classe*/
		AST::Variable * assignVariableClasse ( AST::Objeto* objeto, std::string idAtributo );

		/*Usa uma variavel*/
		AST::Node * useVariable ( std::string id );

		/*Obtém o tipo de um identificador*/
		Tipos::Tipo returnType ( std::string id );

		/*Coerge para real*/
		void realizaCoercao ( std::string id );

		/*Atribui o escopo superior*/
		void defineTabelaOrigem ( ST::SymbolTable * to ) {tabelaOrigem = to;};

		/*O escopo superior*/
		ST::SymbolTable * tabelaOrigem = NULL;

		/*Obtém a funcao relacinada ao identificador*/
		ST::Symbol getFunction ( std::string id ) {return entryList[id];};

		/*Cria uma nova função*/
		AST::Node * newFunction ( std::string id, Tipos::Tipo tipoVariavel, std::vector<AST::Variable *> parametros );

		/*Atribui uma função*/
		AST::Node * assignFunction ( std::string id, Tipos::Tipo tipoVariavel, std::vector<AST::Variable *> next, AST::Node * body );

		/*Utilizacao de funcao*/
		AST::Funcao* useFunction (std::string id );

		/*Criacao de nova classe*/
		AST::Classe* newClass (std::string id, ST::SymbolTable* tabelaSimbolosClasse, AST::Block* escopoClasse, AST::ConstrutorClasse* construtor);

		/*Utiliza classe*/
		AST::Classe* useClass(std::string id);

		/*Criacao de novo objeto*/
		AST::Objeto* newObjeto (std::string id, AST::Classe* classePertencente);

		/*Utiliza classe*/
		AST::Objeto* useObjeto(std::string id);

		/*Cria novo atributo de classe*/
		AST::Atributo* newAtributo(AST::Variable* var, AST::Classe* classePertencente);

		/*Usa atributo de classe*/
		AST::Atributo* useAtributo(std::string id);

		/*Atribui variavel a um atributo de classe*/
		AST::Atributo * assignAtributo ( AST::Variable* var, AST::Classe* classePertencente );

		void printTable();
	};

}
