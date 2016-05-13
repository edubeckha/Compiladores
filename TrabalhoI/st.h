/*Symbol Table definition*/
#pragma once

#include <map>
#include "ast.h"

extern void yyerror(const char* s, ...);

namespace ST {

class Symbol;
enum Kind { variable, arranjo,  function };


typedef std::map<std::string,Symbol> SymbolList; //Set of Symbols

class Symbol {
    public:
        AST::Tipo type = AST::indefinido;              /*[Return] type of Symbol: integer, double.*/
        Kind kind;              /*Kind of symbol: variable, function, etc.*/
        int64_t value;        /*Space to store a value while we are doing interpretation.*/
        bool initialized;       /*Defines if symbol has been initialized or not.*/
        Symbol(AST::Tipo type, Kind kind, int64_t value, bool initialized) :
            type(type), kind(kind), value(value), initialized(initialized) {  }
        Symbol() {type = AST::indefinido; kind = variable; value = 0; initialized = false;}
};

class SymbolTable {
    public:
        SymbolList entryList;
        SymbolTable() {}

        /*checkId returns true if the variable has been defined and false if it does not exist*/
        bool checkId(std::string id) {return entryList.find(id) != entryList.end();}
        void addSymbol(std::string id, Symbol newsymbol) {entryList[id] = newsymbol;}
        AST::Node* newVariable(std::string id, AST::Tipo tipo,  AST::Node* next);
        AST::Node* assignVariable(std::string id);
        AST::Node* useVariable(std::string id);
        AST::Tipo returnType(std::string id);
};

}
