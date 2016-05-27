/*Symbol Table definition - Ja previamente definido por Laércio Lima Pilla*/
#pragma once

#include <map>
#include "ast.h"

extern void yyerror(const char* s, ...);
namespace AST {class Node;}
namespace ST {

class Symbol;
enum Kind { variable, arranjo,  function };


typedef std::map<std::string,Symbol> SymbolList; //Set of Symbols

class Symbol {
    public:
        Tipos::Tipo type = Tipos::indefinido;              /*[Return] type of Symbol: integer, double.*/
        Kind kind;              /*Kind of symbol: variable, function, etc.*/
        int64_t value;        /*Space to store a value while we are doing interpretation.*/
        bool initialized;       /*Defines if symbol has been initialized or not.*/
        Symbol(Tipos::Tipo type, Kind kind, int64_t value, bool initialized) :
            type(type), kind(kind), value(value), initialized(initialized) {  }
        Symbol() {type = Tipos::indefinido; kind = variable; value = 0; initialized = false;}
};

class SymbolTable {
    public:
        SymbolList entryList;
        SymbolTable() {}
       // ST::SymbolTable tabelaOrigem;
        /*checkId returns true if the variable has been defined and false if it does not exist*/
        bool checkId(std::string id) {return entryList.find(id) != entryList.end();}
        void addSymbol(std::string id, Symbol newsymbol) {entryList[id] = newsymbol;}
        AST::Node* newVariable(std::string id, Tipos::Tipo tipo,  AST::Node* next);
        AST::Node* assignVariable(std::string id);
        AST::Node* useVariable(std::string id);
        Tipos::Tipo returnType(std::string id);
        void realizaCoercao(std::string id);
};

}
